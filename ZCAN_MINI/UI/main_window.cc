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
    menuSendData(new QMenu(QStringLiteral("发送数据"), this)),
    actDeviceManage(new QAction(QStringLiteral("设备管理"), this)),
    actSendData(new QAction(QStringLiteral("发送数据"), this))
{
    ui->setupUi(this);

    // 添加菜单和action
    ui->menubar->addAction(actDeviceManage);
    ui->menubar->addMenu(menuSendData);
    menuSendData->addAction(actSendData);

    // QMainWindow中自带中央窗体，如果不去除，可能会造成窗口间有空块的情况，去除后，所有窗口都由QDockWidget构成
    // 移除中间窗口组件，可以使dock居中显示
//    QWidget * const central_widget = takeCentralWidget();
//    if (central_widget)
//        delete central_widget;

    canviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    plotviewDcok->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dbcviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    QVBoxLayout* const layout = new QVBoxLayout();
    layout->addWidget(canviewDock);
    ui->tabCan->setLayout(layout);

    QHBoxLayout* const layout1 = new QHBoxLayout();
    layout1->addWidget(dbcviewDock);
    layout1->addWidget(plotviewDcok);
    ui->tabSpeed->setLayout(layout1);

//    QVBoxLayout* const layout2 = new QVBoxLayout();
//    layout2->addWidget(dbcviewDock);
//    ui->tabPwm->setLayout(layout2);



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
    connect(actDeviceManage, &QAction::triggered, this, [=] {
        deviceManagerDlg->exec();
    });
    connect(actSendData, &QAction::triggered, this, [=] {
        senddataDlg->exec();
    });
    connect(dbcviewDock, &DBCViewDockWidget::sig_paint, plotviewDcok, &PlotViewDockWidget::slot_paint);
}
