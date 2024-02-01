#ifndef PLOT_DOCKWIDGET_H
#define PLOT_DOCKWIDGET_H

#include <QObject>
#include <QDockWidget>
#include "zlgcan.h"
#include "CANDatabase.h"
#include "qcustomplot.h"
#include "plotgraph_thread.h"

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
    void slot_checkState_Changed(Qt::CheckState state, const unsigned long long msg_id, const CppCAN::CANSignal &signal);

private:
    Ui::PlotViewDockWidget *ui;

};

#endif // PLOT_DOCKWIDGET_H
