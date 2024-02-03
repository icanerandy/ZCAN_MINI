#include "plotgraph_thread.h"

PlotGraphThread::PlotGraphThread(QCustomPlot *plot, uint plot_index, const unsigned long long msg_id, const CppCAN::CANSignal &signal)
    : plot_(plot),
      plot_index_(plot_index),
      msg_id_(msg_id),
      signal_(signal)
{
    RecMsgThread *rec_msg_thread = RecMsgThread::getInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_Receive_Data *, uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(ZCAN_Receive_Data *, uint)>(&PlotGraphThread::slot_newMsg));
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&PlotGraphThread::slot_newMsg));
}

void PlotGraphThread::beginThread()
{
    m_pause = false;

    RecMsgThread *rec_msg_thread = RecMsgThread::getInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_Receive_Data *, uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(ZCAN_Receive_Data *, uint)>(&PlotGraphThread::slot_newMsg));
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&PlotGraphThread::slot_newMsg));
}

void PlotGraphThread::pauseThread()
{
    m_pause = true;

    RecMsgThread *rec_msg_thread = RecMsgThread::getInstance();
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_Receive_Data *, uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(ZCAN_Receive_Data *, uint)>(&PlotGraphThread::slot_newMsg));
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&PlotGraphThread::slot_newMsg));
}

void PlotGraphThread::stopThread()
{
    m_stop = true;
}

int PlotGraphThread::getValue(const unsigned char *data, int len)
{
    QString bits = "";

    for(int i=0;i<len;i++)
    {
        QString str = QString("%1").arg(data[i],8,2,QLatin1Char('0'));
        QString str1;
        str1.fill('0',str.size());
        for(int j = 0;j<str1.length();j++)
            str1[j] = str[str1.length()-j-1];
        bits += str1;
    }

    int value = 0;
    bool isGetValue = true;

    if (CppCAN::CANSignal::LittleEndian == signal_.endianness())
    {
        for (int i = 0; i < signal_.length(); i++)
        {
            int p = i + signal_.start_bit();
            if (p >= 0 && p < len * 8)
            {
                if (bits[i + signal_.start_bit()] == QLatin1Char('1'))
                    value += (int)qPow(2, i);
            }
            else
            {
                isGetValue = false;
                break;
            }
        }
    }
    else
    {
        int offset = 0;
        for (int i = 0; i < signal_.length(); i++)
        {
            int p = i + signal_.start_bit();
            if ((p % 8 == 0) && (i != 0))
                offset -= 16;
            p += offset;

            if (p >= 0 && p < len * 8)
            {
                if (bits[p] == QLatin1Char('1'))
                    value += (qint32)qPow(2, i);
            }
            else
            {
                isGetValue = false;
                break;
            }
        }
    }

    if (CppCAN::CANSignal::Signed == signal_.signedness())
    {
        qint32 vv = qPow(2, signal_.length());

        if (value >= vv / 2) //负数
        {
            value = value - vv;
        }
    }

    if (isGetValue)
    {
        qDebug() << value;
        return value;
    }
}

void PlotGraphThread::run()
{
    // 线程任务
    m_stop = false;

    while (!m_stop) // 循环主体
    {
        if (!m_pause)
        {
            //分类信号

            //绘制图像

            //避免无数据时变成While(1),会占用大量的CPU
            msleep(15);
        }
    }
    quit(); // 相当于exit(0)，退出线程的事件循环
}

void PlotGraphThread::slot_newMsg(ZCAN_Receive_Data *can_data, uint len)
{
    uint i = 0;
    while (len--)
    {
        if (GET_ID(can_data[i].frame.can_id) != msg_id_)
            return;

        unsigned char buf[can_data[i].frame.can_dlc];
        memcpy(buf, can_data[i].frame.data, can_data[i].frame.can_dlc);

        int real_value = getValue(buf, can_data[i].frame.can_dlc);

        //key的单位是 ms
        double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

        double value = test_value_;
        test_value_ -= 10;
        if (0 == test_value_)
            test_value_ = 1000;

        //这里的1，是指横坐标时间宽度为1s，如果想要横坐标显示更多的时间
        //就把1调整为比较大到值，比如要显示10s，那就改成10。
        plot_->graph(plot_index_)->addData(key, real_value);
        plot_->xAxis->setRange(key+0.1, /*100*/1, Qt::AlignRight);
        plot_->replot();

        ++i;
    }
}

void PlotGraphThread::slot_newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len)
{
    if (GET_ID(canfd_data->frame.can_id) != msg_id_)
        return;

    //key的单位是 ms
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    double value = test_value_;
    test_value_ -= 10;
    if (0 == test_value_)
        test_value_ = 1000;

    //这里的1，是指横坐标时间宽度为1s，如果想要横坐标显示更多的时间
    //就把1调整为比较大到值，比如要显示10s，那就改成10。
    plot_->graph(plot_index_)->addData(key, value);
    plot_->xAxis->setRange(key+0.1, /*100*/1, Qt::AlignRight);
    plot_->replot();
}

