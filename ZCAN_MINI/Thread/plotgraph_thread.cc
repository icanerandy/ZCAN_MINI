#include "plotgraph_thread.h"

PlotGraphThread::PlotGraphThread(QCustomPlot *plot)
    : plot_(plot)
{
    RecMsgThread *rec_msg_thread = RecMsgThread::GetInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_Receive_Data *, uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(ZCAN_Receive_Data *, uint)>(&PlotGraphThread::slot_newMsg));
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotGraphThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&PlotGraphThread::slot_newMsg));
}

void PlotGraphThread::beginThread()
{
    m_pause = false;
}

void PlotGraphThread::pauseThread()
{
    m_pause = true;
}

void PlotGraphThread::stopThread()
{
    m_stop = true;
}

void PlotGraphThread::run()
{
    // 线程任务
    m_stop = false;

    while (!m_stop) // 循环主体
    {
        if (!m_pause)
        {
            //分类信号

            //绘制图像

            //避免无数据时变成While(1),会占用大量的CPU
            msleep(15);
        }
    }
    quit(); // 相当于exit(0)，退出线程的事件循环
}

void PlotGraphThread::slot_newMsg(ZCAN_Receive_Data *can_data, uint len)
{
    //key的单位是 ms
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    double value = test_value_;
    test_value_ -= 10;
    if (0 == test_value_)
        test_value_ = 1000;

    //这里的1，是指横坐标时间宽度为1s，如果想要横坐标显示更多的时间
    //就把1调整为比较大到值，比如要显示10s，那就改成10。
    plot_->graph(0)->addData(key, value);
    plot_->xAxis->setRange(key+0.1, /*100*/1, Qt::AlignRight);
    plot_->replot();
}

void PlotGraphThread::slot_newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len)
{

}

