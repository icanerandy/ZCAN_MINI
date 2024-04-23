#ifndef SIGNALPARSER_H
#define SIGNALPARSER_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QThread>
#include "qcustomplot.h"
#include "Vector/DBC.h"
#include "recmsg_thread.h"

class SignalParser : public QObject
{
    Q_OBJECT

public:
    explicit SignalParser(QList< QPair<uint32_t, Vector::DBC::Signal> > sig_lst);

signals:
    void sig_speed(const QList<double> vals);

public slots:
    void slot_newMsg(const ZCAN_Receive_Data* can_data, const uint len);
    void slot_newMsg(const ZCAN_ReceiveFD_Data* canfd_data, const uint len);

private:
    const QList< QPair<uint32_t, Vector::DBC::Signal> > sig_lst_;
};

#endif // SIGNALPARSER_H
