#ifndef DBCPARSER_DOCKWIDGET_H
#define DBCPARSER_DOCKWIDGET_H

#include <QObject>
#include <QDockWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QItemSelectionModel>
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

private:
    void showSignals();

private slots:
    void slot_btnReadDBC_clicked();

signals:
    void sig_paint(const unsigned long long msg_id, QList<CppCAN::CANSignal*>& sig_lst);

private:
    Ui::DBCViewDockWidget * const ui;

    CppCAN::CANDatabase db_;
    QStandardItemModel* const message_model_;
    QStandardItemModel* const signal_model_;
    QItemSelectionModel* const item_selection_model_;

    CppCAN::CANFrame* msg_;
    QList<CppCAN::CANSignal*> sig_lst_;
};

#endif // DBCPARSER_DOCKWIDGET_H
