#include "devicemanager.h"

const DeviceManager::DeviceInfo DeviceManager::kDeviceType[] = {
    {ZCAN_USBCAN1, 1},
    {ZCAN_USBCAN2, 2},
    {ZCAN_PCI9820I,2},
    {ZCAN_USBCAN_E_U, 1},
    {ZCAN_USBCAN_2E_U, 2},
    {ZCAN_USBCAN_4E_U, 4},
    {ZCAN_PCIE_CANFD_100U, 1},
    {ZCAN_PCIE_CANFD_200U, 2},
    {ZCAN_PCIE_CANFD_400U_EX, 4 },
    {ZCAN_USBCANFD_200U, 2},
    {ZCAN_USBCANFD_100U, 1},
    {ZCAN_USBCANFD_MINI, 1},
    {ZCAN_CANETTCP, 1},
    {ZCAN_CANETUDP, 1},
    {ZCAN_WIFICAN_TCP, 1},
    {ZCAN_WIFICAN_UDP, 1},
    {ZCAN_CLOUD, 1},
    {ZCAN_CANFDWIFI_TCP, 1},
    {ZCAN_CANFDWIFI_UDP, 1},
    {ZCAN_CANFDNET_TCP, 2},
    {ZCAN_CANFDNET_UDP, 2},
    {ZCAN_CANFDNET_400U_TCP, 4},
    {ZCAN_CANFDNET_400U_UDP, 4},
};

const uint DeviceManager::kAbitTimingUSB[] = {
    1000000,//1Mbps
    800000,//800kbps
    500000,//500kbps
    250000,//250kbps
    125000,//125kbps
    100000,//100kbps
    50000 //50kbps
};

const uint DeviceManager::kDbitTimingUSB[] = {
    5000000,//5Mbps
    4000000,//4Mbps
    2000000,//2Mbps
    1000000 //1Mbps
};

const uint DeviceManager::kAbitTimingPCIE[] = {
    1000000, //1M(80%)
    800000, //800K(80%)
    500000, //500K(80%)
    250000, //250K(80%)
    125000  //125K(80%)
};

const uint DeviceManager::kDbitTimingPCIE[] = {
    8000000, //8Mbps(80%)
    5000000, //5Mbps(75%)
    5000000, //5Mbps(87.5%)
    4000000, //4Mbps(80%)
    2000000, //2Mbps(80%)
    1000000  //1Mbps(80%)
};

const uint DeviceManager::kBaudrate[] = {
    1000000,
    800000,
    500000,
    250000,
    125000,
    100000,
    50000,
    20000,
    10000,
    5000
};

/**
 * @brief DeviceManager::getInstance    局部静态的方式实现单例类
 * @return
 */
DeviceManager *DeviceManager::getInstance()
{
    static DeviceManager deviceManager;
    return &deviceManager;
}

DeviceManager::DeviceManager(QObject *parent) : QObject(parent),
    device_type_index_(DeviceTypeIndex::zCAN_USBCAN1),
    device_index_(0),
    channel_index_(0),
    work_mode_(WorkMode::Normal),
    resistance_enable_(Enable::Enabled),
    abit_baud_index_(2),
    dbit_baud_index_(2),
    canfd_standard_type_(StandardType::Iso),
    id_(0),
    frame_type_(FrameType::Can),
    protocol_type_(ProtocolType::Can),
    dlc_(8),
    datas_("00 01 02 03 04 05 06 07"),
    send_type_(SendType::Normal),
    send_count_once_(1),
    send_count_(1),
    frm_delay_flag_(false),
    frm_delay_time_(0),
    support_delay_send_(false),
    support_delay_send_mode_(false),
    support_get_send_mode_(false),
    send_enable_(Enable::Unenabled),
    auto_send_index_(0),
    auto_send_period_(1000),
    filter_mode_(1),
    acc_code_("00000000"),
    acc_mask_("FFFFFFFF"),
    device_opened_(DeviceState::Unopened),
    can_start_(CanState::Unstarted),
    sendmsg_thread_(nullptr)
{
    /* 初始化相关数据 */
    device_opened_ = DeviceState::Unopened;
    can_start_ = CanState::Unstarted;
    // property_ = NULL;
    support_delay_send_ = false;
    support_delay_send_mode_ = false;
    support_get_send_mode_ = false;
}

DeviceManager::~DeviceManager()
{
    RecMsgThread* rec_msg_thread = RecMsgThread::getInstance();
    rec_msg_thread->stopThread();
}

DeviceManager::DeviceTypeIndex DeviceManager::device_type_index() const
{
    return device_type_index_;
}

