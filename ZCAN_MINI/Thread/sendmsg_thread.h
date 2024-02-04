#ifndef SENDMSG_THREAD_H
#define SENDMSG_THREAD_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include "zlgcan.h"

class SendMsgThread : public QThread
{
    Q_OBJECT

private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止

protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

public:
    explicit SendMsgThread(CHANNEL_HANDLE channel_handle, const QVariant &can_data, uint send_count_once, uint send_count);
//    ~SendMsgThread() {};

public:
    explicit SendMsgThread(const SendMsgThread &sendmsg_thread) = delete;
    const SendMsgThread &operator = (const SendMsgThread &sendmsg_thread) = delete;

public:
    void beginThread();
    void pauseThread();
    void stopThread();

private:
    CHANNEL_HANDLE channel_handle_;
    QVariant can_data_;
    uint send_count_once_;
    uint send_count_;

signals:
    void signal_SendError();
};

#endif // SENDMSG_THREAD_H
