#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <QObject>
#include "zlgcan.h"

#define TMP_BUFFER_LEN      1000

// 设备信息
typedef struct _DeviceInfo
{
    uint device_type;  //设备类型
    uint channel_count;//设备的通道个数
} DeviceInfo;

/*
列表数据需要和对话框中设备列表数据一一对应
*/
static const DeviceInfo kDeviceType[] = {
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

//USBCANFD
static const uint kAbitTimingUSB[] = {
    1000000,//1Mbps
    800000,//800kbps
    500000,//500kbps
    250000,//250kbps
    125000,//125kbps
    100000,//100kbps
    50000 //50kbps
};
static const uint kDbitTimingUSB[] = {
    5000000,//5Mbps
    4000000,//4Mbps
    2000000,//2Mbps
    1000000 //1Mbps
};

//PCIECANFD brp=1
static const uint kAbitTimingPCIE[] = {
    1000000, //1M(80%)
    800000, //800K(80%)
    500000, //500K(80%)
    250000, //250K(80%)
    125000  //125K(80%)
};
static const uint kDbitTimingPCIE[] = {
    8000000, //8Mbps(80%)
    5000000, //5Mbps(75%)
    5000000, //5Mbps(87.5%)
    4000000, //4Mbps(80%)
    2000000, //2Mbps(80%)
    1000000  //1Mbps(80%)
};

static const unsigned kBaudrate[] = {
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

class DeviceManager : public QObject
{
    Q_OBJECT

signals:

public slots:

public:
    static DeviceManager *GetInstance();    // 获取单例对象

private:
    explicit DeviceManager(QObject *parent = nullptr);  // 禁止外部构造
    //explicit ~DeviceManager();   // 禁止外部析构
    explicit DeviceManager(const DeviceManager &deviceManager) = delete;  // 禁止外部拷贝构造
    const DeviceManager &operator = (const DeviceManager &deviceManager) = delete;   // 禁止外部赋值构造

public:
    int device_type_index();

    int set_abit_baud_index(int index);
    int set_dbit_baud_index(int index);

    int set_protocol_index(int index);

    int set_canfd_exp_index(int index);

    int set_work_mode_index(int index);
    int set_resistance_enable(int index);

public:
    void ChangeDeviceType(int index);
    void ChangeDeviceIndex(int index);
    bool OpenDevice();
    bool InitCan();
    bool StartCan();
    bool StopCan();
    bool CloseDevice();
    ZCAN_DEVICE_INFO *GetDeviceInfo();

private:
    bool IsNetCAN( uint type );
    bool IsNetCANFD( uint type );
    bool IsNetTCP( uint type );
    bool IsNetUDP( uint type );
    bool SetBaudrate();
    bool SetCanfdBaudrate();
    bool SetResistanceEnable();

private:
    int device_type_index_;/* 设备 */
    int device_index_;/* 设备索引 */
    int channel_index_;/* 通道 */

    int work_mode_index_;/* 工作模式 */
    bool resistance_enable_;/* 终端电阻使能 */

    int abit_baud_index_;/* 仲裁域波特率 */
    int dbit_baud_index_;/* 数据域波特率 */

    int filter_mode_;/* 滤波模式 */
    QString acc_code_;/* 验收码 */
    QString acc_mask_;/* 屏蔽码 */

    QString id_;/* 报文id */
    int frame_type_index_;/* 帧类型 */
    int protocol_index_;/* 协议 */
    int canfd_exp_index_;/* CANFD加速 */
    int frm_delay_time;/* 延时 */
    bool frm_delay_flag;/* 队列帧延时标记 */

    QString datas_;/* 要发送的数据 */

    int send_type_index_;/* 发送方式 */
    int send_count_once_;/* 一次发送帧数量 */

    /* 队列发送相关数据定义 */
    bool support_delay_send_;/* 设备是否支持队列发送 */
    bool support_delay_send_mode_;/* 设备队列发送是否需要设置队列发送模式，USBCANFD系列，PCIECANFD系列设备需要设置发送模式才可以进行队列发送 */
    bool support_get_send_mode_;/* 设备是否支持查询当前模式 */

    /* 定时发送相关数据定义 */
    int auto_send_index_;/* 定时发送索引 */
    int auto_send_period_;/* 定时间隔 */


    //?vector<string> data_recv_list_;/* 接收到的数据 */ // 还未确定用何种数据类型


    DEVICE_HANDLE device_handle_;/* 设备句柄 */
    CHANNEL_HANDLE channel_handle_;/* 通道句柄 */
    bool device_opened_;/* 设备是否已经打开 */

    bool start_;/* CAN是否已经启动 */

    // IProperty *property_;/* 属性 */
};

#endif // DEVICE_MANAGER_H