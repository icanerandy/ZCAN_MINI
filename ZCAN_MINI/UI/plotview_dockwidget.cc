#include "plotview_dockwidget.h"
#include "ui_plot_dockwidget.h"

PlotViewDockWidget::PlotViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PlotViewDockWidget)
{
    ui->setupUi(this);

    //blue line
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::blue));

    //xAxis
    ui->plot->axisRect()->setupFullAxesBox();

    ui->plot->xAxis->setRange(1, 1, Qt::AlignRight);
    ui->plot->yAxis->setRange(30, 30, Qt::AlignRight);

    ui->plot->xAxis->setLabel("I(A)");
    ui->plot->yAxis->setLabel("U(V)");
}

PlotViewDockWidget::~PlotViewDockWidget()
{
    delete ui;
}
