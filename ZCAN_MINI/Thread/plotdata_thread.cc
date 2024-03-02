#include "plotdata_thread.h"

PlotDataThread::PlotDataThread(QCustomPlot* const plot, SignalParserThread* const sig_parser_thread)
    : plot_(plot),
      sig_parser_thread_(sig_parser_thread)
{

}

void PlotDataThread::beginThread()
{
    m_pause = false;

    connect(sig_parser_thread_, static_cast<void (SignalParserThread::*)(const QList<double>)>(&SignalParserThread::sig_speed),
            this, static_cast<void (PlotDataThread::*)(const QList<double>)>(&PlotDataThread::slot_realTimeData));
    connect(sig_parser_thread_, static_cast<void (SignalParserThread::*)(const QList<double>)>(&SignalParserThread::sig_pwm),
            this, static_cast<void (PlotDataThread::*)(const QList<double>)>(&PlotDataThread::slot_realTimeData));
}

void PlotDataThread::pauseThread()
{
    m_pause = true;

    disconnect(sig_parser_thread_, static_cast<void (SignalParserThread::*)(const QList<double>)>(&SignalParserThread::sig_speed),
            this, static_cast<void (PlotDataThread::*)(const QList<double>)>(&PlotDataThread::slot_realTimeData));
    disconnect(sig_parser_thread_, static_cast<void (SignalParserThread::*)(const QList<double>)>(&SignalParserThread::sig_pwm),
            this, static_cast<void (PlotDataThread::*)(const QList<double>)>(&PlotDataThread::slot_realTimeData));
}

void PlotDataThread::stopThread()
{
    m_stop = true;
}

void PlotDataThread::run()
{
    // 线程任务
    m_stop = false;

    while (!m_stop)
    {
        if (!m_pause)
        {
            msleep(15);
        }
    }
    quit();
}

void PlotDataThread::slot_realTimeData(const QList<double> vals)
{
    // static auto start_time = std::chrono::high_resolution_clock::now();

    // auto current_time = std::chrono::high_resolution_clock::now();

    // auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);

    // double key = duration_us.count() / 1000000.0;

    // 假设的时间戳，以微秒为单位
    uint64_t timestamp_us = vals.at(0);

    // 将时间戳转换为std::chrono::microseconds
    std::chrono::microseconds us_duration(timestamp_us);

    // 转换为小时、分钟和秒
    auto hours = std::chrono::duration_cast<std::chrono::hours>(us_duration);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(us_duration % std::chrono::hours(1));
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(us_duration % std::chrono::minutes(1));
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(us_duration % std::chrono::milliseconds(1));
    auto mircors = std::chrono::duration_cast<std::chrono::microseconds>(us_duration % std::chrono::microseconds(1));

    QVector<QCPGraphData>* data = nullptr;
    for (int i = 0; i < plot_->graphCount() - 1; ++i)
    {
        data = plot_->graph(i)->data()->coreData();
        data->push_back(QCPGraphData( timestamp_us, vals.at(i+1) ));
    }
}
