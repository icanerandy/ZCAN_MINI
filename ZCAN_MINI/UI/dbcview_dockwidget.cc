#include "dbcview_dockwidget.h"
#include "ui_dbcview_dockwidget.h"

DBCViewDockWidget::DBCViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DBCViewDockWidget),
    message_model(nullptr),
    signal_model(nullptr)
{
    ui->setupUi(this);

    message_model = new QStandardItemModel();
    signal_model = new QStandardItemModel();

    ui->msgView->setModel(message_model);
    ui->sigView->setModel(signal_model);


    //设置选中时为整行选中
    ui->msgView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->sigView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->msgView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sigView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 表格宽度随内容自动扩展
    ui->msgView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 表格宽度自动根据UI进行计算，不可手动调整宽度
    //ui->msgView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 表格宽度随内容自动扩展
    ui->sigView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 表格宽度自动根据UI进行计算，不可手动调整宽度
    //ui->sigView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList str_list;
    str_list << QStringLiteral("名字") << QStringLiteral("ID") << QStringLiteral("DLC") << QStringLiteral("注释");
    message_model->setHorizontalHeaderLabels(str_list);
    str_list.clear();
    str_list << QStringLiteral("名字") << QStringLiteral("长度") << QStringLiteral("起始位") << QStringLiteral("因子")
             << QStringLiteral("偏移") << QStringLiteral("类型") << QStringLiteral("字节序") << QStringLiteral("最小值")
             << QStringLiteral("最大值") << QStringLiteral("注释");
    signal_model->setHorizontalHeaderLabels(str_list);

    connect(ui->btnReadDBC, &QPushButton::clicked, this, &DBCViewDockWidget::slot_btnReadDBC_clicked);
    connect(ui->msgView, &QAbstractItemView::clicked, this, &DBCViewDockWidget::slot_message_model_clicked);
}

DBCViewDockWidget::~DBCViewDockWidget()
{
    delete ui;
}

void DBCViewDockWidget::slot_btnReadDBC_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "选择dbc文件", QDir::currentPath(), nullptr);
    if (filename.isEmpty())
        return;

    db = CppCAN::CANDatabase::fromFile(filename.toStdString());
    QStandardItem *item = nullptr;
    size_t i = 0;
    for(const auto& frame : db) {
        item = new QStandardItem(QString::fromStdString(frame.second.name()));
        message_model->setItem(i, 0, item);

        item = new QStandardItem(QString::number(frame.second.can_id(), 16));
        message_model->setItem(i, 1, item);

        item = new QStandardItem(QString::number(frame.second.dlc(), 10));
        message_model->setItem(i, 2, item);

        item = new QStandardItem(QString::fromStdString(frame.second.comment()));
        message_model->setItem(i, 3, item);

        i++;
    }
}

void DBCViewDockWidget::slot_message_model_clicked(const QModelIndex &index)
{
    uint row = index.row();
    QStandardItem *item = message_model->item(row);
    QString msg_name = item->text();
    const CppCAN::CANFrame& msg = db.at(msg_name.toStdString());

    item = nullptr;
    size_t i = 0;
    for(const auto& sig : msg) {
        item = new QStandardItem(QString::fromStdString(sig.second.name()));
        signal_model->setItem(i, 0, item);

        item = new QStandardItem(QString::number(sig.second.length(), 16));
        signal_model->setItem(i, 1, item);

        item = new QStandardItem(QString::number(sig.second.start_bit(), 10));
        signal_model->setItem(i, 2, item);

        item = new QStandardItem(QString::number(sig.second.scale(), 'f', 2));
        signal_model->setItem(i, 3, item);

        item = new QStandardItem(QString::number(sig.second.offset(), 'f', 2));
        signal_model->setItem(i, 4, item);

        item = new QStandardItem(QString(sig.second.signedness()==CppCAN::CANSignal::Signed?"Signed":"Unsigned"));
        signal_model->setItem(i, 5, item);

        item = new QStandardItem(QString(sig.second.endianness()==CppCAN::CANSignal::BigEndian?"BigEndian":"LittleEndian"));
        signal_model->setItem(i, 6, item);

        item = new QStandardItem(QString::number(sig.second.range().min, 10));
        signal_model->setItem(i, 7, item);

        item = new QStandardItem(QString::number(sig.second.range().max, 10));
        signal_model->setItem(i, 8, item);

        item = new QStandardItem(QString::fromStdString(sig.second.comment()));
        signal_model->setItem(i, 9, item);

        i++;
    }
}
