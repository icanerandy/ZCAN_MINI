#ifndef DEVICE_MANAGER_DIALOG_H
#define DEVICE_MANAGER_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStringList>
#include <QTreeWidget>
#include <QMessageBox>
#include "devicemanager.h"
#include "initcan_dialog.h"

namespace Ui {
class DeviceManagerDialog;
}

/**
 * @brief The DeviceManagerDialog class
 * 这是设备管理对话框，他应该完成设备的打开、配置和关闭等一系列功能
 * - initCanDlg 配置CAN通道对话框
 * 所有指针都应该是指针常量，并在初始化列表中完成初始化
 */
class DeviceManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceManagerDialog(QWidget *parent = 0);
    ~DeviceManagerDialog();

private:
    void initTypeCBox();
    void initIndexCBox(QObject *obj, int start, int end, int current);
    void bindSignals();
    void enableCtrl(bool enabled);

signals:
    void sig_chkDeviceType();

private slots:
    void slot_btnDeviceInfo_clicked();

private:
    Ui::DeviceManagerDialog * const ui;
    InitCanDialog * const initCanDlg;
};

#endif // DEVICE_MANAGER_DIALOG_H
