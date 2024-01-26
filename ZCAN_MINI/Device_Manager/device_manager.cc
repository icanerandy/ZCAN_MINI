#include "device_manager.h"

/**
 * @brief DeviceManager::getInstance    局部静态的方式实现单例类
 * @return
 */
DeviceManager *DeviceManager::GetInstance()
{
    static DeviceManager deviceManager;
    return &deviceManager;
}

DeviceManager::DeviceManager(QObject *parent) : QObject(parent),
    device_type_index_(0),
    device_index_(0),
    channel_index_(0),
    work_mode_index_(0),
    resistance_enable_(true),
    baud_index_(0),
    abit_baud_index_(0),
    dbit_baud_index_(0),
    filter_mode_(1),
    acc_code_("00000000"),
    acc_mask_("FFFFFFFF"),
    id_("00000001"),
    frame_type_index_(0),
    protocol_index_(1),
    canfd_exp_index_(1),
    frm_delay_time(1000),
    frm_delay_flag(false),
    datas_("00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63"),
    send_type_index_(0),
    send_count_once_(10),
    auto_send_index_(0),
    auto_send_period_(1000)
{
    /* 初始化相关数据 */
    device_opened_ = false;
    start_ = false;
    // property_ = NULL;
    support_delay_send_ = false;
    support_delay_send_mode_ = false;
    support_get_send_mode_ = false;
}

void DeviceManager::ChangeDeviceType(int index)
{
    device_type_index_ = index;
    // InitIndexComboBox(ui->comboChannelIndex, 0, kDeviceType[device_type_index_].channel_count, 0);/* 根据设备类型设置相关通道数 */
    uint type = kDeviceType[device_type_index_].device_type;/* 获取设备类型 */

    const bool cloudDevice = type==ZCAN_CLOUD;
    const bool netcanfd = IsNetCANFD(type);
    const bool netcan = IsNetCAN(type);
    const bool netDevice = (netcan || netcanfd);
    const bool tcpDevice = IsNetTCP(type);
    const bool usbcanfd = type==ZCAN_USBCANFD_100U ||
        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
    const bool pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
        type==ZCAN_PCIE_CANFD_200U || type==ZCAN_PCIE_CANFD_400U|| type==ZCAN_PCIE_CANFD_400U_EX;

    const bool canfdDevice = usbcanfd || pciecanfd || netcanfd;
    const bool accFilter = pciecanfd || type==ZCAN_USBCAN1 || type==ZCAN_USBCAN2;

    //队列发送支持
    support_delay_send_ = usbcanfd || pciecanfd || netcanfd;
    support_delay_send_mode_ = usbcanfd || pciecanfd;
    support_get_send_mode_ = usbcanfd || pciecanfd;
    //SetCtrlStateDelaySend(support_delay_send_, support_delay_send_mode_, support_get_send_mode_);
    //ui->chkFrmDelayFlag->setChecked(Qt::Unchecked);

    //定时发送支持
    const bool support_autosend_canfd = canfdDevice;    // CANFD 设备
    const bool support_autosend_can = canfdDevice ;     // CANFD 设备和其他CAN设备
    const bool support_autosend_index = (support_autosend_can && !pciecanfd);   // PCIECANFD 不支持使用索引控制定时，PCIECANFD添加一条即立即发送
    const bool support_stop_single_autosend = usbcanfd;
    const bool support_get_autosend_list = netcanfd;
    //SetAutoSendCtrlState(support_autosend_can, support_autosend_canfd, support_autosend_index, support_stop_single_autosend, support_get_autosend_list);

//    if (usbcanfd)
//    {
//        ui->comboAbit->clear();
//        QStringList strList;
//        strList << "1Mbps" << "800kbps" << "500kbps" << "250kbps" << "125kbps" << "100kbps" << "50kbps";
//        ui->comboAbit->addItems(strList);

//        ui->comboDbit->clear();
//        strList.clear();
//        strList << "5Mbps" << "4Mbps" << "2Mbps" << "1Mbps";
//        ui->comboDbit->addItems(strList);
//    }
//    else if (pciecanfd)
//    {
//        ui->comboAbit->clear();
//        QStringList strList;
//        strList << "1Mbps(80%)" << "800kbps(80%)" << "500kbps(80%)" << "250kbps(80%)" << "125kbps(80%)" << "100kbps" << "50kbps";
//        ui->comboAbit->addItems(strList);

//        ui->comboDbit->clear();
//        strList.clear();
//        strList << "5Mbps(80%)" << "4Mbps(80%)" << "2Mbps(80%)" << "1Mbps(80%)";
//        ui->comboDbit->addItems(strList);
//    }

//    /* 设置组件使能 */
//    ui->comboDeviceMode->setEnabled(!cloudDevice && !netDevice);
//    ui->chkResistance->setEnabled(usbcanfd);
//    ui->comboBaud->setEnabled(!canfdDevice && !netDevice && !cloudDevice);
//    ui->comboAbit->setEnabled(canfdDevice && !netDevice && !cloudDevice);
//    ui->comboDbit->setEnabled(canfdDevice && !netDevice && !cloudDevice);
//    ui->comboFilterMode->setEnabled(accFilter && !cloudDevice && !netDevice);
//    ui->editAccCode->setEnabled(accFilter && !cloudDevice && !netDevice);
    //    ui->editAccMask->setEnabled(accFilter && !cloudDevice && !netDevice);
}

void DeviceManager::ChangeDeviceIndex(int index)
{
    device_index_ = index;
}

bool DeviceManager::OpenDevice()
{
    device_handle_ = ZCAN_OpenDevice(kDeviceType[device_type_index_].device_type, device_index_, 0);/* 打开设备 */
    if (INVALID_DEVICE_HANDLE == device_handle_)
    {
        return false;
    }
    device_opened_ = true;
    // EnableCtrl(true);
    return true;
}

bool DeviceManager::IsNetCAN( uint type )
{
    return (type==ZCAN_CANETUDP || type==ZCAN_CANETTCP || type==ZCAN_WIFICAN_TCP || type==ZCAN_WIFICAN_UDP ||
            type==ZCAN_CANDTU_NET || type==ZCAN_CANDTU_NET_400);
}

bool DeviceManager::IsNetCANFD( uint type )
{
    return (type==ZCAN_CANFDNET_TCP || type==ZCAN_CANFDNET_UDP ||
        type==ZCAN_CANFDNET_400U_TCP || type==ZCAN_CANFDNET_400U_UDP ||
        type==ZCAN_CANFDWIFI_TCP || type==ZCAN_CANFDWIFI_UDP);
}

bool DeviceManager::IsNetTCP( uint type )
{
    return (type==ZCAN_CANETTCP || type==ZCAN_WIFICAN_TCP || type==ZCAN_CANDTU_NET || type==ZCAN_CANDTU_NET_400 ||
        type==ZCAN_CANFDNET_TCP || type==ZCAN_CANFDNET_400U_TCP ||type==ZCAN_CANFDWIFI_TCP );
}

bool DeviceManager::IsNetUDP( uint type )
{
    return (type==ZCAN_CANETUDP || type==ZCAN_WIFICAN_UDP ||
            type==ZCAN_CANFDNET_UDP || type==ZCAN_CANFDNET_400U_UDP ||type==ZCAN_CANFDWIFI_UDP);
}
