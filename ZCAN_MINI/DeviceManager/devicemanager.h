#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include "zlgcan.h"

class DeviceManager : public QObject
{
    Q_OBJECT

private:
    int device_type_index_;/* 设备 */
    int device_index_;/* 设备索引 */
    int channel_index_;/* 通道 */

    int work_mode_index_;/* 工作模式 */
    bool resistance_enable_;/* 终端电阻使能 */
    int baud_index_;/* 波特率 */

    int abit_baud_index_;/* 仲裁与波特率 */
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

    // QReceiveMessageThread threadRecMsg;/* 消息接收线程 */

    // IProperty *property_;/* 属性 */

public:
    explicit DeviceManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DEVICEMANAGER_H
