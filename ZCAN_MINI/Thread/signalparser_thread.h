#ifndef SIGNALPARSER_THREAD_H
#define SIGNALPARSER_THREAD_H

#include <QThread>
#include "qcustomplot.h"
#include "CANDatabase.h"
#include "recmsg_thread.h"

class SignalParserThread : public QThread
{
    Q_OBJECT


protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

public:
    explicit SignalParserThread(const unsigned long long msg_id, const QList<CppCAN::CANSignal>& sig_lst);

public:
    void beginThread();
    void pauseThread();
    void stopThread();

private:
    double getValue(const BYTE * const data, const CppCAN::CANSignal& signal);

signals:
    void sig_speed(const QList<double> vals);
    void sig_pwm(const QList<double> vals);

private slots:
    void slot_newMsg(const ZCAN_Receive_Data* const can_data, const uint len);
    void slot_newMsg(const ZCAN_ReceiveFD_Data* const canfd_data, const uint len);

private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止

    const unsigned long long msg_id_;

    const QList<CppCAN::CANSignal> sig_lst_;


};

#endif // SIGNALPARSER_THREAD_H
