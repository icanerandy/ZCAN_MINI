#include "sendlist_tablemodel.h"

SendListTableModel::SendListTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    header_lst << "序号" << "ID(Hex)" << "协议"
               << "长度" << "名称" << "数据"
               << "帧类型" << "每次发送帧数" << "发送次数"
               << "每次间隔(ms)";
}

QVariant SendListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section < header_lst.size())
        {
            return header_lst[section];
        }
    }

    // 交给父类处理
    return QAbstractItemModel::headerData(section, orientation, role);
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
