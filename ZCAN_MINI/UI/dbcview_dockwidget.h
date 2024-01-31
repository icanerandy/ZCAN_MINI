#ifndef DBCPARSER_DOCKWIDGET_H
#define DBCPARSER_DOCKWIDGET_H

#include <QObject>
#include <QDockWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include "CANDatabase.h"

namespace Ui {
class DBCViewDockWidget;
}

class DBCViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit DBCViewDockWidget(QWidget *parent = 0);
    ~DBCViewDockWidget();

private slots:
    void slot_btnReadDBC_clicked();
    void slot_message_model_clicked(const QModelIndex &index);

private:
    Ui::DBCViewDockWidget *ui;

    CppCAN::CANDatabase db;

    QStandardItemModel *message_model;
    QStandardItemModel *signal_model;
};

#endif // DBCPARSER_DOCKWIDGET_H
