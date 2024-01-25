#ifndef QWMAINWINDOW_H
#define QWMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class QWMainWindow;
}

class QWMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QWMainWindow(QWidget *parent = 0);
    ~QWMainWindow();

private:
    Ui::QWMainWindow *ui;
};

#endif // QWMAINWINDOW_H
