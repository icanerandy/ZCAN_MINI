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

class DeviceManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceManagerDialog(QWidget *parent = 0);
    ~DeviceManagerDialog();

private:
    void InitDialog();
    void InitTypeComboBox();
    void InitIndexComboBox(QObject *obj, int start, int end, int current);
    void BindSlots();
    void EnableCtrl(bool enabled);

private slots:
    void slot_comboDeviceType_currentIndexChanged(int index);
    void slot_comboDeviceIndex_currentIndexChanged(int index);
    void slot_btnOpenDevice_clicked();
    void slot_btnStartDevice_clicked();
    void slot_btnStopDevice_clicked();
    void slot_btnCloseDevice_clicked();
    void slot_btnDeviceInfo_clicked();

private:
    Ui::DeviceManagerDialog *ui;
    InitCanDialog *initCanDialog;
};

#endif // DEVICE_MANAGER_DIALOG_H
