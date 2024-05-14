#include "speedview_dockwidget.h"
#include "ui_speedview_dockwidget.h"

SpeedViewDockWidget::SpeedViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SpeedViewDockWidget),
    distribution_dialog_(new DistributionDialog(this)),
    signal_parser_(nullptr),
    line_plot_(nullptr),
    line_replot_(nullptr),
    deviation_plot_(nullptr),
    deviation_replot_(nullptr),
    default_deviation_value_(100),
    default_sampling_point_nums_(1),
    tester_("null"),
    device_name_("null")
{
    ui->setupUi(this);

    init_ui();

    bind_signals();

    ui->plot->setNoAntialiasingOnDrag(true);
    ui->plot_2->setNoAntialiasingOnDrag(true);

    init_plot(ui->plot);
    init_plot(ui->plot_2);

    ui->plot_2->legend->setVisible(false);

    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_2->xAxis, SLOT(setRange(QCPRange)));
    connect(ui->plot_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis, SLOT(setRange(QCPRange)));
}

SpeedViewDockWidget::~SpeedViewDockWidget()
{
    if (signal_parser_)
        destroy_thread();

    delete ui;
}

void SpeedViewDockWidget::init_ui()
{
    int max_height = 35;

    // QWidget* titleBarWidget = new QWidget();
    // setTitleBarWidget(titleBarWidget);

    QColor color("#607D8B");
    ui->btnPaint->setBackgroundColor(color);
    ui->btnPaint->setFixedHeight(max_height);
    ui->btnClear->setBackgroundColor(color);
    ui->btnClear->setFixedHeight(max_height);
    ui->btnRescale->setBackgroundColor(color);
    ui->btnRescale->setFixedHeight(max_height);
    ui->btnDis->setBackgroundColor(color);
    ui->btnDis->setFixedHeight(max_height);
    ui->btnDeviation->setBackgroundColor(color);
    ui->btnDeviation->setFixedHeight(max_height);
    ui->btnSavePic->setBackgroundColor(color);
    ui->btnSavePic->setFixedHeight(max_height);
    ui->btnSaveExcel->setBackgroundColor(color);
    ui->btnSaveExcel->setFixedHeight(max_height);
    ui->btnWidth->setBackgroundColor(color);
    ui->btnWidth->setFixedHeight(max_height);
    ui->btnOpenGL->setBackgroundColor(color);
    ui->btnOpenGL->setFixedHeight(max_height);
    ui->btnAntialiase->setBackgroundColor(color);
    ui->btnAntialiase->setFixedHeight(max_height);
    ui->btnDisEnable->setBackgroundColor(color);
    ui->btnDisEnable->setFixedHeight(max_height);
    ui->btnSampling->setBackgroundColor(color);
    ui->btnSampling->setFixedHeight(max_height);

    ui->spinDeviation->setMaximumHeight(max_height);
    ui->spinWidth->setMaximumHeight(max_height);

    ui->btnPaint->setCheckable(true);
    ui->btnPaint->setChecked(false);
    ui->btnPaint->setEnabled(false);
}

