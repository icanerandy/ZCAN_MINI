#ifndef CANFRAMETABLEMODEL_H
#define CANFRAMETABLEMODEL_H

#include <QAbstractTableModel>
#include "zlgcan.h"

class CanFrameTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CanFrameTableModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const override;
    void SetHeadData(QStringList header_list);

public:
    void SetVisibleColumns(const QSet<int> &columns);


public slots:
    void newMsg(ZCAN_Receive_Data *can_data, uint len);
    void newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len);

private:
    QStringList header_list;
    QSet<int> visible_columns; // 存储可见列的索引
    QList<QVariant> *can_frame_list;
};

#endif // CANFRAMETABLEMODEL_H
