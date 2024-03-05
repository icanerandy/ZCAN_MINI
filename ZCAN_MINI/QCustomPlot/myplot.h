#ifndef MYPLOT_H
#define MYPLOT_H

#include <QObject>
#include "qcustomplot.h"

class MyPlot : public QCustomPlot
{
public:
    MyPlot(QWidget* widget);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public:
    void set_tracer_graph(QCPGraph* tracer_graph);

private:
    QCPItemText* const text_label_;
    QCPItemLine* const arrow_;
    QCPItemTracer* const tracer_;
    QCPItemText* const tracer_x_label_;
    QCPItemText* const tracer_y_label_;
    bool tracer_enable_;
    QCPGraph* tracer_graph_;
};

#endif // MYPLOT_H
