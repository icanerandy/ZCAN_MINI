#ifndef SENDMSG_THREAD_H
#define SENDMSG_THREAD_H

#include <QObject>
#include <QThread>
#include "zlgcan.h"
#include "devicemanager.h"

class SendMsgThread : public QThread
{
    Q_OBJECT

private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止

private:
    CHANNEL_HANDLE channel_handle_;// CAN通道句柄

protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

public:
    explicit SendMsgThread(const QVariant &can_data, int send_count_once, int send_count, uint interval);
//    ~SendMsgThread() {};
    explicit SendMsgThread(const SendMsgThread &sendmsg_thread) = delete;
    const SendMsgThread &operator = (const SendMsgThread &sendmsg_thread) = delete;

public:
    static SendMsgThread *GetInstance();

    void beginThread();
    void pauseThread();
    void stopThread();

private:
    QVariant can_data_;
//    ZCAN_Transmit_Data can_data_;
//    ZCAN_TransmitFD_Data canfd_data_;
    int send_count_once_;
    int send_count_;
    uint interval_;

signals:
    void signal_SendError();
};

#endif // SENDMSG_THREAD_H
