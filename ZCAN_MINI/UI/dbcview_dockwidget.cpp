#include "dbcview_dockwidget.h"
#include "ui_dbcview_dockwidget.h"

DBCViewDockWidget::DBCViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DBCViewDockWidget),
    message_model_(new QStandardItemModel()),
    signal_model_(new QStandardItemModel()),
    item_selection_model_(new QItemSelectionModel(message_model_)),
    paint_enabled_(true)
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

    ui->msgView->horizontalHeader()->setVisible(false);
    ui->sigView->verticalHeader()->setVisible(false);

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
        emit sig_paint(paint_enabled_, msg_.id, sig_lst_);
        paint_enabled_ = !paint_enabled_;
        if (paint_enabled_)
            ui->btnPaint->setText(QStringLiteral("开始绘图"));
        else
            ui->btnPaint->setText(QStringLiteral("停止绘图"));
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

    std::ifstream ifs(filename.toStdString());
    if (!ifs.is_open())
    {
        qDebug() << "List_Message_Signals <database.dbc>";
        return;
    }

    network_.messages.clear();
    network_.newSymbols.clear();
    ifs >> network_;
    if (!network_.successfullyParsed)
    {
        qDebug() << "Unable to parse file";
        return;
    }

    /* loop over messages */
    QStandardItem* item = nullptr;
    for (const auto& message : network_.messages)
    {
        item = new QStandardItem(QString::fromStdString(message.second.name));
        message_model_->setItem(0, 0, item);

        item = new QStandardItem(QString::number(message.second.id, 16));
        message_model_->setItem(1, 0, item);

        item = new QStandardItem(QString::number(message.second.size, 10));
        message_model_->setItem(2, 0, item);

        item = new QStandardItem(QString::fromStdString(message.second.comment));
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

    QStandardItem* item = message_model_->item(1);
    uint32_t can_id = item->text().toUInt(nullptr, 16);
    msg_ = network_.messages.at(can_id);

    item = nullptr;
    size_t i = 0;
    sig_lst_.clear();
    for(auto& sig : msg_._signals)
    {
        sig_lst_.push_back(&sig.second);

        item = new QStandardItem(QString::fromStdString(sig.second.name));
        item->setEditable(false);
        signal_model_->setItem(i, 0, item);

        item = new QStandardItem(QString::number(sig.second.bitSize, 16));
        item->setEditable(false);
        signal_model_->setItem(i, 1, item);

        item = new QStandardItem(QString::number(sig.second.startBit, 10));
        item->setEditable(false);
        signal_model_->setItem(i, 2, item);

        item = new QStandardItem(QString::number(sig.second.factor, 'f', 2));
        item->setEditable(false);
        signal_model_->setItem(i, 3, item);

        item = new QStandardItem(QString::number(sig.second.offset, 'f', 2));
        item->setEditable(false);
        signal_model_->setItem(i, 4, item);

        item = new QStandardItem(QString(sig.second.valueType==Vector::DBC::ValueType::Unsigned?"Unsigned":"Signed"));
        item->setEditable(false);
        signal_model_->setItem(i, 5, item);

        item = new QStandardItem(QString(sig.second.byteOrder==Vector::DBC::ByteOrder::Motorola?"Motorola":"Intel"));
        item->setEditable(false);
        signal_model_->setItem(i, 6, item);

        item = new QStandardItem(QString::number(sig.second.minimum));
        item->setEditable(false);
        signal_model_->setItem(i, 7, item);

        item = new QStandardItem(QString::number(sig.second.maximum));
        item->setEditable(false);
        signal_model_->setItem(i, 8, item);

        item = new QStandardItem(QString::fromStdString(sig.second.comment));
        item->setEditable(false);
        signal_model_->setItem(i, 9, item);

        i++;
    }

    ui->btnPaint->setEnabled(true);
}
