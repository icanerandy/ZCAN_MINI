#include "plot_dockwidget.h"
#include "ui_plot_dockwidget.h"

PlotDockWidget::PlotDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PlotDockWidget)
{
    ui->setupUi(this);
}

PlotDockWidget::~PlotDockWidget()
{
    delete ui;
}
