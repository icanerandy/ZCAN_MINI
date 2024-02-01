#include "devicemanager.h"

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
    abit_baud_index_(2),
    dbit_baud_index_(2),
    filter_mode_(1),
    acc_code_("00000000"),
    acc_mask_("FFFFFFFF"),
    id_("00000001"),
    frame_type_index_(0),
    protocol_index_(0),
    frm_delay_time_(1000),
    frm_delay_flag_(false),
    datas_("00 01 02 03 04 05 06 07"),
    data_length_(8),
    send_type_index_(0),
    send_count_once_(1),
    send_enable_(false),
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

int DeviceManager::device_type_index()
{
    return device_type_index_;
}

CHANNEL_HANDLE DeviceManager::channel_handle()
{
    return channel_handle_;
}

bool DeviceManager::start()
{
    return start_;
}

bool DeviceManager::send_enable()
{
    return send_enable_;
}

void DeviceManager::set_abit_baud_index(int index)
{
    abit_baud_index_ = index;
}

void DeviceManager::set_dbit_baud_index(int index)
{
    dbit_baud_index_ = index;
}

void DeviceManager::set_protocol_index(int index)
{
    protocol_index_ = index;
}

void DeviceManager::set_work_mode_index(int index)
{
    work_mode_index_ = index;
}

void DeviceManager::set_resistance_enable(int index)
{
    resistance_enable_ = index;
}

void DeviceManager::set_frame_type_index(int index)
{
    frame_type_index_ = index;
}

void DeviceManager::set_send_count_once(int value)
{
    send_count_once_ = value;
}

void DeviceManager::set_id(QString &id)
{
    id_ = id;
}

void DeviceManager::set_data(QString &data)
{
    datas_ = data;
}

void DeviceManager::ChangeDeviceType(int index)
{
    device_type_index_ = index;

//    uint type = kDeviceType[device_type_index_].device_type;/* 获取设备类型 */

//    const bool cloudDevice = type==ZCAN_CLOUD;
//    const bool netcanfd = IsNetCANFD(type);
//    const bool netcan = IsNetCAN(type);
//    const bool netDevice = (netcan || netcanfd);
//    const bool tcpDevice = IsNetTCP(type);
//    const bool usbcanfd = type==ZCAN_USBCANFD_100U ||
//        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
//    const bool pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
//        type==ZCAN_PCIE_CANFD_200U || type==ZCAN_PCIE_CANFD_400U|| type==ZCAN_PCIE_CANFD_400U_EX;

//    const bool canfdDevice = usbcanfd || pciecanfd || netcanfd;
//    const bool accFilter = pciecanfd || type==ZCAN_USBCAN1 || type==ZCAN_USBCAN2;

    //队列发送支持
//    support_delay_send_ = usbcanfd || pciecanfd || netcanfd;
//    support_delay_send_mode_ = usbcanfd || pciecanfd;
//    support_get_send_mode_ = usbcanfd || pciecanfd;
//    SetCtrlStateDelaySend(support_delay_send_, support_delay_send_mode_, support_get_send_mode_);
//    ui->chkFrmDelayFlag->setChecked(Qt::Unchecked);

    //定时发送支持
//    const bool support_autosend_canfd = canfdDevice;    // CANFD 设备
//    const bool support_autosend_can = canfdDevice ;     // CANFD 设备和其他CAN设备
//    const bool support_autosend_index = (support_autosend_can && !pciecanfd);   // PCIECANFD 不支持使用索引控制定时，PCIECANFD添加一条即立即发送
//    const bool support_stop_single_autosend = usbcanfd;
//    const bool support_get_autosend_list = netcanfd;
//    SetAutoSendCtrlState(support_autosend_can, support_autosend_canfd, support_autosend_index, support_stop_single_autosend, support_get_autosend_list);
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
        qDebug("打开设备失败!");
        return false;
    }
    device_opened_ = true;
    qDebug("打开设备成功!");
    return true;
}

