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

public:
    Ui::DistributionDialog *ui;

    QCustomPlot* myplot_;
};

#endif // DISTRIBUTION_DIALOG_H
