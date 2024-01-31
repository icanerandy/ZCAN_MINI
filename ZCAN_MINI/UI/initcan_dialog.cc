#include "initcan_dialog.h"
#include "ui_initcan_dialog.h"

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
    DeviceManager *device_manager = DeviceManager::GetInstance();
    int device_type_index_ = device_manager->device_type_index();
    uint type = kDeviceType[device_type_index_].device_type;

    const bool usbcanfd = type==ZCAN_USBCANFD_100U ||
        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
    const bool pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
        type == ZCAN_PCIE_CANFD_200U || type == ZCAN_PCIE_CANFD_400U_EX;
    const bool canfdDevice = usbcanfd || pciecanfd;

    QStringList strList;

    if (!canfdDevice)
    {
        strList << "CAN";
        ui->comboProtocol->addItems(strList);
        ui->comboProtocol->setCurrentIndex(0);
        ui->comboProtocol->setEnabled(false);

        strList.clear();
        strList << "禁用";
        ui->comboDbit->addItems(strList);
        ui->comboDbit->setCurrentIndex(0);
        ui->comboDbit->setEnabled(false);
    }
    else
    {
        strList << "CANFD";
        ui->comboProtocol->addItems(strList);
        ui->comboProtocol->setCurrentIndex(0);
        ui->comboProtocol->setEnabled(false);

        strList.clear();
        strList << "5Mbps" << "4Mbps" << "2Mbps" << "1Mbps";
        ui->comboDbit->addItems(strList);
        ui->comboDbit->setCurrentIndex(2);
    }

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
    strList << "正常模式" << "只听模式";
    ui->comboWorkMode->addItems(strList);

    strList.clear();
    strList << "禁能" << "使能";
    ui->comboResistance->addItems(strList);
    ui->comboResistance->setCurrentIndex(1);
}

void InitCanDialog::BindSlots()
{
    // 内部信号自身做处理
    connect(ui->comboCanfdStandard,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &InitCanDialog::slot_comboCanfdStandard_currentIndexChanged);

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

void InitCanDialog::slot_comboCanfdStandard_currentIndexChanged(int index)
{

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

    this->hide();
}
