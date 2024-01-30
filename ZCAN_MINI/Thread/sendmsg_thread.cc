#include "sendmsg_thread.h"

void SendMsgThread::beginThread()
{
    m_pause = false;
}

void SendMsgThread::pauseThread()
{
    m_pause = true;
}

void SendMsgThread::stopThread()
{
    m_stop = true;
}

void SendMsgThread::run()
{
    // 线程任务
    channel_handle_ = DeviceManager::GetInstance()->channel_handle();
    m_stop = false;

    uint result = 0;
    QString text = "";
    if (can_data_.canConvert<ZCAN_Transmit_Data>())
    {
        ZCAN_Transmit_Data data = can_data_.value<ZCAN_Transmit_Data>();
        ZCAN_Transmit_Data* pData = nullptr;
        if (send_count_once_ > 0)
        {
            pData = new ZCAN_Transmit_Data[send_count_once_];
            for (int i=0; i<send_count_once_; ++i)
            {
                memcpy_s(&pData[i], sizeof(ZCAN_Transmit_Data), &data, sizeof(data));
            }
        }

        if (!m_pause)
        {
            while (send_count_--)
            {
                result = ZCAN_Transmit(channel_handle_, pData, send_count_once_);
                text = QString::asprintf(("发送数量:%d, 成功数量:%d"), send_count_once_, result);
                //qDebug(text);
                //避免无数据时变成While(1),会占用大量的CPU
                msleep(interval_);
            }
            delete [] pData;
        }
    }
    else
    {
        ZCAN_TransmitFD_Data data = can_data_.value<ZCAN_TransmitFD_Data>();
        ZCAN_TransmitFD_Data* pData = nullptr;
        if (send_count_once_ > 0)
        {
            pData = new ZCAN_TransmitFD_Data[send_count_once_];
            for (int i=0; i<send_count_once_; ++i)
            {
                memcpy_s(&pData[i], sizeof(ZCAN_TransmitFD_Data), &data, sizeof(data));
            }
        }

        if (!m_pause)
        {
            while (send_count_--)
            {
                result = ZCAN_TransmitFD(channel_handle_, pData, send_count_once_);
                text = QString::asprintf(("发送数量:%d, 成功数量:%d"), send_count_once_, result);
                //qDebug(text);
                //避免无数据时变成While(1),会占用大量的CPU
                msleep(interval_);
            }
            delete [] pData;
        }
    }

    quit(); // 相当于exit(0)，退出线程的事件循环
}

SendMsgThread::SendMsgThread(const QVariant &can_data, int send_count_once, int send_count, uint interval)
    : can_data_(can_data),
      send_count_once_(send_count_once),
      send_count_(send_count),
      interval_(interval)
{

}
