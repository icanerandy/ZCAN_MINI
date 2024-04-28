#include "senddata_dialog.h"
#include "ui_senddata_dialog.h"

SendDataDialog::SendDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendDataDialog),
    id_(0x01),
    datas_("00 01 02 03 04 05 06 07 08"),
    send_count_once_(1),
    frame_type_(DeviceManager::FrameType::Can),
    frame_delay_time_(0),
    protocol_type_(DeviceManager::ProtocolType::Can),
    data_length_(8),
    send_type_(DeviceManager::SendType::Normal),
    send_count_(1)
{
    ui->setupUi(this);

    int max_height = 35;
    QColor color(QStringLiteral("#607D8B"));

    ui->btnSend->setBackgroundColor(color);
    ui->btnSend->setFixedHeight(max_height);
    ui->btnAddToList->setBackgroundColor(color);
    ui->btnAddToList->setFixedHeight(max_height);
    ui->btnSendSeq->setBackgroundColor(color);
    ui->btnSendSeq->setFixedHeight(max_height);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    initDlg();
    bindSignals();
}

SendDataDialog::~SendDataDialog()
{
    delete ui;
}

void SendDataDialog::initDlg()
{
    QStringList str_list;
    str_list << QStringLiteral("标准帧") << QStringLiteral("扩展帧");
    ui->comboFrameType->addItems(str_list);
    str_list.clear();

    str_list << QStringLiteral("CAN") << QStringLiteral("CANFD") << QStringLiteral("CANFD加速");
    ui->comboProtocolType->addItems(str_list);
    str_list.clear();

    str_list << QStringLiteral("数据帧") << QStringLiteral("远程帧");
    ui->comboFormat->addItems(str_list);
    str_list.clear();

    str_list << QStringLiteral("0") << QStringLiteral("1") << QStringLiteral("2") << QStringLiteral("3")
                << QStringLiteral("4") << QStringLiteral("5") << QStringLiteral("6") << QStringLiteral("7")
                   << QStringLiteral("8");
    ui->comboLength->addItems(str_list);
    str_list.clear();
    ui->comboLength->setCurrentIndex(8);

    str_list << QStringLiteral("正常发送") << QStringLiteral("单次发送") << QStringLiteral("自发自收") << QStringLiteral("单次自发自收");
    ui->comboSendType->addItems(str_list);
    str_list.clear();

    ui->editData->setText(QStringLiteral("00 01 02 03 04 05 06 07"));
    ui->spinSendCountOnce->setValue(1);
    ui->spinSendCount->setValue(1);
    ui->spinInterval->setValue(0);

    ui->editId->setText(QStringLiteral("1"));

    const QString reg = "^([0-9A-Fa-f]{2}\\s?){1,"+ QString::number(data_length_, 10) +"}$";
    const QRegularExpression regExp(reg);
    ui->editData->setValidator(new QRegularExpressionValidator(regExp, this));
}

