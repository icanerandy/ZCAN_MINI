#include "distribution_dialog.h"
#include "ui_distribution_dialog.h"

DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DistributionDialog)
{
    ui->setupUi(this);

    myplot_ = new MyPlot(ui->widget);
    ui->gridLayout->addWidget(myplot_, 0, 0, 1, 1);
}

DistributionDialog::~DistributionDialog()
{
    delete ui;
}
