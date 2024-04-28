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

void DistributionDialog::set_max_error(double val)
{
    ui->labMaxError->setText(QString::number(val));
}

void DistributionDialog::set_mean_error(double val)
{
    ui->labMean->setText(QString::number(val));
}

void DistributionDialog::set_correlation_coefficient(double val)
{
    ui->labCor->setText(QString::number(val));
}

void DistributionDialog::set_RMSE(double val)
{
    ui->labRMSE->setText(QString::number(val));
}
