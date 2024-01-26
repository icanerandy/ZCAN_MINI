#include "device_manager_dialog.h"
#include "ui_device_manager_dialog.h"

DeviceManagerDialog::DeviceManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceManagerDialog)
{
    ui->setupUi(this);

    InitDialog();

    connect(ui->combo_device_type,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &DeviceManagerDialog::slot_ComboDeviceType_currentIndexChanged);

    connect(ui->combo_device_index,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &DeviceManagerDialog::slot_ComboDeviceIndex_currentIndexChanged);

    connect(ui->btn_open_device, &QPushButton::clicked, this, &slot_BtnOpenDevice_clicked);
}

DeviceManagerDialog::~DeviceManagerDialog()
{
    delete ui;
}

void DeviceManagerDialog::InitDialog()
{
    InitTypeComboBox();
    InitIndexComboBox(ui->combo_device_index, 0, 32, 0);

    // 隐藏组件
    ui->lab_channel->setVisible(false);
    ui->combo_channel_index->setVisible(false);
    ui->btn_start_device->setVisible(false);
    ui->btn_stop_device->setVisible(false);
    ui->btn_close_device->setVisible(false);
    ui->btn_device_info->setVisible(false);
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
    ui->combo_device_type->addItems(string_list);
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
        ui->lab_channel->setVisible(true);
        ui->combo_channel_index->setVisible(true);
        ui->btn_start_device->setVisible(true);
        ui->btn_stop_device->setVisible(true);
        ui->btn_close_device->setVisible(true);
        ui->btn_device_info->setVisible(true);
        qDebug("打开设备成功");
    }
    else
        qDebug("打开设备失败");
}
