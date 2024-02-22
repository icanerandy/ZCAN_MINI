#ifndef PLOT_DOCKWIDGET_H
#define PLOT_DOCKWIDGET_H

#include <QObject>
#include <QMap>
#include <QDockWidget>
#include "zlgcan.h"
#include "CANDatabase.h"
#include "qcustomplot.h"
#include "plotgraph_thread.h"
#include "replot_thread.h"
#include "datatracer.h"

#include <GL/freeglut.h>

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
    void slot_paint(const unsigned long long msg_id, const CppCAN::CANSignal& ref_speed, const CppCAN::CANSignal& rel_speed);
    bool slot_btnSave_clicked(bool checked);

private slots:
    void slot_customPlot_mousePress(QMouseEvent* event);
    void slot_customPlot_selectionChanged();
    void onLegendClicked(QCPLegend* legend, QCPAbstractLegendItem* item);

private:
    void findSelectedPoint(QCPGraph *graph, QPoint select_point, double &key, double &value);

private:
    QPoint m_PressedPoint;
    DataTracer *p_DataTracer;

private:
    Ui::PlotViewDockWidget * const ui;
    QCPItemTracer *tracer_;
    QCPItemText *tracer_label_;
    PlotGraphThread* plot_thread_;
};

#endif // PLOT_DOCKWIDGET_H
