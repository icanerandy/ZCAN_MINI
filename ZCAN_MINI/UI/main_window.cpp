#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    info_viewDock(new InfoDockWidget(this)),
    can_viewDock(new CanViewDockWidget(this)),
    dbc_viewDock(new DBCViewDockWidget(this)),
    speed_plotviewDock(new SpeedViewDockWidget(this)),
    deviceManagerDlg(new DeviceManagerDialog(this)),
    senddataDlg(new SendDataDialog(this)),
    actDeviceManage(new QAction(QStringLiteral("设备管理"), this)),
    menuSendData(new QMenu(QStringLiteral("发送数据"), this)),
    actSendData(new QAction(QStringLiteral("发送数据"), this))
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icon/analys.ico"));

    ui->menubar->addAction(actDeviceManage);

    ui->menubar->addMenu(menuSendData);
    menuSendData->addAction(actSendData);

    layout = new QVBoxLayout();

    tabs = new QtMaterialTabs;
    tabs->setFixedHeight(50);
    tabs->addTab("info视图");
    tabs->addTab("can视图");
    tabs->addTab("dbc视图");
    tabs->addTab("speed视图");

    info_viewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    can_viewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    speed_plotviewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    speed_plotviewDock->setFeatures(QDockWidget::DockWidgetMovable);
    dbc_viewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dbc_viewDock->setFeatures(QDockWidget::DockWidgetMovable);

    delete ui->centralwidget->layout();
    ui->centralwidget->setLayout(layout);

    layout->setSpacing(0); // 设置布局中控件之间的间距为0
    layout->setContentsMargins(0, 0, 0, 0); // 设置布局的边距为0

    layout->addWidget(tabs);
    tabs->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(info_viewDock);
    info_viewDock->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(can_viewDock);
    can_viewDock->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(dbc_viewDock);
    dbc_viewDock->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(speed_plotviewDock);
    speed_plotviewDock->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    tabs->setCurrentTab(0);
    info_viewDock->setVisible(true);
    can_viewDock->setVisible(false);
    dbc_viewDock->setVisible(false);
    speed_plotviewDock->setVisible(false);

    tabs->setBackgroundColor(QColor("#1C3A48"));
    tabs->setInkColor(QColor("#57C7FF"));

    setStatusBar(nullptr);

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

    connect(tabs, &QtMaterialTabs::currentChanged, this, [=] (int index) {
        info_viewDock->setVisible(index == 0);
        can_viewDock->setVisible(index == 1);
        dbc_viewDock->setVisible(index == 2);
        speed_plotviewDock->setVisible(index == 3);
    });

    connect(dbc_viewDock, &DBCViewDockWidget::sig_sigChecked, speed_plotviewDock, &SpeedViewDockWidget::slot_paint_enable);

    connect(actSendData, &QAction::triggered, this, [=] {
        senddataDlg->exec();
    });
}
