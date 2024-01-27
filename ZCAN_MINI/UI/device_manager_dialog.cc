#include "device_manager_dialog.h"
#include "ui_device_manager_dialog.h"

DeviceManagerDialog::DeviceManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceManagerDialog),
    initCanDialog(nullptr)
{
    ui->setupUi(this);

    InitDialog();

    connect(ui->comboDeviceType,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &DeviceManagerDialog::slot_ComboDeviceType_currentIndexChanged);

    connect(ui->comboDeviceIndex,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &DeviceManagerDialog::slot_ComboDeviceIndex_currentIndexChanged);

    connect(ui->btnOpenDevice, &QPushButton::clicked, this, &slot_BtnOpenDevice_clicked);

    connect(ui->btnStartDevice, &QPushButton::clicked, this, &slot_BtnStartDevice_clicked);
}

DeviceManagerDialog::~DeviceManagerDialog()
{
    delete ui;
}

void DeviceManagerDialog::InitDialog()
{
    InitTypeComboBox();
    InitIndexComboBox(ui->comboDeviceIndex, 0, 32, 0);

    // 隐藏组件
    EnableCtrl(false);
}

void DeviceManagerDialog::InitTypeComboBox()
{
    QStringList string_list;
    string_list << "ZCAN_USBCAN1" << "ZCAN_USBCAN2" << "ZCAN_PCI9820I" << "ZCAN_USBCAN_E_U"
                << "ZCAN_USBCAN_2E_U" << "ZCAN_USBCAN_4E_U" << "ZCAN_PCIE_CANFD_100U"
                << "ZCAN_PCIE_CANFD_200U" << "ZCAN_PCIE_CANFD_400U_EX" << "ZCAN_USBCANFD_200U"
                << "ZCAN_USBCANFD_100U" << "ZCAN_USBCANFD_MINI" << "ZCAN_CANETTCP"
                << "ZCAN_CANETUDP" << "ZCAN_WIFICAN_TCP" << "ZCAN_WIFICAN_UDP"
                << "ZCAN_CLOUD" << "ZCAN_CANFDWIFI_TCP" << "ZCAN_CANFDWIFI_UDP"
                << "ZCAN_CANFDNET_TCP" << "ZCAN_CANFDNET_UDP" << "ZCAN_CANFDNET_400U_TCP"
                << "ZCAN_CANFDNET_400U_UDP";
    ui->comboDeviceType->addItems(string_list);
}

void DeviceManagerDialog::InitIndexComboBox(QObject *obj, int start, int end, int current)
{
    QComboBox *combo = static_cast<QComboBox*>(obj);
    Q_ASSERT(combo != NULL);
    combo->clear();
    for (int i = start; i < end; ++i)
    {
        combo->addItem(QString::asprintf("%d", i));
    }
    combo->setCurrentIndex(current);
}

void DeviceManagerDialog::EnableCtrl(bool enabled)
{
    ui->comboDeviceType->setEnabled(!enabled);
    ui->comboDeviceIndex->setEnabled(!enabled);
    ui->btnOpenDevice->setEnabled(!enabled);
    ui->labChannel->setVisible(enabled);
    ui->comboChannelIndex->setVisible(enabled);
    ui->btnStartDevice->setVisible(enabled);
    ui->btnStopDevice->setEnabled(enabled);
    ui->btnStopDevice->setVisible(enabled);
    ui->btnStopDevice->setEnabled(!enabled);
    ui->btnCloseDevice->setVisible(enabled);
    ui->btnDeviceInfo->setVisible(enabled);
}

void DeviceManagerDialog::slot_ComboDeviceType_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->ChangeDeviceType(index);
}

void DeviceManagerDialog::slot_ComboDeviceIndex_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->ChangeDeviceIndex(index);
}

void DeviceManagerDialog::slot_BtnOpenDevice_clicked()
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    bool ret = device_manager->OpenDevice();
    if (ret)
    {
        EnableCtrl(true);
        int device_type_index = device_manager->device_type_index();
        InitIndexComboBox(ui->comboChannelIndex, 0, kDeviceType[device_type_index].channel_count, 0);/* 根据设备类型设置相关通道数 */
    }
    else
    {
        QMessageBox::warning(this, "warning", "打开设备失败！");
    }
}

void DeviceManagerDialog::slot_BtnStartDevice_clicked()
{
    // 一次创建，多次调用，对话框关闭时只是隐藏
    if (!initCanDialog)
        initCanDialog = new InitCanDialog(this);
    initCanDialog->exec();  // 以模态方式显示对话框
}
