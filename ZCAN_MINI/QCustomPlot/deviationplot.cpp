#include "deviationplot.h"

DeviationPlot::DeviationPlot(QCustomPlot* const plot)
    : plot_(plot)
{
    bars_ = new QCPBars(plot_->xAxis, plot_->yAxis);// 示例：根据图表的缩放级别动态设置柱宽
    double currentScale = plot_->xAxis->range().size(); // 获取当前x轴范围大小
    double barWidth = currentScale / 10000; // 假设我们基于当前范围的一部分来设置柱宽
    bars_->setWidth(barWidth);

    // plot_->addPlottable(bars);
}

void DeviationPlot::slot_absDeviation(double key, double abs_deviation)
{
    static int count = 0;

    QVector<QCPGraphData>* data = nullptr;

    data = plot_->graph(0)->data()->coreData();
    data->push_back(QCPGraphData( key, abs_deviation ));
    data = plot_->graph(1)->data()->coreData();
    data->push_back(QCPGraphData( key, 0 ));

    // bars_->addData(key, abs_deviation);

    if (count == 0)
    {
        plot_->xAxis->setRange(key, key + 10);
        plot_->replot(QCustomPlot::rpQueuedReplot);
        ++count;
    }
}
