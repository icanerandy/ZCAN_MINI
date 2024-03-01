#ifndef REPLOT_THREAD_H
#define REPLOT_THREAD_H

#include <QThread>
#include <chrono>
#include <qcustomplot.h>

class ReplotThread : public QThread
{
    Q_OBJECT

public:
    explicit ReplotThread(QCustomPlot* const plot);

protected:
    void run() override; // 线程任务

signals:
    void sig_frmChanged(const QString& msg);

public:
    void beginThread();
    void pauseThread();
    void stopThread();

private slots:
    void replotData(); // 定时重绘

private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止

    QCustomPlot* const plot_;

    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;

    std::chrono::high_resolution_clock::time_point last_time;
};
#endif // REPLOT_THREAD_H
