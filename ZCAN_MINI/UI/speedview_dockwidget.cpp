#include "speedview_dockwidget.h"
#include "ui_speedview_dockwidget.h"

SpeedViewDockWidget::SpeedViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SpeedViewDockWidget),
    distribution_dialog_(new DistributionDialog(this)),
    signal_parser_(nullptr),
    line_plot_(nullptr),
    line_replot_(nullptr)
{
    ui->setupUi(this);

    ui->plot->setOpenGl(true);
    qDebug() << "plot OpenGl开启状态: " << ui->plot->openGl();

    initPlot(ui->plot);
    initPlot(ui->plot_2);

    ui->plot_2->legend->setVisible(false);
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_2->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis, SLOT(setRange(QCPRange)));
}

SpeedViewDockWidget::~SpeedViewDockWidget()
{
    if (signal_parser_)
        destroyThread();

    delete ui;
}

void SpeedViewDockWidget::initPlot(QCustomPlot* const plot)
{
    // plot->setNoAntialiasingOnDrag(true);

    // 使用框选
    plot->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    plot->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    plot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);

    // 时间轴做x轴，X轴的数据以1970-01-01 00:00:00至当前时间的总秒数
    QSharedPointer<QCPAxisTickerDateTime> date_tick(new QCPAxisTickerDateTime);
    date_tick->setDateTimeSpec(Qt::LocalTime);
    // date_tick->setDateTimeSpec(Qt::UTC);

    date_tick->setDateTimeFormat("hh:mm:ss.zzz");
    plot->xAxis->setTicker(date_tick);
    plot->xAxis->ticker()->setTickOrigin(0);//设置刻度原点
    plot->xAxis->ticker()->setTickCount(20);
    plot->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置
    plot->xAxis->setTickLabelRotation(35);

    // 边框右侧和上侧均显示刻度线，但不显示刻度值
    plot->xAxis->setVisible(true);
    plot->xAxis2->setVisible(true);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->yAxis2->setTickLabels(false);
    plot->yAxis->setRangeUpper(10000);
    plot->yAxis->setRangeLower(-10000);

    // plot->axisRect()->setRangeZoomFactor(1, 2.2);
    plot->axisRect()->setBackground(QBrush(QColor(255, 255, 255, 255))); // 设置背景颜色

    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    qRegisterMetaType<QCPRange>("QCPRange");
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    // 设置图例
    plot->legend->setVisible(true); // 设置图例可见
    plot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);  // 设置为让图例居右上
    plot->legend->setBrush(QColor(255, 255, 255, 150));   // 设置图例为灰色透明
    plot->legend->setSelectableParts(QCPLegend::spItems);    //设置legend只能选择图例
    connect(plot, &QCustomPlot::selectionChangedByUser, this, &SpeedViewDockWidget::slot_selectionChanged);

    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                          QCP::iSelectLegend | QCP::iSelectPlottables);
}

void SpeedViewDockWidget::addGraphs(QCustomPlot* const plot, QList<Vector::DBC::Signal>& sig_lst)
{
    if (0 == plot->graphCount())
    {
        plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        QColor color("#A52A2A");    // 浅褐色
        QPen pen(color.lighter());
        pen.setWidthF(1.5);
        plot->graph()->setLineStyle(QCPGraph::lsLine);
        // plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 3));
        plot->graph()->setPen(pen);
        plot->graph()->setName(QString::fromStdString(sig_lst.at(0).name));//曲线名称

        plot->graph()->rescaleAxes();

        plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        QColor color1("#87CEEB");   // 天蓝色
        QPen pen1(color1.darker(120));
        pen1.setWidthF(1.5);
        plot->graph()->setLineStyle(QCPGraph::lsLine);
        // plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 3));
        plot->graph()->setPen(pen1);
        plot->graph()->setName(QString::fromStdString(sig_lst.at(1).name));//曲线名称

        plot->graph()->rescaleAxes(true);

        plot->replot();
    }
}

