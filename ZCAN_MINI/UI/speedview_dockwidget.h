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
#include "plotdata.h"
#include "replot.h"
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
    void addGraphs(const uint32_t msg_id, QList<Vector::DBC::Signal*>& sig_lst);

public slots:
    void slot_selectionChanged();
    void slot_paint(bool enabled, const uint32_t msg_id, QList<Vector::DBC::Signal*>& sig_lst);
    void slot_actDisPic_triggered();
    bool slot_actSavePic_triggered();
    void slot_actSaveExcel_triggered();

private:
    Ui::SpeedViewDockWidget* const ui;
    PlotData* plot_thread_;
    DistributionDialog* distribution_dialog_;

    SignalParser* signal_parser_;
    PlotData* plotdata_;
    Replot* replot_;

    QThread* signal_parser_thread_;
    QThread* plotdata_thread_;
    QThread* replot_thread_;
};

#endif // PLOT_DOCKWIDGET_H
