#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    deviceManager_dialog(nullptr)
{
    ui->setupUi(this);

    QIcon icon;
    //icon.addFile();
    actDeviceManage = new QAction(icon, QStringLiteral("设备管理"), this);

    ui->menubar->addAction(actDeviceManage);

    QMenu *createView = new QMenu(QStringLiteral("新建视图"));
    ui->menubar->addMenu(createView);

    actCreateCanView = new QAction(icon, QStringLiteral("新建CAN视图"), this);
    createView->addAction(actCreateCanView);

    BindSignals();

    // 移除中间窗口组件
    QWidget *central_widget = takeCentralWidget();
    if (central_widget)
        delete central_widget;

    setDockNestingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BindSignals()
{
    // 内部信号内部处理即可
    connect(actDeviceManage, &QAction::triggered, this, &MainWindow::slot_actDeviceManage_triggered);
    connect(actCreateCanView, &QAction::triggered, this, &MainWindow::slot_actCreateCanView_triggered);
}

void MainWindow::slot_actDeviceManage_triggered(bool checked)
{
    Q_UNUSED(checked);
    // 一次创建，多次调用，对话框关闭时只是隐藏
    if (!deviceManager_dialog)
        deviceManager_dialog = new DeviceManagerDialog(this);
    deviceManager_dialog->exec();  // 以模态方式显示对话框
}

void MainWindow::slot_actCreateCanView_triggered(bool checked)
{
    Q_UNUSED(checked);
    canview_dockWidget = new CanViewDockWidget(this);
    this->addDockWidget(Qt::TopDockWidgetArea, canview_dockWidget);
}