CHANNEL_HANDLE DeviceManager::channel_handle() const
{
    return channel_handle_;
}

DeviceManager::CanState DeviceManager::can_start() const
{
    return can_start_;
}

DeviceManager::Enable DeviceManager::send_enable() const
{
    return send_enable_;
}

DeviceManager::StandardType DeviceManager::canfd_standard_type() const
{
    return canfd_standard_type_;
}

void DeviceManager::set_abit_baud_index(uint index)
{
    abit_baud_index_ = index;
}

void DeviceManager::set_dbit_baud_index(uint index)
{
    dbit_baud_index_ = index;
}

void DeviceManager::set_canfd_standard_type(DeviceManager::StandardType type)
{
    canfd_standard_type_ = type;
}

void DeviceManager::set_protocol_index(DeviceManager::ProtocolType type)
{
    protocol_type_ = type;
}

void DeviceManager::set_work_mode_index(DeviceManager::WorkMode mode)
{
    work_mode_ = mode;
}

void DeviceManager::set_resistance_enable(DeviceManager::Enable type)
{
    resistance_enable_ = type;
}

void DeviceManager::set_frame_type_index(DeviceManager::FrameType type)
{
    frame_type_ = type;
}

void DeviceManager::set_send_count_once(uint value)
{
    send_count_once_ = value;
}

void DeviceManager::set_id(uint id)
{
    id_ = id;
}

void DeviceManager::set_data(QString &data)
{
    datas_ = data;
}

void DeviceManager::slot_deviceType_changed(DeviceManager::DeviceTypeIndex index)
{
    device_type_index_ = index;

//    uint type = kDeviceType[static_cast<uint>(device_type_index_)].device_type;/* 获取设备类型 */

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

//    // 队列发送支持
//    support_delay_send_ = usbcanfd || pciecanfd || netcanfd;
//    support_delay_send_mode_ = usbcanfd || pciecanfd;
//    support_get_send_mode_ = usbcanfd || pciecanfd;
//    SetCtrlStateDelaySend(support_delay_send_, support_delay_send_mode_, support_get_send_mode_);
//    ui->chkFrmDelayFlag->setChecked(Qt::Unchecked);

//    // 定时发送支持
//    const bool support_autosend_canfd = canfdDevice;    // CANFD 设备
//    const bool support_autosend_can = canfdDevice ;     // CANFD 设备和其他CAN设备
//    const bool support_autosend_index = (support_autosend_can && !pciecanfd);   // PCIECANFD 不支持使用索引控制定时，PCIECANFD添加一条即立即发送
//    const bool support_stop_single_autosend = usbcanfd;
//    const bool support_get_autosend_list = netcanfd;
//    SetAutoSendCtrlState(support_autosend_can, support_autosend_canfd, support_autosend_index, support_stop_single_autosend, support_get_autosend_list);
}

void DeviceManager::changeDeviceIndex(uint index)
{
    device_index_ = index;
}

bool DeviceManager::openDevice()
{
    if (DeviceState::Opened == device_opened_)
        return true;

    const uint type = kDeviceType[static_cast<uint>(device_type_index_)].device_type;
    device_handle_ = ZCAN_OpenDevice(type, device_index_, 0);
    if (INVALID_DEVICE_HANDLE == device_handle_)
    {
        qDebug() << "打开设备失败!";
        /* 启动消息接收线程 */
        RecMsgThread * const rec_msg_thread = RecMsgThread::getInstance();
        connect(this, &DeviceManager::sig_channelHandle, rec_msg_thread, &RecMsgThread::slot_channelHandle);
        emit sig_channelHandle(channel_handle_);

        CanFrameTableModel* const canframe_table_model = CanFrameTableModel::GetInstance();
        connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data*, const uint)>(&RecMsgThread::sig_newMsg),
                canframe_table_model, static_cast<void (CanFrameTableModel::*)(const ZCAN_Receive_Data*, const uint)>(&CanFrameTableModel::slot_newMsg));
        connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&RecMsgThread::sig_newMsg),
                canframe_table_model, static_cast<void (CanFrameTableModel::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&CanFrameTableModel::slot_newMsg));
        canframe_table_thread_ = new QThread;
        canframe_table_model->moveToThread(canframe_table_thread_);
        canframe_table_thread_->start();

        rec_msg_thread->start();
        rec_msg_thread->beginThread();
        return false;
    }
    device_opened_ = DeviceState::Opened;
    qDebug() << "打开设备成功!";
    return true;
}

