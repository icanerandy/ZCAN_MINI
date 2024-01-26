#ifndef APP_EVENT_H
#define APP_EVENT_H

#include <QObject>
#include "main_window.h"

class AppEvent : public QObject
{
    Q_OBJECT

public:
    static AppEvent *GetInstance();

private:

private:
    explicit AppEvent(QObject *parent = nullptr);
    // explicit ~AppEvent();
    explicit AppEvent(const AppEvent &appEvent) = delete;
    const AppEvent &operator = (const AppEvent &appEvent) = delete;
};

#endif // APP_EVENT_H
