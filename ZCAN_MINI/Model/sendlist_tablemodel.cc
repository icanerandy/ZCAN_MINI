#include "sendlist_tablemodel.h"

SendListTableModel::SendListTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant SendListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    header_lst << QStringLiteral("序号") << QStringLiteral("ID(Hex)") << QStringLiteral("协议")
               << QStringLiteral("长度") << QStringLiteral("名称") << QStringLiteral("数据")
               << QStringLiteral("帧类型") << QStringLiteral("每次发送帧数") << QStringLiteral("发送次数")
               << QStringLiteral("每次间隔(ms)");
}

int SendListTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return can_frame_lst.size();
}

int SendListTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return header_lst.size();
}

QVariant SendListTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
