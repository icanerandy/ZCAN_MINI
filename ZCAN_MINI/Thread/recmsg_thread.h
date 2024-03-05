#ifndef RECMSG_THREAD_H
#define RECMSG_THREAD_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QObject>
#include <QThread>
#include "zlgcan.h"
#include "canframe_tablemodel.h"

class RecMsgThread : public QThread
{
    Q_OBJECT

private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止

private:
    CHANNEL_HANDLE channel_handle_;// CAN通道句柄

protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

private:
    explicit RecMsgThread();
//    ~RecMsgThread() {};

public:
    explicit RecMsgThread(const RecMsgThread &recmsg_thread) = delete;
    const RecMsgThread &operator = (const RecMsgThread &recmsg_thread) = delete;

public:
    static RecMsgThread *getInstance();

    void beginThread();
    void pauseThread();
    void stopThread();

signals:
    void sig_newMsg(const ZCAN_Receive_Data* can_data, const uint len);
    void sig_newMsg(const ZCAN_ReceiveFD_Data* canfd_data, const uint len);

public slots:
    void slot_channelHandle(CHANNEL_HANDLE channel_handle);
};

#endif // RECMSG_THREAD_H
