#ifndef CANVIEWOPTION_DIALOG_H
#define CANVIEWOPTION_DIALOG_H

#include <QDialog>
#include "canframe_tablemodel.h"

namespace Ui {
class CanViewOptionDialog;
}

class CanViewOptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CanViewOptionDialog(QWidget *parent = 0);
    ~CanViewOptionDialog();

private slots:
    slot_chkId_checked(bool isChecked);
    slot_chkLength_checked(bool isChecked);
    slot_chkData_checked(bool isChecked);
    slot_chkStamp_checked(bool isChecked);
    slot_chkDirection_checked(bool isChecked);
    slot_chkFrameType_checked(bool isChecked);
    slot_chkFormat_checked(bool isChecked);
    slot_chkCanType_checked(bool isChecked);
    slot_btnOk_clicked();

signals:
    void signal_visibleCol(QList<int> visible_columns);

private:
    Ui::CanViewOptionDialog *ui;
};

#endif // CANVIEWOPTION_DIALOG_H