void SendDataDialog::bindSignals()
{
    connect(ui->comboFrameType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] (int index) {
        frame_type_ = static_cast<DeviceManager::FrameType>(index);
    });

    connect(ui->comboProtocolType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] (int index) {
        protocol_type_ = static_cast<DeviceManager::ProtocolType>(index);

        if (0 == index)
        {
            QStringList str_list;
            str_list << QStringLiteral("0") << QStringLiteral("1") << QStringLiteral("2") << QStringLiteral("3")
                        << QStringLiteral("4") << QStringLiteral("5") << QStringLiteral("6") << QStringLiteral("7")
                           << QStringLiteral("8");
            ui->comboLength->clear();
            ui->comboLength->addItems(str_list);
            ui->comboLength->setCurrentIndex(8);
        }
        else
        {
            QStringList str_list;
            str_list << QStringLiteral("0") << QStringLiteral("1") << QStringLiteral("2") << QStringLiteral("3")
                        << QStringLiteral("4") << QStringLiteral("5") << QStringLiteral("6") << QStringLiteral("7")
                           << QStringLiteral("8") << QStringLiteral("16") << QStringLiteral("20") << QStringLiteral("24")
                           << QStringLiteral("32") << QStringLiteral("48") << QStringLiteral("64");
            ui->comboLength->clear();
            ui->comboLength->addItems(str_list);
            ui->comboLength->setCurrentIndex(8);
        }
    });

    connect(ui->comboSendType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] (int index) {
        send_type_ = static_cast<DeviceManager::SendType>(index);
    });

    connect(ui->spinSendCountOnce, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int value) {
        send_count_once_ = value;
    });

    connect(ui->spinSendCount, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int value) {
        send_count_ = value;
    });

    connect(ui->spinInterval, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] (int value) {
        frame_delay_time_ = value;
    });

    connect(ui->editData, static_cast<void (QLineEdit::*)(const QString &)>(&QLineEdit::textChanged), this, [=] (const QString &text) {
        const uint size = text.size();
        if (size > 1 && size > text_length_)
        {
            if (text.at(size-1) != ' ' && text.at(size-2) != ' ')
            {
                QString str = text;
                str.append(' ');
                ui->editData->setText(str);
                //ui->editData->setCursorPosition(size + 1);  // 更新光标位置
            }
        }
        text_length_ = text.size();
    });

    connect(ui->comboLength, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] {
        data_length_ = ui->comboLength->currentText().toInt(nullptr, 10);

        const QStringList str_list = ui->editData->text().split(' ');
        if (static_cast<uint>(str_list.size()) > data_length_)
        {
            QString str = "";
            for (size_t i = 0; i < data_length_; ++i)
            {
                // i为uint，at(int)，i过大会怎样？数据切割，qt6已解决
                str.append(str_list.at(i));
                str.append(' ');
            }
            ui->editData->setText(str);
        }
        const QString reg = "^([0-9A-Fa-f]{2}\\s?){1,"+ QString::number(data_length_, 10) +"}$";
        const QRegularExpression regExp(reg);
        ui->editData->setValidator(new QRegularExpressionValidator(regExp, this));
    });

    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(1);
    ui->tableWidget->insertColumn(2);
    ui->tableWidget->insertColumn(3);
    ui->tableWidget->insertColumn(4);
    ui->tableWidget->insertColumn(5);

    QStringList headers;
    headers << QStringLiteral("id") << QStringLiteral("帧格式") << QStringLiteral("协议类型") << QStringLiteral("帧类型") << QStringLiteral("数据长度") << QStringLiteral("数据");
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);   // 设置最后一列自适应宽度

    connect(ui->btnAddToList, &QtMaterialRaisedButton::clicked, this, [=] {
        id_ = ui->editId->text().toUInt(nullptr, 16);
        datas_ = ui->editData->text();
        QStringList str_list = datas_.split(' ');
        if (static_cast<uint>(str_list.size()) < data_length_)
        {
            for (uint i = 0; i < data_length_ - str_list.size(); ++i)
                str_list.append("00");
        }
        datas_ = str_list.join(" ");

        uint row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        QTableWidgetItem* item = new QTableWidgetItem(QString::number(id_));
        item->setData(Qt::UserRole, QVariant(id_));
        ui->tableWidget->setItem(row, 0, item);

        item = new QTableWidgetItem(frame_type_ == DeviceManager::FrameType::Can ? "标准帧" : "扩展帧");
        if (DeviceManager::FrameType::Can == frame_type_)
            item->setData(Qt::UserRole, QVariant(0));
        else
            item->setData(Qt::UserRole, QVariant(1));
        ui->tableWidget->setItem(row, 1, item);

        item = new QTableWidgetItem(protocol_type_ == DeviceManager::ProtocolType::Can ? "CAN" :
                                        (protocol_type_ == DeviceManager::ProtocolType::CanFd ? "CANFD" : "CANFD加速"));
        if (DeviceManager::ProtocolType::Can == protocol_type_)
            item->setData(Qt::UserRole, QVariant(0));
        else if (DeviceManager::ProtocolType::CanFd == protocol_type_)
            item->setData(Qt::UserRole, QVariant(1));
        else
            item->setData(Qt::UserRole, QVariant(2));
        ui->tableWidget->setItem(row, 2, item);

        ui->tableWidget->setItem(row, 3, new QTableWidgetItem("数据帧"));

        item = new QTableWidgetItem(QString::number(data_length_));
        item->setData(Qt::UserRole, QVariant(data_length_));
        ui->tableWidget->setItem(row, 4, item);

        item = new QTableWidgetItem(datas_);
        item->setData(Qt::UserRole, QVariant(datas_));
        ui->tableWidget->setItem(row, 5, item);
    });

    connect(ui->btnSend, &QtMaterialRaisedButton::clicked, this, &SendDataDialog::slot_btnSend_clicked);

    connect(ui->btnSendSeq, &QtMaterialRaisedButton::clicked, this, [=] {
        DeviceManager * const device_manager = DeviceManager::getInstance();

        if (DeviceManager::Enable::Enabled == device_manager->send_enable())
        {
            device_manager->set_send_enable(DeviceManager::Enable::Unenabled);
            timer_.stop();
            ui->btnSendSeq->setText("开始列表发送");
        }
        else
        {
            device_manager->set_send_enable(DeviceManager::Enable::Enabled);
            timer_.start(ui->spinFrmInterval->value());
            ui->btnSendSeq->setText("停止列表发送");
        }
    });

    connect(&timer_, &QTimer::timeout, this, [=] {
        DeviceManager * const device_manager = DeviceManager::getInstance();

        static uint i = 0;
        if (0 == ui->tableWidget->rowCount())
            return;
        if (i == ui->tableWidget->rowCount())
            i = 0;

        device_manager->set_id(ui->tableWidget->item(i, 0)->data(Qt::UserRole).toUInt(nullptr));

        if (ui->tableWidget->item(i, 1)->data(Qt::UserRole) == 0)
            device_manager->set_frame_type_index(DeviceManager::FrameType::Can);
        else
            device_manager->set_frame_type_index(DeviceManager::FrameType::CanFd);

        if (ui->tableWidget->item(i, 2)->data(Qt::UserRole) == 0)
            device_manager->set_protocol_index(DeviceManager::ProtocolType::Can);
        else if (ui->tableWidget->item(i, 2)->data(Qt::UserRole) == 1)
            device_manager->set_protocol_index(DeviceManager::ProtocolType::CanFd);
        else
            device_manager->set_protocol_index(DeviceManager::ProtocolType::CanFdBrs);

        device_manager->set_data_length(ui->tableWidget->item(i, 4)->data(Qt::UserRole).toUInt(nullptr));
        device_manager->set_data(ui->tableWidget->item(i, 5)->data(Qt::UserRole).toString());
        device_manager->set_send_count_once(send_count_once_);
        device_manager->set_frm_delay_time(frame_delay_time_);
        device_manager->set_send_type_index(send_type_);
        device_manager->set_send_count(send_count_);

        device_manager->sendMsg();
        device_manager->stopSendMsg();

        ++i;
    });
}

