#ifndef DEVIATIONPLOT_H
#define DEVIATIONPLOT_H

#include <QObject>

#include "qcustomplot.h"

class DeviationPlot : public QObject
{
    Q_OBJECT
public:
    explicit DeviationPlot(QCustomPlot* const plot);
    void set_default_deviation_value_(double value);

public Q_SLOTS:
    void slot_absDeviation(double key, double abs_deviation);

private:
    QCustomPlot* const plot_;

    double default_deviation_value_;
};

#endif // DEVIATIONPLOT_H
