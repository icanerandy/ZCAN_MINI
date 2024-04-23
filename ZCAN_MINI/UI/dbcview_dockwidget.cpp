#include "dbcview_dockwidget.h"
#include "ui_dbcview_dockwidget.h"

DBCViewDockWidget::DBCViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DBCViewDockWidget),
    tree_model_(new QStandardItemModel()),
    item_selection_model_(new QItemSelectionModel(tree_model_)),
    table_model_(new QStandardItemModel())
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 2);

    ui->treeView->setColumnWidth(0, 200);
    ui->treeView->setColumnWidth(1, 200);

    ui->treeView->setModel(tree_model_);
    ui->treeView->setSelectionModel(item_selection_model_);

    // 为tableview设置model
    ui->tableView->setModel(table_model_);
    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectItems);

    //设置选中时为整行选中
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 隐藏不必要的表头
    ui->treeView->header()->hide();
    ui->tableView->verticalHeader()->hide();

    // 设置表头左对齐
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //表头设置最后一列数据填充整个控件
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    //表头内容均分填充整个控件
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    int max_height = 35;
    QColor color("#607D8B");
    ui->btnSearch->setBackgroundColor(color);
    ui->btnSearch->setFixedHeight(max_height);
    ui->btnReadDBC->setBackgroundColor(QColor("#3881A6"));
    ui->btnReadDBC->setFixedHeight(max_height);

    ui->lineEdit->setFixedHeight(max_height);
    ui->lineEdit->setLabelColor(QColor(0, 0, 0, 0));
    // ui->lineEdit->setLabel("dafdsafdsa");
    ui->lineEdit->setInkColor(QColor("#7BA0B3"));

    connect(item_selection_model_, &QItemSelectionModel::currentChanged, this, &DBCViewDockWidget::slot_currentChanged);
    connect(ui->btnReadDBC, &QPushButton::clicked, this, &DBCViewDockWidget::slot_btnReadDBC_clicked);  
    connect(tree_model_, &QStandardItemModel::itemChanged, this, &DBCViewDockWidget::slot_itemCheckStatChanged);
}

DBCViewDockWidget::~DBCViewDockWidget()
{
    delete ui;
}

void DBCViewDockWidget::slot_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    QStringList str_list;
    QStandardItem* item = tree_model_->itemFromIndex(current);
    if (item->data(Qt::UserRole).toBool())
    {
        str_list.clear();
        str_list << QStringLiteral("名字") << QStringLiteral("ID(Hex)") << QStringLiteral("DLC") << QStringLiteral("注释");

        Vector::DBC::Message msg;
        msg = network_.messages.at( item->data(Qt::UserRole+1).toUInt(nullptr) );

        table_model_->clear();
        item = new QStandardItem(QString::fromStdString(msg.name));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 0, item);
        item = new QStandardItem(QString("0x") + QString::number(msg.id, 16));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 1, item);
        item = new QStandardItem(QString::number(msg.size));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 2, item);
        item = new QStandardItem(QString::fromStdString(msg.comment));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 3, item);
    }
    else
    {
        str_list.clear();
        str_list << QStringLiteral("名字") << QStringLiteral("长度") << QStringLiteral("起始位") << QStringLiteral("因子")
                 << QStringLiteral("偏移") << QStringLiteral("类型") << QStringLiteral("字节序") << QStringLiteral("最小值")
                 << QStringLiteral("最大值") << QStringLiteral("注释");

        table_model_->clear();

        Vector::DBC::Message msg;
        msg = network_.messages.at( item->data(Qt::UserRole+1).toUInt(nullptr) );

        Vector::DBC::Signal sig;
        sig = msg._signals.at( item->data(Qt::UserRole+2).toString().toStdString() );

        item = new QStandardItem(QString::fromStdString(sig.name));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 0, item);

        item = new QStandardItem(QString::number(sig.bitSize, 16));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 1, item);

        item = new QStandardItem(QString::number(sig.startBit, 10));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 2, item);

        item = new QStandardItem(QString::number(sig.factor, 'f', 2));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 3, item);

        item = new QStandardItem(QString::number(sig.offset, 'f', 2));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 4, item);

        item = new QStandardItem(QString(sig.valueType==Vector::DBC::ValueType::Unsigned?"Unsigned":"Signed"));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 5, item);

        item = new QStandardItem(QString(sig.byteOrder==Vector::DBC::ByteOrder::Motorola?"Motorola":"Intel"));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 6, item);

        item = new QStandardItem(QString::number(sig.minimum));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 7, item);

        item = new QStandardItem(QString::number(sig.maximum));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 8, item);

        item = new QStandardItem(QString::fromStdString(sig.comment));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        table_model_->setItem(0, 9, item);
    }
    table_model_->setHorizontalHeaderLabels(str_list);
}

