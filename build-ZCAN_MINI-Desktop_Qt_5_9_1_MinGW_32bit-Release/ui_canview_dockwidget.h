/********************************************************************************
** Form generated from reading UI file 'canview_dockwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANVIEW_DOCKWIDGET_H
#define UI_CANVIEW_DOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CanViewDockWidget
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnRealTimeSave;
    QPushButton *btnSave;
    QPushButton *btnClear;
    QPushButton *btnPause;
    QCheckBox *chkClassification;
    QCheckBox *chkAllFrameInfo;
    QPushButton *btnOption;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;

    void setupUi(QDockWidget *CanViewDockWidget)
    {
        if (CanViewDockWidget->objectName().isEmpty())
            CanViewDockWidget->setObjectName(QStringLiteral("CanViewDockWidget"));
        CanViewDockWidget->resize(750, 460);
        CanViewDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnRealTimeSave = new QPushButton(dockWidgetContents);
        btnRealTimeSave->setObjectName(QStringLiteral("btnRealTimeSave"));

        horizontalLayout->addWidget(btnRealTimeSave);

        btnSave = new QPushButton(dockWidgetContents);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        horizontalLayout->addWidget(btnSave);

        btnClear = new QPushButton(dockWidgetContents);
        btnClear->setObjectName(QStringLiteral("btnClear"));

        horizontalLayout->addWidget(btnClear);

        btnPause = new QPushButton(dockWidgetContents);
        btnPause->setObjectName(QStringLiteral("btnPause"));
        btnPause->setCheckable(true);
        btnPause->setChecked(false);
        btnPause->setAutoExclusive(true);
        btnPause->setAutoDefault(false);

        horizontalLayout->addWidget(btnPause);

        chkClassification = new QCheckBox(dockWidgetContents);
        chkClassification->setObjectName(QStringLiteral("chkClassification"));

        horizontalLayout->addWidget(chkClassification);

        chkAllFrameInfo = new QCheckBox(dockWidgetContents);
        chkAllFrameInfo->setObjectName(QStringLiteral("chkAllFrameInfo"));

        horizontalLayout->addWidget(chkAllFrameInfo);

        btnOption = new QPushButton(dockWidgetContents);
        btnOption->setObjectName(QStringLiteral("btnOption"));

        horizontalLayout->addWidget(btnOption);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(dockWidgetContents);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        CanViewDockWidget->setWidget(dockWidgetContents);

        retranslateUi(CanViewDockWidget);

        QMetaObject::connectSlotsByName(CanViewDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *CanViewDockWidget)
    {
        CanViewDockWidget->setWindowTitle(QApplication::translate("CanViewDockWidget", "CAN\350\247\206\345\233\276", Q_NULLPTR));
        btnRealTimeSave->setText(QApplication::translate("CanViewDockWidget", "\345\256\236\346\227\266\344\277\235\345\255\230", Q_NULLPTR));
        btnSave->setText(QApplication::translate("CanViewDockWidget", "\344\277\235\345\255\230", Q_NULLPTR));
        btnClear->setText(QApplication::translate("CanViewDockWidget", "\346\270\205\347\251\272", Q_NULLPTR));
        btnPause->setText(QApplication::translate("CanViewDockWidget", "\346\232\202\345\201\234", Q_NULLPTR));
        chkClassification->setText(QApplication::translate("CanViewDockWidget", "\345\210\206\347\261\273\346\230\276\347\244\272", Q_NULLPTR));
        chkAllFrameInfo->setText(QApplication::translate("CanViewDockWidget", "\346\211\200\346\234\211\345\270\247\344\277\241\346\201\257", Q_NULLPTR));
        btnOption->setText(QApplication::translate("CanViewDockWidget", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CanViewDockWidget: public Ui_CanViewDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVIEW_DOCKWIDGET_H
