#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QAction>
#include <devicemanager_dialog.h>
#include "zlgcan.h"
#include "devicemanager.h"
#include <recmsg_thread.h>
#include "canview_dockwidget.h"
#include "senddata_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void BindSignals();

private slots:
    void slot_actDeviceManage_triggered(bool checked);
    void slot_actCreateCanView_triggered(bool checked);
    void slot_actSendData_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    DeviceManagerDialog *devicemanager_dialog;
    CanViewDockWidget *canview_dockWidget;
    SendDataDialog *senddata_dialog;


    QAction *actDeviceManage;
    QAction *actCreateCanView;
    QAction *actSendData;

private:
    RecMsgThread *recmsg_thread;
};

#endif // MAIN_WINDOW_H
