/********************************************************************************
** Form generated from reading UI file 'senddata_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDDATA_DIALOG_H
#define UI_SENDDATA_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SendDataDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *chkInc;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_21;
    QLineEdit *editId;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QLineEdit *editName;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_3;
    QComboBox *comboSendType;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboFrameType;
    QComboBox *comboProtocolType;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_4;
    QComboBox *comboLength;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QSpinBox *spinSendCountOnce;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *editData;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_2;
    QComboBox *comboFormat;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QSpinBox *spinSendCount;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QSpinBox *spinInterval;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnSend;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnSendList;

    void setupUi(QDialog *SendDataDialog)
    {
        if (SendDataDialog->objectName().isEmpty())
            SendDataDialog->setObjectName(QStringLiteral("SendDataDialog"));
        SendDataDialog->resize(739, 523);
        verticalLayout_2 = new QVBoxLayout(SendDataDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(SendDataDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        chkInc = new QCheckBox(groupBox);
        chkInc->setObjectName(QStringLiteral("chkInc"));

        gridLayout->addWidget(chkInc, 6, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_15->addWidget(label_21);

        editId = new QLineEdit(groupBox);
        editId->setObjectName(QStringLiteral("editId"));
        editId->setMinimumSize(QSize(100, 0));
        editId->setMaximumSize(QSize(100, 22));

        horizontalLayout_15->addWidget(editId);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_15->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout_15, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_3->addWidget(label_10);

        editName = new QLineEdit(groupBox);
        editName->setObjectName(QStringLiteral("editName"));
        editName->setMinimumSize(QSize(100, 0));
        editName->setMaximumSize(QSize(100, 22));

        horizontalLayout_3->addWidget(editName);


        gridLayout->addLayout(horizontalLayout_3, 2, 2, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_13->addWidget(label_3);

        comboSendType = new QComboBox(groupBox);
        comboSendType->setObjectName(QStringLiteral("comboSendType"));

        horizontalLayout_13->addWidget(comboSendType);


        gridLayout->addLayout(horizontalLayout_13, 0, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboFrameType = new QComboBox(groupBox);
        comboFrameType->setObjectName(QStringLiteral("comboFrameType"));

        horizontalLayout->addWidget(comboFrameType);

        comboProtocolType = new QComboBox(groupBox);
        comboProtocolType->setObjectName(QStringLiteral("comboProtocolType"));

        horizontalLayout->addWidget(comboProtocolType);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_12->addWidget(label_4);

        comboLength = new QComboBox(groupBox);
        comboLength->setObjectName(QStringLiteral("comboLength"));

        horizontalLayout_12->addWidget(comboLength);


        gridLayout->addLayout(horizontalLayout_12, 3, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_4->addWidget(label_7);

        spinSendCountOnce = new QSpinBox(groupBox);
        spinSendCountOnce->setObjectName(QStringLiteral("spinSendCountOnce"));
        spinSendCountOnce->setMaximum(100000);

        horizontalLayout_4->addWidget(spinSendCountOnce);


        gridLayout->addLayout(horizontalLayout_4, 5, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        editData = new QLineEdit(groupBox);
        editData->setObjectName(QStringLiteral("editData"));
        editData->setMinimumSize(QSize(200, 0));

        horizontalLayout_2->addWidget(editData);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_11->addWidget(label_2);

        comboFormat = new QComboBox(groupBox);
        comboFormat->setObjectName(QStringLiteral("comboFormat"));

        horizontalLayout_11->addWidget(comboFormat);


        gridLayout->addLayout(horizontalLayout_11, 0, 2, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        spinSendCount = new QSpinBox(groupBox);
        spinSendCount->setObjectName(QStringLiteral("spinSendCount"));
        spinSendCount->setMaximum(100000);

        horizontalLayout_9->addWidget(spinSendCount);


        gridLayout->addLayout(horizontalLayout_9, 5, 2, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_10->addWidget(label_9);

        spinInterval = new QSpinBox(groupBox);
        spinInterval->setObjectName(QStringLiteral("spinInterval"));
        spinInterval->setMaximum(100000);

        horizontalLayout_10->addWidget(spinInterval);


        gridLayout->addLayout(horizontalLayout_10, 5, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        btnSend = new QPushButton(groupBox);
        btnSend->setObjectName(QStringLiteral("btnSend"));

        gridLayout->addWidget(btnSend, 6, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(SendDataDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableView = new QTableView(groupBox_2);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout_2->addWidget(tableView, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        btnSendList = new QPushButton(groupBox_2);
        btnSendList->setObjectName(QStringLiteral("btnSendList"));

        horizontalLayout_5->addWidget(btnSendList);


        gridLayout_2->addLayout(horizontalLayout_5, 1, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);


        retranslateUi(SendDataDialog);

        QMetaObject::connectSlotsByName(SendDataDialog);
    } // setupUi

    void retranslateUi(QDialog *SendDataDialog)
    {
        SendDataDialog->setWindowTitle(QApplication::translate("SendDataDialog", "\346\225\260\346\215\256\345\217\221\351\200\201", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SendDataDialog", "\345\270\247\345\217\221\351\200\201", Q_NULLPTR));
        chkInc->setText(QApplication::translate("SendDataDialog", "ID\351\200\222\345\242\236", Q_NULLPTR));
        label_21->setText(QApplication::translate("SendDataDialog", "\345\270\247ID:0x", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SendDataDialog", "...", Q_NULLPTR));
        label_10->setText(QApplication::translate("SendDataDialog", "\345\220\215\347\247\260(\345\217\257\351\200\211):", Q_NULLPTR));
        label_3->setText(QApplication::translate("SendDataDialog", "\345\217\221\351\200\201\346\226\271\345\274\217:", Q_NULLPTR));
        label->setText(QApplication::translate("SendDataDialog", "\345\270\247\347\261\273\345\236\213:", Q_NULLPTR));
        label_4->setText(QApplication::translate("SendDataDialog", "\346\225\260\346\215\256\351\225\277\345\272\246:", Q_NULLPTR));
        label_7->setText(QApplication::translate("SendDataDialog", "\346\257\217\346\254\241\345\217\221\351\200\201\345\270\247\346\225\260:", Q_NULLPTR));
        label_6->setText(QApplication::translate("SendDataDialog", "\346\225\260\346\215\256:0x", Q_NULLPTR));
        editData->setText(QString());
        label_2->setText(QApplication::translate("SendDataDialog", "\345\270\247\346\240\274\345\274\217:", Q_NULLPTR));
        label_8->setText(QApplication::translate("SendDataDialog", "\345\217\221\351\200\201\346\254\241\346\225\260:", Q_NULLPTR));
        label_9->setText(QApplication::translate("SendDataDialog", "\346\257\217\346\254\241\351\227\264\351\232\224(ms):", Q_NULLPTR));
        btnSend->setText(QApplication::translate("SendDataDialog", "\347\253\213\345\215\263\345\217\221\351\200\201", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("SendDataDialog", "\345\210\227\350\241\250\345\217\221\351\200\201", Q_NULLPTR));
        btnSendList->setText(QApplication::translate("SendDataDialog", "\345\210\227\350\241\250\345\217\221\351\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SendDataDialog: public Ui_SendDataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDDATA_DIALOG_H
