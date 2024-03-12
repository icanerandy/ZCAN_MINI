#include "linereplot.h"

LineReplot::LineReplot(QCustomPlot* const plot) :
    plot_(plot)
{
    connect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
    timer_.start(0);
}

void LineReplot::replotData()
{
    double key = 0;
    if (plot_->graphCount() > 0 && plot_->graph(0)->dataCount() > 0)
        key = plot_->graph(0)->data()->coreData()->at(plot_->graph(0)->dataCount()-1).key;

    plot_->replot(QCustomPlot::rpQueuedReplot);

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
