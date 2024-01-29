#include "appevent.h"

AppEvent *AppEvent::GetInstance()
{
    static AppEvent appEvent;
    return &appEvent;
}

AppEvent::AppEvent(QObject *parent) : QObject(parent)
{
}

void AppEvent::slot_newMsg(ZCAN_Receive_Data *can_data, uint len)
{
    emit newMsg(can_data, len);
}

void AppEvent::slot_newMsg(ZCAN_ReceiveFD_Data *can_data, uint len)
{
    emit newMsg(can_data, len);
}
