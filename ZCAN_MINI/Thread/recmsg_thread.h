#ifndef RECMSG_THREAD_H
#define RECMSG_THREAD_H

#include <QObject>
#include <QThread>
#include "zlgcan.h"
#include "canframe_tablemodel.h"
#include "devicemanager.h"

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
    explicit RecMsgThread(const RecMsgThread &recMsgThread) = delete;
    const RecMsgThread &operator = (const RecMsgThread &recMsgThread) = delete;

public:
    static RecMsgThread *GetInstance();

    void beginThread();
    void pauseThread();
    void stopThread();

signals:
    void newMsg(ZCAN_Receive_Data *can_data, uint len);
    void newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len);
};

#endif // RECMSG_THREAD_H