void SpeedViewDockWidget::bind_signals()
{
    connect(ui->btnPaint, &QtMaterialRaisedButton::clicked, this, [this] {
        static bool paint_enable = true;
        if (paint_enable)
        {
            ui->btnPaint->setChecked(true);
            ui->btnPaint->setText(QStringLiteral("停止绘图"));
        }
        else
        {
            ui->btnPaint->setChecked(false);
            if (sig_lst_.size() != 2)
                ui->btnPaint->setEnabled(false);
            ui->btnPaint->setText(QStringLiteral("开始绘图"));
        }
        slot_btnPaint_clicked(paint_enable);
        paint_enable = !paint_enable;
    });

    connect(ui->btnDis, &QtMaterialRaisedButton::clicked, this, &SpeedViewDockWidget::slot_btnShowDis);

    connect(ui->btnClear, &QtMaterialRaisedButton::clicked, this, &SpeedViewDockWidget::slot_clearData);

    connect(ui->btnRescale, &QtMaterialRaisedButton::clicked, this, [=] {
        if (ui->plot->graphCount() == 0)
            QMessageBox::information(this,"fail","当前无图像可进行重缩放");
        ui->plot->rescaleAxes();
        ui->plot->rescaleAxes(true);
    });

    connect(ui->chkGraph1, &QCheckBox::toggled, this, [=] (bool checked) {
        if (ui->plot->graphCount() == 0)
            return;
        ui->plot->graph(0)->setVisible(checked);
        ui->plot->replot(QCustomPlot::rpQueuedReplot);
    });

    connect(ui->chkGraph2, &QCheckBox::toggled, this, [=] (bool checked) {
        if (ui->plot->graphCount() == 0)
            return;
        ui->plot->graph(1)->setVisible(checked);
        ui->plot->replot(QCustomPlot::rpQueuedReplot);
    });

    connect(ui->chkScatter1, &QCheckBox::toggled, this, [=] (bool checked) {
        if (ui->plot->graphCount() == 0)
            return;
        if (checked)
        {
            ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
            ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 2));
            ui->plot->replot(QCustomPlot::rpQueuedReplot);
        }
        else
        {
            ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
            ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 1));
            ui->plot->replot(QCustomPlot::rpQueuedReplot);
        }
    });

    connect(ui->chkScatter2, &QCheckBox::toggled, this, [=] (bool checked) {
        if (ui->plot->graphCount() == 0)
            return;
        if (checked)
        {
            ui->plot->graph(1)->setLineStyle(QCPGraph::lsNone);
            ui->plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 2));
            ui->plot->replot(QCustomPlot::rpQueuedReplot);
        }
        else
        {
            ui->plot->graph(1)->setLineStyle(QCPGraph::lsLine);
            ui->plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 1));
            ui->plot->replot(QCustomPlot::rpQueuedReplot);
        }
    });

    connect(ui->btnDeviation, &QtMaterialRaisedButton::clicked, this, [this] {
        double value = ui->spinDeviation->value();
        slot_disSigVal_changed(value);
    });

    connect(ui->btnSampling, &QtMaterialRaisedButton::clicked, this, [=] {
        default_sampling_point_nums_ = ui->spinSampling->value();
        QMessageBox::information(this,"success","设置采样点成功");
    });

    connect(ui->btnSavePic, &QtMaterialRaisedButton::clicked, this, &SpeedViewDockWidget::slot_btnSavePic_clicked);

    connect(ui->btnSaveExcel, &QtMaterialRaisedButton::clicked, this, &SpeedViewDockWidget::slot_btnSaveExcel_clicked);

    connect(ui->btnOpenGL, &QtMaterialRaisedButton::clicked, this, [=] {
        static bool state = true;
        if (state)
            ui->btnOpenGL->setText(QStringLiteral("关闭显卡加速"));
        else
            ui->btnOpenGL->setText(QStringLiteral("开启显卡加速"));

        ui->plot->setOpenGl(state);
        state = !state;
    });

    connect(ui->btnAntialiase, &QtMaterialRaisedButton::clicked, this, [=] {
        if (ui->plot->graphCount() == 0)
        {
            QMessageBox::information(this,"fail","当前无图像可进行抗锯齿处理");
            return;
        }

        static bool is_antialiase = true;
        if (is_antialiase)
            ui->btnAntialiase->setText(QStringLiteral("关闭抗锯齿"));
        else
            ui->btnAntialiase->setText(QStringLiteral("开启抗锯齿"));

        ui->plot->graph(0)->setAntialiased(is_antialiase);
        ui->plot->graph(1)->setAntialiased(is_antialiase);
        is_antialiase = !is_antialiase;
    });

    connect(ui->btnDisEnable, &QtMaterialRaisedButton::clicked, this, [=] {
        static bool is_showing = true;
        if (is_showing)
        {
            ui->btnDisEnable->setText(QStringLiteral("显示误差图"));
            if (deviation_replot_)
                deviation_replot_->pause();
        }
        else
        {
            ui->btnDisEnable->setText(QStringLiteral("隐藏误差图"));
            if (deviation_replot_)
                deviation_replot_->start();
        }

        ui->plot_2->setVisible(!is_showing);
        ui->plot_2->replot(QCustomPlot::rpQueuedReplot);
        is_showing = !is_showing;
    });

    connect(ui->btnWidth, &QtMaterialRaisedButton::clicked, this, [=] {
        if (ui->plot->graphCount() == 0)
            return;

        double width = ui->spinWidth->value();

        QColor color("#A52A2A");    // 浅褐色
        QPen pen(color.lighter());
        pen.setWidthF(width);
        ui->plot->graph(0)->setPen(pen);

        QColor color1("#87CEEB");   // 天蓝色
        pen.setColor(color1.darker(120));
        ui->plot->graph(1)->setPen(pen);
        ui->plot->replot(QCustomPlot::rpQueuedReplot);
    });
}