bool DeviceManager::InitCan()
{
    if (!device_opened_)
    {
        /* 后续提供额外信息函数 */
        qDebug("设备还没有打开");
        return false;
    }

    ZCAN_CHANNEL_INIT_CONFIG config;
    memset(&config, 0, sizeof(config));
    uint type = kDeviceType[device_type_index_].device_type;

    const bool usbcanfd = type==ZCAN_USBCANFD_100U ||
        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
    const bool pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
        type == ZCAN_PCIE_CANFD_200U || type == ZCAN_PCIE_CANFD_400U_EX;
    const bool canfdDevice = usbcanfd || pciecanfd;

    // 本地设备设置，云设备和网络设备设置请参考例程
    //设置非 canfd设备 波特率
    if (!canfdDevice && !SetBaudrate())
    {
        /* 后续提供额外信息函数 */
        qDebug("设置波特率失败!");
        return false;
    }

    if (usbcanfd)
    {
        char path[50] = {0};
        char value[100] = {0};
        snprintf(path, sizeof(path), "%d/canfd_standard", channel_index_);
        snprintf(value, sizeof(value), "%d", 0);
        ZCAN_SetValue(device_handle_, path, value);
    }
    if (usbcanfd)
    {
        /* 设置波特率 */
        if (!SetCanfdBaudrate())
        {
            qDebug("设置波特率失败!");
            return false;
        }
        config.can_type = TYPE_CANFD;
        config.canfd.mode = work_mode_index_;
        config.canfd.filter = filter_mode_;
        bool ok;
        config.canfd.acc_code = acc_mask_.toUInt(&ok, 16);
        config.canfd.acc_mask = acc_mask_.toUInt(&ok, 16);
    }
    else if (pciecanfd)
    {
        char path[50] = { 0 };
        char value[100] = { 0 };
        if (!SetCanfdBaudrate())
        {
            qDebug("设置波特率失败!");
            return false;
        }

        if (type == ZCAN_PCIE_CANFD_400U_EX )
        {
            snprintf(path, sizeof(path), "0/set_device_recv_merge");
            snprintf(value, sizeof(value), "0");
            ZCAN_SetValue(device_handle_, path, value);
        }

        config.can_type = TYPE_CANFD;
        config.canfd.mode = work_mode_index_;
        config.canfd.filter = filter_mode_;
        bool ok;
        config.canfd.acc_code = acc_mask_.toUInt(&ok, 16);
        config.canfd.acc_mask = acc_mask_.toUInt(&ok, 16);
    }
    else
    {
        config.can_type = TYPE_CAN;
        config.can.mode = work_mode_index_;
        config.can.filter = filter_mode_;
        bool ok;
        config.canfd.acc_code = acc_mask_.toUInt(&ok, 16);
        config.canfd.acc_mask = acc_mask_.toUInt(&ok, 16);
    }

    /* 初始化 CAN */
    channel_handle_ = ZCAN_InitCAN(device_handle_, channel_index_, &config);
    if (INVALID_CHANNEL_HANDLE == channel_handle_)
    {
        qDebug("初始化CAN通道失败!");
        return false;
    }
    if (usbcanfd)
    {
        if (resistance_enable_ && !SetResistanceEnable())
        {
            qDebug("设置终端电阻失败!");
            return false;
        }
    }
    qDebug("初始化CAN通道成功!");
    return true;
}

bool DeviceManager::StartCan()
{
    if (ZCAN_StartCAN(channel_handle_) != STATUS_OK)
    {
        qDebug("启动CAN通道失败!");
        return false;
    }
    start_ = true;
    qDebug("启动CAN通道成功!");

    /* 启动消息接收线程 */
    RecMsgThread *rec_msg_thread = RecMsgThread::GetInstance();
    rec_msg_thread->start();
    rec_msg_thread->beginThread();

    return true;
}

