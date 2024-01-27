#include "recmsg_thread.h"

RecMsgThread::RecMsgThread()
{
}

RecMsgThread *RecMsgThread::GetInstance()
{
    static RecMsgThread recMsgThread;
    return &recMsgThread;
}

void RecMsgThread::beginThread()
{
    m_pause = false;
}

void RecMsgThread::pauseThread()
{
    m_pause = true;
}

void RecMsgThread::stopThread()
{
    m_stop = true;
}

void RecMsgThread::run()
{
    // 线程任务
    m_stop = false;

    ZCAN_Receive_Data can_data[100];
    ZCAN_ReceiveFD_Data canfd_data[100];
    uint len;

    while (!m_stop) // 循环主体
    {
        if (!m_pause)
        {
            if (len = ZCAN_GetReceiveNum(channel_handle_, TYPE_CAN))
            {
                len = ZCAN_Receive(channel_handle_, can_data, 100, 50);
                emit newMsg(can_data, len);
            }
            if (len = ZCAN_GetReceiveNum(channel_handle_, TYPE_CANFD))
            {
                len = ZCAN_ReceiveFD(channel_handle_, canfd_data, 100, 50);
                emit newMsg(canfd_data, len);
            }
            //避免无数据时变成While(1),会占用大量的CPU
            msleep(15);
        }
    }
    quit(); // 相当于exit(0)，退出线程的事件循环
}