void SpeedViewDockWidget::init_plot(QCustomPlot* const plot)
{
    // 使用框选
    plot->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    plot->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    plot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);

    // 时间轴做x轴，X轴的数据以1970-01-01 00:00:00至当前时间的总秒数
    QSharedPointer<QCPAxisTickerDateTime> date_tick(new QCPAxisTickerDateTime);
    date_tick->setDateTimeSpec(Qt::LocalTime);
    // date_tick->setDateTimeSpec(Qt::UTC);

    date_tick->setDateTimeFormat("mm:ss.zzz");
    plot->xAxis->setTicker(date_tick);

    QFont font;
    font.setPixelSize(12);
    font.setFamily("黑体");
    plot->xAxis->setTickLabelFont(font);
    plot->yAxis->setTickLabelFont(font);
    plot->xAxis->ticker()->setTickOrigin(0);//设置刻度原点
    plot->xAxis->ticker()->setTickCount(10);
    plot->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置

    plot->xAxis->setLabel("时间 mm:ss.zzz");
    plot->yAxis->setLabel("km/h");
    plot->xAxis->setLabelFont(font);
    plot->yAxis->setLabelFont(font);

    // 边框右侧和上侧均显示刻度线，但不显示刻度值
    plot->xAxis->setVisible(true);
    plot->xAxis2->setVisible(true);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->yAxis2->setTickLabels(false);
    plot->yAxis->setRangeUpper(1000);
    plot->yAxis->setRangeLower(-1000);

    // 设置坐标轴及其标签选中颜色
    plot->xAxis->setSelectedTickLabelFont(font);
    plot->xAxis->setSelectedTickLabelColor(QColor(0, 0, 255, 255));
    plot->yAxis->setSelectedTickLabelFont(font);
    plot->yAxis->setSelectedTickLabelColor(QColor(0, 0, 255, 255));

    plot->axisRect()->setBackground(QBrush(QColor(255, 255, 255, 255))); // 设置背景颜色

    plot->setNotAntialiasedElements(QCP::aeAll);
    // plot->setNoAntialiasingOnDrag(true);

    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    qRegisterMetaType<QCPRange>("QCPRange");
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    // 坐标轴刻度缩放
    connect(ui->plot->xAxis, static_cast<void (QCPAxis::*)(const QCPRange &)>(&QCPAxis::rangeChanged),
            [this, date_tick](const QCPRange &range) {
        double rangeSize = range.size(); // 获得当前x轴的范围大小

        if (rangeSize > 86400) { // 大于一天
            date_tick->setDateTimeFormat("yyyy-MM-dd");
            ui->plot->xAxis->setLabel("时间 yyyy-MM-dd");
        } else if (rangeSize > 3600) { // 大于一小时
            date_tick->setDateTimeFormat("MM-dd HH:mm");
            ui->plot->xAxis->setLabel("时间 MM-dd HH:mm");
        } else if (rangeSize > 60) { // 大于一分钟
            date_tick->setDateTimeFormat("HH:mm:ss");
            ui->plot->xAxis->setLabel("时间 HH:mm:ss");
        } else { // 一分钟以内
            date_tick->setDateTimeFormat("mm:ss.zzz");
            ui->plot->xAxis->setLabel("时间 mm:ss.zzz");
        }

        if (ui->plot->graphCount() == 0)
            return;
        ui->plot->replot(QCustomPlot::rpQueuedReplot); // 重新绘制以应用新的格式
    });


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

