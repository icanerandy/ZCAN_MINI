#include "init_can_dialog.h"
#include "ui_init_can_dialog.h"

InitCanDialog::InitCanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitCanDialog)
{
    ui->setupUi(this);

    InitDialog();
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
