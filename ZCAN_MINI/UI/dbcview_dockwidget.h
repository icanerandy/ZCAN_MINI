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

private slots:
    void slot_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void slot_itemCheckStatChanged(QStandardItem* item);
    void slot_btnReadDBC_clicked();

signals:
    void sig_sigChecked(QList<QPair<uint32_t, Vector::DBC::Signal>> sig_lst);

private:
    Ui::DBCViewDockWidget * const ui;

    QStandardItemModel* const tree_model_;
    QItemSelectionModel* const item_selection_model_;
    QStandardItemModel* const table_model_;

    Vector::DBC::Network network_;
    QList<QPair<uint32_t, Vector::DBC::Signal>> sig_lst_;
};

#endif // DBCPARSER_DOCKWIDGET_H
