﻿#include "recmsg_thread.h"

RecMsgThread::RecMsgThread()
{
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


void RecMsgThread::slot_channelHandle(CHANNEL_HANDLE channel_handle)
{
    channel_handle_ = channel_handle;
}

void RecMsgThread::run()
{
    // 线程任务
    m_stop = false;

    ZCAN_Receive_Data can_data[1024];
    ZCAN_ReceiveFD_Data canfd_data[1024];
    uint len = 0;

    while (!m_stop) // 循环主体
    {
        if (!m_pause)
        {
            if ((len = ZCAN_GetReceiveNum(channel_handle_, TYPE_CAN)) > 0)
            {
                len = ZCAN_Receive(channel_handle_, can_data, 1024, 50);
                emit sig_newMsg(can_data, len);
            }
            if ((len = ZCAN_GetReceiveNum(channel_handle_, TYPE_CANFD)) > 0)
            {
                len = ZCAN_ReceiveFD(channel_handle_, canfd_data, 1024, 50);
                emit sig_newMsg(canfd_data, len);
            }

            // test
            {
                memset(&canfd_data, 0, sizeof(canfd_data));
                canfd_data[0].frame.can_id = MAKE_CAN_ID(/*258*/123, static_cast<BYTE>(1), 0, 0);
                for (size_t i = 0; i < 48; ++i)
                {
                    canfd_data[0].frame.data[i] = 0xff;
                }
                canfd_data[0].frame.len = 48;
                canfd_data[0].frame.flags |= 0;
                {
                    canfd_data[0].frame.flags |= TX_DELAY_SEND_FLAG;
                    uint frm_delay_time = 10;
                    canfd_data[0].frame.__res0 = static_cast<BYTE>(frm_delay_time & 0xff);
                    canfd_data[0].frame.__res1 = static_cast<BYTE>(((frm_delay_time)>>8) & 0xff);
                }
                emit sig_newMsg(canfd_data, 1);
            }

            msleep(15);
        }
    }
    quit(); // 相当于exit(0)，退出线程的事件循环
}
