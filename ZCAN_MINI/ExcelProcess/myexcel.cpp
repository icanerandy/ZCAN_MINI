#include "myexcel.h"

MyExcel::MyExcel()
{

}

void MyExcel::slot_info(QString date, QString device_name, QString tester, QString sig1, QString sig2)
{
    date_ = date;
    device_name_ = device_name;
    tester_ = tester;
    sig1_ = sig1;
    sig2_ = sig2;
}

QString MyExcel::slot_saveAs()
{
    QString file;
    QString filter;
    //如果版本低于QT5,则需要将:
    //  QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
    //改为:QDesktopServices::storageLocation(QDesktopServices::DesktopLocation),
    file = QFileDialog::getSaveFileName (
        NULL,
        "save",
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),      //设置路径, .表示当前路径,./表示更目录
        "Excel(*.xlsx)",     //过滤器
        &filter);

    return file.replace("/","\\");
}

void MyExcel::slot_setOneCell(QAxObject* worksheet, ColumnType column, int row, QColor color, QString text)
{
    // 确保 column 变量能被转换为 QVariant。假设 ColumnType 可以转换为 int，这里将 column 显式转换为 int。
    QAxObject* cell = worksheet->querySubObject("Cells(int, int)", row, static_cast<int>(column));

    cell->setProperty("Value", text);

    QAxObject* font = cell->querySubObject("Font");
    // 设置字体颜色。QColor 需要转换为 Excel 识别的颜色代码，这通常是一个 RGB 整数值。
    font->setProperty("Color", color.rgb());  // 使用 QColor 的 rgb() 方法获取颜色的整数值
}

bool MyExcel::slot_writeOneTable(QString filepath, int startRow, QVector< QVector<QVariant> > table)
{
    if (!table.isEmpty() && !filepath.isEmpty())
    {
        filepath.replace("/","\\");
        //新建excel表
        QAxObject excel("Excel.Application");
        excel.dynamicCall("SetVisible (bool Visible)", "false");
        excel.setProperty("DisplayAlerts", false);
        QAxObject* workbooks = excel.querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");
        QAxObject* workbook = excel.querySubObject("ActiveWorkBook");
        QAxObject* sheet = workbook->querySubObject("WorkSheets(int)", 1);

        startRow += 3;

        QAxObject* cellRange = nullptr;
        slot_setOneCell(sheet, ColumnType::ColumnA, 1, Qt::black, "测试记录");
        cellRange = sheet->querySubObject("Range(const QString&)", "A1:F1");
        cellRange->dynamicCall("Merge()");
        cellRange->setProperty("HorizontalAlignment", -4108); // xlCenter
        cellRange->setProperty("VerticalAlignment", -4108); // xlCenter
        delete cellRange;

        slot_setOneCell(sheet, ColumnType::ColumnA, 2, Qt::black, "日期:"+date_);
        cellRange = sheet->querySubObject("Range(const QString&)", "A2:B2");
        cellRange->dynamicCall("Merge()");
        cellRange->setProperty("HorizontalAlignment", -4108); // xlCenter
        cellRange->setProperty("VerticalAlignment", -4108); // xlCenter
        delete cellRange;

        slot_setOneCell(sheet, ColumnType::ColumnC, 2, Qt::black, "产品型号:"+device_name_);
        cellRange = sheet->querySubObject("Range(const QString&)", "C2:D2");
        cellRange->dynamicCall("Merge()");
        cellRange->setProperty("HorizontalAlignment", -4108); // xlCenter
        cellRange->setProperty("VerticalAlignment", -4108); // xlCenter
        delete cellRange;

        slot_setOneCell(sheet, ColumnType::ColumnE, 2, Qt::black, "测试人:"+tester_);
        cellRange = sheet->querySubObject("Range(const QString&)", "E2:F2");
        cellRange->dynamicCall("Merge()");
        cellRange->setProperty("HorizontalAlignment", -4108); // xlCenter
        cellRange->setProperty("VerticalAlignment", -4108); // xlCenter
        delete cellRange;

        slot_setOneCell(sheet, ColumnType::ColumnA, 3, Qt::black, "时间");
        slot_setOneCell(sheet, ColumnType::ColumnB, 3, Qt::black, sig1_);
        slot_setOneCell(sheet, ColumnType::ColumnC, 3, Qt::black, sig2_);
        slot_setOneCell(sheet, ColumnType::ColumnD, 3, Qt::black, "绝对偏差");

        // 数据转换
        QVariantList tdata;
        QVariant var;
        int row = table.count();
        int col = table[0].count();

        for (int i = 0; i < row; i++)
        {
            //tdata << table[i].toList(); // 这个地方一定要注意！！！这种写法是错误的
            tdata << QVariant(table[i].toList());//ok
        }
        var = tdata; // 注意！

        // 例如写入单元格范围A1:L2243
        QString crange;
        convert_to_col_name(col, crange);
        crange = QString("A%1:%2%3").arg(startRow).arg(crange).arg(row+startRow-1);

        //写入数据
        QAxObject* range = sheet->querySubObject("Range(const QString &)", crange);
        QVariant res = range->setProperty("Value", var);
        range->setProperty("HorizontalAlignment", -4108); // xlCenter
        range->setProperty("VerticalAlignment", -4108); // xlCenter
        delete range;

        //退出
        workbook->dynamicCall("SaveAs(const QString&)", filepath);
        workbook->dynamicCall("Close(Boolean)", false);
        excel.dynamicCall("Quit(void)");

        emit finished(true);
        return true;
    }

    emit finished(false);
    return false;
}

void MyExcel::convert_to_col_name(int data, QString &res)
{
    Q_ASSERT(data > 0 && data < 65535);
    int tempData = data / 26;
    if (tempData > 0)
    {
        int mode = data % 26;
        convert_to_col_name(mode, res);
        convert_to_col_name(tempData, res);
    }
    else
    {
        res = (to_26_alphabet_string(data) + res);
    }
}

QString MyExcel::to_26_alphabet_string(int data)
{
    QChar ch = data + 0x40;//A对应0x41
    return QString(ch);
}
