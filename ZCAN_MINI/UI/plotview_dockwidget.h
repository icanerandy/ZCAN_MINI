#ifndef PLOT_DOCKWIDGET_H
#define PLOT_DOCKWIDGET_H

#include <QObject>
#include <QMap>
#include <QDockWidget>
#include "zlgcan.h"
#include "CANDatabase.h"
#include "qcustomplot.h"
#include "plotgraph_thread.h"
#include "datatracer.h"

namespace Ui {
class PlotViewDockWidget;
}

class PlotViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit PlotViewDockWidget(QWidget *parent = 0);
    ~PlotViewDockWidget();

public slots:
    void slot_checkState_changed(Qt::CheckState state, const unsigned long long msg_id, const CppCAN::CANSignal &signal);

private slots:
    void CustomPlotMousePress(QMouseEvent* event);
    void CustomPlotSelectionChanged();
private:
    void FindSelectedPoint(QCPGraph *graph, QPoint select_point, double &key, double &value);
private:
    QPoint m_PressedPoint;
    DataTracer *p_DataTracer;

private:
    Ui::PlotViewDockWidget *ui;
    QCPItemTracer *tracer_;
    QCPItemText *tracer_label_;
    uint plot_num_;
    QMap<std::string, uint> sig_plot_;
    QList<PlotGraphThread *> plot_threads;
};

#endif // PLOT_DOCKWIDGET_H
