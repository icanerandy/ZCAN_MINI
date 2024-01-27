#ifndef INIT_CAN_DIALOG_H
#define INIT_CAN_DIALOG_H

#include <QDialog>

namespace Ui {
class InitCanDialog;
}

class InitCanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitCanDialog(QWidget *parent = 0);
    ~InitCanDialog();

private:
    void InitDialog();


private:
    Ui::InitCanDialog *ui;
};

#endif // INIT_CAN_DIALOG_H
