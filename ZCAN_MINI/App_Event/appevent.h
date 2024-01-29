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
    explicit AppEvent(QObject *parent = nullptr);
    // explicit ~AppEvent();
    explicit AppEvent(const AppEvent &appEvent) = delete;
    const AppEvent &operator = (const AppEvent &appEvent) = delete;

/* 接收到信号就通过槽函数响应 */
public slots:
    void slot_newMsg(ZCAN_Receive_Data *can_data, uint len);
    void slot_newMsg(ZCAN_ReceiveFD_Data *can_data, uint len);
/* 槽函数通过发送新的信号做中转 */
signals:
    void newMsg(ZCAN_Receive_Data *can_data, uint len);
    void slot_newMsg(ZCAN_ReceiveFD_Data *can_data, uint len);
};

#endif // APP_EVENT_H
