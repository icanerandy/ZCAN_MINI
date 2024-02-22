/********************************************************************************
** Form generated from reading UI file 'devicemanager_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEMANAGER_DIALOG_H
#define UI_DEVICEMANAGER_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DeviceManagerDialog
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboDeviceType;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QComboBox *comboDeviceIndex;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnOpenDevice;
    QSpacerItem *horizontalSpacer;
    QLabel *labChannel;
    QComboBox *comboChannelIndex;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *btnStartDevice;
    QPushButton *btnStopDevice;
    QPushButton *btnCloseDevice;
    QPushButton *btnDeviceInfo;

    void setupUi(QDialog *DeviceManagerDialog)
    {
        if (DeviceManagerDialog->objectName().isEmpty())
            DeviceManagerDialog->setObjectName(QStringLiteral("DeviceManagerDialog"));
        DeviceManagerDialog->resize(242, 165);
        gridLayout_2 = new QGridLayout(DeviceManagerDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(DeviceManagerDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboDeviceType = new QComboBox(DeviceManagerDialog);
        comboDeviceType->setObjectName(QStringLiteral("comboDeviceType"));

        horizontalLayout->addWidget(comboDeviceType);

        horizontalSpacer_2 = new QSpacerItem(575, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(DeviceManagerDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboDeviceIndex = new QComboBox(DeviceManagerDialog);
        comboDeviceIndex->setObjectName(QStringLiteral("comboDeviceIndex"));

        horizontalLayout->addWidget(comboDeviceIndex);

        horizontalSpacer_4 = new QSpacerItem(575, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(575, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btnOpenDevice = new QPushButton(DeviceManagerDialog);
        btnOpenDevice->setObjectName(QStringLiteral("btnOpenDevice"));

        horizontalLayout_2->addWidget(btnOpenDevice);

        horizontalSpacer = new QSpacerItem(575, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        labChannel = new QLabel(DeviceManagerDialog);
        labChannel->setObjectName(QStringLiteral("labChannel"));

        horizontalLayout_2->addWidget(labChannel);

        comboChannelIndex = new QComboBox(DeviceManagerDialog);
        comboChannelIndex->setObjectName(QStringLiteral("comboChannelIndex"));

        horizontalLayout_2->addWidget(comboChannelIndex);

        horizontalSpacer_5 = new QSpacerItem(575, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(DeviceManagerDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnStartDevice = new QPushButton(groupBox);
        btnStartDevice->setObjectName(QStringLiteral("btnStartDevice"));

        gridLayout->addWidget(btnStartDevice, 0, 0, 1, 1);

        btnStopDevice = new QPushButton(groupBox);
        btnStopDevice->setObjectName(QStringLiteral("btnStopDevice"));

        gridLayout->addWidget(btnStopDevice, 0, 1, 1, 1);

        btnCloseDevice = new QPushButton(groupBox);
        btnCloseDevice->setObjectName(QStringLiteral("btnCloseDevice"));

        gridLayout->addWidget(btnCloseDevice, 1, 0, 1, 1);

        btnDeviceInfo = new QPushButton(groupBox);
        btnDeviceInfo->setObjectName(QStringLiteral("btnDeviceInfo"));

        gridLayout->addWidget(btnDeviceInfo, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 1);


        retranslateUi(DeviceManagerDialog);

        QMetaObject::connectSlotsByName(DeviceManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *DeviceManagerDialog)
    {
        DeviceManagerDialog->setWindowTitle(QApplication::translate("DeviceManagerDialog", "\350\256\276\345\244\207\347\256\241\347\220\206", Q_NULLPTR));
        label->setText(QApplication::translate("DeviceManagerDialog", "\347\261\273\345\236\213", Q_NULLPTR));
        label_2->setText(QApplication::translate("DeviceManagerDialog", "\347\264\242\345\274\225", Q_NULLPTR));
        btnOpenDevice->setText(QApplication::translate("DeviceManagerDialog", "\346\211\223\345\274\200\350\256\276\345\244\207", Q_NULLPTR));
        labChannel->setText(QApplication::translate("DeviceManagerDialog", "\351\200\232\351\201\223", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DeviceManagerDialog", "\350\256\276\345\244\207\346\223\215\344\275\234", Q_NULLPTR));
        btnStartDevice->setText(QApplication::translate("DeviceManagerDialog", "\345\220\257\345\212\250", Q_NULLPTR));
        btnStopDevice->setText(QApplication::translate("DeviceManagerDialog", "\345\201\234\346\255\242", Q_NULLPTR));
        btnCloseDevice->setText(QApplication::translate("DeviceManagerDialog", "\345\205\263\351\227\255", Q_NULLPTR));
        btnDeviceInfo->setText(QApplication::translate("DeviceManagerDialog", "\350\256\276\345\244\207\344\277\241\346\201\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DeviceManagerDialog: public Ui_DeviceManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEMANAGER_DIALOG_H
