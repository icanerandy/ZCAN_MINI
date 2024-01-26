#ifndef DEVICE_MANAGER_DIALOG_H
#define DEVICE_MANAGER_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStringList>
#include <QTreeWidget>
#include "device_manager.h"

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

private slots:
    void slot_ComboDeviceType_currentIndexChanged(int index);
    void slot_ComboDeviceIndex_currentIndexChanged(int index);
    void slot_BtnOpenDevice_clicked();

private:
    QWidget *centralWidget;
    QGridLayout *gLayout;
    QHBoxLayout *hLayout;
    QSpacerItem *hSpacer;
    QSpacerItem *hSpacer_2;
    QSpacerItem *vSpacer;

    QLabel *lab_device_type_;
    QComboBox *combo_device_type_;
    QLabel *lab_device_index_;
    QComboBox *combo_device_index_;
    QPushButton *btn_open_device;

    // 目录树相关
    // QTreeWidget *treeWidget;
private:
    Ui::DeviceManagerDialog *ui;
};

#endif // DEVICE_MANAGER_DIALOG_H
