#include "canviewoption_dialog.h"
#include "ui_canviewoption_dialog.h"

CanViewOptionDialog::CanViewOptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CanViewOptionDialog)
{
    ui->setupUi(this);
}

CanViewOptionDialog::~CanViewOptionDialog()
{
    delete ui;
}
