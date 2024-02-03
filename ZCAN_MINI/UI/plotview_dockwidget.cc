#include "plotview_dockwidget.h"
#include "ui_plot_dockwidget.h"

PlotViewDockWidget::PlotViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PlotViewDockWidget),
    tracer_(nullptr),
    tracer_label_(nullptr),
    plot_num_(0)
{
    ui->setupUi(this);

    sig_plot_.clear();
    plot_threads.clear();

    QCustomPlot *plot = ui->plot;

    connect(plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(CustomPlotMousePress(QMouseEvent*)));
    connect(plot, SIGNAL(selectionChangedByUser()), this, SLOT(CustomPlotSelectionChanged()));
    this->p_DataTracer = new DataTracer(plot);
}

PlotViewDockWidget::~PlotViewDockWidget()
{
    delete ui;
}

void PlotViewDockWidget::slot_checkState_changed(Qt::CheckState state, const unsigned long long msg_id, const CppCAN::CANSignal &signal)
{
    QCustomPlot *plot = ui->plot;
    if (Qt::Checked == state)
    {
        if (sig_plot_.end() != sig_plot_.find(signal.name()))
        {
            int index = *sig_plot_.find(signal.name());
            PlotGraphThread *plotgraph_thread = plot_threads.at(index);
            plotgraph_thread->beginThread();
            plot->graph(index)->setVisible(true);
            return;
        }

        //设置属性可缩放，移动等
        plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                         QCP::iSelectLegend | QCP::iSelectPlottables);
        //设置坐标轴标签名称
        plot->xAxis->setLabel("timestamp");
        plot->yAxis->setLabel("value");
        plot->legend->setVisible(true);

        //  plot->axisRect()->setupFullAxesBox();
        plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        ++plot_num_;    // 曲线总数加一
        sig_plot_.insert(signal.name(), plot_num_-1);  // 将信号与曲线关联起来
        plot->graph(plot_num_-1)->setName(QString::fromStdString(signal.name()));//曲线名称

        PlotGraphThread *plotgraph_thread = new PlotGraphThread(plot, plot_num_-1, msg_id, signal);
        plot_threads.append(plotgraph_thread);
        plotgraph_thread->start();
        plotgraph_thread->beginThread();

        //设置坐标轴显示范围,否则我们只能看到默认的范围
        QSharedPointer<QCPAxisTickerDateTime> date_tick(new QCPAxisTickerDateTime);
        date_tick->setDateTimeFormat("HH:mm:ss.zzz");
        plot->xAxis->setTicker(date_tick);

        plot->graph(plot_num_-1)->rescaleAxes();
        plot->replot();
    }
    else if (Qt::Unchecked == state)
    {
        int index = *sig_plot_.find(signal.name());
        PlotGraphThread *plotgraph_thread = plot_threads.at(index);
        plotgraph_thread->pauseThread();
        //plot->removeGraph(index);
        plot->graph(index)->setVisible(false);
    }
}

void PlotViewDockWidget::CustomPlotMousePress(QMouseEvent *event)
{
    this->m_PressedPoint = event->pos();
}

void PlotViewDockWidget::CustomPlotSelectionChanged()
{
    QCustomPlot *plot = ui->plot;
    if (plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) || plot->xAxis->selectedParts().testFlag(QCPAxis::spAxisLabel))
    {
        plot->xAxis2->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels | QCPAxis::spAxisLabel);
        plot->xAxis->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels | QCPAxis::spAxisLabel);
    }
    if (plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || plot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) || plot->yAxis->selectedParts().testFlag(QCPAxis::spAxisLabel))
    {
        plot->yAxis2->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels | QCPAxis::spAxisLabel);
        plot->yAxis->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels | QCPAxis::spAxisLabel);
    }

    int graph_index = -1;
    bool haveselected=false;
    for (int i=0; i<plot->graphCount(); ++i)
    {
        QCPGraph *graph = plot->graph(i);
        graph->setVisible(false);
        QCPPlottableLegendItem *item = plot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            //仅显示当前被选中的曲线
            graph_index = i;
            haveselected=true;
            graph->setVisible(true);
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }

    if(!haveselected){
        this->p_DataTracer->setVisible(false);
        for (int i=0; i<plot->graphCount(); ++i){
            plot->graph(i)->setVisible(true);
        }
    }else{
        this->p_DataTracer->setVisible(true);
        double key, value;
        FindSelectedPoint(plot->graph(graph_index), this->m_PressedPoint, key, value);
        QDateTime time = QCPAxisTickerDateTime::keyToDateTime(key);
        this->p_DataTracer->setText(time.toString("Time:hh:mm.ss.zzz"), QString("Depth:%1m").arg(value, 0,'f',2));
        this->p_DataTracer->updatePosition(plot->graph(graph_index), key, value);
    }
}

void PlotViewDockWidget::FindSelectedPoint(QCPGraph *graph, QPoint select_point, double &key, double &value)
{
    double temp_key, temp_value;
    graph->pixelsToCoords(select_point, temp_key, temp_value);
    QSharedPointer<QCPGraphDataContainer> tmpContainer;
    tmpContainer = graph->data();
    int low=0, high=tmpContainer->size();

    if(tmpContainer->size()<3){
        if(tmpContainer->size() == 1){
            key = tmpContainer->constBegin()->mainKey();
            value = tmpContainer->constBegin()->mainValue();
            return;
        }else if(tmpContainer->size() == 2){
            double diff1 = qAbs(tmpContainer->at(1)->mainKey()-temp_key);
            double diff2 = qAbs(tmpContainer->at(0)->mainKey()-temp_key);
            if(diff1 <= diff2){
                key =  tmpContainer->at(1)->mainKey();
                value = tmpContainer->at(1)->mainValue();
            }else{
                key = tmpContainer->at(0)->mainKey();
                value = tmpContainer->at(0)->mainValue();
            }
            return;
        }
    }

    while (high>low) {
        int mid = (low+high)>>1;
        if(temp_key == (tmpContainer->constBegin()+mid)->mainKey()){
            key = temp_key;
            value = (tmpContainer->constBegin()+mid)->mainValue();
            break;
        }else if(temp_key > (tmpContainer->constBegin()+mid)->mainKey()){
            low = mid;
        }else if(temp_key < (tmpContainer->constBegin()+mid)->mainKey()){
            high = mid;
        }
        if(high - low <= 1){
            double diff1 = qAbs((tmpContainer->constBegin()+high)->mainKey()-temp_key);
            double diff2 = qAbs((tmpContainer->constBegin()+low)->mainKey()-temp_key);
            if(diff1 <= diff2){
                key =  (tmpContainer->constBegin()+high)->mainKey();
                value = (tmpContainer->constBegin()+high)->mainValue();
            }else{
                key = (tmpContainer->constBegin()+low)->mainKey();
                value = (tmpContainer->constBegin()+low)->mainValue();
            }
            break;
        }
    }
}
