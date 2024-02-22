#include "replot_thread.h"

ReplotThread::ReplotThread(QCustomPlot* const plot) :
    plot_(plot)
{

}

void ReplotThread::run()
{
    // 线程任务
    m_stop = false;

    while (!m_stop) // 循环主体
    {
        if (!m_pause)
        {
            msleep(15);
        }
    }
    quit(); // 相当于exit(0)，退出线程的事件循环
}

void ReplotThread::beginThread()
{
    m_pause = false;

    connect(&replot_timer_, SIGNAL(timeout()), this, SLOT(slot_replotData()));
    replot_timer_.start(10);    // 间隔10ms刷新一次
}

void ReplotThread::pauseThread()
{
    m_pause = true;

    disconnect(&replot_timer_, SIGNAL(timeout()), this, SLOT(slot_replotData()));
    replot_timer_.stop();
}

void ReplotThread::stopThread()
{
    m_stop = true;
}

void ReplotThread::slot_replotData()
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;

    // 设定x范围为最近的100ms个时刻
    plot_->xAxis->setRange(key, 0.100, Qt::AlignRight);
    // 重绘
    plot_->replot(QCustomPlot::rpQueuedReplot);
    // 计算帧数
    static double last_fps;
    static int frame_count;
    ++frame_count;
    if (key - last_fps > 1) // 每1秒求一次平均值
    {
        qDebug() << QString("%1 FPS, Total Data points: %2")
                    .arg(frame_count/(key-last_fps), 0, 'f', 0)
                    .arg(plot_->graph(0)->data()->size()+plot_->graph(1)->data()->size());
        last_fps = key;
        frame_count = 0;
    }

    if (key > 10)
        pauseThread();
}
