#ifndef REPLOTH_H
#define REPLOTH_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QThread>
#include <chrono>
#include <qcustomplot.h>

class Replot : public QObject
{
    Q_OBJECT

public:
    explicit Replot(QCustomPlot* const plot);

signals:
    void sig_frmChanged(const QString& msg);

private slots:
    void replotData(); // 定时重绘

private:
    QCustomPlot* const plot_;

    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    std::chrono::high_resolution_clock::time_point last_time;

    QTimer timer_;
};
#endif // REPLOTH_H
