#ifndef CANVIEWOPTION_DIALOG_H
#define CANVIEWOPTION_DIALOG_H

#include <QDialog>

namespace Ui {
class CanViewOptionDialog;
}

class CanViewOptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CanViewOptionDialog(QWidget *parent = 0);
    ~CanViewOptionDialog();

private:
    Ui::CanViewOptionDialog *ui;
};

#endif // CANVIEWOPTION_DIALOG_H
