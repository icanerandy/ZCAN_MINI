#ifndef REPLOT_THREAD_H
#define REPLOT_THREAD_H

#include <QThread>

#include <qcustomplot.h>

class ReplotThread : public QThread
{
    Q_OBJECT

public:
    explicit ReplotThread(QCustomPlot* const plot);

protected:
    void run() Q_DECL_OVERRIDE; // 线程任务

public:
    void beginThread();
    void pauseThread();
    void stopThread();

private slots:
    void slot_replotData(); // 定时重绘


private:
    bool m_pause = true;    // 暂停
    bool m_stop = false;    // 停止

    QCustomPlot* const plot_;
    QTimer replot_timer_;    // 定时绘图
};

#endif // REPLOT_THREAD_H
