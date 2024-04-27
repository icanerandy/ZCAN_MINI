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
    QVector<QCPGraphData>* data = plot_->graph(0)->data()->coreData();;
    data->push_back(QCPGraphData( key, abs_deviation ));

    if (qAbs(abs_deviation) >= default_deviation_value_)
    {
        QVector<QCPGraphData>* exception_data = plot_->graph(1)->data()->coreData();;
        exception_data->push_back(QCPGraphData( key, abs_deviation ));
    }
}
