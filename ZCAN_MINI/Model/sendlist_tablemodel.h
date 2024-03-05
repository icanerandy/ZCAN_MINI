#ifndef SENDLISTTABLEMODEL_H
#define SENDLISTTABLEMODEL_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QAbstractTableModel>

class SendListTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit SendListTableModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QStringList header_lst;
    QList<QVariant> can_frame_lst;
};

#endif // SENDLISTTABLEMODEL_H
