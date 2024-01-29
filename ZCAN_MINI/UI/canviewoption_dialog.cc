#include "canviewoption_dialog.h"
#include "ui_canviewoption_dialog.h"

CanViewOptionDialog::CanViewOptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CanViewOptionDialog)
{
    ui->setupUi(this);

    ui->chkId->setChecked(true);
    ui->chkLength->setChecked(true);
    ui->chkData->setChecked(true);
    ui->chkStamp->setChecked(true);
    ui->chkDirection->setChecked(true);
    ui->chkFrameType->setChecked(true);
    ui->chkFormat->setChecked(true);
    ui->chkCanType->setChecked(true);

    connect(ui->btnOk, &QPushButton::clicked, this, &slot_btnOk_clicked);
}

CanViewOptionDialog::~CanViewOptionDialog()
{
    delete ui;
}

CanViewOptionDialog::slot_chkId_checked(bool isChecked)
{

}

CanViewOptionDialog::slot_chkLength_checked(bool isChecked)
{

}

CanViewOptionDialog::slot_chkData_checked(bool isChecked)
{

}

CanViewOptionDialog::slot_chkStamp_checked(bool isChecked)
{

}

CanViewOptionDialog::slot_chkDirection_checked(bool isChecked)
{

}

CanViewOptionDialog::slot_chkFrameType_checked(bool isChecked)
{

}

CanViewOptionDialog::slot_chkFormat_checked(bool isChecked)
{

}

CanViewOptionDialog::slot_chkCanType_checked(bool isChecked)
{

}

CanViewOptionDialog::slot_btnOk_clicked()
{
    QList<int> visible_columns; // 存储可见列的索引
    if (ui->chkStamp->isChecked())
        visible_columns.append(kTimeStamp);
    if (ui->chkId->isChecked())
        visible_columns.append(kId);
    if (ui->chkFrameType->isChecked())
        visible_columns.append(kFrameType);
    if (ui->chkFormat->isChecked())
        visible_columns.append(kFormat);
    if (ui->chkCanType->isChecked())
        visible_columns.append(kCanType);
    if (ui->chkDirection->isChecked())
        visible_columns.append(kDirection);
    if (ui->chkLength->isChecked())
        visible_columns.append(kLength);
    if (ui->chkData->isChecked())
        visible_columns.append(kData);

    emit signal_visibleCol(visible_columns);

    this->hide();
}
