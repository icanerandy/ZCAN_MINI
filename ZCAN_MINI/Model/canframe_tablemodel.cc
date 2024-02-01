#include "canframe_tablemodel.h"

CanFrameTableModel::CanFrameTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    header_list << "时间标识" << "帧ID" << "帧类型" << "帧格式" << "CAN类型" << "方向" << "长度" << "数据";
    for (int i = 0; i < 8; ++i)
    {
        visible_columns.append(kTimeStamp + i);
    }
}

CanFrameTableModel *CanFrameTableModel::GetInstance()
{
    static CanFrameTableModel canFrameTableModel;
    return &canFrameTableModel;
}

int CanFrameTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return can_frame_list.size();
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

        if (can_frame_list.at(row).canConvert<ZCAN_Receive_Data>())
        {
            ZCAN_Receive_Data can = can_frame_list.at(row).value<ZCAN_Receive_Data>();
            can_frame frame = can.frame;
            int visible_column = visible_columns.at(index.column());
            switch (visible_column)
            {
                case kTimeStamp: {
                    QDateTime currentTime = QDateTime::currentDateTime();
                    QString formattedTime = currentTime.toString("[hh:mm:ss.zzz] ");
                    return formattedTime;

//                    double timestamp = can.timestamp / 1000.0;

//                    return QString::number(timestamp, 'f', 3);
                } break;
                case kId: return QString::asprintf("%08X", GET_ID(frame.can_id)); break;
                case kFrameType: return QString(IS_EFF(frame.can_id)?"扩展帧" : "标准帧"); break;
                case kFormat: return QString(IS_RTR(frame.can_id)?"远程帧" : "数据帧"); break;
                case kCanType: return QString("CAN"); break;
                case kDirection: return QString("RX"); break;
                case kLength: return QString::asprintf("%d", frame.can_dlc); break;
                case kData: {
                    QString str;
                    for (int i = 0; i < frame.can_dlc; ++i) {
                        str += QString::asprintf("%02X ", can.frame.data[i]);
                        if (i < CAN_MAX_DLEN - 1)
                            str += " "; // 添加空格分隔符
                    }
                    return str;
                } break;
            }
        }
        else if (can_frame_list.at(row).canConvert<ZCAN_ReceiveFD_Data>())
        {
            ZCAN_ReceiveFD_Data can = can_frame_list.at(row).value<ZCAN_ReceiveFD_Data>();
            canfd_frame frame = can.frame;
            int visible_column = visible_columns.at(index.column());
            switch (visible_column)
            {
                case kTimeStamp: {
                    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(can.timestamp);
                    return dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
                } break;
                case kId: return QString::asprintf("%08X", GET_ID(frame.can_id)); break;
                case kFrameType: return QString(IS_EFF(frame.can_id)?"扩展帧" : "标准帧"); break;
                case kFormat: return QString(IS_RTR(frame.can_id)?"远程帧" : "数据帧"); break;
                case kCanType: return QString(CANFD_BRS==frame.flags?"CANFD加速":"CANFD"); break;
                case kDirection: return QString("RX"); break;
                case kLength: return QString::asprintf("%d", frame.len); break;
                case kData: {
                    QString str;
                    for (int i = 0; i < frame.len; ++i) {
                        str += QString::asprintf("%02X ", can.frame.data[i]);
                        if (i < CAN_MAX_DLEN - 1)
                            str += " "; // 添加空格分隔符
                    }
                    return str;
                } break;
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
            return header_list[visible_columns.at(section)];
        }
    }

    // 交给父类处理
    return QAbstractItemModel::headerData(section, orientation, role);
}

bool CanFrameTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 || count < 1 || row+count > rowCount())
        return false;

    beginRemoveRows(parent, row, row+count-1);
    can_frame_list.erase(can_frame_list.begin(), can_frame_list.begin()+count);
    endRemoveRows();

    return true;
}

void CanFrameTableModel::ClearData()
{
    beginResetModel();
    can_frame_list.clear();
    endResetModel();
}

void CanFrameTableModel::newMsg(ZCAN_Receive_Data *can_data, uint len)
{
    QString item;
    for (uint i = 0; i < len; ++i)
    {
        if (can_frame_list.size() == 10000)
            removeRows(0, 1);

        const ZCAN_Receive_Data& can = can_data[i];
        const canid_t& id = can.frame.can_id;

        beginInsertRows(QModelIndex(), can_frame_list.size(), can_frame_list.size());
        can_frame_list.append(QVariant::fromValue(can));
        //emit dataChanged(QModelIndex(), QModelIndex());
        endInsertRows();
    }
}

void CanFrameTableModel::newMsg(ZCAN_ReceiveFD_Data *canfd_data, uint len)
{
    QString item;
    for (uint i = 0; i < len; ++i)
    {
        if (can_frame_list.size() == 10000)
            removeRows(0, 1);

        const ZCAN_ReceiveFD_Data& canfd = canfd_data[i];
        const canid_t& id = canfd.frame.can_id;

        beginInsertRows(QModelIndex(), can_frame_list.size(), can_frame_list.size());
        can_frame_list.append(QVariant::fromValue(canfd));
        //emit dataChanged(QModelIndex(), QModelIndex());
        endInsertRows();
    }
}

void CanFrameTableModel::slot_visibleCol(QList<int> visible_columns)
{
    beginResetModel();
    this->visible_columns = visible_columns;
    endResetModel();
}
