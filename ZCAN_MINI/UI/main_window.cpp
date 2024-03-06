#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    can_viewDock(new CanViewDockWidget(this)),
    speed_dbcviewDock(new DBCViewDockWidget(this)),
    speed_plotviewDock(new SpeedViewDockWidget(this)),
    deviceManagerDlg(new DeviceManagerDialog(this)),
    senddataDlg(new SendDataDialog(this)),
    actDeviceManage(new QAction(QStringLiteral("设备管理"), this)),
    menuDataAnalys(new QMenu(QStringLiteral("数据分析"), this)),
    actDisPic(new QAction(QStringLiteral("误差图"), this)),
    actSavePic(new QAction(QStringLiteral("保存图像"), this)),
    actSaveExcel(new QAction(QStringLiteral("保存Excel"), this)),
    menuSendData(new QMenu(QStringLiteral("发送数据"), this)),
    actSendData(new QAction(QStringLiteral("发送数据"), this))
{
    ui->setupUi(this);

    // 添加菜单和action
    ui->menubar->addAction(actDeviceManage);

    ui->menubar->addMenu(menuDataAnalys);
    menuDataAnalys->addAction(actDisPic);
    menuDataAnalys->addAction(actSavePic);
    menuDataAnalys->addAction(actSaveExcel);

    ui->menubar->addMenu(menuSendData);
    menuSendData->addAction(actSendData);

    can_viewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    speed_plotviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    speed_plotviewDock->setFeatures(QDockWidget::DockWidgetMovable);
    speed_dbcviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    speed_dbcviewDock->setFeatures(QDockWidget::DockWidgetMovable);

    QVBoxLayout* const layout = new QVBoxLayout();
    layout->addWidget(can_viewDock);
    ui->tabCan->setLayout(layout);

    QHBoxLayout* const layout1 = new QHBoxLayout();
    layout1->addWidget(speed_dbcviewDock, 1);
    layout1->addWidget(speed_plotviewDock, 2);
    ui->tabSpeed->setLayout(layout1);

    // 按键使能
    menuDataAnalys->setEnabled(false);

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

    connect(speed_dbcviewDock, &DBCViewDockWidget::sig_paint, speed_plotviewDock, &SpeedViewDockWidget::slot_paint);
    connect(speed_dbcviewDock, &DBCViewDockWidget::sig_paint, this, [=] {
       menuDataAnalys->setEnabled(true);
    });
    connect(actDisPic, &QAction::triggered, speed_plotviewDock, &SpeedViewDockWidget::slot_actDisPic_triggered);
    connect(actSavePic, &QAction::triggered, speed_plotviewDock, &SpeedViewDockWidget::slot_actSavePic_triggered);
    connect(actSaveExcel, &QAction::triggered, speed_plotviewDock, &SpeedViewDockWidget::slot_actSaveExcel_triggered);

    connect(actSendData, &QAction::triggered, this, [=] {
        senddataDlg->exec();
    });
}