void SpeedViewDockWidget::initThread(const uint32_t msg_id, QList<Vector::DBC::Signal>& sig_lst)
{
    signal_parser_ = new SignalParser(msg_id, sig_lst);
    signal_parser_thread_ = new QThread;
    signal_parser_->moveToThread(signal_parser_thread_);
    signal_parser_thread_->start();
    RecMsgThread* const rec_msg_thread = RecMsgThread::getInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data*, const uint)>(&RecMsgThread::sig_newMsg),
            signal_parser_, static_cast<void (SignalParser::*)(const ZCAN_Receive_Data*, const uint)>(&SignalParser::slot_newMsg));
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&RecMsgThread::sig_newMsg),
            signal_parser_, static_cast<void (SignalParser::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&SignalParser::slot_newMsg));

    line_plot_ = new LinePlot(ui->plot);
    line_plot_thread_ = new QThread;
    line_plot_->moveToThread(line_plot_thread_);
    line_plot_thread_->start();
    qRegisterMetaType<QList<double>>("QList<double>");
    connect(signal_parser_, static_cast<void (SignalParser::*)(const QList<double>)>(&SignalParser::sig_speed),
            line_plot_, static_cast<void (LinePlot::*)(const QList<double>)>(&LinePlot::slot_realTimeData));

    line_replot_ = new LineReplot(ui->plot);
    line_replot_thread_ = new QThread;
    line_replot_->moveToThread(line_replot_thread_);
    connect(line_replot_, static_cast<void (LineReplot::*)(void)>(&LineReplot::sig_replot),
            this, [=] { ui->plot->replot(QCustomPlot::rpQueuedReplot); });
    line_replot_thread_->start();

    deviation_plot_ = new DeviationPlot(ui->plot_2);
    deviation_plot_thread_ = new QThread;
    deviation_plot_->moveToThread(deviation_plot_thread_);
    deviation_plot_thread_->start();

    connect(line_plot_, static_cast<void (LinePlot::*)(double, double)>(&LinePlot::sig_absDeviation),
            deviation_plot_, static_cast<void (DeviationPlot::*)(double, double)>(&DeviationPlot::slot_absDeviation));

    deviation_replot_ = new DeviationReplot(ui->plot_2);
    deviation_replot_thread_ = new QThread;
    deviation_replot_->moveToThread(deviation_replot_thread_);
    connect(deviation_replot_, static_cast<void (DeviationReplot::*)(void)>(&DeviationReplot::sig_replot),
            this, [=] { ui->plot_2->replot(QCustomPlot::rpQueuedReplot); });
    deviation_replot_thread_->start();

    connect(line_replot_, &LineReplot::sig_frmChanged, this, [=] (const QString& msg) {
        ui->labFps->setText(msg);
    });
}

