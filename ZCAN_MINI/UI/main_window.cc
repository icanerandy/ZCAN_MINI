#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    devicemanager_dialog(nullptr),
    canview_dockWidget(nullptr),
    dbcview_dockWidget(nullptr),
    plotview_dockWidget(nullptr),
    senddata_dialog(nullptr)
{
    ui->setupUi(this);

    QIcon icon;
    //icon.addFile();
    actDeviceManage = new QAction(icon, QStringLiteral("设备管理"), this);

    ui->menubar->addAction(actDeviceManage);

    QMenu *createView = new QMenu(QStringLiteral("打开视图"));
    ui->menubar->addMenu(createView);

    actCreateCanView = new QAction(icon, QStringLiteral("CAN视图"), this);
    createView->addAction(actCreateCanView);

    actCreateDBCView = new QAction(icon, QStringLiteral("DBC视图"), this);
    createView->addAction(actCreateDBCView);

    actCreatePlotView = new QAction(icon, QStringLiteral("Plot视图"), this);
    createView->addAction(actCreatePlotView);

    QMenu *sendData = new QMenu(QStringLiteral("发送数据"), this);
    ui->menubar->addMenu(sendData);

    actSendData = new QAction(icon, QStringLiteral("普通发送"), this);
    sendData->addAction(actSendData);

    BindSignals();

    // 移除中间窗口组件
    QWidget *central_widget = takeCentralWidget();
    if (central_widget)
        delete central_widget;

    setDockNestingEnabled(true);

    canview_dockWidget = new CanViewDockWidget(this);
    this->addDockWidget(Qt::TopDockWidgetArea, canview_dockWidget);
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
    connect(actCreateDBCView, &QAction::triggered, this, &MainWindow::slot_actCreateDBCView_triggered);
    connect(actCreatePlotView, &QAction::triggered, this, &MainWindow::slot_actCreatePlotView_triggered);
    connect(actSendData, &QAction::triggered, this, &MainWindow::slot_actSendData_triggered);
}

void MainWindow::slot_actDeviceManage_triggered(bool checked)
{
    Q_UNUSED(checked);
    // 一次创建，多次调用，对话框关闭时只是隐藏
    if (!devicemanager_dialog)
        devicemanager_dialog = new DeviceManagerDialog(this);
    devicemanager_dialog->exec();  // 以模态方式显示对话框
}

void MainWindow::slot_actCreateCanView_triggered(bool checked)
{
    Q_UNUSED(checked);
    if (!canview_dockWidget)
    {
        canview_dockWidget = new CanViewDockWidget(this);
        this->addDockWidget(Qt::TopDockWidgetArea, canview_dockWidget);
    }
    canview_dockWidget->show();
}

void MainWindow::slot_actCreateDBCView_triggered(bool checked)
{
    Q_UNUSED(checked);
    if (!dbcview_dockWidget)
    {
        dbcview_dockWidget = new DBCViewDockWidget(this);
        this->addDockWidget(Qt::TopDockWidgetArea, dbcview_dockWidget);
    }
    dbcview_dockWidget->show();
}

void MainWindow::slot_actCreatePlotView_triggered(bool checked)
{
    Q_UNUSED(checked);
    if (!plotview_dockWidget)
    {
        plotview_dockWidget = new PlotViewDockWidget(this);
        this->addDockWidget(Qt::TopDockWidgetArea, plotview_dockWidget);
        if (!dbcview_dockWidget)
        {
            dbcview_dockWidget = new DBCViewDockWidget(this);
            this->addDockWidget(Qt::TopDockWidgetArea, dbcview_dockWidget);
        }

        connect(dbcview_dockWidget, &DBCViewDockWidget::sig_checkState_Changed, plotview_dockWidget, &PlotViewDockWidget::slot_checkState_Changed);
    }
    plotview_dockWidget->show();
}

void MainWindow::slot_actSendData_triggered(bool checked)
{
    Q_UNUSED(checked);
    // 一次创建，多次调用，对话框关闭时只是隐藏
    if (!senddata_dialog)
        senddata_dialog = new SendDataDialog(this);
    senddata_dialog->exec();  // 以模态方式显示对话框
}
