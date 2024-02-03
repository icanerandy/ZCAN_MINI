#include "recmsg_thread.h"

RecMsgThread::RecMsgThread()
{
    // 线程接收到新的消息后，数据模型进行相应的更新
    CanFrameTableModel *canFrameTableModel = CanFrameTableModel::GetInstance();
    connect(this, static_cast<void (RecMsgThread::*)(ZCAN_Receive_Data *, uint)>(&RecMsgThread::newMsg),
            canFrameTableModel, static_cast<void (CanFrameTableModel::*)(ZCAN_Receive_Data *, uint)>(&CanFrameTableModel::newMsg));
    connect(this, static_cast<void (RecMsgThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&RecMsgThread::newMsg),
            canFrameTableModel, static_cast<void (CanFrameTableModel::*)(ZCAN_ReceiveFD_Data *, uint)>(&CanFrameTableModel::newMsg));
}

RecMsgThread * RecMsgThread::getInstance()
{
    static RecMsgThread recmsg_thread;
    return &recmsg_thread;
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
    channel_handle_ = DeviceManager::getInstance()->channel_handle();
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
