/********************************************************************************
** Form generated from reading UI file 'dbcview_dockwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBCVIEW_DOCKWIDGET_H
#define UI_DBCVIEW_DOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DBCViewDockWidget
{
public:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnReadDBC;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableView *msgView;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTableView *sigView;

    void setupUi(QDockWidget *DBCViewDockWidget)
    {
        if (DBCViewDockWidget->objectName().isEmpty())
            DBCViewDockWidget->setObjectName(QStringLiteral("DBCViewDockWidget"));
        DBCViewDockWidget->resize(698, 491);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnReadDBC = new QPushButton(dockWidgetContents);
        btnReadDBC->setObjectName(QStringLiteral("btnReadDBC"));

        horizontalLayout->addWidget(btnReadDBC);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        msgView = new QTableView(groupBox);
        msgView->setObjectName(QStringLiteral("msgView"));

        gridLayout->addWidget(msgView, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        sigView = new QTableView(groupBox_2);
        sigView->setObjectName(QStringLiteral("sigView"));

        gridLayout_2->addWidget(sigView, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        gridLayout_3->addLayout(verticalLayout, 1, 0, 1, 1);

        DBCViewDockWidget->setWidget(dockWidgetContents);

        retranslateUi(DBCViewDockWidget);

        QMetaObject::connectSlotsByName(DBCViewDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *DBCViewDockWidget)
    {
        DBCViewDockWidget->setWindowTitle(QApplication::translate("DBCViewDockWidget", "DBC\350\247\243\346\236\220", Q_NULLPTR));
        btnReadDBC->setText(QApplication::translate("DBCViewDockWidget", "\345\212\240\350\275\275DBC", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DBCViewDockWidget", "CAN Message", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("DBCViewDockWidget", "Signals of Selected CAN Message", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DBCViewDockWidget: public Ui_DBCViewDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBCVIEW_DOCKWIDGET_H
