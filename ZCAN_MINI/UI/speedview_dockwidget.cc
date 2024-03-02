#include "speedview_dockwidget.h"
#include "ui_speedview_dockwidget.h"

SpeedViewDockWidget::SpeedViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SpeedViewDockWidget)
{
    ui->setupUi(this);

    QCustomPlot* const plot = ui->plot;
    plot->setOpenGl(true);
    qDebug() << "OpenGl开启状态: " << plot->openGl();
    plot->setNoAntialiasingOnDrag(true);

    //设置坐标轴显示范围,否则我们只能看到默认的范围
    // QSharedPointer<QCPAxisTickerDateTime> date_tick(new QCPAxisTickerDateTime);
    // date_tick->setDateTimeFormat("mm:ss.zzz");
    // plot->xAxis->setTicker(date_tick);
    // plot->xAxis->setTickLabelRotation(35);

    plot->yAxis->setVisible(true);
    plot->yAxis2->setVisible(true);

    plot->axisRect()->setupFullAxesBox();   // 四周安上轴并显示
    plot->axisRect()->setBackground(QBrush(QColor(255, 255, 255, 255))); // 设置背景颜色

    qRegisterMetaType<QCPRange>("QCPRange");
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    // 设置图例
    plot->legend->setBrush(QColor(255, 255, 255, 255));   // 设置图例为不透明
    plot->legend->setVisible(true); // 设置图例可见

    //设置属性可缩放，移动等
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                     QCP::iSelectLegend | QCP::iSelectPlottables);

    plot->legend->setSelectableParts(QCPLegend::spItems);    //设置legend只能选择图例

    plot->replot();

    connect(ui->btnSave, SIGNAL(clicked(bool)), this, SLOT(slot_btnSave_clicked(bool)));
    connect(ui->btnExcel, SIGNAL(clicked(bool)), this, SLOT(slot_btnExcel_clicked(bool)));
}

SpeedViewDockWidget::~SpeedViewDockWidget()
{
    delete ui;
}

void SpeedViewDockWidget::slot_paint(const unsigned long long msg_id, QList<CppCAN::CANSignal*>& sig_lst)
{
    QCustomPlot* const plot = ui->plot;

    plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
    //plot->graph()->setSmooth(true); // 启用曲线平滑
    QColor color(20+200/4.0*1,70*(1.6-1/4.0), 150, 250);
    QPen pen(color.lighter(200));
    pen.setWidth(2);
    plot->graph()->setLineStyle(QCPGraph::lsLine);
    plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 3));
    plot->graph()->setPen(pen);
    plot->graph()->setName(QString::fromStdString(sig_lst.at(0)->name()));//曲线名称

    plot->graph()->rescaleAxes();

    plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
    //plot->graph()->setSmooth(true); // 启用曲线平滑
    QColor color1(20+200/4.0*2,70*(1.6-2/4.0), 150, 250);
    QPen pen1(color1.lighter(200));
    pen1.setWidth(2);
    plot->graph()->setLineStyle(QCPGraph::lsLine);
    plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 3));
    plot->graph()->setPen(pen1);
    plot->graph()->setName(QString::fromStdString(sig_lst.at(1)->name()));//曲线名称

    plot->graph()->rescaleAxes(true);
    plot->replot();

    const QList<CppCAN::CANSignal> sig_lst1 { *sig_lst.at(0), *sig_lst.at(1) };
    SignalParserThread* const signal_parser_thread = new SignalParserThread(msg_id, sig_lst1);
    signal_parser_thread->start();
    signal_parser_thread->beginThread();

    PlotDataThread* const plotdata_thread = new PlotDataThread(plot, signal_parser_thread);
    plotdata_thread->start();
    plotdata_thread->beginThread();

    ReplotThread* const replot_thread = new ReplotThread(plot);
    replot_thread->start();
    replot_thread->beginThread();

    connect(replot_thread, &ReplotThread::sig_frmChanged, this, [=] (const QString& msg) {
        ui->labFps->setText(msg);
    });
}

bool SpeedViewDockWidget::slot_btnSave_clicked(bool checked)
{
    Q_UNUSED(checked);

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

void SpeedViewDockWidget::slot_btnExcel_clicked(bool checked)
{
    Q_UNUSED(checked);

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

