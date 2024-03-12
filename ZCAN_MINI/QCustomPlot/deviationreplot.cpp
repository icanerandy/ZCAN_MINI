#include "deviationreplot.h"

DeviationReplot::DeviationReplot(QCustomPlot* plot)
    : plot_(plot)
{
    connect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
    timer_.start(0);
}

void DeviationReplot::replotData()
{
    double key = 0;
    if (plot_->graphCount() > 0 && plot_->graph(0)->dataCount() > 0)
        key = plot_->graph(0)->data()->coreData()->at(plot_->graph(0)->dataCount()-1).key;

    QCPBars *bars = nullptr;
    if (plot_->plottableCount() > 0) {
        // 获取第一个 plottable（这里假设 bars 是第二个 plottable）
        bars = dynamic_cast<QCPBars*>(plot_->plottable(2));
    }
    double currentScale = plot_->xAxis->range().size(); // 获取当前x轴范围大小
    double barWidth = currentScale / 10000; // 假设我们基于当前范围的一部分来设置柱宽
    bars->setWidth(barWidth);

    // if (plot_->graphCount() > 0 && plot_->graph(0)->dataCount() > 0) {
    //     key = plot_->graph(0)->data()->coreData()->at(plot_->graph(0)->dataCount()-1).key; // 获取最新的key值
    //     QCPRange range = plot_->xAxis->range(); // 获取当前x轴的范围

    //     // 如果最新的key值超出当前x轴的最大值
    //     if (key >= range.upper) {
    //         // 计算新的范围，以保持范围宽度不变，同时将最新数据点纳入范围内
    //         double newLower = key /*+ key * 0.01*/ - (range.upper - range.lower); // 计算新的最小值
    //         double newUpper = key /*+ key * 0.01*/; // 计算新的最大值，添加一小部分边缘
    //         plot_->xAxis->setRange(newLower, newUpper); // 设置新的x轴范围
    //     }
    // }

    emit sig_replot();
    // plot_->replot(QCustomPlot::rpQueuedReplot);

    // static QTime time(QTime::currentTime());
    // double current_time = time.elapsed()/1000.0;
    // static double last_time = time.elapsed()/1000.0;
    // static int frame_count;
    // ++frame_count;
    // if (current_time - last_time > 2) // 每2秒求一次平均值
    // {
    //     emit sig_frmChanged(QString("FPS %1, Total Data points: %2")
    //                             .arg(frame_count/(current_time-last_time), 0, 'f', 0)
    //                             .arg(plot_->graph(0)->data()->size()+plot_->graph(1)->data()->size()));
    //     last_time = current_time;
    //     frame_count = 0;
    // }
}
