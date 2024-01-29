#include "canview_dockwidget.h"
#include "ui_canview_dockwidget.h"

CanViewDockWidget::CanViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CanViewDockWidget)
{
    ui->setupUi(this);

    connect(ui->btnClear, &QPushButton::clicked, this, &slot_btnClear_clicked);
    connect(ui->btnPause, &QPushButton::clicked, this, &slot_btnPause_clicked);

    CanFrameTableModel *canframe_tablemodel = CanFrameTableModel::GetInstance();
    this->ui->tableView->setModel(canframe_tablemodel);
}

CanViewDockWidget::~CanViewDockWidget()
{
    delete ui;
}

void CanViewDockWidget::slot_btnClear_clicked()
{
    CanFrameTableModel *canframe_tablemodel = CanFrameTableModel::GetInstance();
    canframe_tablemodel->removeRows(0, canframe_tablemodel->rowCount());
}

void CanViewDockWidget::slot_btnPause_clicked()
{
    if (ui->btnPause->isChecked())
    {
        RecMsgThread *recmsg_thread = RecMsgThread::GetInstance();
        recmsg_thread->pauseThread();
    }
    else
    {
        RecMsgThread *recmsg_thread = RecMsgThread::GetInstance();
        recmsg_thread->beginThread();
    }
}
