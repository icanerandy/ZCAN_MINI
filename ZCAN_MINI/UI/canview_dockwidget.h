#ifndef CANVIEW_DOCKWIDGET_H
#define CANVIEW_DOCKWIDGET_H

#include <QDockWidget>
#include "canframe_tablemodel.h"
#include "recmsg_thread.h"

namespace Ui {
class CanViewDockWidget;
}

class CanViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CanViewDockWidget(QWidget *parent = 0);
    ~CanViewDockWidget();

private slots:
    void slot_btnClear_clicked();
    void slot_btnPause_clicked();

private:
    Ui::CanViewDockWidget *ui;
};

#endif // CANVIEW_DOCKWIDGET_H
