#include "plotview_dockwidget.h"
#include "ui_plot_dockwidget.h"

PlotViewDockWidget::PlotViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PlotViewDockWidget)
{
    ui->setupUi(this);
}

PlotViewDockWidget::~PlotViewDockWidget()
{
    delete ui;
}

void PlotViewDockWidget::slot_checkState_Changed(Qt::CheckState state, const unsigned long long msg_id, const CppCAN::CANSignal &signal)
{
    QCustomPlot *plot = ui->plot;
    if (Qt::Checked == state)
    {
        //设置属性可缩放，移动等
        plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                         QCP::iSelectLegend | QCP::iSelectPlottables);
        //设置坐标轴标签名称
        plot->xAxis->setLabel("timestamp");
        plot->yAxis->setLabel("value");
        plot->legend->setVisible(true);

        //  plot->axisRect()->setupFullAxesBox();
        plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        plot->graph(0)->setName(QString::fromStdString(signal.name()));//曲线名称
        PlotGraphThread *plotgraph_thread = new PlotGraphThread(plot);
        plotgraph_thread->start();
        plotgraph_thread->beginThread();

        //设置坐标轴显示范围,否则我们只能看到默认的范围
        QSharedPointer<QCPAxisTickerDateTime> date_tick(new QCPAxisTickerDateTime);
        date_tick->setDateTimeFormat("HH:mm:ss");
        plot->xAxis->setTicker(date_tick);

        plot->graph(0)->rescaleAxes();
        plot->replot();
    }
    else if (Qt::Unchecked == state)
    {

    }
}
