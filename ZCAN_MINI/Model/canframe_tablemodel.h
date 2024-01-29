#ifndef CANFRAMETABLEMODEL_H
#define CANFRAMETABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QDateTime>
#include <QDebug>
#include "zlgcan.h"


enum VisibleColumns {
    kTimeStamp = 0,
    kId,
    kFrameType,
    kFormat,
    kCanType,
    kDirection,
    kLength,
    kData
};

class CanFrameTableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    explicit CanFrameTableModel(QObject *parent = nullptr);

public:
    static CanFrameTableModel *GetInstance();
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    //Qt::ItemFlags flags(const QModelIndex &index) const override;

public:
    void ClearData();

signals:
    void rowsInserted();

public slots:
    void newMsg(ZCAN_Receive_Data *can_data, uint len);
    void newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len);
    void slot_visibleCol(QList<int> visible_columns);

private:
    QStringList header_list;
    QList<int> visible_columns; // 存储可见列的索引
    QList<QVariant> can_frame_list;
};

#endif // CANFRAMETABLEMODEL_H
