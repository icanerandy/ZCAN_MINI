/********************************************************************************
** Form generated from reading UI file 'canviewoption_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANVIEWOPTION_DIALOG_H
#define UI_CANVIEWOPTION_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CanViewOptionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QCheckBox *chkDirection;
    QCheckBox *chkFrameType;
    QCheckBox *chkFormat;
    QCheckBox *chkCanType;
    QCheckBox *chkId;
    QCheckBox *chkData;
    QCheckBox *chkLength;
    QCheckBox *chkStamp;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *CanViewOptionDialog)
    {
        if (CanViewOptionDialog->objectName().isEmpty())
            CanViewOptionDialog->setObjectName(QStringLiteral("CanViewOptionDialog"));
        CanViewOptionDialog->resize(387, 171);
        verticalLayout = new QVBoxLayout(CanViewOptionDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(CanViewOptionDialog);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        chkDirection = new QCheckBox(widget);
        chkDirection->setObjectName(QStringLiteral("chkDirection"));

        gridLayout->addWidget(chkDirection, 2, 0, 1, 1);

        chkFrameType = new QCheckBox(widget);
        chkFrameType->setObjectName(QStringLiteral("chkFrameType"));

        gridLayout->addWidget(chkFrameType, 2, 1, 1, 1);

        chkFormat = new QCheckBox(widget);
        chkFormat->setObjectName(QStringLiteral("chkFormat"));

        gridLayout->addWidget(chkFormat, 2, 2, 1, 1);

        chkCanType = new QCheckBox(widget);
        chkCanType->setObjectName(QStringLiteral("chkCanType"));

        gridLayout->addWidget(chkCanType, 2, 3, 1, 1);

        chkId = new QCheckBox(widget);
        chkId->setObjectName(QStringLiteral("chkId"));

        gridLayout->addWidget(chkId, 1, 0, 1, 1);

        chkData = new QCheckBox(widget);
        chkData->setObjectName(QStringLiteral("chkData"));

        gridLayout->addWidget(chkData, 1, 2, 1, 1);

        chkLength = new QCheckBox(widget);
        chkLength->setObjectName(QStringLiteral("chkLength"));

        gridLayout->addWidget(chkLength, 1, 1, 1, 1);

        chkStamp = new QCheckBox(widget);
        chkStamp->setObjectName(QStringLiteral("chkStamp"));

        gridLayout->addWidget(chkStamp, 1, 3, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget_2 = new QWidget(CanViewOptionDialog);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(widget_2);
        btnOk->setObjectName(QStringLiteral("btnOk"));

        horizontalLayout->addWidget(btnOk);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget_2);


        retranslateUi(CanViewOptionDialog);

        QMetaObject::connectSlotsByName(CanViewOptionDialog);
    } // setupUi

    void retranslateUi(QDialog *CanViewOptionDialog)
    {
        CanViewOptionDialog->setWindowTitle(QApplication::translate("CanViewOptionDialog", "\350\256\276\347\275\256", Q_NULLPTR));
        chkDirection->setText(QApplication::translate("CanViewOptionDialog", "\346\226\271\345\220\221", Q_NULLPTR));
        chkFrameType->setText(QApplication::translate("CanViewOptionDialog", "\345\270\247\347\261\273\345\236\213", Q_NULLPTR));
        chkFormat->setText(QApplication::translate("CanViewOptionDialog", "\345\270\247\346\240\274\345\274\217", Q_NULLPTR));
        chkCanType->setText(QApplication::translate("CanViewOptionDialog", "CAN\347\261\273\345\236\213", Q_NULLPTR));
        chkId->setText(QApplication::translate("CanViewOptionDialog", "\345\270\247ID", Q_NULLPTR));
        chkData->setText(QApplication::translate("CanViewOptionDialog", "\346\225\260\346\215\256", Q_NULLPTR));
        chkLength->setText(QApplication::translate("CanViewOptionDialog", "\351\225\277\345\272\246", Q_NULLPTR));
        chkStamp->setText(QApplication::translate("CanViewOptionDialog", "\346\227\266\351\227\264\346\240\207\350\257\206", Q_NULLPTR));
        label->setText(QApplication::translate("CanViewOptionDialog", "\345\210\227\350\241\250\346\230\276\347\244\272\351\241\271:", Q_NULLPTR));
        btnOk->setText(QApplication::translate("CanViewOptionDialog", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CanViewOptionDialog: public Ui_CanViewOptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVIEWOPTION_DIALOG_H