void SpeedViewDockWidget::add_graphs(QCustomPlot* const plot, int graph_count)
{
    if (0 == plot->graphCount())
    {
        plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 1));
        plot->graph()->setAntialiased(false);   // 设置曲线无抗锯齿
        plot->graph()->setAdaptiveSampling(true);   // 自适应采样
        qDebug() << "graph(0)自适应采样开启状态： " << plot->graph()->adaptiveSampling();

        plot->graph()->rescaleAxes();

        plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 1));
        plot->graph()->setName(QString::fromStdString(sig_lst_.at(1).second.name));//曲线名称
        plot->graph()->setAntialiased(false);   // 设置曲线抗锯齿
        plot->graph()->setAdaptiveSampling(true);   // 自适应采样
        qDebug() << "graph(1)自适应采样开启状态： " << plot->graph()->adaptiveSampling();

        plot->graph()->rescaleAxes(true);

        if (1 == graph_count)
        {
            QColor color("#87CEEB");    // 浅褐色
            QPen pen(color.lighter(120));
            pen.setWidthF(1);   // 宽度超过1性能急剧下降
            plot->graph(0)->setPen(pen);

            QColor color1("#A52A2A");   // 天蓝色
            QPen pen1(color1.darker(120));
            pen1.setWidthF(1);   // 宽度超过1性能急剧下降
            plot->graph(1)->setPen(pen1);

            plot->graph(0)->setLineStyle(QCPGraph::lsLine);
            plot->graph(1)->setLineStyle(QCPGraph::lsLine);
        }
        else if (2 == graph_count)
        {
            QColor color1("#87CEEB");   // 天蓝色
            QPen pen(color1.darker(120));
            pen.setWidthF(1);   // 宽度超过1性能急剧下降
            plot->graph(0)->setPen(pen);

            QColor color("#A52A2A");    // 浅褐色
            QPen pen1(color.lighter(120));
            pen1.setWidthF(1);   // 宽度超过1性能急剧下降
            plot->graph(1)->setPen(pen1);

            plot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
            plot->graph(1)->setLineStyle(QCPGraph::lsImpulse);
        }

        plot->replot(QCustomPlot::rpQueuedReplot);
    }
}

void SpeedViewDockWidget::init_thread()
{
    ui->plot->graph(0)->setName(QString::fromStdString(sig_lst_.at(0).second.name));//曲线名称
    ui->plot->graph(1)->setName(QString::fromStdString(sig_lst_.at(1).second.name));//曲线名称

    signal_parser_ = new SignalParser(sig_lst_);
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
    // 让其自动重绘，偏差图如果无需自动重绘，可以提高约一倍的性能
    connect(deviation_replot_, static_cast<void (DeviationReplot::*)(void)>(&DeviationReplot::sig_replot),
            this, [=] { ui->plot_2->replot(QCustomPlot::rpQueuedReplot); });
    deviation_replot_thread_->start();

    connect(line_replot_, &LineReplot::sig_frmChanged, this, [=] (const QString& msg) {

        ui->labFps->setText(msg);
    });
}

void SpeedViewDockWidget::destroy_thread()
{
    RecMsgThread* const rec_msg_thread = RecMsgThread::getInstance();
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data*, const uint)>(&RecMsgThread::sig_newMsg),
               signal_parser_, static_cast<void (SignalParser::*)(const ZCAN_Receive_Data*, const uint)>(&SignalParser::slot_newMsg));
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&RecMsgThread::sig_newMsg),
               signal_parser_, static_cast<void (SignalParser::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&SignalParser::slot_newMsg));

    disconnect(signal_parser_, static_cast<void (SignalParser::*)(const QList<double>)>(&SignalParser::sig_speed),
               line_plot_, static_cast<void (LinePlot::*)(const QList<double>)>(&LinePlot::slot_realTimeData));

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

