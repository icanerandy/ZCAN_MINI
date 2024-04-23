#include "signalparser.h"

SignalParser::SignalParser(QList< QPair<uint32_t, Vector::DBC::Signal> > sig_lst)
    : sig_lst_(sig_lst)
{

}

void SignalParser::slot_newMsg(const ZCAN_Receive_Data* can_data, const uint len)
{
    unsigned int raw_value = 0;
    double physical_value = 0.0;
    uint i = 0;
    while (i < len)
    {
        QList<double> vals;
        for (const auto& ref : sig_lst_)
            if (ref.first == GET_ID(can_data[i].frame.can_id))  // 消息id可以匹配
            {
                // 开始解析消息中的信号
                vals.push_back(can_data[i].timestamp);

                const BYTE* const data = can_data[i].frame.data;
                std::vector< uint8_t > raw_data (data, data+can_data[i].frame.can_dlc);

                raw_value = ref.second.decode(raw_data);
                physical_value = ref.second.rawToPhysicalValue(raw_value);
                vals.push_back(physical_value);
            }
        if (!vals.empty())  // 有解析到数据
            emit sig_speed(vals);

        ++i;
    }
}

void SignalParser::slot_newMsg(const ZCAN_ReceiveFD_Data* canfd_data, const uint len)
{
    unsigned int raw_value = 0;
    double physical_value = 0.0;
    uint i = 0;
    while (i < len)
    {
        QList<double> vals;
        for (const auto& ref : sig_lst_)
            if (ref.first == GET_ID(canfd_data[i].frame.can_id))  // 消息id可以匹配
            {
                // 开始解析消息中的信号
                vals.push_back(canfd_data[i].timestamp);

                const BYTE* const data = canfd_data[i].frame.data;
                std::vector< uint8_t > raw_data (data, data+canfd_data[i].frame.len);

                raw_value = ref.second.decode(raw_data);
                physical_value = ref.second.rawToPhysicalValue(raw_value);
                vals.push_back(physical_value);
            }
        if (!vals.empty())  // 有解析到数据
            emit sig_speed(vals);

        ++i;
    }
}

