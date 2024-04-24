#include "lineplot.h"

LinePlot::LinePlot(QCustomPlot* const plot)
    : plot_(plot)
{

}

void LinePlot::slot_realTimeData(const QList<double> vals)
{
    if (!plot_)
        return;

    static int count = 0;

    // 假设的时间戳，以微秒为单位
    uint64_t timestamp_us = vals.at(0);
    double key = static_cast<double>(timestamp_us) / 1000000.0;

    // double key = static_cast<double>(QDateTime::currentMSecsSinceEpoch()) / 1000;
    // int x = qrand() % 100;
    // int y = qrand() % 100;
    // emit sig_absDeviation(key, x - y);

    emit sig_absDeviation(key, vals.at(1) - vals.at(3));

    QVector<QCPGraphData>* data = nullptr;
    for (int i = 0; i < plot_->graphCount(); ++i)
    {
        data = plot_->graph(i)->data()->coreData();
        data->push_back(QCPGraphData( key, vals.at(2*i+1) /*i==0?x:y*/ ));

        if (count == 0)
        {
            plot_->xAxis->setRange(key, key + 10);
            plot_->replot(QCustomPlot::rpQueuedReplot);
            ++count;
        }
    }
}