double SpeedViewDockWidget::cal_max_error(std::vector<double>& tmp_vec1, std::vector<double>& tmp_vec2)
{
    // 使用 Map 将 std::vector 映射为 Eigen::VectorXd
    Eigen::Map<Eigen::VectorXd> vec1(tmp_vec1.data(), tmp_vec1.size());
    Eigen::Map<Eigen::VectorXd> vec2(tmp_vec2.data(), tmp_vec2.size());

    // 计算误差向量
    Eigen::VectorXd error = vec1 - vec2;

    // 计算最大绝对误差
    double mean = error.array().abs().maxCoeff();

    return mean;
}

double SpeedViewDockWidget::cal_mean_error(std::vector<double> &tmp_vec1, std::vector<double> &tmp_vec2)
{
    // 使用 Map 将 std::vector 映射为 Eigen::VectorXd
    Eigen::Map<Eigen::VectorXd> vec1(tmp_vec1.data(), tmp_vec1.size());
    Eigen::Map<Eigen::VectorXd> vec2(tmp_vec2.data(), tmp_vec2.size());

    // 计算误差向量
    Eigen::VectorXd error = vec1 - vec2;

    // 计算平均绝对误差 (MAE)
    double mean = error.array().abs().mean();

    return mean;
}

double SpeedViewDockWidget::cal_correlation_coefficient(std::vector<double> &tmp_vec1, std::vector<double> &tmp_vec2)
{
    // 使用 Map 将 std::vector 映射为 Eigen::VectorXd
    Eigen::Map<Eigen::VectorXd> vec1(tmp_vec1.data(), tmp_vec1.size());
    Eigen::Map<Eigen::VectorXd> vec2(tmp_vec2.data(), tmp_vec2.size());

    // 计算向量的均值
    double mean1 = vec1.mean();
    double mean2 = vec2.mean();

    // 计算向量减去均值
    Eigen::VectorXd vec1_centered = vec1.array() - mean1;
    Eigen::VectorXd vec2_centered = vec2.array() - mean2;

    // 计算协方差
    double covariance = (vec1_centered.array() * vec2_centered.array()).sum() / (vec1.size() - 1);

    // 计算标准差
    double stddev1 = std::sqrt((vec1_centered.array().square()).sum() / (vec1.size() - 1));
    double stddev2 = std::sqrt((vec2_centered.array().square()).sum() / (vec2.size() - 1));

    // 计算相关系数
    double correlation = covariance / (stddev1 * stddev2);

    return correlation;
}

double SpeedViewDockWidget::cal_RMSE(std::vector<double> &tmp_vec1, std::vector<double> &tmp_vec2)
{
    // 使用 Map 将 std::vector 映射为 Eigen::VectorXd
    Eigen::Map<Eigen::VectorXd> vec1(tmp_vec1.data(), tmp_vec1.size());
    Eigen::Map<Eigen::VectorXd> vec2(tmp_vec2.data(), tmp_vec2.size());

    // 计算误差向量
    Eigen::VectorXd error = vec1 - vec2;

    // 计算均方根误差 (RMSE)
    double rmse = std::sqrt((error.array().square()).mean());

    return rmse;
}

void SpeedViewDockWidget::slot_paint_enable(QList<QPair<uint32_t, Vector::DBC::Signal>> sig_lst)
{
    // qDebug() << "判断是否为深拷贝";
    sig_lst_ = sig_lst;

    if (ui->btnPaint->isChecked())  // 正在绘制图像时不改变check状态
        return;

    if (!ui->btnPaint->isEnabled() && sig_lst_.size() == 2)
        ui->btnPaint->setEnabled(true);
    else
        ui->btnPaint->setEnabled(false);
}

