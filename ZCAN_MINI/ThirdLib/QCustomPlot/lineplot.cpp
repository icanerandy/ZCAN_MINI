#include "lineplot.h"

LinePlot::LinePlot(QCustomPlot* const plot)
    : plot_(plot)
{

}

void LinePlot::addDataWithResampling(QCPGraph* graph, QCPGraphData new_data)
{
    uint max_total_points = 10000;

    // 将新数据添加到当前数据
    total_data.append(new_data);

    QVector<QCPGraphData>* data_set = graph->data()->coreData();
    data_set->append(new_data);

    // 如果当前总数据点数超过最大允许值，则进行降采样
    uint total_points = data_set->size();
    if (total_points > max_total_points)
    {
        QVector<double> resampledX;
        QVector<double> resampledY;

        // 计算需要的降采样率
        uint sampleRate = total_points / max_total_points;

        // 降采样，每 sampleRate 个点取一个点
        for (uint i = 0; i < total_points; i += sampleRate)
        {
            resampledX.push_back(data_set->at(i).key);
            resampledY.push_back(data_set->at(i).value);
        }

        // 更新图表数据
        graph->setData(resampledX, resampledY);
    } else {
        // 如果没有超过最大点数，直接更新数据
    }
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
        // addDataWithResampling(plot_->graph(i), QCPGraphData( key, vals.at(2*i+1) /*i==0?x:y*/ ));

        if (count == 0)
        {
            plot_->xAxis->setRange(key, key + 10);
            plot_->replot(QCustomPlot::rpQueuedReplot);
            ++count;
        }
    }
}
