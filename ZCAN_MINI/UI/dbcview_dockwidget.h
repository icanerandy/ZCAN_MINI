#ifndef DBCPARSER_DOCKWIDGET_H
#define DBCPARSER_DOCKWIDGET_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDebug>
#include <QObject>
#include <QDockWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QItemSelectionModel>
#include <QFileDialog>
#include <fstream>
#include "Vector/DBC.h"

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
    void sig_paint(bool enabled, const uint32_t msg_id, QList<Vector::DBC::Signal>& sig_lst);

private:
    Ui::DBCViewDockWidget * const ui;

    QStandardItemModel* const message_model_;
    QStandardItemModel* const signal_model_;
    QItemSelectionModel* const item_selection_model_;

    bool paint_enabled_;

    Vector::DBC::Network network_;
    Vector::DBC::Message msg_;
    QList<Vector::DBC::Signal> sig_lst_;
};

#endif // DBCPARSER_DOCKWIDGET_H