void SpeedViewDockWidget::slot_selectionChanged()
{
    ui->plot->xAxis2->setSelectableParts(QCPAxis::spNone);
    ui->plot_2->xAxis2->setSelectableParts(QCPAxis::spNone);
    ui->plot->yAxis2->setSelectableParts(QCPAxis::spNone);
    ui->plot_2->yAxis2->setSelectableParts(QCPAxis::spNone);

    if ((!ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || !ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels)) &&
         ui->plot_2->xAxis->selectedParts().testFlag(QCPAxis::spAxis) && ui->plot_2->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->plot->xAxis->setSelectedParts(QCPAxis::spNone);
        ui->plot_2->xAxis->setSelectedParts(QCPAxis::spNone);
    }
    else if (ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) && ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) &&
            (!ui->plot_2->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || !ui->plot_2->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels)))
    {
        ui->plot->xAxis->setSelectedParts(QCPAxis::spNone);
        ui->plot_2->xAxis->setSelectedParts(QCPAxis::spNone);
    }
    else if (ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        ui->plot_2->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot_2->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->plot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->plot_2->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    static bool last_axis_y1_stat = false;
    if (!last_axis_y1_stat &&
        (ui->plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels)))
    {
        ui->plot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        last_axis_y1_stat = true;
    }
    else
    {
        ui->plot->yAxis->setSelectedParts(QCPAxis::spNone);
        last_axis_y1_stat = false;
    }
    static bool last_axis_y2_stat = false;
    if (!last_axis_y2_stat &&
        (ui->plot_2->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->plot_2->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels)))
    {
        ui->plot_2->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        last_axis_y2_stat = true;
    }
    else
    {
        ui->plot_2->yAxis->setSelectedParts(QCPAxis::spNone);
        last_axis_y2_stat = false;
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
        }
        else
        {
            item->setSelected(false);
        }
    }
}

void SpeedViewDockWidget::slot_btnPaint_clicked(bool paint_enable)
{
    if (sig_lst_.size() != 2)
        return;

    static bool is_first_paint = true;

    if (paint_enable)
    {
        if (is_first_paint)
        {
            is_first_paint = false;
            add_graphs(ui->plot, 1);
            add_graphs(ui->plot_2, 2);

            ui->chkGraph1->setChecked(true);
            ui->chkGraph2->setChecked(true);

            ui->chkScatter1->setChecked(false);
            ui->chkScatter2->setChecked(false);
        }

        init_thread();
    }
    else
    {
        destroy_thread();
    }
}

/**
 * @brief SpeedViewDockWidget::slot_clearData 清除数据而已，不会清除图例等
 */
void SpeedViewDockWidget::slot_clearData()
{
    if (ui->plot->graphCount() == 0)
    {
        QMessageBox::information(this,"fail","当前无数据可清除");
        return;
    }

    for (int i = 0; i < ui->plot->graphCount(); ++i)
    {
        ui->plot->graph(i)->data()->clear();
    }

    static_cast<QCPBars*>(ui->plot_2->plottable(0))->data()->clear();
    static_cast<QCPBars*>(ui->plot_2->plottable(1))->data()->clear();

    ui->plot->replot(QCustomPlot::rpQueuedReplot);
    ui->plot_2->replot(QCustomPlot::rpQueuedReplot);
}

// 是否需要放在 deviation_plot_ 中修改？没必要，因为暂停绘图后使用它的函数仍然是在主线程中进行的
// 已经移出了 thread
void SpeedViewDockWidget::slot_disSigVal_changed(double value)
{
    default_deviation_value_ = value;

    if (deviation_plot_)
        deviation_plot_->set_default_deviation_value_(value);

    if (ui->plot_2->graphCount() == 0)
    {
        QMessageBox::information(this,"fail","当前无数据!");
        return;
    }

    QVector<QCPGraphData>* normal_data = ui->plot_2->graph(0)->data()->coreData();
    QVector<QCPGraphData>* exception_data = ui->plot_2->graph(1)->data()->coreData();
    deviation_replot_->pause();
    exception_data->clear();

    // 遍历正常偏差条形图的所有数据
    for (auto it = normal_data->begin(); it != normal_data->end(); ++it)
    {
        double key = it->key;
        double abs_deviation = it->value;

        if (qAbs(abs_deviation) >= default_deviation_value_)
        {
            exception_data->push_back(QCPGraphData( key, abs_deviation ));
        }
    }

    deviation_replot_->start();
    ui->plot_2->replot(QCustomPlot::rpQueuedReplot);
}