bool DeviceManager::SendMsg()
{
    if (datas_.isEmpty())
    {
        qDebug("数据为空");
        return false;
    }

    if (0 == protocol_index_)//can
    {
//        ZCAN_AUTO_TRANSMIT_OBJ autoObj;
//        memset(&autoObj, 0, sizeof(autoObj));
//        autoObj.enable = send_enable_;
//        autoObj.interval = auto_send_period_;
//        autoObj.index = auto_send_index_;

        ZCAN_Transmit_Data can_data/* = autoObj.obj*/;

        /* 设置CAN帧 */
        bool ok = false;
        uint id = id_.toUInt(&ok, 16);
        frm_delay_flag_ = true;
        uint frm_delay_time = frm_delay_time_;

        memset(&can_data, 0, sizeof(can_data));
        can_data.frame.can_id = MAKE_CAN_ID(id, frame_type_index_, 0, 0);
        split(can_data.frame.data, CAN_MAX_DLEN, datas_, ' ', 16);
        can_data.frame.can_dlc = data_length_;
        can_data.transmit_type = send_type_index_;
        if (frm_delay_flag_)
        {
            can_data.frame.__pad |= TX_DELAY_SEND_FLAG;
            can_data.frame.__res0 = static_cast<uint8_t>(static_cast<uint32_t>(frm_delay_time) & 0xff);
            can_data.frame.__res1 = static_cast<uint8_t>((static_cast<uint32_t>(frm_delay_time)>>8) & 0xff);
        }

//        char path[50] = {0};
//        snprintf(path, sizeof("%d/auto_send"), "%d/auto_send", channel_index_);
//        int nRet = ZCAN_SetValue(device_handle_, path, (const char*)&autoObj);

//        if (send_enable())
//        {
//            char path[50] = {0};
//            char value[50] = {0};
//            snprintf(path, sizeof("%d/apply_auto_send"), "%d/apply_auto_send", channel_index_);
//            int nRet = ZCAN_SetValue(device_handle_, path, "0");
//        }
//        else
//        {
//            char path[50] = {0};
//            char value[50] = {0};
//            snprintf(path, sizeof("%d/clear_auto_send"), "%d/apply_auto_send", channel_index_);
//            int nRet = ZCAN_SetValue(device_handle_, path, "0");
//        }

//        ZCAN_Transmit(channel_handle_, &can_data, 1);
        SendMsgThread *sendmsg_thread = new SendMsgThread(QVariant::fromValue(can_data), send_count_once_, send_count_, frm_delay_time);
        sendmsg_thread->start();
        sendmsg_thread->beginThread();
    }
    else//canfd
    {
//        ZCANFD_AUTO_TRANSMIT_OBJ autoObj;
//        memset(&autoObj, 0, sizeof(autoObj));
//        autoObj.enable = send_enable_;
//        autoObj.interval = auto_send_period_;
//        autoObj.index = auto_send_index_;

        ZCAN_TransmitFD_Data canfd_data/* = autoObj.obj*/;

        /* 设置CANFD帧 */
        bool ok = false;
        uint id = id_.toUInt(&ok, 16);
        frm_delay_flag_ = true;
        uint frm_delay_time = frm_delay_time_;

        memset(&canfd_data, 0, sizeof(canfd_data));
        canfd_data.frame.can_id = MAKE_CAN_ID(id, frame_type_index_, 0, 0);
        split(canfd_data.frame.data, CANFD_MAX_DLEN, datas_, ' ', 16);
        canfd_data.frame.len = data_length_;
        canfd_data.transmit_type = send_type_index_;
        canfd_data.frame.flags |= (2==protocol_index_) ? CANFD_BRS : 0;
        if (frm_delay_flag_)
        {
            canfd_data.frame.flags |= TX_DELAY_SEND_FLAG;
            canfd_data.frame.__res0 = static_cast<uint8_t>(static_cast<uint32_t>(frm_delay_time) & 0xff);
            canfd_data.frame.__res1 = static_cast<uint8_t>((static_cast<uint32_t>(frm_delay_time)>>8) & 0xff);
        }

//        char path[50] = {0};
//        snprintf(path, sizeof("%d/auto_send_canfd"), "%d/auto_send_canfd", channel_index_);
//        int nRet = ZCAN_SetValue(device_handle_, path, (const char*)&autoObj);

//        if (send_enable())
//        {
//            char path[50] = {0};
//            char value[50] = {0};
//            snprintf(path, sizeof("%d/apply_auto_send"), "%d/apply_auto_send", channel_index_);
//            int nRet = ZCAN_SetValue(device_handle_, path, "0");
//        }
//        else
//        {
//            char path[50] = {0};
//            char value[50] = {0};
//            snprintf(path, sizeof("%d/clear_auto_send"), "%d/apply_auto_send", channel_index_);
//            int nRet = ZCAN_SetValue(device_handle_, path, "0");
//        }

        SendMsgThread *sendmsg_thread = new SendMsgThread(QVariant::fromValue(canfd_data), send_count_once_, send_count_, frm_delay_time);
        sendmsg_thread->start();
        sendmsg_thread->beginThread();
    }
}

