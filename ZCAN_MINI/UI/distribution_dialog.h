#ifndef DISTRIBUTION_DIALOG_H
#define DISTRIBUTION_DIALOG_H

#include <QDialog>
#include "myplot.h"

namespace Ui {
class DistributionDialog;
}

class DistributionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DistributionDialog(QWidget *parent = nullptr);
    ~DistributionDialog();
    void set_max_error(double val);
    void set_mean_error(double val);
    void set_correlation_coefficient(double val);
    void set_RMSE(double val);

public:
    Ui::DistributionDialog *ui;

    QCustomPlot* myplot_;
};

#endif // DISTRIBUTION_DIALOG_H
