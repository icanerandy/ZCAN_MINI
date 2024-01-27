#ifndef CANVIEW_DOCKWIDGET_H
#define CANVIEW_DOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class CanViewDockWidget;
}

class CanViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CanViewDockWidget(QWidget *parent = 0);
    ~CanViewDockWidget();

private:
    Ui::CanViewDockWidget *ui;
};

#endif // CANVIEW_DOCKWIDGET_H
