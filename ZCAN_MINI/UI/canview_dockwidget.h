#ifndef CANVIEW_DOCKWIDGET_H
#define CANVIEW_DOCKWIDGET_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDockWidget>
#include <QTimer>
#include "canframe_tablemodel.h"
#include "recmsg_thread.h"
#include "canviewoption_dialog.h"

namespace Ui {
class CanViewDockWidget;
}

class CanViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CanViewDockWidget(QWidget *parent = 0);
    ~CanViewDockWidget();

public:
    void bindSignals();

private:
    Ui::CanViewDockWidget * const ui;
    CanViewOptionDialog * const option_dialog;

    QTimer timer_;
    bool scroll_enabled_;
};

#endif // CANVIEW_DOCKWIDGET_H
