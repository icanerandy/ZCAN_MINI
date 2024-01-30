#ifndef SENDDATA_DIALOG_H
#define SENDDATA_DIALOG_H

#include <QDialog>
#include "devicemanager.h"

namespace Ui {
class SendDataDialog;
}

class SendDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendDataDialog(QWidget *parent = 0);
    ~SendDataDialog();

private:
    void InitDialog();

private slots:
    void BindSignals();
    slot_btnSend_clicked();

private:
    Ui::SendDataDialog *ui;

private:
    QString id_;
    QString datas_;
    int send_count_once_;
    int frame_type_index_;
    int frame_delay_time_;
    int protocol_index_;
    int data_length_;
    int send_type_index_;
    int send_count_;
};

#endif // SENDDATA_DIALOG_H
