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

    CanViewDockWidget *canview_dockwidget = new CanViewDockWidget(this);
    this->addDockWidget(Qt::TopDockWidgetArea, canview_dockwidget);
    this->dockwidgets.append(canview_dockwidget);
    setCentralWidget(canview_dockwidget);
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
    if (!device_manager_dialog)
        device_manager_dialog = new DeviceManagerDialog(this);
    device_manager_dialog->exec();  // 以模态方式显示对话框
}

void MainWindow::slot_actCreateCanView_triggered(bool checked)
{
    Q_UNUSED(checked);

}
