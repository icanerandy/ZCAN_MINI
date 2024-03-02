﻿#include "plotdata_thread.h"

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
    // 假设的时间戳，以微秒为单位
    uint64_t timestamp_us = vals.at(0);
    double key = static_cast<double>(timestamp_us) / 1000000.0;
    // qDebug() << "timestamp: " << timestamp_us;
    // qDebug() << "key: " << key;

    QVector<QCPGraphData>* data = nullptr;
    for (int i = 0; i < plot_->graphCount() - 1; ++i)
    {
        data = plot_->graph(i)->data()->coreData();
        data->push_back(QCPGraphData( key, vals.at(i+1) ));
    }
}
