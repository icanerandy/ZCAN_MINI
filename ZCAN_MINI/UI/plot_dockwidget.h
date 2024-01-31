#ifndef PLOT_DOCKWIDGET_H
#define PLOT_DOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class PlotDockWidget;
}

class PlotDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit PlotDockWidget(QWidget *parent = 0);
    ~PlotDockWidget();

private:
    Ui::PlotDockWidget *ui;
};

#endif // PLOT_DOCKWIDGET_H
