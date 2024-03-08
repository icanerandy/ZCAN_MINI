﻿#include "plotdata.h"

PlotData::PlotData(QCustomPlot* const plot)
    : plot_(plot)
{

}

void PlotData::slot_realTimeData(const QList<double> vals)
{
    static int count = 0;

    // 假设的时间戳，以微秒为单位
    // uint64_t timestamp_us = vals.at(0);
    // double key = static_cast<double>(timestamp_us) / 1000000.0;

    double key = QDateTime::currentMSecsSinceEpoch() / 1000.0;

    QVector<QCPGraphData>* data = nullptr;
    for (int i = 0; i < plot_->graphCount(); ++i)
    {
        data = plot_->graph(i)->data()->coreData();
        // data->push_back(QCPGraphData( key, vals.at(i+1) ));
        data->push_back(QCPGraphData( key, static_cast<double>(qrand() % 10) ));

        if (count == 0)
        {
            plot_->xAxis->setRange(key, key + 10);
            plot_->replot(QCustomPlot::rpQueuedReplot);
            ++count;
        }
    }
}