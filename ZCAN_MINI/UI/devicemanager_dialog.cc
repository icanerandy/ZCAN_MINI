#include "devicemanager_dialog.h"
#include "ui_device_manager_dialog.h"

DeviceManagerDialog::DeviceManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceManagerDialog),
    initCanDialog(nullptr)
{
    ui->setupUi(this);

    InitDialog();

    BindSlots();
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

void DeviceManagerDialog::BindSlots()
{
    connect(ui->comboDeviceType,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &DeviceManagerDialog::slot_comboDeviceType_currentIndexChanged);

    connect(ui->comboDeviceIndex,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &DeviceManagerDialog::slot_comboDeviceIndex_currentIndexChanged);

    connect(ui->btnOpenDevice, &QPushButton::clicked, this, &slot_btnOpenDevice_clicked);

    connect(ui->btnStartDevice, &QPushButton::clicked, this, &slot_btnStartDevice_clicked);

    connect(ui->btnStopDevice, &QPushButton::clicked, this, &slot_btnStopDevice_clicked);

    connect(ui->btnStopDevice, &QPushButton::clicked, this, &slot_btnCloseDevice_clicked);

    connect(ui->btnDeviceInfo, &QPushButton::clicked, this, &slot_btnDeviceInfo_clicked);
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
    ui->btnStopDevice->setVisible(enabled);
    ui->btnDeviceInfo->setVisible(enabled);
}

void DeviceManagerDialog::slot_comboDeviceType_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->ChangeDeviceType(index);
}

void DeviceManagerDialog::slot_comboDeviceIndex_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->ChangeDeviceIndex(index);
}

void DeviceManagerDialog::slot_btnOpenDevice_clicked()
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

void DeviceManagerDialog::slot_btnStartDevice_clicked()
{
    // 一次创建，多次调用，对话框关闭时只是隐藏
    if (!initCanDialog)
        initCanDialog = new InitCanDialog(this);
    initCanDialog->exec();  // 以模态方式显示对话框

    /* 子对话框隐藏后设置相应按键使能 */
    ui->btnStartDevice->setEnabled(false);
    ui->btnStopDevice->setEnabled(true);
}

void DeviceManagerDialog::slot_btnStopDevice_clicked()
{
    RecMsgThread *rec_msg_thread = RecMsgThread::GetInstance();
    if (rec_msg_thread->isRunning())
    {
        rec_msg_thread->stopThread();
        rec_msg_thread->wait();
    }

    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->StopCan();

    /* 设置相应按键使能 */
    ui->btnStartDevice->setEnabled(true);
    ui->btnStopDevice->setEnabled(false);
}

void DeviceManagerDialog::slot_btnCloseDevice_clicked()
{
    RecMsgThread *rec_msg_thread = RecMsgThread::GetInstance();
    if (rec_msg_thread->isRunning())
    {
        rec_msg_thread->stopThread();
        rec_msg_thread->wait();
    }

    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->CloseDevice();

    /* 设置相应按键使能 */
    EnableCtrl(false);
}

void DeviceManagerDialog::slot_btnDeviceInfo_clicked()
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    ZCAN_DEVICE_INFO *info = device_manager->GetDeviceInfo();

    QString hw_version = info->hw_Version==0?"000":QString::number(info->hw_Version, 16);
    hw_version.insert(1, '.');
    QString fw_version = info->fw_Version==0?"000":QString::number(info->fw_Version, 16);
    fw_version.insert(1, '.');
    QString dr_version = info->dr_Version==0?"000":QString::number(info->dr_Version, 16);
    dr_version.insert(1, '.');
    QString in_version = info->in_Version==0?"000":QString::number(info->in_Version, 16);
    in_version.insert(1, '.');

    QString strInfo;
    strInfo.append("硬件版本:V" + hw_version + "\n");
    strInfo.append("固件版本:V" + fw_version + "\n");
    strInfo.append("驱动版本:V" + dr_version + "\n");
    strInfo.append("动态库版本:V" + in_version + "\n");
    strInfo.append("CAN路数:" + QString::number(info->can_Num, 10) + "\n");
    strInfo.append("序列号:" + QString::fromUtf8(reinterpret_cast<const char*>(info->str_Serial_Num), 20) + "\n");
    strInfo.append("硬件类型:" + QString::fromUtf8(reinterpret_cast<const char*>(info->str_hw_Type)) + "\n");

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("设备信息");
    msgBox.setText(strInfo);

    // 自定义布局
    QGridLayout* layout = qobject_cast<QGridLayout*>(msgBox.layout());
    if (layout) {
        layout->setColumnStretch(1, 2);  // 增加文本列的拉伸系数
        layout->setRowStretch(5, 10);    // 增加图标行的拉伸系数
    }

    msgBox.exec();

    delete info;
}
