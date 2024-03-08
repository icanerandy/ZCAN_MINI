#include "signalparser.h"

SignalParser::SignalParser(const uint32_t msg_id, QList<Vector::DBC::Signal*>& sig_lst)
    : msg_id_(msg_id),
      sig_lst_(sig_lst)
{

}

void SignalParser::slot_newMsg(const ZCAN_Receive_Data* can_data, const uint len)
{
    unsigned int raw_value = 0;
    double physical_value = 0.0;
    uint i = 0;
    while (i < len)
    {
        if (GET_ID(can_data[i].frame.can_id) != msg_id_)
            return;

        const BYTE* const data = can_data[i].frame.data;
        std::vector< uint8_t > raw_data (data, data+can_data[i].frame.can_dlc);

        QList<double> vals;
        vals.push_back(can_data[i].timestamp);
        for (auto sig : sig_lst_)
        {
            raw_value = sig->decode(raw_data);
            physical_value = sig->rawToPhysicalValue(raw_value);
            vals.push_back(physical_value);
        }
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
        if (GET_ID(canfd_data[i].frame.can_id) != msg_id_)
            return;

        const BYTE* const data = canfd_data[i].frame.data;
        std::vector< uint8_t > raw_data (data, data+canfd_data[i].frame.len);

        QList<double> vals;
        vals.push_back(canfd_data[i].timestamp);
        for (auto sig : sig_lst_)
        {
            raw_value = sig->decode(raw_data);
            physical_value = sig->rawToPhysicalValue(raw_value);
            vals.push_back(physical_value);
        }
        emit sig_speed(vals);

        ++i;
    }
}

