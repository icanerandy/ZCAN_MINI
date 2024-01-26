#include "device_manager_dialog.h"
#include "ui_device_manager_dialog.h"

DeviceManagerDialog::DeviceManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceManagerDialog)
{
    ui->setupUi(this);

    InitDialog();

    connect(combo_device_type_,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &DeviceManagerDialog::slot_ComboDeviceType_currentIndexChanged);

    connect(combo_device_index_,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &DeviceManagerDialog::slot_ComboDeviceIndex_currentIndexChanged);

    connect(btn_open_device, &QPushButton::clicked, this, &slot_BtnOpenDevice_clicked);
}

DeviceManagerDialog::~DeviceManagerDialog()
{
    delete ui;
}

void DeviceManagerDialog::InitDialog()
{
    centralWidget = new QWidget(this);
    gLayout = new QGridLayout(centralWidget);
    gLayout->setSpacing(6);
    gLayout->setContentsMargins(11, 11, 11, 11);

    hLayout = new QHBoxLayout();
    hLayout->setSpacing(6);

    lab_device_type_ = new QLabel(QStringLiteral("类型"), centralWidget);
    hLayout->addWidget(lab_device_type_);

    combo_device_type_ = new QComboBox(centralWidget);
    hLayout->addWidget(combo_device_type_);

    hSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hLayout->addItem(hSpacer);

    lab_device_index_ = new QLabel(QStringLiteral("索引"), centralWidget);
    hLayout->addWidget(lab_device_index_);

    combo_device_index_ = new QComboBox(centralWidget);
    hLayout->addWidget(combo_device_index_);

    hSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hLayout->addItem(hSpacer_2);

    btn_open_device = new QPushButton(QStringLiteral("打开设备"), centralWidget);
    hLayout->addWidget(btn_open_device);

    gLayout->addLayout(hLayout, 0, 0, 1, 1);

    vSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gLayout->addItem(vSpacer, 1, 0, 1, 1);

    InitTypeComboBox();
    InitIndexComboBox(combo_device_index_, 0, 32, 0);



//    treeWidget = new QTreeWidget(centralWidget);
//    treeWidget->header()->setVisible(false);
//    treeWidget->setStyleSheet("QTreeWidget {"
//                              "background-color: transparent;"
//                              "border: none;"
//                              "}"
//                              "QTreeWidget::item {"
//                              "background-color: transparent;"
//                              "}");
//    treeWidget->setColumnCount(5);
//    QTreeWidgetItem *parent = new QTreeWidgetItem(treeWidget);
//    parent->setText(0, QStringLiteral("设备"));
//    treeWidget->setItemWidget(parent, 1, new QPushButton(("启动")));
//    treeWidget->setItemWidget(parent, 2, new QPushButton("停止"));
//    treeWidget->setItemWidget(parent, 3, new QPushButton("关闭设备"));
//    treeWidget->setItemWidget(parent, 4, new QPushButton("设备信息"));

//    QTreeWidgetItem *child = new QTreeWidgetItem(parent);
//    child->setText(0, QStringLiteral("通道"));
//    treeWidget->setItemWidget(child, 1, new QPushButton("启动"));
//    treeWidget->setItemWidget(child, 2, new QPushButton("停止"));

//    gLayout->addWidget(treeWidget);
}

void DeviceManagerDialog::InitTypeComboBox()
{
    QStringList string_list;
    string_list << "ZCAN_USBCAN1" << "ZCAN_USBCAN2" << "ZCAN_PCI9820I" << "ZCAN_USBCAN_E_U"
                << "ZCAN_USBCAN_2E_U" << "ZCAN_USBCAN_4E_U" << "ZCAN_PCIE_CANFD_100U"
                << "ZCAN_PCIE_CANFD_200U" << "ZCAN_PCIE_CANFD_400U_EX" << "ZCAN_USBCANFD_200U"
                << "ZCAN_USBCANFD_100U" << "ZCAN_USBCANFD_MINI" << "ZCAN_CANETTCP"
                << "ZCAN_CANETUDP" << "ZCAN_WIFICAN_TCP" << "ZCAN_WIFICAN_UDP"
                << "ZCAN_CLOUD" << "ZCAN_CANFDWIFI_TCP" << "ZCAN_CANFDWIFI_UDP"
                << "ZCAN_CANFDNET_TCP" << "ZCAN_CANFDNET_UDP" << "ZCAN_CANFDNET_400U_TCP"
                << "ZCAN_CANFDNET_400U_UDP";
    combo_device_type_->addItems(string_list);
}

void DeviceManagerDialog::InitIndexComboBox(QObject *obj, int start, int end, int current)
{
    QComboBox *combo = static_cast<QComboBox*>(obj);
    Q_ASSERT(combo != NULL);
    combo->clear();
    for (int i = start; i < end; ++i)
    {
        combo->addItem(QString::asprintf("%d", i));
    }
    combo->setCurrentIndex(current);
}

void DeviceManagerDialog::slot_ComboDeviceType_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->ChangeDeviceType(index);
}

void DeviceManagerDialog::slot_ComboDeviceIndex_currentIndexChanged(int index)
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    device_manager->ChangeDeviceIndex(index);
}

void DeviceManagerDialog::slot_BtnOpenDevice_clicked()
{
    DeviceManager *device_manager = DeviceManager::GetInstance();
    bool ret = device_manager->OpenDevice();
    if (ret)
        qDebug("打开设备成功");
    else
        qDebug("打开设备失败");
}
