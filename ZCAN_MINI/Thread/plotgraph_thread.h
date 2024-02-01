#ifndef PLOTGRAPH_THREAD_H
#define PLOTGRAPH_THREAD_H

#include <QThread>
#include "qcustomplot.h"
#include "recmsg_thread.h"

class PlotGraphThread : public QThread
{
    Q_OBJECT


protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

public:
    explicit PlotGraphThread(QCustomPlot *plot = nullptr);

public:
    void beginThread();
    void pauseThread();
    void stopThread();

private slots:
    void slot_newMsg(ZCAN_Receive_Data *can_data, uint len);
    void slot_newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len);


private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止
    QCustomPlot *plot_;
    int test_value_ = 1000;
};

#endif // PLOTGRAPH_THREAD_H
