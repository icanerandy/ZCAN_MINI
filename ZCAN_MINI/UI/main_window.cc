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
    act_device_manage = new QAction(icon, QStringLiteral("设备管理"), this);

    ui->menubar->addAction(act_device_manage);



    BindSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BindSignals()
{
    connect(act_device_manage, &QAction::triggered, this, &MainWindow::slot_ActDeviceManage_triggered);
}

void MainWindow::slot_ActDeviceManage_triggered(bool checked)
{
    // 一次创建，多次调用，对话框关闭时只是隐藏
    if (!device_manager_dialog)
        device_manager_dialog = new DeviceManagerDialog(this);
    device_manager_dialog->exec();  // 以模态方式显示对话框
}
