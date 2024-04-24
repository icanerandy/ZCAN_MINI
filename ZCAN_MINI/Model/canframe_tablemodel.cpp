#include "canframe_tablemodel.h"

CanFrameTableModel::CanFrameTableModel(QObject *parent)
    : QAbstractTableModel(parent),
    chk_id_enable_(false),
    chk_id_(0),
    page_num_(1),
    total_page_num_(10),
    max_num_per_page_(100),
    is_paused_(false),
    reset_flag_(false),
    paused_row_count_(0)
{
    header_list_ << "序号" << "时间标识" << "帧ID(Hex)" << "帧类型" << "帧格式" << "CAN类型" << "方向" << "长度" << "数据";
    for (uint i = 0; i < 9; ++i)
    {
        visible_columns_.append(static_cast<uint>(VisibleColumns::Index) + i);
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

    if (is_paused_)
        return paused_row_count_;

    uint init_size = can_frame_list_.size();

    if (init_size > (page_num_-1)*max_num_per_page_)
    {
        if (init_size <= page_num_*max_num_per_page_) // 在当前页中
            return init_size - (page_num_-1)*max_num_per_page_;
        else    // 超出了当前页面
            return max_num_per_page_;
    }
    else    // 还没达到当前页面
        return 0;
}

int CanFrameTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return visible_columns_.size();  // 仅计算可见列的数量
}

QVariant CanFrameTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::TextAlignmentRole){
        QVariant value = Qt::AlignCenter;
        return value;
    }

    if (index.column() == 0 && role == Qt::FontRole) {
        QFont boldFont;
        boldFont.setBold(true);
        QVariant value = boldFont;
        return value;
    }

    if (role == Qt::DisplayRole)
    {
        int row = index.row();

        row += (page_num_-1)*max_num_per_page_;

        // 返回行中每一列的数据（其中一个CAN帧对应一行）
        // 根据可见列调整列索引
        QVariant tmp = can_frame_list_.at(row);
        if (tmp.canConvert<ZCAN_Receive_Data>())
        {
            if (is_add_data)
                qDebug() << "data() is_add_data = " << is_add_data;
            ZCAN_Receive_Data can = qvariant_cast<ZCAN_Receive_Data>(tmp);
            can_frame frame = can.frame;
            int visible_column = visible_columns_.at(index.column());

            if (chk_id_enable_ && GET_ID(frame.can_id) != chk_id_)
                return QVariant();

            switch (visible_column)
            {
                case static_cast<uint>(VisibleColumns::Index):
                    return QString::number(row+1);
                case static_cast<uint>(VisibleColumns::TimeStamp):
                    {
                        uint64_t timestamp_us = can.timestamp;
                        uint64_t key = timestamp_us / 1000;
                        QString formattedTime = QDateTime::fromMSecsSinceEpoch(key).toString("[mm:ss.zzz:");
                        formattedTime += QString::number(timestamp_us % 1000);
                        formattedTime += "] ";
                        return formattedTime;
                    } break;
                case static_cast<uint>(VisibleColumns::Id):
                    return QString::asprintf("%08X", GET_ID(frame.can_id));
                case static_cast<uint>(VisibleColumns::FrameType):
                    return QString(IS_EFF(frame.can_id)?"扩展帧" : "标准帧");
                case static_cast<uint>(VisibleColumns::Format):
                    return QString(IS_RTR(frame.can_id)?"远程帧" : "数据帧");
                case static_cast<uint>(VisibleColumns::CanType):
                    return QString("CAN");
                case static_cast<uint>(VisibleColumns::Direction):
                    return QString("RX");
                case static_cast<uint>(VisibleColumns::Length):
                    return QString::asprintf("%d", frame.can_dlc);
                case static_cast<uint>(VisibleColumns::Data):
                    {
                    QString str;
                    for (int i = 0; i < frame.can_dlc; ++i) {
                        str += QString::asprintf("%02X ", can.frame.data[i]);
                        if (i < CAN_MAX_DLEN - 1)
                            str += " "; // 添加空格分隔符
                    }
                    return str;
                    };
            }
        }
        else if (tmp.canConvert<ZCAN_ReceiveFD_Data>())
        {
            ZCAN_ReceiveFD_Data can = qvariant_cast<ZCAN_ReceiveFD_Data>(tmp);
            canfd_frame frame = can.frame;
            int visible_column = visible_columns_.at(index.column());

            if (chk_id_enable_ && GET_ID(frame.can_id) != chk_id_)
                return QVariant();

            switch (visible_column)
            {
                case static_cast<uint>(VisibleColumns::Index):
                    return QString::number(row+1);
                case static_cast<uint>(VisibleColumns::TimeStamp):
                    {
                        uint64_t timestamp_us = can.timestamp;
                        uint64_t key = timestamp_us / 1000;

                        QString formattedTime = QDateTime::fromMSecsSinceEpoch(key).toString("[mm:ss.zzz:");
                        formattedTime += QString::number(timestamp_us % 1000);
                        formattedTime += "] ";
                        return formattedTime;
                    };
                case static_cast<uint>(VisibleColumns::Id):
                    return QString::asprintf("%08X", GET_ID(frame.can_id));
                case static_cast<uint>(VisibleColumns::FrameType):
                    return QString(IS_EFF(frame.can_id)?"扩展帧" : "标准帧");
                case static_cast<uint>(VisibleColumns::Format):
                    return QString(IS_RTR(frame.can_id)?"远程帧" : "数据帧");
                case static_cast<uint>(VisibleColumns::CanType):
                    return QString(CANFD_BRS==frame.flags?"CANFD加速":"CANFD");
                case static_cast<uint>(VisibleColumns::Direction):
                    return QString("RX");
                case static_cast<uint>(VisibleColumns::Length):
                    return QString::asprintf("%d", frame.len);
                case static_cast<uint>(VisibleColumns::Data):
                    {
                        QString str;
                        for (int i = 0; i < frame.len; ++i) {
                            str += QString::asprintf("%02X ", can.frame.data[i]);
                            if (i < CAN_MAX_DLEN - 1)
                                str += " "; // 添加空格分隔符
                        }
                        return str;
                    };
            }
        }
    }

    return QVariant();
}

