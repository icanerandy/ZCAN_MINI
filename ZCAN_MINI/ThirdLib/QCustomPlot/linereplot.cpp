#include "linereplot.h"

LineReplot::LineReplot(QCustomPlot* const plot) :
    plot_(plot)
{
    connect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
    timer_.start(10);
}

void LineReplot::replotData()
{
    double key = 0;
    if (plot_->graphCount() > 0 && plot_->graph(0)->dataCount() > 0) {
        key = plot_->graph(0)->data()->coreData()->at(plot_->graph(0)->dataCount()-1).key; // 获取最新的key值
        QCPRange range = plot_->xAxis->range(); // 获取当前x轴的范围

        // 如果最新的key值超出当前x轴的最大值
        if (key >= range.upper) {
            // 计算新的范围，以保持范围宽度不变，同时将最新数据点纳入范围内
            double newLower = key + (range.upper - range.lower)/5 - (range.upper - range.lower); // 计算新的最小值
            double newUpper = key + (range.upper - range.lower)/5; // 计算新的最大值，添加一小部分边缘
            plot_->xAxis->setRange(newLower, newUpper); // 设置新的x轴范围
        }
    }

    emit sig_replot();

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
