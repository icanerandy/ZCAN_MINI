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

    connect(ui->btnSend, &QPushButton::clicked, this, &SendDataDialog::slot_btnSend_clicked);
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