QVariant CanFrameTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section < header_list_.size())
        {
            return header_list_.at( visible_columns_.at(section) );
        }
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

bool CanFrameTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 || count < 1 || row+count > rowCount() || can_frame_list_.empty())
        return false;

    beginRemoveRows(parent, row, row+count-1);
    // can_frame_list_.erase(can_frame_list_.begin() + row, can_frame_list_.begin() + row + count);
    for (int i = 0; i < count; ++i)
    {
        can_frame_list_.removeAt(row+i);
    }
    endRemoveRows();

    return true;
}

void CanFrameTableModel::clearData()
{
    beginResetModel();
    if (!can_frame_list_.empty())
        can_frame_list_.clear();
    paused_row_count_ = 0;
    endResetModel();
}

void CanFrameTableModel::slot_newMsg(const ZCAN_Receive_Data* can_data, const uint len)
{
    for (uint i = 0; i < len; ++i)
    {
        if (is_show_data)
            qDebug() << "newMsg() is_show_data = " << is_show_data;

        const ZCAN_Receive_Data& can = can_data[i];
        can_frame_list_.append(QVariant::fromValue(can));

        if (can_frame_list_.size() > (page_num_-1)*max_num_per_page_)
        {
            if (can_frame_list_.size() <= page_num_*max_num_per_page_) // 在当前页中
            {
                if (!is_paused_)
                {
                    if (reset_flag_)
                    {
                        // 将暂停时新添加的数据重新全部添加到 view 中
                        beginResetModel();
                        endResetModel();

                        beginInsertRows(QModelIndex(), 0, can_frame_list_.size() - 1 - (page_num_-1)*max_num_per_page_);
                        endInsertRows();

                        reset_flag_ = false;
                    }
                    else
                    {
                        beginInsertRows(QModelIndex(), can_frame_list_.size() - 1 - (page_num_-1)*max_num_per_page_, can_frame_list_.size() - 1 - (page_num_-1)*max_num_per_page_);
                        endInsertRows();
                    }
                }
            }
            else    // 超出了当前页面
            {
                if (can_frame_list_.size() > total_page_num_*max_num_per_page_)
                {
                    if (!is_paused_)
                    {
                        if (reset_flag_)
                        {
                            // 将暂停时新添加的数据重新全部添加到 view 中
                            beginResetModel();
                            int init_size = can_frame_list_.size();
                            for (int i = 0; i <= init_size - total_page_num_*max_num_per_page_; ++i)
                            {
                                can_frame_list_.removeAt(i);
                            }
                            endResetModel();

                            beginInsertRows(QModelIndex(), 0, max_num_per_page_ - 1);
                            endInsertRows();

                            reset_flag_ = false;
                        }
                        else
                        {

                            removeRows(0, 1);
                            beginInsertRows(QModelIndex(), max_num_per_page_-1, max_num_per_page_-1);
                            endInsertRows();
                        }
                    }
                }
            }
        }
        else    // 还没达到当前页面
        {
        }
    }
}

