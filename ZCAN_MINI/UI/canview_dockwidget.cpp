#include "canview_dockwidget.h"
#include "ui_canview_dockwidget.h"

CanViewDockWidget::CanViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CanViewDockWidget),
    option_dialog(new CanViewOptionDialog(this))
{
    ui->setupUi(this);

    bindSignals();

    CanFrameTableModel* const canframe_tablemodel = CanFrameTableModel::GetInstance();
    ui->tableView->setModel(canframe_tablemodel);
}

CanViewDockWidget::~CanViewDockWidget()
{
    delete ui;
}

void CanViewDockWidget::bindSignals()
{
    CanFrameTableModel* const canframe_tablemodel = CanFrameTableModel::GetInstance();

    connect(ui->btnClear, &QPushButton::clicked, this, [=] {
        if (canframe_tablemodel->rowCount() > 0)
            canframe_tablemodel->removeRows(0, canframe_tablemodel->rowCount());
    });
    connect(ui->btnPause, &QPushButton::clicked, this, [=] {
        if (ui->btnPause->isChecked())
            ui->tableView->setUpdatesEnabled(false);
        else
            ui->tableView->setUpdatesEnabled(true);
    });
    connect(ui->btnOption, &QPushButton::clicked, this, [=] {
        option_dialog->exec();
    });
    connect(option_dialog, &CanViewOptionDialog::sig_visibleCol_changed, canframe_tablemodel, &CanFrameTableModel::slot_visibleCol_changed);

    // connect(canframe_tablemodel, &CanFrameTableModel::dataChanged, this, [] { ui->tableView->scrollToBottom(); });
}
