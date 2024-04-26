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
#include "signalparser.h"

class LinePlot : public QObject
{
    Q_OBJECT

public:
    explicit LinePlot(QCustomPlot* const plot);
    void addDataWithResampling(QCPGraph* graph, QCPGraphData new_data);

Q_SIGNALS:
    void sig_absDeviation(double key, double abs_deviation);

public Q_SLOTS:
    void slot_realTimeData(const QList<double> vals);

private:
    QCustomPlot* const plot_;
    QVector<QCPGraphData> total_data;

    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;

    std::chrono::high_resolution_clock::time_point last_time;
};

#endif // PLOTGRAPH_THREAD_H
