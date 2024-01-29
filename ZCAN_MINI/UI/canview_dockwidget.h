#ifndef CANVIEW_DOCKWIDGET_H
#define CANVIEW_DOCKWIDGET_H

#include <QDockWidget>
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

private slots:
    void slot_btnClear_clicked();
    void slot_btnPause_clicked();
    void slot_btnOption_clicked();
    void slot_rowsInserted(const QModelIndex &index, const QModelIndex &index2);

private:
    Ui::CanViewDockWidget *ui;
    CanViewOptionDialog *option_dialog;
};

#endif // CANVIEW_DOCKWIDGET_H
