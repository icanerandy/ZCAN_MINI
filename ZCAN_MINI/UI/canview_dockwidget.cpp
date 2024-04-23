#include "canview_dockwidget.h"
#include "ui_canview_dockwidget.h"

CanViewDockWidget::CanViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CanViewDockWidget),
    option_dialog(new CanViewOptionDialog(this))
{
    ui->setupUi(this);

    ui->chkIdIndex->setCheckedColor("#449CC8");

    int max_height = 35;
    // editIdIndex
    ui->editIdIndex->setFixedHeight(25);
    ui->editIdIndex->setLabelColor(QColor(0, 0, 0, 0));
    // ui->editIdIndex->setLabel("dafdsafdsa");
    ui->editIdIndex->setInkColor(QColor("#7BA0B3"));

    // button
    QColor color("#607D8B");
    ui->btnClear->setBackgroundColor(color);
    ui->btnClear->setFixedHeight(max_height);
    ui->btnPause->setBackgroundColor(color);
    ui->btnPause->setFixedHeight(max_height);
    ui->btnOpt->setBackgroundColor(color);
    ui->btnOpt->setFixedHeight(max_height);
    ui->btnFirstPage->setBackgroundColor(color);
    ui->btnFirstPage->setFixedHeight(max_height);
    ui->btnPreviousPage->setBackgroundColor(color);
    ui->btnPreviousPage->setFixedHeight(max_height);
    ui->btnNextPage->setBackgroundColor(color);
    ui->btnNextPage->setFixedHeight(max_height);
    ui->btnLastPage->setBackgroundColor(color);
    ui->btnLastPage->setFixedHeight(max_height);
    ui->btnJumpPage->setBackgroundColor(color);
    ui->btnJumpPage->setFixedHeight(max_height);

    bindSignals();

    CanFrameTableModel* const canframe_tablemodel = CanFrameTableModel::GetInstance();
    ui->tableView->setModel(canframe_tablemodel);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);  // 禁用resizeToContents()
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);
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
        {
            canframe_tablemodel->clearData();
        }
    });

    // 让按钮可以被选中
    ui->btnPause->setCheckable(true);

    connect(ui->btnPause, &QPushButton::clicked, this, [=]() {
        if (ui->btnPause->isChecked()) {
            canframe_tablemodel->slot_paused_clicked(true);
            ui->btnPause->setText(QStringLiteral("开始"));
        } else {
            canframe_tablemodel->slot_paused_clicked(false);
            ui->btnPause->setText(QStringLiteral("暂停"));
        }
    });
    connect(ui->btnOpt, &QPushButton::clicked, this, [=] {
        option_dialog->exec();
    });
    qRegisterMetaType<QList<uint>>("QList<uint>");
    connect(option_dialog, &CanViewOptionDialog::sig_visibleCol_changed, canframe_tablemodel, &CanFrameTableModel::slot_visibleCol_changed);

    connect(ui->chkIdIndex, &QtMaterialCheckBox::toggled, this, [=] {
        QString str = ui->editIdIndex->text();
        canframe_tablemodel->slot_check_id(ui->chkIdIndex->isChecked(), str.toUInt(nullptr, 16));
    });

    connect(ui->btnFirstPage, &QPushButton::clicked, canframe_tablemodel, [=] {
        canframe_tablemodel->page_num_ = 1;
        ui->labCurrentPage->setText(QString::number(1));
    });
    connect(ui->btnPreviousPage, &QPushButton::clicked, canframe_tablemodel, [=] {
        if (canframe_tablemodel->page_num_ == 1)
            return;
        --canframe_tablemodel->page_num_;
        ui->labCurrentPage->setText(QString::number(canframe_tablemodel->page_num_));
    });
    connect(ui->btnNextPage, &QPushButton::clicked, canframe_tablemodel, [=] {
        if (canframe_tablemodel->page_num_ == 10)
            return;
        ++canframe_tablemodel->page_num_;
        ui->labCurrentPage->setText(QString::number(canframe_tablemodel->page_num_));
    });
    connect(ui->btnLastPage, &QPushButton::clicked, canframe_tablemodel, [=] {
        canframe_tablemodel->page_num_ = 10;
        ui->labCurrentPage->setText(QString::number(10));
    });
    connect(ui->btnJumpPage, &QPushButton::clicked, canframe_tablemodel, [=] {
        canframe_tablemodel->page_num_ = ui->spinBox->value();
        ui->labCurrentPage->setText(QString::number(ui->spinBox->value()));
    });

    // connect(&timer_, &QTimer::timeout, this, [=] {
    //     if (scroll_enabled_)
    //     {
    //         scroll_enabled_ = false;
    //         ui->tableView->scrollToBottom();
    //     }
    // });
    // timer_.start(30);
    // connect(canframe_tablemodel, &CanFrameTableModel::dataChanged, this, [=] {
    //     ui->tableView->viewport()->update();
    //     scroll_enabled_ = true;
    // });
}
