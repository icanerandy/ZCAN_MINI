#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QAction>
#include <devicemanager_dialog.h>
#include "zlgcan.h"
#include "devicemanager.h"
#include <recmsg_thread.h>
#include "canview_dockwidget.h"
#include "dbcview_dockwidget.h"
#include "speedview_dockwidget.h"
#include "pwmview_dockwidget.h"
#include "senddata_dialog.h"

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
    CanViewDockWidget * const canviewDock;
    DBCViewDockWidget * const speed_dbcviewDock;
    SpeedViewDockWidget * const speedviewDock;
    DBCViewDockWidget * const pwm_dbcviewDock;
    PwmViewDockWidget * const pwmviewDock;
    DeviceManagerDialog * const deviceManagerDlg;
    SendDataDialog * const senddataDlg;

    QMenu * const menuSendData;
    QAction * const actDeviceManage;
    QAction * const actSendData;

    RecMsgThread *recmsg_thread_;
};

#endif // MAIN_WINDOW_H