bool DeviceManager::initCan()
{
    if (DeviceState::Unopened == device_opened_)
    {
        qDebug() << "初始化CAN通道: 设备还没有打开!";
        return false;
    }

    ZCAN_CHANNEL_INIT_CONFIG config;
    memset(&config, 0, sizeof(config));
    uint type = kDeviceType[static_cast<uint>(device_type_index_)].device_type;

    const bool usbcanfd = type==ZCAN_USBCANFD_100U ||
        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
    const bool pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
        type == ZCAN_PCIE_CANFD_200U || type == ZCAN_PCIE_CANFD_400U_EX;
    const bool canfdDevice = usbcanfd || pciecanfd;

    // 本地设备设置，云设备和网络设备设置请参考例程
    //设置非 canfd设备 波特率
    if (!canfdDevice && !setBaudrate())
    {
        qDebug() << "初始化CAN通道: 设置波特率失败!";
        return false;
    }

    if (usbcanfd)
    {
        char path[50] = {0};
        char value[100] = {0};
        snprintf(path, sizeof(path), "%d/canfd_standard", channel_index_);
        snprintf(value, sizeof(value), "%d", static_cast<int>(canfd_standard_type_));
        ZCAN_SetValue(device_handle_, path, value);
    }

    if (usbcanfd)
    {
        if (!setCanfdBaudrate())
        {
            qDebug() << "初始化CAN通道: 设置波特率失败!";
            return false;
        }
        config.can_type = TYPE_CANFD;
        config.canfd.mode = static_cast<BYTE>(work_mode_);
        config.canfd.filter = filter_mode_;
        bool ok;
        config.canfd.acc_code = acc_mask_.toUInt(&ok, 16);
        config.canfd.acc_mask = acc_mask_.toUInt(&ok, 16);
    }
    else if (pciecanfd)
    {
        char path[50] = { 0 };
        char value[100] = { 0 };
        if (!setCanfdBaudrate())
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
        config.canfd.mode = static_cast<BYTE>(work_mode_);
        config.canfd.filter = filter_mode_;
        bool ok;
        config.canfd.acc_code = acc_mask_.toUInt(&ok, 16);
        config.canfd.acc_mask = acc_mask_.toUInt(&ok, 16);
    }
    else
    {
        config.can_type = TYPE_CAN;
        config.can.mode = static_cast<BYTE>(work_mode_);
        config.can.filter = filter_mode_;
        bool ok;
        config.canfd.acc_code = acc_mask_.toUInt(&ok, 16);
        config.canfd.acc_mask = acc_mask_.toUInt(&ok, 16);
    }

    channel_handle_ = ZCAN_InitCAN(device_handle_, channel_index_, &config);
    if (INVALID_CHANNEL_HANDLE == channel_handle_)
    {
        qDebug() << "初始化CAN通道: 失败!";
        return false;
    }
    if (usbcanfd)
    {
        if (Enable::Enabled == resistance_enable_ && !setResistanceEnable())
        {
            qDebug() << "设置终端电阻: 失败!";
            return false;
        }
    }
    qDebug() << "初始化CAN通道: 成功!";
    return true;
}

bool DeviceManager::startCan()
{
    if (STATUS_OK != ZCAN_StartCAN(channel_handle_))
    {
        qDebug() << "启动CAN通道: 失败!";
        return false;
    }
    can_start_ = CanState::Started;
    qDebug() << "启动CAN通道: 成功!";

    /* 启动消息接收线程 */
    RecMsgThread * const rec_msg_thread = RecMsgThread::getInstance();
    connect(this, &DeviceManager::sig_channelHandle, rec_msg_thread, &RecMsgThread::slot_channelHandle);
    emit sig_channelHandle(channel_handle_);

    CanFrameTableModel* const canframe_table_model = CanFrameTableModel::GetInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data*, const uint)>(&RecMsgThread::sig_newMsg),
            canframe_table_model, static_cast<void (CanFrameTableModel::*)(const ZCAN_Receive_Data*, const uint)>(&CanFrameTableModel::slot_newMsg));
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&RecMsgThread::sig_newMsg),
            canframe_table_model, static_cast<void (CanFrameTableModel::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&CanFrameTableModel::slot_newMsg));
    canframe_table_thread_ = new QThread;
    canframe_table_model->moveToThread(canframe_table_thread_);
    canframe_table_thread_->start();

    rec_msg_thread->start();
    rec_msg_thread->beginThread();

    return true;
}

