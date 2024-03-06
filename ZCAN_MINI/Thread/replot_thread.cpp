#include "replot_thread.h"

ReplotThread::ReplotThread(QCustomPlot* const plot) :
    plot_(plot)
{

}

void ReplotThread::run()
{
    // 线程任务
    m_stop = false;

    last_time = std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::now());

    double duration_time = 0.0;
    t1 = std::chrono::high_resolution_clock::time_point(std::chrono::microseconds::zero());
    t2 = std::chrono::high_resolution_clock::time_point(std::chrono::microseconds::zero());
    t1 = std::chrono::high_resolution_clock::now();

    while (!m_stop) // 循环主体
    {
        if (!m_pause)
        {
            // t2 = std::chrono::high_resolution_clock::now();
            // duration_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1.0;
            // if (qAbs(duration_time - 10000) < 50 || duration_time - 10000 > 0) // 定时 10000us，即 10ms
            // {
            //     /*
            //      1. qAbs(duration_time - 10000) < 50 是为了提前进入新周期开始绘制，保证绘图精度及帧率（因为 replotData() 的调用会消耗时间）
            //      2. if 判断中，如果 replotData执行完后，为 t1 重新赋值 - 再次判断 这个过程，如果时间间隔超过了 11000 会发生什么？
            //         会卡住，if 内条件不满足会一直循环下去
            //         如何解决？添加第二条判断语句 || duration_time - 10000 > 0
            //      */
            //     // 采用异步编程呢？是否更加精确
            //     replotData();
            //     t1 = std::chrono::high_resolution_clock::now();
            // }
            msleep(15);
        }
    }
    quit(); // 相当于exit(0)，退出线程的事件循环
}

void ReplotThread::beginThread()
{
    m_pause = false;

    connect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
    timer_.start(0);
}

void ReplotThread::pauseThread()
{
    m_pause = true;

    disconnect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
}

void ReplotThread::stopThread()
{
    m_stop = true;

    disconnect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
}

void ReplotThread::replotData()
{
    double key = 0;
    if (plot_->graph(0)->dataCount() > 0)
        key = plot_->graph(0)->data()->coreData()->at(plot_->graph(0)->dataCount()-1).key;

    // if (plot_->xAxis->range().size() < key)
    //     plot_->xAxis->setRange(key, 0.100, Qt::AlignRight);

    // 重绘
    plot_->replot(QCustomPlot::rpQueuedReplot);

    // 计算帧数
    static QTime time(QTime::currentTime());
    double current_time = time.elapsed()/1000.0;
    static double last_time = time.elapsed()/1000.0;
    static int frame_count;
    ++frame_count;
    if (current_time - last_time > 2) // 每2秒求一次平均值
    {
        emit sig_frmChanged(QString("FPS %1, Total Data points: %2")
                 .arg(frame_count/(current_time-last_time), 0, 'f', 0)
                 .arg(plot_->graph(0)->data()->size()+plot_->graph(1)->data()->size()));
        last_time = current_time;
        frame_count = 0;
    }
}
