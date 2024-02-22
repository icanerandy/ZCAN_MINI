/********************************************************************************
** Form generated from reading UI file 'initcan_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITCAN_DIALOG_H
#define UI_INITCAN_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitCanDialog
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labProtocol;
    QComboBox *comboProtocol;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labCanfdStandard;
    QComboBox *comboCanfdStandard;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labCanfdSpeedUp;
    QComboBox *comboCanfdSpeedUp;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labAbit;
    QComboBox *comboAbit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labDbit;
    QComboBox *comboDbit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labWorkMode;
    QComboBox *comboWorkMode;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labResistance;
    QComboBox *comboResistance;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QComboBox *comboBox_8;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QComboBox *comboBox_9;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QComboBox *comboBox_10;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnOk;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *InitCanDialog)
    {
        if (InitCanDialog->objectName().isEmpty())
            InitCanDialog->setObjectName(QStringLiteral("InitCanDialog"));
        InitCanDialog->resize(296, 350);
        verticalLayout = new QVBoxLayout(InitCanDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(InitCanDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 262, 450));
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 450));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labProtocol = new QLabel(scrollAreaWidgetContents);
        labProtocol->setObjectName(QStringLiteral("labProtocol"));

        horizontalLayout_2->addWidget(labProtocol);

        comboProtocol = new QComboBox(scrollAreaWidgetContents);
        comboProtocol->setObjectName(QStringLiteral("comboProtocol"));

        horizontalLayout_2->addWidget(comboProtocol);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labCanfdStandard = new QLabel(scrollAreaWidgetContents);
        labCanfdStandard->setObjectName(QStringLiteral("labCanfdStandard"));

        horizontalLayout_3->addWidget(labCanfdStandard);

        comboCanfdStandard = new QComboBox(scrollAreaWidgetContents);
        comboCanfdStandard->setObjectName(QStringLiteral("comboCanfdStandard"));

        horizontalLayout_3->addWidget(comboCanfdStandard);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labCanfdSpeedUp = new QLabel(scrollAreaWidgetContents);
        labCanfdSpeedUp->setObjectName(QStringLiteral("labCanfdSpeedUp"));

        horizontalLayout_4->addWidget(labCanfdSpeedUp);

        comboCanfdSpeedUp = new QComboBox(scrollAreaWidgetContents);
        comboCanfdSpeedUp->setObjectName(QStringLiteral("comboCanfdSpeedUp"));

        horizontalLayout_4->addWidget(comboCanfdSpeedUp);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labAbit = new QLabel(scrollAreaWidgetContents);
        labAbit->setObjectName(QStringLiteral("labAbit"));

        horizontalLayout_5->addWidget(labAbit);

        comboAbit = new QComboBox(scrollAreaWidgetContents);
        comboAbit->setObjectName(QStringLiteral("comboAbit"));

        horizontalLayout_5->addWidget(comboAbit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labDbit = new QLabel(scrollAreaWidgetContents);
        labDbit->setObjectName(QStringLiteral("labDbit"));

        horizontalLayout_6->addWidget(labDbit);

        comboDbit = new QComboBox(scrollAreaWidgetContents);
        comboDbit->setObjectName(QStringLiteral("comboDbit"));

        horizontalLayout_6->addWidget(comboDbit);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labWorkMode = new QLabel(scrollAreaWidgetContents);
        labWorkMode->setObjectName(QStringLiteral("labWorkMode"));

        horizontalLayout_7->addWidget(labWorkMode);

        comboWorkMode = new QComboBox(scrollAreaWidgetContents);
        comboWorkMode->setObjectName(QStringLiteral("comboWorkMode"));

        horizontalLayout_7->addWidget(comboWorkMode);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        labResistance = new QLabel(scrollAreaWidgetContents);
        labResistance->setObjectName(QStringLiteral("labResistance"));

        horizontalLayout_8->addWidget(labResistance);

        comboResistance = new QComboBox(scrollAreaWidgetContents);
        comboResistance->setObjectName(QStringLiteral("comboResistance"));

        horizontalLayout_8->addWidget(comboResistance);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        comboBox_8 = new QComboBox(scrollAreaWidgetContents);
        comboBox_8->setObjectName(QStringLiteral("comboBox_8"));

        horizontalLayout_9->addWidget(comboBox_8);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_10->addWidget(label_9);

        comboBox_9 = new QComboBox(scrollAreaWidgetContents);
        comboBox_9->setObjectName(QStringLiteral("comboBox_9"));

        horizontalLayout_10->addWidget(comboBox_9);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_11->addWidget(label_10);

        comboBox_10 = new QComboBox(scrollAreaWidgetContents);
        comboBox_10->setObjectName(QStringLiteral("comboBox_10"));

        horizontalLayout_11->addWidget(comboBox_10);


        verticalLayout_2->addLayout(horizontalLayout_11);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnOk = new QPushButton(InitCanDialog);
        btnOk->setObjectName(QStringLiteral("btnOk"));

        horizontalLayout->addWidget(btnOk);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnCancel = new QPushButton(InitCanDialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(InitCanDialog);

        QMetaObject::connectSlotsByName(InitCanDialog);
    } // setupUi

    void retranslateUi(QDialog *InitCanDialog)
    {
        InitCanDialog->setWindowTitle(QApplication::translate("InitCanDialog", "CAN\351\200\232\351\201\223\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        labProtocol->setText(QApplication::translate("InitCanDialog", "\345\215\217\350\256\256", Q_NULLPTR));
        labCanfdStandard->setText(QApplication::translate("InitCanDialog", "CANFD\346\240\207\345\207\206", Q_NULLPTR));
        labCanfdSpeedUp->setText(QApplication::translate("InitCanDialog", "CANFD\345\212\240\351\200\237", Q_NULLPTR));
        labAbit->setText(QApplication::translate("InitCanDialog", "\344\273\262\350\243\201\345\237\237\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        labDbit->setText(QApplication::translate("InitCanDialog", "\346\225\260\346\215\256\347\216\207\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        labWorkMode->setText(QApplication::translate("InitCanDialog", "\345\267\245\344\275\234\346\250\241\345\274\217", Q_NULLPTR));
        labResistance->setText(QApplication::translate("InitCanDialog", "\347\273\210\347\253\257\347\224\265\351\230\273", Q_NULLPTR));
        label_8->setText(QApplication::translate("InitCanDialog", "\344\270\212\346\212\245\346\200\273\347\272\277\345\210\251\347\224\250\347\216\207", Q_NULLPTR));
        label_9->setText(QApplication::translate("InitCanDialog", "\346\200\273\347\272\277\345\210\251\347\224\250\345\221\250\346\234\237(ms)", Q_NULLPTR));
        label_10->setText(QApplication::translate("InitCanDialog", "\345\217\221\351\200\201\351\207\215\350\257\225", Q_NULLPTR));
        btnOk->setText(QApplication::translate("InitCanDialog", "\347\241\256\350\256\244", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("InitCanDialog", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InitCanDialog: public Ui_InitCanDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITCAN_DIALOG_H
