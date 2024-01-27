#include "canframe_tablemodel.h"

CanFrameTableModel::CanFrameTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int CanFrameTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return can_frame_list->size();
}

int CanFrameTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return visible_columns.size();  // 仅计算可见列的数量
}

QVariant CanFrameTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        const int row = index.row();
        // 返回行中每一列的数据（其中一个CAN帧对应一行）
        // 根据可见列调整列索引

        if (can_frame_list->at(row).canConvert<ZCAN_Receive_Data>())
        {
            ZCAN_Receive_Data can;
            for (int i = 0; i < 8; ++i)
            {
                if (visible_columns.find(i) != visible_columns.end())
                    switch (i) {
                        case 0: return can.timestamp;break;
                        case 1: return GET_ID(can.frame.can_id); break;
                        case 2:  break;
                        case 3:  break;
                        case 4:  break;
                        case 5:  break;
                        case 6:  break;
                        case 7:  break;
                    }
            }
        }
    }

    return QVariant();
}

QVariant CanFrameTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section < header_list.size())
        {
            return header_list[section];
        }
    }

    // 交给父类处理
    return QAbstractItemModel::headerData(section, orientation, role);
}

void CanFrameTableModel::SetHeadData(QStringList header_list)
{
    this->header_list = header_list;
}

void CanFrameTableModel::SetVisibleColumns(const QSet<int> &columns)
{
    beginResetModel();
    visible_columns = columns;
    endResetModel();
}

void CanFrameTableModel::newMsg(ZCAN_Receive_Data *can_data, uint len)
{
    QString item;
    for (uint i = 0; i < len; ++i)
    {
        const ZCAN_Receive_Data& can = can_data[i];
        const canid_t& id = can.frame.can_id;
        can_frame_list->append(QVariant::fromValue(can));


        /* 调试输出报文信息 */
        item = QString::asprintf(
                    "接收到CAN ID:%08X %s %s 长度:%d 数据:", GET_ID(id), IS_EFF(id)?"扩展帧" : "标准帧",
                    IS_RTR(id)?"远程帧" : "数据帧", can.frame.can_dlc
                    );
        for (UINT i = 0; i < can.frame.can_dlc; ++i)
        {
            item.append(QString::asprintf("%02X ", can.frame.data[i]));
        }
        qDebug() << item;
    }
}

void CanFrameTableModel::newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len)
{
    QString item;
    for (uint i = 0; i < len; ++i)
    {
        const ZCAN_ReceiveFD_Data& canfd = canfd_data[i];
        const canid_t& id = canfd.frame.can_id;
        can_frame_list->append(QVariant::fromValue(canfd));

        /* 调试输出报文信息 */
        item = QString::asprintf(
                    "接收到CANFD ID:%08X %s %s 长度:%d 数据:", GET_ID(id), IS_EFF(id)?"扩展帧":"标准帧",
                    IS_RTR(id)?"远程帧":"数据帧", canfd.frame.len
                    );
        for (uint i = 0; i < canfd.frame.len; ++i)
        {
            item.append(QString::asprintf("%02X ", canfd.frame.data[i]));
        }
        qDebug() << item;
    }
}
