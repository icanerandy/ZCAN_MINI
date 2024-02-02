#ifndef PLOTGRAPH_THREAD_H
#define PLOTGRAPH_THREAD_H

#include <QThread>
#include "qcustomplot.h"
#include "recmsg_thread.h"
#include "CANDatabase.h"

class PlotGraphThread : public QThread
{
    Q_OBJECT


protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

public:
    explicit PlotGraphThread(QCustomPlot *plot, uint plot_index, const unsigned long long msg_id, const CppCAN::CANSignal &signal);

public:
    void beginThread();
    void pauseThread();
    void stopThread();

public:
    int getValue(const unsigned char *data, int len);

private slots:
    void slot_newMsg(ZCAN_Receive_Data *can_data, uint len);
    void slot_newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len);


private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止
    QCustomPlot *plot_;
    uint plot_index_;
    int test_value_ = 1000;

    unsigned long long msg_id_;
    const CppCAN::CANSignal signal_;
};

#endif // PLOTGRAPH_THREAD_H
