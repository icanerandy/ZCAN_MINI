#ifndef INIT_CAN_DIALOG_H
#define INIT_CAN_DIALOG_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

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
    void initDlg();
    void bindSignals();

public slots:
    void slot_chkDeviceType();

private:
    Ui::InitCanDialog * const ui;
};

#endif // INIT_CAN_DIALOG_H
