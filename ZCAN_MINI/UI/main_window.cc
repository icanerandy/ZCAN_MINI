#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    canviewDock(new CanViewDockWidget(this)),
    dbcviewDock(new DBCViewDockWidget(this)),
    plotviewDcok(new PlotViewDockWidget(this)),
    deviceManagerDlg(new DeviceManagerDialog(this)),
    senddataDlg(new SendDataDialog(this)),
    menuCreateView(new QMenu(QStringLiteral("打开视图"), this)),
    menuSendData(new QMenu(QStringLiteral("发送数据"), this)),
    actCreateCanView(new QAction(QStringLiteral("CAN视图"), this)),
    actCreateDBCView(new QAction(QStringLiteral("DBC视图"), this)),
    actCreatePlotView(new QAction(QStringLiteral("Plot视图"), this)),
    actDeviceManage(new QAction(QStringLiteral("设备管理"), this)),
    actSendData(new QAction(QStringLiteral("发送数据"), this))
{
    ui->setupUi(this);

    // 添加菜单和action
    ui->menubar->addAction(actDeviceManage);
    ui->menubar->addMenu(menuCreateView);
    ui->menubar->addMenu(menuSendData);
    menuCreateView->addAction(actCreateCanView);
    menuCreateView->addAction(actCreateDBCView);
    menuCreateView->addAction(actCreatePlotView);
    menuSendData->addAction(actSendData);

    // QMainWindow中自带中央窗体，如果不去除，可能会造成窗口间有空块的情况，去除后，所有窗口都由QDockWidget构成
    // 移除中间窗口组件，可以使dock居中显示
    QWidget * const central_widget = takeCentralWidget();
    if (central_widget)
        delete central_widget;

    setDockNestingEnabled(true);

    // 进行布局
    this->addDockWidget(Qt::LeftDockWidgetArea, canviewDock);
    this->addDockWidget(Qt::RightDockWidgetArea, dbcviewDock);
    this->addDockWidget(Qt::RightDockWidgetArea, plotviewDcok);

    // 分割窗口
    splitDockWidget(dbcviewDock, plotviewDcok, Qt::Vertical);

    // 合并窗口
    tabifyDockWidget(plotviewDcok, dbcviewDock);

    // 信号绑定
    bindSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bindSignals()
{
    // 内部信号内部处理即可
    connect(actCreateCanView, &QAction::triggered, this, [=] {
        canviewDock->show();
    });
    connect(actCreateDBCView, &QAction::triggered, this, [=] {
        dbcviewDock->show();
    });
    connect(actCreatePlotView, &QAction::triggered, this, [=] {
        plotviewDcok->show();
    });
    connect(actDeviceManage, &QAction::triggered, this, [=] {
        deviceManagerDlg->exec();
    });
    connect(actSendData, &QAction::triggered, this, [=] {
        senddataDlg->exec();
    });
    connect(dbcviewDock, &DBCViewDockWidget::sig_checkState_changed, plotviewDcok, &PlotViewDockWidget::slot_checkState_changed);
}
