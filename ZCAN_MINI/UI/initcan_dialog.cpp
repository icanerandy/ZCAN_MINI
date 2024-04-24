#include "initcan_dialog.h"
#include "ui_initcan_dialog.h"

InitCanDialog::InitCanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitCanDialog)
{
    ui->setupUi(this);

    initDlg();

    bindSignals();
}

InitCanDialog::~InitCanDialog()
{
    delete ui;
}

void InitCanDialog::initDlg()
{
    const DeviceManager * const device_manager = DeviceManager::getInstance();
    const DeviceManager::DeviceTypeIndex device_type_index_ = device_manager->device_type_index();
    const uint type = DeviceManager::kDeviceType[static_cast<uint>(device_type_index_)].device_type;

    const bool usbcanfd = type==ZCAN_USBCANFD_100U ||
        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
    const bool pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
        type == ZCAN_PCIE_CANFD_200U || type == ZCAN_PCIE_CANFD_400U_EX;
    const bool canfdDevice = usbcanfd || pciecanfd;

    QStringList strList;
    strList.clear();

    if (canfdDevice)
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

void InitCanDialog::bindSignals()
{
    DeviceManager * const device_manager = DeviceManager::getInstance();
    // 内部信号自身做处理
    connect(ui->comboCanfdStandard, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [=] (int index) { device_manager->set_canfd_standard_type(static_cast<DeviceManager::StandardType>(index)); });

    connect(ui->comboAbit, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [=] (int index) { device_manager->set_abit_baud_index(index); });

    connect(ui->comboDbit, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [=] (int index) { device_manager->set_dbit_baud_index(index); });

    connect(ui->comboWorkMode, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [=] (int index) { device_manager->set_work_mode_index(static_cast<DeviceManager::WorkMode>(index)); });

    connect(ui->comboResistance, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, [=] (int index) { device_manager->set_resistance_enable(static_cast<DeviceManager::Enable>(index)); });

    connect(ui->btnOk, &QPushButton::clicked, this, [=] {
        bool ret = device_manager->initCan();
        if (!ret)
            return;

        ret = device_manager->startCan();
        if (!ret)
            return;

        this->hide();
    });

    connect(ui->btnCancel, &QPushButton::clicked, this, [=] {
       this->hide();
    });
}

void InitCanDialog::slot_chkDeviceType()
{
    const DeviceManager * const device_manager = DeviceManager::getInstance();
    const DeviceManager::DeviceTypeIndex device_type_index_ = device_manager->device_type_index();
    const uint type = DeviceManager::kDeviceType[static_cast<uint>(device_type_index_)].device_type;

    const bool usbcanfd = type==ZCAN_USBCANFD_100U ||
        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
    const bool pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
        type == ZCAN_PCIE_CANFD_200U || type == ZCAN_PCIE_CANFD_400U_EX;
    const bool canfdDevice = usbcanfd || pciecanfd;

    QStringList strList;
    strList.clear();

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
