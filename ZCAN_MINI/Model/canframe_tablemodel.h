#ifndef CANFRAMETABLEMODEL_H
#define CANFRAMETABLEMODEL_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QAbstractTableModel>
#include <QList>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QFont>
#include <QTimer>
#include <QMutex>
#include "zlgcan.h"


class CanFrameTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum struct VisibleColumns {
        Index,
        TimeStamp,
        Id,
        FrameType,
        Format,
        CanType,
        Direction,
        Length,
        Data
    };

private:
    explicit CanFrameTableModel(QObject *parent = nullptr);

public:
    static CanFrameTableModel *GetInstance();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    //Qt::ItemFlags flags(const QModelIndex &index) const override;

public:
    void clearData();

signals:
    void rowsInserted();
    void updateView();

public slots:
    void slot_newMsg(const ZCAN_Receive_Data* can_data, const uint len);
    void slot_newMsg(const ZCAN_ReceiveFD_Data* canfd_data, const uint len);
    void slot_visibleCol_changed(QList<uint> visible_columns);
    void slot_check_id(bool chk_id_enable, uint32_t chk_id);
    void slot_paused_clicked(bool is_paused);

public:
    bool chk_id_enable_;
    uint32_t chk_id_;
    uint32_t page_num_; // 页码
    uint32_t total_page_num_;    // 总页数
    uint32_t max_num_per_page_;    // 每页最大显示数量
    mutable QMutex mutex;
    bool is_add_data;
    mutable bool is_show_data;

private:
    bool is_paused_;
    bool reset_flag_;
    uint paused_row_count_;

private:
    QStringList header_list_;
    QList<uint> visible_columns_; // 存储可见列的索引
    QList<QVariant> can_frame_list_;
};

#endif // CANFRAMETABLEMODEL_H