void SpeedViewDockWidget::slot_btnShowDis()
{
    // 计算误差数据
    if (ui->plot->graphCount() == 0)
    {
        QMessageBox::information(this,"fail","当前无数据可进行分析");
        return;
    }

    QVector<QCPGraphData>* map1 = ui->plot->graph(0)->data()->coreData();
    QVector<QCPGraphData>* map2 = ui->plot->graph(1)->data()->coreData();
    std::vector<double> tmp_vec1;
    std::vector<double> tmp_vec2;

    if (map1->size() == 0)
    {
        QMessageBox::information(this,"fail","当前无数据可进行分析");
        return;
    }

    for (int i = 0; i < map1->count(); ++i)
        tmp_vec1.push_back(qAbs(map1->at(i).value));
    for (int i = 0; i < map2->count(); ++i)
        tmp_vec2.push_back(qAbs(map2->at(i).value));

    double max_error = cal_max_error(tmp_vec1, tmp_vec2);
    double mean_error = cal_mean_error(tmp_vec1, tmp_vec2); // 平均绝对误差
    double correlation_coefficient = cal_correlation_coefficient(tmp_vec1, tmp_vec2);
    double RMSE = cal_RMSE(tmp_vec1, tmp_vec2);

    distribution_dialog_->set_max_error(max_error);
    distribution_dialog_->set_MAE(mean_error);
    distribution_dialog_->set_correlation_coefficient(correlation_coefficient);
    distribution_dialog_->set_RMSE(RMSE);

    // 计算误差
    std::vector<double> error_data;
    for (size_t i = 0; i < tmp_vec1.size(); ++i)
        error_data.push_back(qAbs(tmp_vec1.at(i) - tmp_vec2.at(i)));    // 取绝对值

    // 准备直方图数据
    QVector<double> ticks;
    QVector<double> values;
    int number_of_bins = 20; // 可以根据需要调整直方图的分组数量
    double abs_max_error = *std::max_element(error_data.begin(), error_data.end());
    double abs_min_error = *std::min_element(error_data.begin(), error_data.end());
    double bin_width = (abs_max_error - abs_min_error) / number_of_bins;

    ticks.resize(number_of_bins);
    values.resize(number_of_bins);

    for (int i = 0; i < number_of_bins; ++i)
        ticks[i] = abs_min_error + (i + 0.5) * bin_width; // 中点

    for (double error : error_data)
    {
        int bin_index = static_cast<int>((error - abs_min_error) / bin_width);
        if (bin_index >= 0 && bin_index < number_of_bins)
            values[bin_index]++;
    }

    // 创建一个直方图（bar chart）
    QCustomPlot* const plot = distribution_dialog_->myplot_;
    plot->clearPlottables();
    plot->replot();
    QCPBars* histogram = new QCPBars(plot->xAxis, plot->yAxis);

    histogram->setData(ticks, values);
    histogram->setWidth(bin_width * 0.9); // 设置柱子的宽度

    // 设定样式
    histogram->setPen(QPen(QColor(150, 202, 255))); // 边框颜色
    histogram->setBrush(QColor(150, 202, 255, 150)); // 填充颜色

    plot->rescaleAxes();
    plot->replot(QCustomPlot::rpQueuedReplot);
    distribution_dialog_->show();
}

