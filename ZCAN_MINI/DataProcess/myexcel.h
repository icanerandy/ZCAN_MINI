#ifndef MYEXCEL_H
#define MYEXCEL_H

#include <QObject>
#include <QMetaType>
#include <QString>
#include <QVariant>
#include <QColor>
#include <QAxObject>
#include <QStandardPaths>
#include <QFileDialog>
#include <QRegExp>
#include <qdebug.h>

/*excel操作*/
enum class ColumnType{
    ColumnA = 1,
    ColumnB = 2,
    ColumnC = 3,
    ColumnD = 4,
    ColumnE = 5,
    ColumnF = 6,
    ColumnG = 7,
    ColumnH = 8,
    ColumnI = 9
};

class MyExcel : public QObject
{
    Q_OBJECT

public:
    MyExcel();

public slots:
    void slot_info(QString date, QString device_name, QString tester, QString sig1, QString sig2);

    /**
     * @brief slot_writeOneTable 批量写入数据 效率高
     * @param filepath 文件路径
     * @param startRow 起始的列
     * @param table 要保存的表(二维数据)
     * @return
     */
    bool slot_writeOneTable(QString filepath, int startRow, QVector<QVector<QVariant>> table);

    /**
     * @brief slot_saveAs 另存为 对话框
     * @return
     */
    QString slot_saveAs();

    /**
     * @brief slot_setOneCell 设置单行Excel数据,效率低
     * @param worksheet
     * @param column
     * @param row
     * @param color
     * @param text
     */
    void slot_setOneCell(QAxObject* worksheet, ColumnType column, int row, QColor color, QString text);

private:
    void convert_to_col_name(int data, QString& res);
    QString to_26_alphabet_string(int data);

signals:
    void finished(bool success);

private:
    QString date_;
    QString device_name_;
    QString tester_;
    QString sig1_;
    QString sig2_;
};

#endif // MYEXCEL_H