void DeviceManager::sendMsg()
{
    if (datas_.isEmpty())
    {
        qDebug() << "数据发送: 数据为空!";
        return;
    }

    if (ProtocolType::Can == protocol_type_)
    {
//        ZCAN_AUTO_TRANSMIT_OBJ autoObj;
//        memset(&autoObj, 0, sizeof(autoObj));
//        autoObj.enable = send_enable_;
//        autoObj.interval = auto_send_period_;
//        autoObj.index = auto_send_index_;

        ZCAN_Transmit_Data can_data/* = autoObj.obj*/;

        frm_delay_flag_ = true;

        memset(&can_data, 0, sizeof(can_data));
        can_data.frame.can_id = MAKE_CAN_ID(id_, static_cast<BYTE>(frame_type_), 0, 0);
        split(can_data.frame.data, CAN_MAX_DLEN, datas_, ' ', 16);
        can_data.frame.can_dlc = dlc_;
        can_data.transmit_type = static_cast<uint>(send_type_);
        if (frm_delay_flag_)
        {
            can_data.frame.__pad |= TX_DELAY_SEND_FLAG;
            uint frm_delay_time = frm_delay_time_;
            can_data.frame.__res0 = static_cast<BYTE>(frm_delay_time & 0xff);
            can_data.frame.__res1 = static_cast<BYTE>(((frm_delay_time)>>8) & 0xff);
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
        sendmsg_thread_ = new SendMsgThread(channel_handle_, QVariant::fromValue(can_data), send_count_once_, send_count_);
        sendmsg_thread_->start();
        sendmsg_thread_->beginThread();
    }
    else//canfd
    {
//        ZCANFD_AUTO_TRANSMIT_OBJ autoObj;
//        memset(&autoObj, 0, sizeof(autoObj));
//        autoObj.enable = send_enable_;
//        autoObj.interval = auto_send_period_;
//        autoObj.index = auto_send_index_;

        ZCAN_TransmitFD_Data canfd_data/* = autoObj.obj*/;

        frm_delay_flag_ = true;

        memset(&canfd_data, 0, sizeof(canfd_data));
        canfd_data.frame.can_id = MAKE_CAN_ID(id_, static_cast<BYTE>(frame_type_), 0, 0);
        split(canfd_data.frame.data, CANFD_MAX_DLEN, datas_, ' ', 16);
        canfd_data.frame.len = dlc_;
        canfd_data.transmit_type = static_cast<uint>(send_type_);
        canfd_data.frame.flags |= (ProtocolType::CanFdBrs==protocol_type_) ? CANFD_BRS : 0;
        if (frm_delay_flag_)
        {
            canfd_data.frame.flags |= TX_DELAY_SEND_FLAG;
            uint frm_delay_time = frm_delay_time_;
            canfd_data.frame.__res0 = static_cast<BYTE>(frm_delay_time & 0xff);
            canfd_data.frame.__res1 = static_cast<BYTE>(((frm_delay_time)>>8) & 0xff);
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

        sendmsg_thread_ = new SendMsgThread(channel_handle_, QVariant::fromValue(canfd_data), send_count_once_, send_count_);
        sendmsg_thread_->start();
        sendmsg_thread_->beginThread();
    }
}

void DeviceManager::stopSendMsg()
{
    if (sendmsg_thread_->isRunning())
    {
        sendmsg_thread_->stopThread();
        sendmsg_thread_->wait();
    }
    sendmsg_thread_ = nullptr;
}

bool DeviceManager::stopCan()
{
    RecMsgThread * const rec_msg_thread = RecMsgThread::getInstance();
    CanFrameTableModel* const canframe_table_model = CanFrameTableModel::GetInstance();
    if (rec_msg_thread->isRunning())
    {
        disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data*, const uint)>(&RecMsgThread::sig_newMsg),
                   canframe_table_model, static_cast<void (CanFrameTableModel::*)(const ZCAN_Receive_Data*, const uint)>(&CanFrameTableModel::slot_newMsg));
        disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&RecMsgThread::sig_newMsg),
                   canframe_table_model, static_cast<void (CanFrameTableModel::*)(const ZCAN_ReceiveFD_Data*, const uint)>(&CanFrameTableModel::slot_newMsg));

        rec_msg_thread->stopThread();
        rec_msg_thread->wait();

        canframe_table_thread_->quit();
        canframe_table_thread_->wait();
    }

    if (STATUS_OK != ZCAN_ResetCAN(channel_handle_))
    {
        qDebug() << "CAN通道复位: 失败!";
        return false;
    }
    can_start_ = CanState::Unstarted;
    qDebug() << "CAN通道复位: 成功!";
    return true;
}

bool DeviceManager::closeDevice()
{
    RecMsgThread *rec_msg_thread = RecMsgThread::getInstance();
    if (rec_msg_thread->isRunning())
    {
        rec_msg_thread->stopThread();
        rec_msg_thread->wait();
    }

    ZCAN_ResetCAN(channel_handle_);
    ZCAN_CloseDevice(device_handle_);
    can_start_ = CanState::Unstarted;
    device_opened_ = DeviceState::Unopened;
    qDebug() << "关闭设备成功!";
    return true;
}