void SendDataDialog::slot_btnSend_clicked()
{
    DeviceManager * const device_manager = DeviceManager::getInstance();
    id_ = ui->editId->text().toUInt(nullptr, 16);
    device_manager->set_id(id_);

    datas_ = ui->editData->text();

    device_manager->set_data_length(data_length_);

    QStringList str_list = datas_.split(' ');
    if (static_cast<uint>(str_list.size()) < data_length_)
    {
        for (uint i = 0; i < data_length_ - str_list.size(); ++i)
            str_list.append("00");
    }
    datas_ = str_list.join(" ");

    device_manager->set_data(datas_);

    device_manager->set_frame_type_index(frame_type_);
    device_manager->set_protocol_index(protocol_type_);
    device_manager->set_send_count_once(send_count_once_);
    device_manager->set_frm_delay_time(frame_delay_time_);
    device_manager->set_send_type_index(send_type_);
    device_manager->set_send_count(send_count_);

    if (DeviceManager::Enable::Enabled == device_manager->send_enable())
    {
        device_manager->set_send_enable(DeviceManager::Enable::Unenabled);
        device_manager->stopSendMsg();
        ui->btnSend->setText(QStringLiteral("开始发送"));
    }
    else
    {
        device_manager->set_send_enable(DeviceManager::Enable::Enabled);
        device_manager->sendMsg();
        ui->btnSend->setText(QStringLiteral("停止发送"));
    }
}
