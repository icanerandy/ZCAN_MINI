#include "app_event.h"

AppEvent *AppEvent::GetInstance()
{
    static AppEvent appEvent;
    return &appEvent;
}

AppEvent::AppEvent(QObject *parent) : QObject(parent)
{
}