const ZCAN_DEVICE_INFO *DeviceManager::getDeviceInfo() const
{
    ZCAN_DEVICE_INFO * const info = new ZCAN_DEVICE_INFO();

    ZCAN_GetDeviceInf(device_handle_, info);

    return info;
}

bool DeviceManager::isNetCAN(uint type)
{
    return (type==ZCAN_CANETUDP || type==ZCAN_CANETTCP || type==ZCAN_WIFICAN_TCP || type==ZCAN_WIFICAN_UDP ||
            type==ZCAN_CANDTU_NET || type==ZCAN_CANDTU_NET_400);
}

bool DeviceManager::isNetCANFD(uint type)
{
    return (type==ZCAN_CANFDNET_TCP || type==ZCAN_CANFDNET_UDP ||
        type==ZCAN_CANFDNET_400U_TCP || type==ZCAN_CANFDNET_400U_UDP ||
        type==ZCAN_CANFDWIFI_TCP || type==ZCAN_CANFDWIFI_UDP);
}

bool DeviceManager::isNetTCP(uint type)
{
    return (type==ZCAN_CANETTCP || type==ZCAN_WIFICAN_TCP || type==ZCAN_CANDTU_NET || type==ZCAN_CANDTU_NET_400 ||
        type==ZCAN_CANFDNET_TCP || type==ZCAN_CANFDNET_400U_TCP ||type==ZCAN_CANFDWIFI_TCP );
}

bool DeviceManager::isNetUDP(uint type)
{
    return (type==ZCAN_CANETUDP || type==ZCAN_WIFICAN_UDP ||
            type==ZCAN_CANFDNET_UDP || type==ZCAN_CANFDNET_400U_UDP ||type==ZCAN_CANFDWIFI_UDP);
}

bool DeviceManager::setBaudrate()
{
    char path[50] = {0};
    snprintf(path, sizeof(path), "%d/baud_rate", channel_index_);
    char value[10] = {0};
    snprintf(value, sizeof(value), "%d", kBaudrate[abit_baud_index_]);

    return 1 == ZCAN_SetValue(device_handle_, path, value);
}

bool DeviceManager::setCanfdBaudrate()
{
    char path[50] = { 0 };
    snprintf(path, sizeof(path), "%d/canfd_abit_baud_rate", channel_index_);
    char value[10] = { 0 };
    snprintf(value, sizeof(value), "%d", kAbitTimingUSB[abit_baud_index_]);
    uint ret_a = ZCAN_SetValue(device_handle_, path, value);

    snprintf(path, sizeof(path), "%d/canfd_dbit_baud_rate", channel_index_);
    snprintf(value, sizeof(value), "%d", kDbitTimingUSB[dbit_baud_index_]);
    uint ret_d = ZCAN_SetValue(device_handle_, path, value);
    return 1 == (ret_a&&ret_d);
}

bool DeviceManager::setResistanceEnable()
{
    char path[50] = {0};
    snprintf(path, sizeof(path), "%d/initenal_resistance", channel_index_);
    char value[10] = {0};
    snprintf(value, sizeof(value),"%d", static_cast<int>(resistance_enable_));
    return 1 == ZCAN_SetValue(device_handle_, path, value);
}

void DeviceManager::set_frm_delay_time(uint value)
{
    frm_delay_time_ = value;
}

void DeviceManager::set_data_length(uint value)
{
    dlc_ = value;
}

void DeviceManager::set_send_type_index(DeviceManager::SendType type)
{
    send_type_ = type;
}

void DeviceManager::set_send_count(uint value)
{
    send_count_ = value;
}

void DeviceManager::set_send_enable(DeviceManager::Enable type)
{
    send_enable_ = type;
}

//对src根据xx进行拆分, base是进制,10:十进制, 16:16进制
size_t DeviceManager::split(BYTE *dst, size_t max_len, const QString &src, char xx, uint base)
{
    if (0 == max_len || nullptr == dst || src.isEmpty())
        return 0;

    QStringList items;
    items.clear();
    items = src.split(xx);

    size_t count = items.size();
    if (count > 0)
    {
        count = count > max_len ? max_len : count; // 传入数据长度比max_len大，丢弃多余部分
        for (size_t i = 0; i < count; ++i)
        {
            dst[i] = static_cast<BYTE>(items[i].toUInt(nullptr, base));
        }
    }
    return count;
}
