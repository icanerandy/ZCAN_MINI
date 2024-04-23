#include "canviewoption_dialog.h"
#include "ui_canviewoption_dialog.h"

CanViewOptionDialog::CanViewOptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CanViewOptionDialog)
{
    ui->setupUi(this);

    QPalette palette = ui->btnOk->palette();
    palette.setColor(QPalette::WindowText, Qt::green);
    ui->btnOk->setPalette(palette);

    QColor color("#449CC8");
    ui->chkCanType->setCheckedColor(color);
    ui->chkData->setCheckedColor(color);
    ui->chkDirection->setCheckedColor(color);
    ui->chkFormat->setCheckedColor(color);
    ui->chkFrameType->setCheckedColor(color);
    ui->chkId->setCheckedColor(color);
    ui->chkLength->setCheckedColor(color);
    ui->chkStamp->setCheckedColor(color);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->chkId->setChecked(true);
    ui->chkLength->setChecked(true);
    ui->chkData->setChecked(true);
    ui->chkStamp->setChecked(true);
    ui->chkDirection->setChecked(true);
    ui->chkFrameType->setChecked(true);
    ui->chkFormat->setChecked(true);
    ui->chkCanType->setChecked(true);

    connect(ui->btnOk, &QPushButton::clicked, this, [=] {
        QList<uint> visible_columns; // 存储可见列的索引
        visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::Index));   // 序号是必须的
        if (ui->chkStamp->isChecked())
            visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::TimeStamp));
        if (ui->chkId->isChecked())
            visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::Id));
        if (ui->chkFrameType->isChecked())
            visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::FrameType));
        if (ui->chkFormat->isChecked())
            visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::Format));
        if (ui->chkCanType->isChecked())
            visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::CanType));
        if (ui->chkDirection->isChecked())
            visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::Direction));
        if (ui->chkLength->isChecked())
            visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::Length));
        if (ui->chkData->isChecked())
            visible_columns.append(static_cast<uint>(CanFrameTableModel::VisibleColumns::Data));

        emit sig_visibleCol_changed(visible_columns);

        this->hide();
    });
}

CanViewOptionDialog::~CanViewOptionDialog()
{
    delete ui;
}