bool DeviceManager::StopCan()
{
    if (ZCAN_ResetCAN(channel_handle_) != STATUS_OK)
    {
        qDebug("复位失败!");
        return false;
    }
    start_ = false;
    qDebug("复位成功!");
    return true;
}

bool DeviceManager::CloseDevice()
{
    ZCAN_ResetCAN(channel_handle_);
    ZCAN_CloseDevice(device_handle_);
    start_ = false;
    device_opened_ = false;
    qDebug("关闭设备成功!");
    return true;
}

ZCAN_DEVICE_INFO *DeviceManager::GetDeviceInfo()
{
    ZCAN_DEVICE_INFO *info = new ZCAN_DEVICE_INFO();

    ZCAN_GetDeviceInf(device_handle_, info);

    return info;
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

bool DeviceManager::SetBaudrate()
{
    char path[50] = {0};
    snprintf(path, sizeof(path), "%d/baud_rate", channel_index_);
    char value[10] = {0};
    snprintf(value, sizeof(value), "%d", kBaudrate[abit_baud_index_]);

    return 1 == ZCAN_SetValue(device_handle_, path, value);
}

bool DeviceManager::SetCanfdBaudrate()
{
    char path[50] = { 0 };
    snprintf(path, sizeof(path), "%d/canfd_abit_baud_rate", channel_index_);
    char value[10] = { 0 };
    snprintf(value, sizeof(value), "%d", kAbitTimingUSB[abit_baud_index_]);
    int ret_a = ZCAN_SetValue(device_handle_, path, value);

    snprintf(path, sizeof(path), "%d/canfd_dbit_baud_rate", channel_index_);
    snprintf(value, sizeof(value), "%d", kDbitTimingUSB[dbit_baud_index_]);
    int ret_d = ZCAN_SetValue(device_handle_, path, value);
    return 1 == (ret_a&&ret_d);
}

bool DeviceManager::SetResistanceEnable()
{
    char path[50] = {0};
    snprintf(path, sizeof(path), "%d/initenal_resistance", channel_index_);
    char value[10] = {0};
    snprintf(value, sizeof(value),"%d", resistance_enable_);
    return 1 == ZCAN_SetValue(device_handle_, path, value);
}

void DeviceManager::set_frm_delay_time(int value)
{
    frm_delay_time_ = value;
}

void DeviceManager::set_data_length(int value)
{
    data_length_ = value;
}

void DeviceManager::set_send_type_index(int index)
{
    send_type_index_ = index;
}

void DeviceManager::set_send_count(int value)
{
    send_count_ = value;
}

void DeviceManager::set_send_enable(bool enable)
{
    send_enable_ = enable;
}

//对src根据xx进行拆分, base是进制,10:十进制, 16:16进制
size_t DeviceManager::split(BYTE *dst, size_t max_len, const QString &src, char xx, int base)
{
    if (0 == max_len || nullptr == dst || src.isEmpty()) return 0;
    QStringList items;
    items = src.split(xx);
    int count = items.size();
    if (count > 0)
    {
        count = count > max_len ? max_len : count;
        for (size_t i = 0; i < count; ++i)
        {
            dst[i] = (BYTE)items[i].toUInt(nullptr, base);
        }
    }
    return count;
}