void DBCViewDockWidget::slot_itemCheckStatChanged(QStandardItem *item)
{
    if (nullptr == item)
        return;

    // 获取对应消息
    Vector::DBC::Message msg;
    msg = network_.messages.at( item->data(Qt::UserRole+1).toUInt(nullptr) );

    static bool update_msg = false;
    if (item->isCheckable())
    {
        Qt::CheckState state = item->checkState(); //获取当前的选择状态

        if (item->data(Qt::UserRole).toBool())  // 是消息 bug!
        {
            update_msg = true;
            int rowCount = item->rowCount();
            for(int i = 0; i < rowCount; ++i)
            {
                QStandardItem* child_item = item->child(i);
                child_item->setCheckState(state);

                Vector::DBC::Signal sig;
                sig = msg._signals.at( child_item->data(Qt::UserRole+2).toString().toStdString() );

                if (item->checkState() == Qt::Checked)
                    sig_lst_.push_back(QPair<uint32_t, Vector::DBC::Signal>(msg.id, sig));
                else
                {
                    int i = 0;
                    for (auto& val : sig_lst_)
                    {
                        if (val.first == msg.id && val.second.name == sig.name)
                            sig_lst_.removeAt(i);
                        ++i;
                    }
                }
            }
            emit sig_sigChecked(sig_lst_);
            update_msg = false;
        }
        else    // 是信号
        {
            if (update_msg)
                return;

            Vector::DBC::Signal sig;
            sig = msg._signals.at( item->data(Qt::UserRole+2).toString().toStdString() );

            if (item->checkState() == Qt::Checked)
                sig_lst_.push_back(QPair<uint32_t, Vector::DBC::Signal>(msg.id, sig));
            else
            {
                int i = 0;
                for (auto& val : sig_lst_)
                {
                    if (val.first == msg.id && val.second.name == sig.name)
                        sig_lst_.removeAt(i);
                    ++i;
                }
            }

            emit sig_sigChecked(sig_lst_);
        }
    }
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

    sig_lst_.clear();
    tree_model_->clear();
    table_model_->clear();
    QStandardItem* item = nullptr;
    QStandardItem* child_item = nullptr;
    for (const auto& message : network_.messages)
    {
        item = new QStandardItem(QString("%1 (0x%2)").
                                 arg(QString::fromStdString(message.second.name)).
                                 arg(QString::number(message.second.id, 16))
                                 );
        item->setData(true, Qt::UserRole);   // 设置一个数据：是否为报文
        item->setData(message.second.id, Qt::UserRole+1);   // 设置一个数据：报文ID
        item->setCheckable(false);
        tree_model_->appendRow(item);

        for(auto& sig : message.second._signals)
        {
            child_item = new QStandardItem(QString::fromStdString(sig.second.name));
            child_item->setData(false, Qt::UserRole);   // 设置一个数据：是否为报文
            child_item->setData(message.second.id, Qt::UserRole+1);   // 设置一个数据：报文ID
            child_item->setData(QString::fromStdString(sig.second.name), Qt::UserRole+2);   // 设置一个数据：信号名
            child_item->setCheckable(true);
            item->appendRow(child_item);
        }
    }
}
