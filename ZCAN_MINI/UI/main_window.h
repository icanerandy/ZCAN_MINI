#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>
#include <QAction>
#include <QVBoxLayout>
#include <QGridLayout>
#include "qtmaterialtabs_internal.h"
#include "qtmaterialtabs.h"
#include <devicemanager_dialog.h>
#include "zlgcan.h"
#include "devicemanager.h"
#include <recmsg_thread.h>
#include "info_dockwidget.h"
#include "canview_dockwidget.h"
#include "dbcview_dockwidget.h"
#include "speedview_dockwidget.h"
#include "senddata_dialog.h"
#include "spdlog_common.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * 一个主窗口由以下属性构成
 * - ui
 * - deviceManagerDlg 设备管理对话框
 * - canviewDock can视图
 * - dbcviewDock 设备视图
 * - plotviewDock 曲线图视图
 * - senddataDlg 数据发送窗口
 * - actDeviceManage
 * - actCreateCanView
 * - actCreateDBCView
 * - actCreatePlotView
 * - actSendData
 * - recmsg_thread_ 消息接收子线程
 * 所有成员变量应该在主窗体初始化时完成定义，且不可改变
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void bindSignals();

private:
    Ui::MainWindow * const ui;
    QVBoxLayout* layout;
    QtMaterialTabs* tabs;
    QtMaterialTab* can_tab;
    QtMaterialTab* dbc_tab;
    QtMaterialTab* speed_tab;
    QWidget* can_widget;
    QWidget* dbc_widget;
    QWidget* speed_widget;
    InfoDockWidget * const info_viewDock;
    CanViewDockWidget * const can_viewDock;
    DBCViewDockWidget * const dbc_viewDock;
    SpeedViewDockWidget * const speed_plotviewDock;
    DeviceManagerDialog * const deviceManagerDlg;
    SendDataDialog * const senddataDlg;

    QAction* const actDeviceManage;

    QMenu* const menuSendData;
    QAction* const actSendData;

    std::shared_ptr<spdlog::logger> logger_;

    RecMsgThread *recmsg_thread_;
};

#endif // MAIN_WINDOW_H