void CanFrameTableModel::slot_newMsg(const ZCAN_ReceiveFD_Data* canfd_data, const uint len)
{
    for (uint i = 0; i < len; ++i)
    {
        const ZCAN_ReceiveFD_Data& canfd = canfd_data[i];
        can_frame_list_.append(QVariant::fromValue(canfd));

        if (can_frame_list_.size() > (page_num_-1)*max_num_per_page_)
        {
            if (can_frame_list_.size() <= page_num_*max_num_per_page_) // 在当前页中
            {
                if (!is_paused_)
                {
                    if (reset_flag_)
                    {
                        // 将暂停时新添加的数据重新全部添加到 view 中
                        if (paused_row_count_ > 0)
                        {
                            beginRemoveRows(QModelIndex(), 0, paused_row_count_ - 1);
                            endRemoveRows();
                        }

                        beginInsertRows(QModelIndex(), 0, can_frame_list_.size() - 1 - (page_num_-1)*max_num_per_page_);
                        endInsertRows();

                        reset_flag_ = false;
                    }
                    else
                    {
                        beginInsertRows(QModelIndex(), can_frame_list_.size() - 1 - (page_num_-1)*max_num_per_page_, can_frame_list_.size() - 1 - (page_num_-1)*max_num_per_page_);
                        endInsertRows();
                    }
                }
            }
            else    // 超出了当前页面
            {
                if (can_frame_list_.size() > total_page_num_*max_num_per_page_)
                {
                    if (!is_paused_)
                    {
                        if (reset_flag_)
                        {
                            // 将暂停时新添加的数据重新全部添加到 view 中
                            if (paused_row_count_ > 0)
                            {
                                beginRemoveRows(QModelIndex(), 0, paused_row_count_ - 1);
                                endRemoveRows();
                            }
                            // 先将列表清空，不然可能出现 view 正在使用 data() 访问 990 行，但是已经删除掉 can_frame_list.at(990) 的情况
                            int init_size = can_frame_list_.size();
                            // can_frame_list_.erase(can_frame_list_.begin(), can_frame_list_.begin() + init_size - total_page_num_*max_num_per_page_);
                            for (int i = 0; i < init_size - total_page_num_*max_num_per_page_; ++i)
                            {
                                can_frame_list_.removeAt(i);
                            }

                            beginInsertRows(QModelIndex(), 0, max_num_per_page_ - 1);
                            endInsertRows();

                            reset_flag_ = false;
                        }
                        else
                        {
                            removeRows(0, 1);
                            // beginInsertRows(QModelIndex(), max_num_per_page_ - 1, max_num_per_page_ - 1); what bug???
                            beginInsertRows(QModelIndex(), rowCount(), rowCount());
                            endInsertRows();
                        }
                    }
                }
            }
        }
        else    // 还没达到当前页面
        {
        }
    }
}

void CanFrameTableModel::slot_visibleCol_changed(QList<uint> visible_columns)
{
    beginResetModel();
    this->visible_columns_ = visible_columns;
    endResetModel();
}

void CanFrameTableModel::slot_check_id(bool chk_id_enable, uint32_t chk_id)
{
    chk_id_enable_ = chk_id_enable;
    chk_id_ = chk_id;
}

void CanFrameTableModel::slot_paused_clicked(bool is_paused)
{
    if (is_paused)
    {
        paused_row_count_ = rowCount(QModelIndex());    // 先获取行数

        reset_flag_ = is_paused_ = is_paused;
    }
    else
    {
        // reset_flag 只能由内部置为 true，不然无法恢复视图
        is_paused_ = is_paused;
    }
}
