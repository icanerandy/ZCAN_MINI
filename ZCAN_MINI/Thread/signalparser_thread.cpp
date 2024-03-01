#include "signalparser_thread.h"

SignalParserThread::SignalParserThread(const unsigned long long msg_id, const QList<CppCAN::CANSignal>& sig_lst)
    : msg_id_(msg_id),
      sig_lst_(sig_lst)
{

}

void SignalParserThread::beginThread()
{
    m_pause = false;

    RecMsgThread* const rec_msg_thread = RecMsgThread::getInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (SignalParserThread::*)(const ZCAN_Receive_Data* const, const uint)>(&SignalParserThread::slot_newMsg));
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (SignalParserThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&SignalParserThread::slot_newMsg));
}

void SignalParserThread::pauseThread()
{
    m_pause = true;

    RecMsgThread* const rec_msg_thread = RecMsgThread::getInstance();
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (SignalParserThread::*)(const ZCAN_Receive_Data* const, const uint)>(&SignalParserThread::slot_newMsg));
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (SignalParserThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&SignalParserThread::slot_newMsg));
}

void SignalParserThread::stopThread()
{
    m_stop = true;
}

double SignalParserThread::getValue(const BYTE * const data, const CppCAN::CANSignal& signal)
{
    const uint8_t start_bit_in_byte = signal.start_bit() % 8;
    uint8_t cur_bit = start_bit_in_byte;
    const uint8_t start_byte = signal.start_bit() / 8;
    uint8_t cur_byte = start_byte;
    int32_t value = 0;  // 读取出来的数据存放单元
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
            uint32_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
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
            uint32_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
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
            uint32_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value += tmp;
            --tmp;
        }
    }
#endif

    if (CppCAN::CANSignal::Signed == signal.signedness())
    {
        uint32_t tmp = 0x01;
        tmp <<= (signal.length()-1);
        if (0 != (tmp & value))   // 负数
        {
            value &= ~tmp;
            value = ~value + 1;
        }
    }

    return value * signal.scale() + signal.offset();
}

void SignalParserThread::run()
{
    // 线程任务
    m_stop = false;

    while (!m_stop)
    {
        if (!m_pause)
        {
            msleep(15);
        }
    }
    quit();
}

void SignalParserThread::slot_newMsg(const ZCAN_Receive_Data* const can_data, const uint len)
{
    uint i = 0;
    while (i < len)
    {
        if (GET_ID(can_data[i].frame.can_id) != msg_id_)
            return;

        const BYTE* const data = can_data[i].frame.data;

        QList<double> vals;
        for (auto sig : sig_lst_)
            vals.push_back(getValue(data, sig));
        emit sig_pwm(vals);

        ++i;
    }
}

void SignalParserThread::slot_newMsg(const ZCAN_ReceiveFD_Data* const canfd_data, const uint len)
{
    uint i = 0;
    while (i < len)
    {
        if (GET_ID(canfd_data[i].frame.can_id) != msg_id_)
            return;

        const BYTE* const data = canfd_data[i].frame.data;

        QList<double> vals;
        for (auto sig : sig_lst_)
            vals.push_back(getValue(data, sig));
        emit sig_pwm(vals);

        ++i;
    }
}