bool SpeedViewDockWidget::slot_btnSavePic_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Picture"), "", tr("Images (*.png *.jpg *.bmp *.pdf)"));
    QCustomPlot* const plot = ui->plot;

    if( filename == "" ){
        QMessageBox::information(this,"fail","图片文件保存失败: 未选择保存文件");
        return false;
    }
    if( filename.endsWith(".png") )
    {
        QMessageBox::information(this,"success","成功保存为png文件");
        return plot->savePng(filename, plot->width(), plot->height());
    }
    if( filename.endsWith(".jpg") || filename.endsWith(".jpeg") )
    {
        QMessageBox::information(this,"success","成功保存为jpg文件");
        return plot->saveJpg(filename, plot->width(), plot->height());
    }
    if( filename.endsWith(".bmp") )
    {
        QMessageBox::information(this,"success","成功保存为bmp文件");
        return plot->saveBmp(filename, plot->width(), plot->height());
    }
    if( filename.endsWith(".pdf") )
    {
        QMessageBox::information(this,"success","成功保存为pdf文件");
        return plot->savePdf(filename, plot->width(), plot->height());
    }
    else
    {
    //否则追加后缀名为.png保存文件
        QMessageBox::information(this,"success","保存成功,已默认保存为png文件");
        return plot->savePng(filename.append(".png"), plot->width(), plot->height());
    }
}

void SpeedViewDockWidget::slot_btnSaveExcel_clicked()
{
    QCustomPlot* const plot = ui->plot;

    if (plot->graphCount() < 2)
    {
        QMessageBox::information(this,"fail","excel文件保存失败: 没有数据");
        return;
    }

    QString csv_file = QFileDialog::getSaveFileName(this, tr("Save Excel"), "", tr("Excel (*.xlsx)"));
    if( csv_file == "")
    {
        QMessageBox::information(this,"fail","excel文件保存失败: 未选择保存文件");
        return;
    }

    QVector<QCPGraphData> ref_speed_lst = *plot->graph(0)->data()->coreData();
    QVector<QCPGraphData> rel_speed_lst = *plot->graph(1)->data()->coreData();

    QVector< QVector<QVariant> > table;

    int points_num = ref_speed_lst.size();

    for (int i = 0; i < points_num; i+=default_sampling_point_nums_)
    {
        QVector<QVariant> aline;

        double key = ref_speed_lst.at(i).key;
        aline.append(QVariant(QDateTime::fromMSecsSinceEpoch(key * 1000.0).toString("hh:mm:ss.zzz")));
        aline.append(QVariant(ref_speed_lst.at(i).value));
        aline.append(QVariant(rel_speed_lst.at(i).value));
        aline.append(QVariant(qAbs( ref_speed_lst.at(i).value - rel_speed_lst.at(i).value )));

        table.append(aline);
    }

    QThread* thread = new QThread;
    MyExcel* myexcel = new MyExcel();
    myexcel->moveToThread(thread);

    connect(myexcel, &MyExcel::finished, this, [=] (bool success) {
        if (success)
        {
            QMessageBox::information(this, "提示", "数据保存成功");
        }
        else
        {
            QMessageBox::information(this, "提示", "数据保存失败");
        }

        thread->quit();
        thread->wait();
        thread->deleteLater();
        myexcel->deleteLater();
    });

    myexcel->slot_info(QDateTime::currentDateTime().toString(), device_name_, tester_, QString::fromStdString(sig_lst_.at(0).second.name), QString::fromStdString(sig_lst_.at(1).second.name));
    // 值传递对性能影响计算
    qRegisterMetaType< QString >("QString");
    qRegisterMetaType< QVector< QVector<QVariant> > >("QVector< QVector<QVariant> >");
    connect(this, &SpeedViewDockWidget::signal_excelData, myexcel, &MyExcel::slot_writeOneTable);

    thread->start();

    emit signal_excelData(csv_file, 1, table);
}

void SpeedViewDockWidget::slot_testerChanged(QString tester)
{
    tester_ = tester;
}

void SpeedViewDockWidget::slot_deviceNameChanged(QString device_name)
{
    device_name_ = device_name;
}
