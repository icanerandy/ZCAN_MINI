#include "initcan_dialog.h"
#include "ui_init_can_dialog.h"

InitCanDialog::InitCanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitCanDialog)
{
    ui->setupUi(this);

    InitDialog();

    BindSlots();
}

InitCanDialog::~InitCanDialog()
{
    delete ui;
}

void InitCanDialog::InitDialog()
{
    QStringList strList;
    strList << "CAN" << "CANFD";
    ui->comboProtocol->addItems(strList);
    ui->comboProtocol->setCurrentIndex(1);

    strList.clear();
    strList << "CANFD ISO" << "NON-ISO";
    ui->comboCanfdStandard->addItems(strList);

    strList.clear();
    strList << "否" << "是";
    ui->comboCanfdSpeedUp->addItems(strList);
    ui->comboCanfdSpeedUp->setCurrentIndex(1);

    strList.clear();
    strList << "1Mbps" << "800kbps" << "500kbps" << "250kbps" << "125kbps" << "100kbps" << "50kbps";
    ui->comboAbit->addItems(strList);
    ui->comboAbit->setCurrentIndex(2);

    strList.clear();
    strList << "5Mbps" << "4Mbps" << "2Mbps" << "1Mbps";
    ui->comboDbit->addItems(strList);
    ui->comboDbit->setCurrentIndex(2);

    strList.clear();
    strList << "正常模式" << "只听模式";
    ui->comboWorkMode->addItems(strList);

    strList.clear();
    strList << "禁能" << "使能";
    ui->comboResistance->addItems(strList);
    ui->comboResistance->setCurrentIndex(1);
}

void InitCanDialog::BindSlots()
{
    connect(ui->comboProtocol,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &InitCanDialog::slot_comboProtocol_currentIndexChanged);

    connect(ui->comboCanfdStandard,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &InitCanDialog::slot_comboCanfdStandard_currentIndexChanged);

    connect(ui->comboCanfdSpeedUp,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &InitCanDialog::slot_comboCanfdSpeedUp_currentIndexChanged);

    connect(ui->comboAbit,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &InitCanDialog::slot_comboAbit_currentIndexChanged);

    connect(ui->comboDbit,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &InitCanDialog::slot_comboDbit_currentIndexChanged);\

    connect(ui->comboWorkMode,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &InitCanDialog::slot_comboWorkMode_currentIndexChanged);

    connect(ui->comboResistance,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &InitCanDialog::slot_comboResistance_currentIndexChanged);
}

void InitCanDialog::slot_comboProtocol_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->set_protocol_index(index);

    if (index == 0) // CAN设备
        ui->comboDbit->setEnabled(false);
    else
        ui->comboDbit->setEnabled(true);
}

void InitCanDialog::slot_comboCanfdStandard_currentIndexChanged(int index)
{

}

void InitCanDialog::slot_comboCanfdSpeedUp_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->set_canfd_exp_index(index);
}

void InitCanDialog::slot_comboAbit_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->set_abit_baud_index(index);
}

void InitCanDialog::slot_comboDbit_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->set_dbit_baud_index(index);
}

void InitCanDialog::slot_comboWorkMode_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->set_work_mode_index(index);
}

void InitCanDialog::slot_comboResistance_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->set_resistance_enable(index);
}

void InitCanDialog::on_btnOk_clicked()
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    bool ret = device_manager->InitCan();
    if (!ret)
    {
        return;
    }

    ret = device_manager->StartCan();
    if (!ret)
        return;

    /* 启动消息接收线程 */
    RecMsgThread *rec_msg_thread = RecMsgThread::GetInstance();
    rec_msg_thread->start();
    rec_msg_thread->beginThread();


    /* 关联数据模型的信号与槽 */
    // 一定要避免多次连接
    CanFrameTableModel *canFrameTableModel = CanFrameTableModel::GetInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_Receive_Data *, uint)>(&RecMsgThread::newMsg),
            canFrameTableModel, static_cast<void (CanFrameTableModel::*)(ZCAN_Receive_Data *, uint)>(&CanFrameTableModel::newMsg),
            Qt::UniqueConnection);
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(ZCAN_ReceiveFD_Data *, uint)>(&RecMsgThread::newMsg),
            canFrameTableModel, static_cast<void (CanFrameTableModel::*)(ZCAN_ReceiveFD_Data *, uint)>(&CanFrameTableModel::newMsg),
            Qt::UniqueConnection);

    this->hide();
}
