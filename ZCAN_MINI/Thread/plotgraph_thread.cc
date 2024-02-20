#include "plotgraph_thread.h"

PlotGraphThread::PlotGraphThread(QCustomPlot *plot,const unsigned long long msg_id, const CppCAN::CANSignal &ref_speed, const CppCAN::CANSignal &rel_speed)
    : plot_(plot),
      msg_id_(msg_id),
      ref_speed_(ref_speed),
      rel_speed_(rel_speed)
{

}

void PlotGraphThread::beginThread()
{
    m_pause = false;

    RecMsgThread* rec_msg_thread = RecMsgThread::getInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(const ZCAN_Receive_Data* const, const uint)>(&PlotGraphThread::slot_newMsg));
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&PlotGraphThread::slot_newMsg));
}

void PlotGraphThread::pauseThread()
{
    m_pause = true;

    RecMsgThread* rec_msg_thread = RecMsgThread::getInstance();
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(const ZCAN_Receive_Data* const, const uint)>(&PlotGraphThread::slot_newMsg));
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&PlotGraphThread::slot_newMsg));
}

void PlotGraphThread::stopThread()
{
    m_stop = true;
}

/**
 * @brief PlotGraphThread::getValue
 * @param data
 * @param len
 * @return
 *
 * 注意：当传入的信号位数大于32位是会出错！因为编译的是32位的程序，其中uint64_t只有32位
 */
int PlotGraphThread::getValue(const BYTE * const data, const CppCAN::CANSignal& signal)
{
    const uint8_t start_bit_in_byte = signal.start_bit() % 8;
    uint8_t cur_bit = start_bit_in_byte;
    const uint8_t start_byte = signal.start_bit() / 8;
    uint8_t cur_byte = start_byte;
    int64_t value = 0;  // 读取出来的数据存放单元
    uint8_t bits = 0;  // 已经读取了多少个位
    if (CppCAN::CANSignal::LittleEndian == signal.endianness())    // Intel
    {
        while (bits < signal.length())
        {
            if (cur_bit > 7)
            {
                cur_bit = 0;
                ++cur_byte;
            }

            uint8_t bit_val = 0x01<<cur_bit;
            uint64_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value |= tmp<<bits;   // tmp<<bits相当于给第bits个位取值，然后让value按位或上tmp，让value的第bits位取值
            ++bits;
            ++cur_bit;
        }
    }
    else  // Motorola_LSB
    {
        while (bits < signal.length())
        {
            if (cur_bit > 7)
            {
                cur_bit = 0;
                --cur_byte;
            }

            uint8_t bit_val = 0x01<<cur_bit;
            uint64_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value |= tmp<<bits;   // tmp<<bits相当于给第bits个位取值，然后让value按位或上tmp，让value的第bits位取值
            ++bits;
            ++cur_bit;
        }
    }
//#define Motorola_MSB
#ifdef Motorola_MSB
    else    // Motorola_MSB
    {
        while (bits < sig.length())
        {
            if (cur_bit < 0)
            {
                cur_bit = 7;
                ++cur_byte;
            }

            value <<= 1;
            uint8_t bit_val = 0x01<<cur_bit;
            uint64_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value += tmp;
            --tmp;
        }
    }
#endif

    if (CppCAN::CANSignal::Signed == signal.signedness())
    {
        uint64_t tmp = 0x01;
        tmp <<= (signal.length()-1);
        if (0 != (tmp & value))   // 负数
        {
            value &= ~tmp;
            value = ~value + 1;
        }
    }

    return value + signal.offset();
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



            plot_->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));

//            plot_->graph(0)->setBrush(QBrush(QColor(255,50,30,75)));
//            plot_->graph(0)->setChannelFillGraph(plot_->graph(1));
            int i = 1;
            while (i++ <= 1000 && !m_stop)
            {
                double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
                plot_->graph(0)->addData(key, rand() % 10);
                plot_->xAxis->setRange(key, 0.5, Qt::AlignRight);

                plot_->graph(1)->addData(key, rand() % 10);
                plot_->xAxis->setRange(key, 0.5, Qt::AlignRight);
                plot_->replot(QCustomPlot::rpQueuedReplot);

                msleep(10);
            }
            m_pause = true;









            //避免无数据时变成While(1),会占用大量的CPU
            msleep(15);
        }
    }
    quit(); // 相当于exit(0)，退出线程的事件循环
}

void PlotGraphThread::slot_newMsg(const ZCAN_Receive_Data* const can_data, const uint len)
{
    uint i = 0;
    while (i < len)
    {
        if (GET_ID(can_data[i].frame.can_id) != msg_id_)
            return;

        //const uint dlc = can_data[i].frame.can_dlc;
        const BYTE* const data = can_data[i].frame.data;

        int real_value = getValue(data, ref_speed_);

        //key的单位是 ms
        double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

        plot_->graph(0)->addData(key, real_value);
        plot_->xAxis->setRange(key, 5, Qt::AlignRight);
        plot_->replot(QCustomPlot::rpQueuedReplot);

        ++i;
    }
}

void PlotGraphThread::slot_newMsg(const ZCAN_ReceiveFD_Data* const canfd_data, const uint len)
{
    uint i = 0;
    while (i < len)
    {
        if (GET_ID(canfd_data[i].frame.can_id) != msg_id_)
            return;

        //const uint dlc = canfd_data[i].frame.len;
        const BYTE* const data = canfd_data[i].frame.data;

        int real_value = getValue(data, ref_speed_);

        //key的单位是 ms
        double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

        plot_->graph(0)->addData(key, real_value);
        plot_->xAxis->setRange(key, 5, Qt::AlignRight);
        plot_->replot(QCustomPlot::rpQueuedReplot);

        ++i;
    }
}

