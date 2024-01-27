#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    device_manager_dialog(nullptr)
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BindSignals()
{
    connect(actDeviceManage, &QAction::triggered, this, &MainWindow::slot_actDeviceManage_triggered);
    connect(actCreateCanView, &QAction::triggered, this, &MainWindow::slot_actCreateCanView_triggered);
}

void MainWindow::slot_actDeviceManage_triggered(bool checked)
{
    // 一次创建，多次调用，对话框关闭时只是隐藏
    if (!device_manager_dialog)
        device_manager_dialog = new DeviceManagerDialog(this);
    device_manager_dialog->exec();  // 以模态方式显示对话框
}

void MainWindow::slot_actCreateCanView_triggered(bool checked)
{
    CanViewDockWidget *canViewDockWidget = new CanViewDockWidget();
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), canViewDockWidget);
}
