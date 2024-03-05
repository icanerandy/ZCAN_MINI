#ifndef PLOTGRAPH_THREAD_H
#define PLOTGRAPH_THREAD_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QThread>
#include <chrono>
#include <QByteArray>
#include "qcustomplot.h"
#include "recmsg_thread.h"
#include "CANDatabase.h"
#include "signalparser_thread.h"

class PlotDataThread : public QThread
{
    Q_OBJECT


protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

public:
    explicit PlotDataThread(QCustomPlot* const plot, SignalParserThread* const sig_parser_thread);

public:
    void beginThread();
    void pauseThread();
    void stopThread();

private slots:
    void slot_realTimeData(const QList<double> vals);

private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止

    QCustomPlot* const plot_;

    SignalParserThread* const sig_parser_thread_;

    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;

    std::chrono::high_resolution_clock::time_point last_time;
};

#endif // PLOTGRAPH_THREAD_H