void SpeedViewDockWidget::destroyThread()
{
    RecMsgThread* const rec_msg_thread = RecMsgThread::getInstance();
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data*, const uint)>(&RecMsgThread::sig_newMsg),
               signal_parser_, static_cast<void (SignalParser::*)(const ZCAN_Receive_Data*, const uint)>(&SignalParser::slot_newMsg));
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&RecMsgThread::sig_newMsg),
               signal_parser_, static_cast<void (SignalParser::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&SignalParser::slot_newMsg));

    disconnect(signal_parser_, static_cast<void (SignalParser::*)(const QList<double>)>(&SignalParser::sig_speed),
               line_plot_, static_cast<void (LinePlot::*)(const QList<double>)>(&LinePlot::slot_realTimeData));

    disconnect(line_plot_, static_cast<void (LinePlot::*)(double, double)>(&LinePlot::sig_absDeviation),
               deviation_plot_, static_cast<void (DeviationPlot::*)(double, double)>(&DeviationPlot::slot_absDeviation));

    disconnect(line_replot_, &LineReplot::sig_frmChanged, nullptr, nullptr);

    signal_parser_thread_->quit();
    signal_parser_thread_->wait();
    signal_parser_thread_->deleteLater();
    if (signal_parser_thread_)
        signal_parser_thread_ = nullptr;
    signal_parser_->deleteLater();
    if (signal_parser_)
        signal_parser_ = nullptr;

    line_plot_thread_->quit();
    line_plot_thread_->wait();
    line_plot_thread_->deleteLater();
    if (line_plot_thread_)
        line_plot_thread_ = nullptr;
    line_plot_->deleteLater();
    if (line_plot_)
        line_plot_ = nullptr;

    line_replot_thread_->quit();
    line_replot_thread_->wait();
    line_replot_thread_->deleteLater();
    if (line_replot_thread_)
        line_replot_thread_ = nullptr;
    line_replot_->deleteLater();
    if (line_replot_)
        line_replot_ = nullptr;

    deviation_plot_thread_->quit();
    deviation_plot_thread_->wait();
    deviation_plot_thread_->deleteLater();
    if (deviation_plot_thread_)
        deviation_plot_thread_ = nullptr;
    deviation_plot_->deleteLater();
    if (deviation_plot_)
        deviation_plot_ = nullptr;

    deviation_replot_thread_->quit();
    deviation_replot_thread_->wait();
    deviation_replot_thread_->deleteLater();
    if (deviation_replot_thread_)
        deviation_replot_thread_ = nullptr;
    deviation_replot_->deleteLater();
    if (deviation_replot_)
        deviation_replot_ = nullptr;
}

void SpeedViewDockWidget::slot_selectionChanged()
{
    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        ui->plot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->plot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->plot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        ui->plot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->plot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->plot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // 将图形的选择与相应图例项的选择同步
    ui->plot->set_tracer_graph(nullptr);
    for (int i=0; i<ui->plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->plot->graph(i);
        QCPPlottableLegendItem *item = ui->plot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            ui->plot->set_tracer_graph(graph);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));

            // 设置选中的图形的颜色
            // graph->setPen(QPen(Qt::red, graph->pen().width())); // 保持原始宽度，改变颜色
        }
        else
        {
            item->setSelected(false);

            // 可以在这里设置非选中状态下的默认颜色，如果需要
            // if (0 == i)
            //     graph->setPen(QPen(Qt::green, graph->pen().width())); // 恢复默认颜色
            // else if (1 == i)
            //     graph->setPen(QPen(Qt::blue, graph->pen().width())); // 恢复默认颜色
        }
    }
}

void SpeedViewDockWidget::slot_paint(bool enabled, const uint32_t msg_id, QList<Vector::DBC::Signal>& sig_lst)
{
    if (enabled)
    {
        addGraphs(ui->plot, sig_lst);
        addGraphs(ui->plot_2, sig_lst);

        ui->plot_2->graph(0)->setChannelFillGraph(ui->plot_2->graph(1));
        ui->plot_2->graph(0)->setBrush(QColor(0, 0, 255, 20));

        initThread(msg_id, sig_lst);
    }
    else
    {
        destroyThread();
    }
}

