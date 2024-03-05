#include "myplot.h"

MyPlot::MyPlot(QWidget* widget) :
    QCustomPlot(widget),
    text_label_(new QCPItemText(this)),
    arrow_(new QCPItemLine(this)),
    tracer_(new QCPItemTracer(this)),
    tracer_x_label_(new QCPItemText(this)),
    tracer_y_label_(new QCPItemText(this)),
    tracer_enable_(true),
    tracer_graph_(nullptr)
{
    //下面这一段是从QCustomPlot官网抄来的
    /*显示数值的提示框*/
    text_label_->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);//方框置于上部中间
    text_label_->position->setType(QCPItemPosition::ptAxisRectRatio);
    text_label_->position->setCoords(0.5, 0); // place position at center/top of axis rect
    text_label_->setFont(QFont(font().family(), 16)); // 字体
    text_label_->setPen(QPen(Qt::black)); // 颜色
    text_label_->setBrush(QBrush(Qt::green));

    //指向数值的箭头:
    arrow_->start->setParentAnchor(text_label_->bottom);//箭头起点位于提示框的下边框中点
    //arrow->end->setCoords(4, 1.6); // 设置箭头的终点
    arrow_->setHead(QCPLineEnding::esSpikeArrow);//箭头类型
    text_label_->setVisible(false);//提示框不可见
    arrow_->setVisible(false);//箭头不可见

    // 游标
    QPen pen(Qt::black); // 可以选择您想要的颜色
    pen.setWidth(2); // 设置线条的宽度为2，您可以根据需要调整这个值
    pen.setStyle(Qt::DashLine); // 设置线型为虚线
    tracer_->setPen(pen);

    tracer_->setPen(QPen(Qt::DashLine));    // 游标线型：虚线
    tracer_->setStyle(QCPItemTracer::tsPlus);   // 游标样式：十字星、圆圈、方框等
    tracer_->setInterpolating(false);   // 游标禁用插值

    // 游标显示的提示框
    pen.setStyle(Qt::SolidLine);
    tracer_x_label_->position->setType(QCPItemPosition::ptAxisRectRatio);
    tracer_x_label_->setFont(QFont(font().family(), 12)); // 字体
    tracer_x_label_->setPen(pen); // 颜色
    tracer_x_label_->setBrush(QBrush(Qt::green));

    tracer_y_label_->position->setType(QCPItemPosition::ptAxisRectRatio);
    tracer_y_label_->setFont(QFont(font().family(), 12)); // 字体
    tracer_y_label_->setPen(pen); // 颜色
    tracer_y_label_->setBrush(QBrush(Qt::green));
}

void MyPlot::mousePressEvent(QMouseEvent *event)
{
    //重写后，仍然要使父类的函数，否则自带的拖动功能等就失效了
    QCustomPlot::mousePressEvent(event);//父类的函数

    if(event->buttons() & Qt::LeftButton)//按下鼠标左键
    {
        text_label_->setVisible(true);//提示框可见
        arrow_->setVisible(true);//箭头可见
        double x = xAxis->pixelToCoord(event->pos().x());//鼠标坐标转化为XY轴的坐标
        double y = yAxis->pixelToCoord(event->pos().y());
        arrow_->end->setCoords(x, y); // 设置箭头的终点
        QString xTime = QDateTime::fromMSecsSinceEpoch(x * 1000.0).toString("hh:mm:ss.zzz");//把单击处的X值转换为时间String
        text_label_->setText(QString("x = %1\ny=%2").arg(xTime).arg(y));//显示XY值
    }
}

void MyPlot::mouseReleaseEvent(QMouseEvent *event)
{
    QCustomPlot::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)//左键弹起
    {
        text_label_->setVisible(false);//隐藏数值方框和箭头
        arrow_->setVisible(false);
    }
}

void MyPlot::wheelEvent(QWheelEvent *event)
{
    if (xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    {
        axisRect()->setRangeZoom(xAxis->orientation());
        // axisRect()->setRangeZoomFactor(1.2,1);//x方向为1.2
    }
    else if (yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    {
        axisRect()->setRangeZoom(yAxis->orientation());
        // axisRect()->setRangeZoomFactor(1.2,1);//x方向为1.2
    }
    else
        axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);

    QCustomPlot::wheelEvent(event);
}

void MyPlot::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);//避免让父类的移动事件失效

    if(tracer_enable_ && tracer_graph_)//游标使能 检查一下游标附着的graph是否还存在
    {
        // 计算鼠标当前的 X 和 Y 坐标
        double x = xAxis->pixelToCoord(event->pos().x());
        double y = yAxis->pixelToCoord(event->pos().y());

        tracer_->setGraph(tracer_graph_);//设置游标吸附在traceGraph这条曲线上
        tracer_->setGraphKey(x);//设置游标的X值（这就是游标随动的关键代码）
        double traceX = tracer_->position->key();
        double traceY = tracer_->position->value();

        // 更新 tracer_x_label_ 的位置和文本
        tracer_x_label_->position->setType(QCPItemPosition::ptPlotCoords);
        tracer_x_label_->position->setCoords(traceX, yAxis->range().lower); // 设置在X轴上方显示X值
        tracer_x_label_->setPositionAlignment(Qt::AlignBottom | Qt::AlignRight); // 标签对齐方式
        tracer_x_label_->setText(QDateTime::fromMSecsSinceEpoch(traceX * 1000.0).toString("x = hh:mm:ss.zzz"));

        // 更新 tracer_y_label_ 的位置和文本
        tracer_y_label_->position->setType(QCPItemPosition::ptPlotCoords);
        tracer_y_label_->position->setCoords(xAxis->range().lower, traceY); // 设置在Y轴旁边显示Y值
        tracer_y_label_->setPositionAlignment(Qt::AlignLeft); // 标签对齐方式
        tracer_y_label_->setText(QString("y = ") + QString::number(traceY));


        //计算游标X值对应的所有曲线的Y值
        for(int i = 0; i < graphCount(); i++)
        {
            //搜索左边离traceX最近的key对应的点，详情参考findBegin函数的帮助
            QCPDataContainer<QCPGraphData>::const_iterator coorPoint = graph(i)->data().data()->findBegin(traceX, true);//true代表向左搜索
        }

        tracer_->setStyle(QCPItemTracer::tsCrosshair);   // 游标样式：十字星、圆圈、方框等
        tracer_->setVisible(true);
        tracer_x_label_->setVisible(true);
        tracer_y_label_->setVisible(true);
    }
    else
    {
        tracer_->setStyle(QCPItemTracer::tsPlus);   // 游标样式：十字星、圆圈、方框等
        tracer_->setVisible(false);
        tracer_x_label_->setVisible(false);
        tracer_y_label_->setVisible(false);
    }
}

void MyPlot::set_tracer_graph(QCPGraph *tracer_graph)
{
    tracer_graph_ = tracer_graph;
}
