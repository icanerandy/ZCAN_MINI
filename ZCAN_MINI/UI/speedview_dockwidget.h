#ifndef PLOT_DOCKWIDGET_H
#define PLOT_DOCKWIDGET_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QObject>
#include <QMap>
#include <QDockWidget>
#include <QMouseEvent>
#include "zlgcan.h"
#include "Vector/DBC.h"
#include "qcustomplot.h"
#include "lineplot.h"
#include "linereplot.h"
#include "deviationplot.h"
#include "deviationreplot.h"
#include "distribution_dialog.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include <GL/freeglut.h>

namespace Ui {
class SpeedViewDockWidget;
}

class SpeedViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SpeedViewDockWidget(QWidget *parent = 0);
    ~SpeedViewDockWidget();

private:
    void initPlot(QCustomPlot* const plot);
    void addGraphs(QCustomPlot* const plot, const uint32_t msg_id, QList<Vector::DBC::Signal>& sig_lst);
    void initThread(const uint32_t msg_id, QList<Vector::DBC::Signal>& sig_lst);
    void destroyThread();

public slots:
    void slot_selectionChanged();
    void slot_paint(bool enabled, const uint32_t msg_id, QList<Vector::DBC::Signal>& sig_lst);
    void slot_actDisPic_triggered();
    bool slot_actSavePic_triggered();
    void slot_actSaveExcel_triggered();

private:
    Ui::SpeedViewDockWidget* const ui;
    DistributionDialog* distribution_dialog_;

    SignalParser* signal_parser_;
    LinePlot* line_plot_;
    LineReplot* line_replot_;
    DeviationPlot* deviation_plot_;
    DeviationReplot* deviation_replot_;

    QThread* signal_parser_thread_;
    QThread* line_plot_thread_;
    QThread* line_replot_thread_;
    QThread* deviation_plot_thread_;
    QThread* deviation_replot_thread_;
};

#endif // PLOT_DOCKWIDGET_H
