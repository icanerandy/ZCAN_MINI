#ifndef DEVIATIONREPLOT_H
#define DEVIATIONREPLOT_H

#include <QObject>

#include "qcustomplot.h"

class DeviationReplot : public QObject
{
    Q_OBJECT
public:
    explicit DeviationReplot(QCustomPlot* plot);

Q_SIGNALS:
    void sig_replot();

private Q_SLOTS:
    void replotData(); // 定时重绘

private:
    QCustomPlot* const plot_;

    QTimer timer_;
};

#endif // DEVIATIONREPLOT_H
