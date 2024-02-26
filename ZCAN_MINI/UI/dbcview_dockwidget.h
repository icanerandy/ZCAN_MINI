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

private slots:
    void slot_btnReadDBC_clicked();
    void slot_message_model_clicked(const QModelIndex &index);

signals:
    void sig_paint(const unsigned long long msg_id, const CppCAN::CANSignal& ref_speed_, const CppCAN::CANSignal& rel_speed_);

private:
    Ui::DBCViewDockWidget * const ui;

    CppCAN::CANDatabase db_;
    QStandardItemModel* const message_model_;
    QStandardItemModel* const signal_model_;
    QItemSelectionModel* const item_selection_model_;

    CppCAN::CANFrame* msg_;
    CppCAN::CANSignal* ref_speed_;
    CppCAN::CANSignal* rel_speed_;
};

#endif // DBCPARSER_DOCKWIDGET_H
