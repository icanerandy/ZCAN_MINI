#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <QObject>
#include "zlgcan.h"
#include "recmsg_thread.h"
#include "sendmsg_thread.h"

#define TMP_BUFFER_LEN      1000


class DeviceManager : public QObject
{
    Q_OBJECT

public:
    // 设备信息
    struct DeviceInfo
    {
        uint device_type;  //设备类型
        uint channel_count;//设备的通道个数
    };

    static const DeviceInfo kDeviceType[];
    //USBCANFD
    static const uint kAbitTimingUSB[];
    static const uint kDbitTimingUSB[];
    //PCIECANFD brp=1
    static const uint kAbitTimingPCIE[];
    static const uint kDbitTimingPCIE[];
    static const uint kBaudrate[];

    enum struct DeviceTypeIndex {
        zCAN_USBCAN1,
        zCAN_USBCAN2,
        zCAN_PCI9820I,
        zCAN_USBCAN_E_U,
        zCAN_USBCAN_2E_U,
        zCAN_USBCAN_4E_U,
        zCAN_PCIE_CANFD_100U,
        zCAN_PCIE_CANFD_200U,
        zCAN_PCIE_CANFD_400U_EX,
        zCAN_USBCANFD_200U,
        zCAN_USBCANFD_100U,
        zCAN_USBCANFD_MINI,
        zCAN_CANETTCP,
        zCAN_CANETUDP,
        zCAN_WIFICAN_TCP,
        zCAN_WIFICAN_UDP,
        zCAN_CLOUD,
        zCAN_CANFDWIFI_TCP,
        zCAN_CANFDWIFI_UDP,
        zCAN_CANFDNET_TCP,
        zCAN_CANFDNET_UDP,
        zCAN_CANFDNET_400U_TCP,
        zCAN_CANFDNET_400U_UDP
    };

    enum struct WorkMode:BYTE {
        Normal, ListenOnly
    };

    enum struct Enable {
        Enabled, Unenabled
    };

    /* 仅针对CANFD控制器 */
    enum struct StandardType {
        Iso, NonIso
    };

    enum struct FrameType {
        Can, CanFd
    };

    enum struct ProtocolType {
        Can, CanFd, CanFdBrs
    };

    enum struct SendType {
        Normal, SingleTransmit, Loopback, SingleLoopback
    };

    enum struct DeviceState {
        Opened, Unopened
    };

    enum struct CanState {
        Started, Unstarted
    };

private:
    explicit DeviceManager(QObject *parent = nullptr);  // 禁止外部构造
    //explicit ~DeviceManager();   // 禁止外部析构

public:
    explicit DeviceManager(const DeviceManager &deviceManager) = delete;  // 禁止外部拷贝构造
    const DeviceManager &operator = (const DeviceManager &deviceManager) = delete;   // 禁止外部赋值构造

public:
    static DeviceManager *getInstance();    // 获取单例对象
    DeviceTypeIndex device_type_index() const;
    CHANNEL_HANDLE channel_handle() const;
    DeviceManager::CanState can_start() const;
    Enable send_enable() const;
    StandardType canfd_standard_type() const;
    void set_abit_baud_index(uint index);
    void set_dbit_baud_index(uint index);
    void set_canfd_standard_type(StandardType type);
    void set_protocol_index(ProtocolType type);
    void set_work_mode_index(WorkMode mode);
    void set_resistance_enable(Enable type);
    void set_frame_type_index(DeviceManager::FrameType type);
    void set_send_count_once(uint value);
    void set_id(uint id);
    void set_data(QString &data);
    void set_frm_delay_time(uint value);
    void set_data_length(uint value);
    void set_send_type_index(DeviceManager::SendType type);
    void set_send_count(uint value);
    void set_send_enable(DeviceManager::Enable type);
    size_t split(BYTE* dst, size_t max_len, const QString& src, char xx, uint base);

    void changeDeviceIndex(uint index);
    bool openDevice();
    bool initCan();
    bool startCan();
    void sendMsg();
    void stopSendMsg();
    bool stopCan();
    bool closeDevice();
    const ZCAN_DEVICE_INFO *getDeviceInfo() const;

private:
    bool isNetCAN( uint type );
    bool isNetCANFD( uint type );
    bool isNetTCP( uint type );
    bool isNetUDP( uint type );
    bool setBaudrate();
    bool setCanfdBaudrate();
    bool setResistanceEnable();

signals:
    void sig_channelHandle(CHANNEL_HANDLE channel_handle);

public slots:
    void slot_deviceType_changed(DeviceManager::DeviceTypeIndex type);

private:
    DeviceTypeIndex device_type_index_;/* 设备 */  // 注意：此处的设备类型仅仅为kDeviceType中的类型索引号
    uint device_index_;/* 设备索引 */
    uint channel_index_;/* 通道 */

    WorkMode work_mode_;/* 工作模式 */
    Enable resistance_enable_;/* 终端电阻使能 */

    uint abit_baud_index_;/* 仲裁域波特率 */
    uint dbit_baud_index_;/* 数据域波特率 */

    StandardType canfd_standard_type_;/* CANFD 控制器标准类型， ISO 或非 ISO，通常使用 ISO 标准 */

    // 数据发送相关成员变量声明
    uint id_;/* 报文id */
    FrameType frame_type_;/* 帧类型 */
    ProtocolType protocol_type_;/* 协议 */
    uint dlc_;/* dlc */
    QString datas_;/* 要发送的数据 */
    SendType send_type_;/* 发送方式 */
    uint send_count_once_;/* 一次发送帧数量 */
    uint send_count_;/* 一共发送多少次 */

    /* 队列发送相关数据定义 */
    bool frm_delay_flag_;/* 队列帧延时标记 */
    uint frm_delay_time_;/* 延时 */
    bool support_delay_send_;/* 设备是否支持队列发送 */
    bool support_delay_send_mode_;/* 设备队列发送是否需要设置队列发送模式，USBCANFD系列，PCIECANFD系列设备需要设置发送模式才可以进行队列发送 */
    bool support_get_send_mode_;/* 设备是否支持查询当前模式 */

    /* 定时发送相关数据定义 */
    Enable send_enable_;/* 发送使能 */
    uint auto_send_index_;/* 定时发送索引 */
    uint auto_send_period_;/* 定时间隔 */

    uint filter_mode_;/* 滤波模式 */
    QString acc_code_;/* 验收码 */
    QString acc_mask_;/* 屏蔽码 */

    DEVICE_HANDLE device_handle_;/* 设备句柄 */
    CHANNEL_HANDLE channel_handle_;/* 通道句柄 */
    DeviceState device_opened_;/* 设备是否已经打开 */

    CanState can_start_;/* CAN是否已经启动 */

    SendMsgThread *sendmsg_thread_;
};

#endif // DEVICE_MANAGER_H
