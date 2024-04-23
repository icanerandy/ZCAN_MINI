#ifndef INFO_DOCKWIDGET_H
#define INFO_DOCKWIDGET_H

#include <QDockWidget>

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
};

#endif // INFO_DOCKWIDGET_H
