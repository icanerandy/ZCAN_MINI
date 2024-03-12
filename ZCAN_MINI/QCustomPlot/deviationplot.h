#ifndef DEVIATIONPLOT_H
#define DEVIATIONPLOT_H

#include <QObject>

#include "qcustomplot.h"

class DeviationPlot : public QObject
{
    Q_OBJECT
public:
    explicit DeviationPlot(QCustomPlot* const plot);

public Q_SLOTS:
    void slot_absDeviation(double key, double abs_deviation);

private:
    QCustomPlot* const plot_;
    QCPBars* bars_;
};

#endif // DEVIATIONPLOT_H
