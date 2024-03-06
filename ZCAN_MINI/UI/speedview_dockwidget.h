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
#include "CANDatabase.h"
#include "qcustomplot.h"
#include "plotdata_thread.h"
#include "replot_thread.h"
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

public slots:
    void slot_selectionChanged();
    void slot_paint(bool enabled, const unsigned long long msg_id, QList<CppCAN::CANSignal*>& sig_lst);
    void slot_actDisPic_triggered();
    bool slot_actSavePic_triggered();
    void slot_actSaveExcel_triggered();

private:
    Ui::SpeedViewDockWidget* const ui;
    PlotDataThread* plot_thread_;
    DistributionDialog* distribution_dialog_;

    SignalParserThread* signal_parser_thread_;
    PlotDataThread* plotdata_thread_;
    ReplotThread* replot_thread_;
};

#endif // PLOT_DOCKWIDGET_H
