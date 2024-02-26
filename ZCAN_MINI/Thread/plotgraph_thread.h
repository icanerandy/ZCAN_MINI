#ifndef PLOTGRAPH_THREAD_H
#define PLOTGRAPH_THREAD_H

#include <QThread>
#include <chrono>
#include <QByteArray>
#include "qcustomplot.h"
#include "recmsg_thread.h"
#include "CANDatabase.h"

class PlotGraphThread : public QThread
{
    Q_OBJECT


protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

public:
    explicit PlotGraphThread(QCustomPlot *plot, const unsigned long long msg_id, const CppCAN::CANSignal& ref_speed, const CppCAN::CANSignal& rel_speed);

public:
    void beginThread();
    void pauseThread();
    void stopThread();

private:
    int getValue(const BYTE * const data, const CppCAN::CANSignal& signal);
    void realTimeData();   // 定时添加数据

private slots:
    void slot_newMsg(const ZCAN_Receive_Data* const can_data, const uint len);
    void slot_newMsg(const ZCAN_ReceiveFD_Data* const canfd_data, const uint len);


private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止
    QCustomPlot *plot_;

    unsigned long long msg_id_;
    const CppCAN::CANSignal ref_speed_;
    const CppCAN::CANSignal rel_speed_;

    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;

    std::chrono::high_resolution_clock::time_point last_time;
};

#endif // PLOTGRAPH_THREAD_H
