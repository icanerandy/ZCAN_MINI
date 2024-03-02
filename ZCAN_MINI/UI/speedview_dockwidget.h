#ifndef PLOT_DOCKWIDGET_H
#define PLOT_DOCKWIDGET_H

#include <QObject>
#include <QMap>
#include <QDockWidget>
#include <QMouseEvent>
#include "zlgcan.h"
#include "CANDatabase.h"
#include "qcustomplot.h"
#include "plotdata_thread.h"
#include "replot_thread.h"

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
    void slot_paint(const unsigned long long msg_id, QList<CppCAN::CANSignal*>& sig_lst);
    bool slot_btnSave_clicked(bool checked);

private slots:
    void slot_btnExcel_clicked(bool checked);

private:
    Ui::SpeedViewDockWidget* const ui;
    PlotDataThread* plot_thread_;
};

#endif // PLOT_DOCKWIDGET_H
