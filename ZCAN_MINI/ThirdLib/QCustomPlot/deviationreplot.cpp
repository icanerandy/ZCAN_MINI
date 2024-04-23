#include "deviationreplot.h"

DeviationReplot::DeviationReplot(QCustomPlot* plot)
    : plot_(plot)
{
    connect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
    timer_.start(30);
}

void DeviationReplot::start()
{
    connect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
    timer_.start(30);
}

void DeviationReplot::pause()
{
    disconnect(&timer_, SIGNAL(timeout()), this, SLOT(replotData()));
    timer_.stop();
}

void DeviationReplot::replotData()
{  
    emit sig_replot();
}
