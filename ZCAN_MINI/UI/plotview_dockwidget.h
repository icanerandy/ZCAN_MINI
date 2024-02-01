#ifndef PLOT_DOCKWIDGET_H
#define PLOT_DOCKWIDGET_H

#include <QObject>
#include <QDockWidget>
#include "qcustomplot.h"

namespace Ui {
class PlotViewDockWidget;
}

class PlotViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit PlotViewDockWidget(QWidget *parent = 0);
    ~PlotViewDockWidget();

private:
    Ui::PlotViewDockWidget *ui;
};

#endif // PLOT_DOCKWIDGET_H
