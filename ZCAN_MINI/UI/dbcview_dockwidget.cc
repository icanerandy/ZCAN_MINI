#include "dbcview_dockwidget.h"
#include "ui_dbcview_dockwidget.h"

DBCViewDockWidget::DBCViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DBCViewDockWidget),
    message_model_(new QStandardItemModel()),
    signal_model_(new QStandardItemModel()),
    item_selection_model_(new QItemSelectionModel(message_model_)),
    msg_(nullptr)
{
    ui->setupUi(this);

    ui->msgView->setModel(message_model_);
    ui->sigView->setModel(signal_model_);
    ui->msgView->setSelectionModel(item_selection_model_);

    ui->msgView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->msgView->setSelectionBehavior(QAbstractItemView::SelectItems);

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
    str_list << QStringLiteral("名字") << QStringLiteral("ID(Hex)") << QStringLiteral("DLC") << QStringLiteral("注释");
    message_model_->setVerticalHeaderLabels(str_list);
    str_list.clear();
    str_list << QStringLiteral("名字") << QStringLiteral("长度") << QStringLiteral("起始位") << QStringLiteral("因子")
             << QStringLiteral("偏移") << QStringLiteral("类型") << QStringLiteral("字节序") << QStringLiteral("最小值")
             << QStringLiteral("最大值") << QStringLiteral("注释");
    signal_model_->setHorizontalHeaderLabels(str_list);

    connect(ui->btnReadDBC, &QPushButton::clicked, this, &DBCViewDockWidget::slot_btnReadDBC_clicked);

    connect(ui->btnPaint, &QPushButton::clicked, this, [=] {
        emit sig_paint(msg_->can_id(), sig_lst_);
    });
}

DBCViewDockWidget::~DBCViewDockWidget()
{
    delete ui;
}

void DBCViewDockWidget::slot_btnReadDBC_clicked()
{
    const QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("选择dbc文件"),
                                                          QDir::currentPath(), QStringLiteral("DBC files (*.dbc)"));
    if (filename.isEmpty())
        return;

    db_ = CppCAN::CANDatabase::fromFile(filename.toStdString());

    QStandardItem* item = nullptr;
    for(const auto& frame : db_) {
        item = new QStandardItem(QString::fromStdString(frame.second.name()));
        message_model_->setItem(0, 0, item);

        item = new QStandardItem(QString::number(frame.second.can_id(), 16));
        message_model_->setItem(1, 0, item);

        item = new QStandardItem(QString::number(frame.second.dlc(), 10));
        message_model_->setItem(2, 0, item);

        item = new QStandardItem(QString::fromStdString(frame.second.comment()));
        message_model_->setItem(3, 0, item);
    }

    showSignals();
}

void DBCViewDockWidget::showSignals()
{
    signal_model_->clear();
    QStringList str_list;
    str_list.clear();
    str_list << QStringLiteral("名字") << QStringLiteral("长度") << QStringLiteral("起始位") << QStringLiteral("因子")
             << QStringLiteral("偏移") << QStringLiteral("类型") << QStringLiteral("字节序") << QStringLiteral("最小值")
             << QStringLiteral("最大值") << QStringLiteral("注释");
    signal_model_->setHorizontalHeaderLabels(str_list);

    QStandardItem *item = message_model_->item(0);
    QString msg_name = item->text();
    msg_ = &db_.at(msg_name.toStdString());

    item = nullptr;
    size_t i = 0;
    sig_lst_.clear();
    for(auto& sig : *msg_) {
        sig_lst_.push_back(&sig.second);
//        if (0 == i)
//            ref_speed_ = &sig.second;
//        else
//            rel_speed_ = &sig.second;

        item = new QStandardItem(QString::fromStdString(sig.second.name()));
        item->setEditable(false);
        signal_model_->setItem(i, 0, item);

        item = new QStandardItem(QString::number(sig.second.length(), 16));
        item->setEditable(false);
        signal_model_->setItem(i, 1, item);

        item = new QStandardItem(QString::number(sig.second.start_bit(), 10));
        item->setEditable(false);
        signal_model_->setItem(i, 2, item);

        item = new QStandardItem(QString::number(sig.second.scale(), 'f', 2));
        item->setEditable(false);
        signal_model_->setItem(i, 3, item);

        item = new QStandardItem(QString::number(sig.second.offset(), 'f', 2));
        item->setEditable(false);
        signal_model_->setItem(i, 4, item);

        item = new QStandardItem(QString(sig.second.signedness()==CppCAN::CANSignal::Signed?"Signed":"Unsigned"));
        item->setEditable(false);
        signal_model_->setItem(i, 5, item);

        item = new QStandardItem(QString(sig.second.endianness()==CppCAN::CANSignal::BigEndian?"BigEndian":"LittleEndian"));
        item->setEditable(false);
        signal_model_->setItem(i, 6, item);

        item = new QStandardItem(QString::number(sig.second.range().min, 10));
        item->setEditable(false);
        signal_model_->setItem(i, 7, item);

        item = new QStandardItem(QString::number(sig.second.range().max, 10));
        item->setEditable(false);
        signal_model_->setItem(i, 8, item);

        item = new QStandardItem(QString::fromStdString(sig.second.comment()));
        item->setEditable(false);
        signal_model_->setItem(i, 9, item);

        i++;
    }

    ui->btnPaint->setEnabled(true);
}
