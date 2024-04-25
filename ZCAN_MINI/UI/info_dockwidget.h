﻿#ifndef INFO_DOCKWIDGET_H
#define INFO_DOCKWIDGET_H

#include <QDockWidget>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class InfoDockWidget;
}

class InfoDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit InfoDockWidget(QWidget *parent = nullptr);
    ~InfoDockWidget();

private:
    Ui::InfoDockWidget *ui;

    QTimer timer;
};

#endif // INFO_DOCKWIDGET_H