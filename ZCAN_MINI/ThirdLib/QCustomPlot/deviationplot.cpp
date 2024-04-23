#include "deviationplot.h"

DeviationPlot::DeviationPlot(QCustomPlot* const plot)
    : plot_(plot),
    default_deviation_value_(100)
{
}

void DeviationPlot::set_default_deviation_value_(double value)
{
    default_deviation_value_ = value;
}

void DeviationPlot::slot_absDeviation(double key, double abs_deviation)
{
    // QVector<QCPGraphData>* data = nullptr;

    QCPBars* bars = static_cast<QCPBars*>(plot_->plottable(0));
    bars->addData(key, abs_deviation);

    if (qAbs(abs_deviation) >= default_deviation_value_)
    {
        QCPBars* bars_exception = static_cast<QCPBars*>(plot_->plottable(1));
        bars_exception->addData(key, abs_deviation);
    }
}
