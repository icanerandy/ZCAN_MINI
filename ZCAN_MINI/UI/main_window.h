#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QAction>
#include <device_manager_dialog.h>
#include "zlgcan.h"
#include "app_event.h"
#include "device_manager.h"

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
    void slot_ActDeviceManage_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    DeviceManagerDialog *device_manager_dialog;


    QAction *act_device_manage;
};

#endif // MAIN_WINDOW_H
