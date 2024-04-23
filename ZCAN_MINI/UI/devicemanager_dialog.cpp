#include "devicemanager_dialog.h"
#include "ui_devicemanager_dialog.h"

DeviceManagerDialog::DeviceManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceManagerDialog),
    initCanDlg(new InitCanDialog(this))
{
    ui->setupUi(this);

    enableCtrl(false);

    // 初始化对话框
    QStringList string_list;
    string_list << QStringLiteral("ZCAN_USBCAN1") << QStringLiteral("ZCAN_USBCAN2") << QStringLiteral("ZCAN_PCI9820I") << QStringLiteral("ZCAN_USBCAN_E_U")
                << QStringLiteral("ZCAN_USBCAN_2E_U") << QStringLiteral("ZCAN_USBCAN_4E_U") << QStringLiteral("ZCAN_PCIE_CANFD_100U")
                << QStringLiteral("ZCAN_PCIE_CANFD_200U") << QStringLiteral("ZCAN_PCIE_CANFD_400U_EX") << QStringLiteral("ZCAN_USBCANFD_200U")
                << QStringLiteral("ZCAN_USBCANFD_100U") << QStringLiteral("ZCAN_USBCANFD_MINI") << QStringLiteral("ZCAN_CANETTCP")
                << QStringLiteral("ZCAN_CANETUDP") << QStringLiteral("ZCAN_WIFICAN_TCP") << QStringLiteral("ZCAN_WIFICAN_UDP")
                << QStringLiteral("ZCAN_CLOUD") << QStringLiteral("ZCAN_CANFDWIFI_TCP") << QStringLiteral("ZCAN_CANFDWIFI_UDP")
                << QStringLiteral("ZCAN_CANFDNET_TCP") << QStringLiteral("ZCAN_CANFDNET_UDP") << QStringLiteral("ZCAN_CANFDNET_400U_TCP")
                << QStringLiteral("ZCAN_CANFDNET_400U_UDP");
    ui->comboDeviceType->addItems(string_list);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    // 按钮样式
    QColor color("#607D8B");
    ui->btnOpenDevice->setBackgroundColor(color);
    ui->btnStartDevice->setBackgroundColor(color);
    ui->btnStopDevice->setBackgroundColor(color);
    ui->btnCloseDevice->setBackgroundColor(color);
    ui->btnDeviceInfo->setBackgroundColor(color);

    bindSignals();
}

DeviceManagerDialog::~DeviceManagerDialog()
{
    delete ui;
}

void DeviceManagerDialog::bindSignals()
{
    DeviceManager * const device_manager = DeviceManager::getInstance();
    // 内部信号自身做处理
    connect(this, &DeviceManagerDialog::sig_chkDeviceType,
            initCanDlg, &InitCanDialog::slot_chkDeviceType);

    connect(ui->comboDeviceType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [=] (int index) {
        device_manager->slot_deviceType_changed(static_cast<DeviceManager::DeviceTypeIndex>(index));
        emit sig_chkDeviceType();
    });

    connect(ui->comboDeviceIndex, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [=] (int index) {
        device_manager->changeDeviceIndex(index);
    });

    connect(ui->btnOpenDevice, &QPushButton::clicked, this, [=] {
        bool ret = device_manager->openDevice();
        if (ret)
        {
            enableCtrl(true);
            DeviceManager::DeviceTypeIndex device_type_index = device_manager->device_type_index();

            // 根据设备类型设置通道数量
            QComboBox * const combo = ui->comboChannelIndex;
            combo->clear();
            for (uint i = 0; i < DeviceManager::kDeviceType[static_cast<uint>(device_type_index)].channel_count; ++i)
                combo->addItem(QString::asprintf("%d", i));
            combo->setCurrentIndex(0);
        }
        else
        {
            QMessageBox::warning(this, "warning", "打开设备失败！");
        }
    });

    connect(ui->btnStartDevice, &QPushButton::clicked, this, [=] {
        initCanDlg->exec();

        if (DeviceManager::CanState::Started == device_manager->can_start())
        {
            ui->btnStartDevice->setEnabled(false);
            ui->btnStopDevice->setEnabled(true);
        }
    });

    connect(ui->btnStopDevice, &QPushButton::clicked, this, [=] {
        device_manager->stopCan();

        ui->btnStartDevice->setEnabled(true);
        ui->btnStopDevice->setEnabled(false);
    });

    connect(ui->btnCloseDevice, &QPushButton::clicked, this, [=] {
        device_manager->closeDevice();

        enableCtrl(false);
    });

    connect(ui->btnDeviceInfo, &QPushButton::clicked, this, &DeviceManagerDialog::slot_btnDeviceInfo_clicked);
}

void DeviceManagerDialog::enableCtrl(bool enabled)
{
    ui->comboDeviceType->setEnabled(!enabled);
    ui->comboDeviceIndex->setEnabled(!enabled);
    ui->btnOpenDevice->setEnabled(!enabled);
    ui->labChannel->setVisible(enabled);
    ui->comboChannelIndex->setVisible(enabled);

    ui->btnStartDevice->setVisible(enabled);
    ui->btnStopDevice->setVisible(enabled);
    ui->btnCloseDevice->setVisible(enabled);
    ui->btnDeviceInfo->setVisible(enabled);

    ui->btnStopDevice->setEnabled(!enabled);
    ui->btnCloseDevice->setEnabled(enabled);
}

void DeviceManagerDialog::slot_btnDeviceInfo_clicked()
{
    const DeviceManager * const device_manager = DeviceManager::getInstance();
    const ZCAN_DEVICE_INFO *info = device_manager->getDeviceInfo();

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
    QGridLayout * const layout = qobject_cast<QGridLayout*>(msgBox.layout());
    if (layout) {
        layout->setColumnStretch(1, 2);  // 增加文本列的拉伸系数
        layout->setRowStretch(5, 10);    // 增加图标行的拉伸系数
    }

    msgBox.exec();

    delete info;
}
