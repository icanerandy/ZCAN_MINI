#ifndef INIT_CAN_DIALOG_H
#define INIT_CAN_DIALOG_H

#include <QDialog>
#include "devicemanager.h"
#include "recmsg_thread.h"

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
    void BindSlots();

private slots:
    void slot_comboProtocol_currentIndexChanged(int index);
    void slot_comboCanfdStandard_currentIndexChanged(int index);
    void slot_comboCanfdSpeedUp_currentIndexChanged(int index);
    void slot_comboAbit_currentIndexChanged(int index);
    void slot_comboDbit_currentIndexChanged(int index);
    void slot_comboWorkMode_currentIndexChanged(int index);
    void slot_comboResistance_currentIndexChanged(int index);

    void on_btnOk_clicked();

private:
    Ui::InitCanDialog *ui;
};

#endif // INIT_CAN_DIALOG_H
