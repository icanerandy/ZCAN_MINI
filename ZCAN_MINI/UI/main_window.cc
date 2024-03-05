#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    canviewDock(new CanViewDockWidget(this)),
    speed_dbcviewDock(new DBCViewDockWidget(this)),
    speedviewDock(new SpeedViewDockWidget(this)),
    pwm_dbcviewDock(new DBCViewDockWidget(this)),
    pwmviewDock(new PwmViewDockWidget(this)),
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

    canviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    speedviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    speed_dbcviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    pwmviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    pwm_dbcviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    QVBoxLayout* const layout = new QVBoxLayout();
    layout->addWidget(canviewDock);
    ui->tabCan->setLayout(layout);

    QHBoxLayout* const layout1 = new QHBoxLayout();
    layout1->addWidget(speed_dbcviewDock);
    layout1->addWidget(speedviewDock);
    ui->tabSpeed->setLayout(layout1);

    QHBoxLayout* const layout2 = new QHBoxLayout();
    layout2->addWidget(pwm_dbcviewDock);
    layout2->addWidget(pwmviewDock);
    ui->tabPwm->setLayout(layout2);

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
    connect(speed_dbcviewDock, &DBCViewDockWidget::sig_paint, speedviewDock, &SpeedViewDockWidget::slot_paint);
    connect(pwm_dbcviewDock, &DBCViewDockWidget::sig_paint, pwmviewDock, &PwmViewDockWidget::slot_paint);
}
