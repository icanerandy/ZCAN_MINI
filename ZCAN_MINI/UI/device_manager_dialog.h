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
#include "device_manager.h"
#include "init_can_dialog.h"

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
    void EnableCtrl(bool enabled);

private slots:
    void slot_ComboDeviceType_currentIndexChanged(int index);
    void slot_ComboDeviceIndex_currentIndexChanged(int index);
    void slot_BtnOpenDevice_clicked();
    void slot_BtnStartDevice_clicked();

private:
    Ui::DeviceManagerDialog *ui;
    InitCanDialog *initCanDialog;
};

#endif // DEVICE_MANAGER_DIALOG_H
