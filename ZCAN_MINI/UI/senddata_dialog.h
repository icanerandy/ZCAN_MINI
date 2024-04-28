#ifndef SENDDATA_DIALOG_H
#define SENDDATA_DIALOG_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDialog>
#include <QMessageBox>
#include <QRegExpValidator>
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
    void initDlg();
    void bindSignals();

private slots:
    void slot_btnSend_clicked();

private:
    Ui::SendDataDialog * const ui;

    uint id_;
    QString datas_;
    uint send_count_once_;
    DeviceManager::FrameType frame_type_;
    uint frame_delay_time_;
    DeviceManager::ProtocolType protocol_type_;
    uint data_length_;
    DeviceManager::SendType send_type_;
    uint send_count_;
    uint text_length_;

    QTimer timer_;
};

#endif // SENDDATA_DIALOG_H