void SpeedViewDockWidget::slot_actDisPic_triggered()
{
    // 创建一个直方图（bar chart）
    QCustomPlot* distribuition_plot = distribution_dialog_->myplot_;
    distribuition_plot->clearPlottables();
    distribuition_plot->replot();
    QCPBars* errorBars = new QCPBars(distribuition_plot->xAxis, distribuition_plot->yAxis);

    // 计算误差数据
    QVector<double> errorData;
    QVector<QCPGraphData>* const ref_speed_lst = ui->plot->graph(0)->data()->coreData();
    QVector<QCPGraphData>* const rel_speed_lst = ui->plot->graph(1)->data()->coreData();
    for (int i = 0; i < ref_speed_lst->size(); ++i)
    {
        double actualSpeed = (*ref_speed_lst)[i].value;
        double estimatedSpeed = (*rel_speed_lst)[i].value;
        double error = actualSpeed - estimatedSpeed;
        errorData.append(error);
    }

    // 准备数据
    QVector<double> errorTicks;
    QVector<double> errorFrequency;
    int numberOfBins = 10; // 可以根据需要调整直方图的分组数量

    double minError = *std::min_element(errorData.constBegin(), errorData.constEnd());
    double maxError = *std::max_element(errorData.constBegin(), errorData.constEnd());
    double binWidth = (maxError - minError) / numberOfBins;

    errorTicks.resize(numberOfBins);
    errorFrequency.resize(numberOfBins);

    for (int i = 0; i < numberOfBins; ++i)
    {
        errorTicks[i] = minError + (i + 0.5) * binWidth; // 计算每个分组的中心值
        errorFrequency[i] = 0;
    }

    for (double error : errorData)
    {
        int binIndex = std::floor((error - minError) / binWidth);
        if (binIndex >= 0 && binIndex < numberOfBins)
        {
            errorFrequency[binIndex]++;
        }
    }

    errorBars->setData(errorTicks, errorFrequency);
    distribuition_plot->rescaleAxes();
    distribuition_plot->replot();

    distribution_dialog_->show();
}

bool SpeedViewDockWidget::slot_actSavePic_triggered()
{
    QString filename = QFileDialog::getSaveFileName();
    QCustomPlot* const plot = ui->plot;

    if( filename == "" ){
        QMessageBox::information(this,"fail","保存失败");
         return false;
     }
     if( filename.endsWith(".png") ){
         QMessageBox::information(this,"success","成功保存为png文件");
         return plot->savePng(filename, plot->width(), plot->height());

     }
     if( filename.endsWith(".jpg")||filename.endsWith(".jpeg") ){
         QMessageBox::information(this,"success","成功保存为jpg文件");
         return plot->saveJpg(filename, plot->width(), plot->height());

     }
     if( filename.endsWith(".bmp") ){
         QMessageBox::information(this,"success","成功保存为bmp文件");
         return plot->saveBmp(filename, plot->width(), plot->height());

     }
     if( filename.endsWith(".pdf") ){
         QMessageBox::information(this,"success","成功保存为pdf文件");
         return plot->savePdf(filename, plot->width(), plot->height());

     }
    else{
         //否则追加后缀名为.png保存文件
         QMessageBox::information(this,"success","保存成功,已默认保存为png文件");
         return plot->savePng(filename.append(".png"), plot->width(), plot->height());
     }
}

void SpeedViewDockWidget::slot_actSaveExcel_triggered()
{
    if (QXlsx::Document("test.xlsx").load())
        return;

    QCustomPlot* const plot = ui->plot;

    QVector<QCPGraphData>* const ref_speed_lst = plot->graph(0)->data()->coreData();
    QVector<QCPGraphData>* const rel_speed_lst = plot->graph(1)->data()->coreData();

    QXlsx::Document doc;

    int row = 1;
    doc.addSheet(QStringLiteral("数据汇总"));
    doc.addSheet(QStringLiteral("误差分析"));
    doc.selectSheet(0);

    for (int i = 0; i < ref_speed_lst->length(); ++i)
    {
        doc.write(i+1, 1, ref_speed_lst->at(i).key);
        doc.write(i+1, 2, ref_speed_lst->at(i).value);
        doc.write(i+1, 3, rel_speed_lst->at(i).value);

        const double difference = doc.cellAt(i+1, 2)->value().toDouble() - doc.cellAt(i+1, 3)->value().toDouble();
        if (qAbs(difference) > 8)
        {
            QXlsx::Format format;
            format.setFontColor(QColor(Qt::black));
            format.setPatternBackgroundColor(Qt::red);
            doc.setRowFormat(i+1, format);

            doc.selectSheet(1);
            doc.write(row, 1, ref_speed_lst->at(i).key);
            doc.write(row, 2, ref_speed_lst->at(i).value);
            doc.write(row, 3, rel_speed_lst->at(i).value);
            ++row;

            doc.selectSheet(0);
        }
    }

    doc.saveAs("test.xlsx");
}

