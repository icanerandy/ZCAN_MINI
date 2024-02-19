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

    QCustomPlot* const plot = ui->plot;

    //设置坐标轴显示范围,否则我们只能看到默认的范围
    QSharedPointer<QCPAxisTickerDateTime> date_tick(new QCPAxisTickerDateTime);
    date_tick->setDateTimeFormat("mm:ss.zzz");
    date_tick->setTickCount(10);   // 设置时间轴，一共多少格
    plot->xAxis->setTicker(date_tick);
    plot->xAxis->setTickLabelRotation(35);

    plot->yAxis->setVisible(true);
    plot->yAxis2->setVisible(true);

    plot->axisRect()->setupFullAxesBox();   // 四周安上轴并显示
    plot->axisRect()->setBackground(QBrush(Qt::black)); // 设置背景颜色

    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    // 设置图例
    plot->legend->setBrush(QColor(255, 255, 255, 150));   // 设置图例为灰色透明
    plot->legend->setVisible(true); // 设置图例可见

    //设置属性可缩放，移动等
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                     QCP::iSelectLegend | QCP::iSelectPlottables);

    plot->legend->setSelectableParts(QCPLegend::spItems);    //设置legend只能选择图例

    connect(plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(slot_customPlot_mousePress(QMouseEvent*)));
    connect(plot, SIGNAL(selectionChangedByUser()), this, SLOT(slot_customPlot_selectionChanged()));
    connect(plot->legend, SIGNAL(legendClicked(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)),
            this, SLOT(onLegendClicked(QCPLegend*, QCPAbstractLegendItem*)));
    this->p_DataTracer = new DataTracer(plot);

    plot->replot();
}

PlotViewDockWidget::~PlotViewDockWidget()
{
    delete ui;
}

void PlotViewDockWidget::slot_checkState_changed(const Qt::CheckState state, const unsigned long long msg_id, const CppCAN::CANSignal &signal)
{
    QCustomPlot* const plot = ui->plot;
    if (Qt::Checked == state)
    {
        plot->addGraph();//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        ++plot_num_;    // 曲线总数加一
        sig_plot_.insert(signal.name(), plot_num_-1);  // 将信号与曲线关联起来

        QColor color(20+200/4.0*plot_num_,70*(1.6-plot_num_/4.0), 150, 150);
        plot->graph()->setLineStyle(QCPGraph::lsLine);
        plot->graph()->setPen(QPen(color.lighter(200)));
        plot->graph()->setBrush(QBrush(color));
        plot->graph()->setName(QString::fromStdString(signal.name()));//曲线名称

        // 坐标轴自动缩放
        if (1 == plot_num_)
            plot->graph()->rescaleAxes();
        else
            plot->graph()->rescaleAxes(true);

        plot->replot();

        PlotGraphThread* plotgraph_thread = new PlotGraphThread(plot, plot_num_-1, msg_id, signal);
        plot_threads.append(plotgraph_thread);
        plotgraph_thread->start();
        plotgraph_thread->beginThread();
    }
    else if (Qt::Unchecked == state)
    {
        const int index = *sig_plot_.find(signal.name());
        PlotGraphThread* const plotgraph_thread = plot_threads.at(index);
        plotgraph_thread->stopThread();

        plot->removeGraph(index);
        sig_plot_.remove(signal.name());
    }
}

void PlotViewDockWidget::slot_customPlot_mousePress(QMouseEvent *event)
{
    this->m_PressedPoint = event->pos();
}

void PlotViewDockWidget::slot_customPlot_selectionChanged()
{
    QCustomPlot* const plot = ui->plot;
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
        findSelectedPoint(plot->graph(graph_index), this->m_PressedPoint, key, value);
        QDateTime time = QCPAxisTickerDateTime::keyToDateTime(key);
        this->p_DataTracer->setText(time.toString("Time:mm.ss.zzz"), QString("Value:%1m").arg(value, 0,'f',2));
        this->p_DataTracer->updatePosition(plot->graph(graph_index), key, value);
    }
}

void PlotViewDockWidget::onLegendClicked(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    Q_UNUSED(legend);
    QCPPlottableLegendItem* plottableLegendItem = qobject_cast<QCPPlottableLegendItem*>(item);
    if (plottableLegendItem)
    {
        QCPAbstractPlottable* plottable = plottableLegendItem->plottable();
        if (plottable)
        {
            plottable->setVisible(!plottable->visible());
            ui->plot->replot();
        }
    }
}

void PlotViewDockWidget::findSelectedPoint(QCPGraph *graph, QPoint select_point, double &key, double &value)
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
