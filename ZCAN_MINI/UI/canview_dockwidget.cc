#include "canview_dockwidget.h"
#include "ui_canview_dockwidget.h"

CanViewDockWidget::CanViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CanViewDockWidget),
    option_dialog(nullptr)
{
    ui->setupUi(this);

    connect(ui->btnClear, &QPushButton::clicked, this, &slot_btnClear_clicked);
    connect(ui->btnPause, &QPushButton::clicked, this, &slot_btnPause_clicked);
    connect(ui->btnOption, &QPushButton::clicked, this, &slot_btnOption_clicked);

    CanFrameTableModel *canframe_tablemodel = CanFrameTableModel::GetInstance();
    this->ui->tableView->setModel(canframe_tablemodel);

    //    connect(canframe_tablemodel, &CanFrameTableModel::dataChanged,
//            this, &CanViewDockWidget::slot_rowsInserted);
}

CanViewDockWidget::~CanViewDockWidget()
{
    delete ui;
}

void CanViewDockWidget::slot_btnClear_clicked()
{
    CanFrameTableModel *canframe_tablemodel = CanFrameTableModel::GetInstance();
    if (canframe_tablemodel->rowCount() > 0)
        canframe_tablemodel->removeRows(0, canframe_tablemodel->rowCount());
}

void CanViewDockWidget::slot_btnPause_clicked()
{
    if (ui->btnPause->isChecked())
    {
        ui->tableView->setUpdatesEnabled(false);
    }
    else
    {
        ui->tableView->setUpdatesEnabled(true);
    }
}

void CanViewDockWidget::slot_btnOption_clicked()
{
    if (!option_dialog)
    {
        option_dialog = new CanViewOptionDialog(this);
        CanFrameTableModel *canframe_tablemodel = CanFrameTableModel::GetInstance();
        connect(option_dialog, &CanViewOptionDialog::signal_visibleCol, canframe_tablemodel, &CanFrameTableModel::slot_visibleCol);
    }
    option_dialog->exec();  // 以模态方式显示对话框
}

void CanViewDockWidget::slot_rowsInserted(const QModelIndex &index, const QModelIndex &index2)
{
    Q_UNUSED(index);
    Q_UNUSED(index2);
    ui->tableView->scrollToBottom();
}
