#include "distribution_dialog.h"
#include "ui_distribution_dialog.h"

DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DistributionDialog)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 4);

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

void DistributionDialog::set_MAE(double val)
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
