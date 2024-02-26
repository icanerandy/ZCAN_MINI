/********************************************************************************
** Form generated from reading UI file 'plot_dockwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_DOCKWIDGET_H
#define UI_PLOT_DOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PlotViewDockWidget
{
public:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labFps;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnSave;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnExcel;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QCustomPlot *plot;

    void setupUi(QDockWidget *PlotViewDockWidget)
    {
        if (PlotViewDockWidget->objectName().isEmpty())
            PlotViewDockWidget->setObjectName(QStringLiteral("PlotViewDockWidget"));
        PlotViewDockWidget->resize(788, 592);
        PlotViewDockWidget->setMinimumSize(QSize(414, 300));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labFps = new QLabel(dockWidgetContents);
        labFps->setObjectName(QStringLiteral("labFps"));

        horizontalLayout->addWidget(labFps);

        horizontalSpacer_3 = new QSpacerItem(348, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnSave = new QPushButton(dockWidgetContents);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        horizontalLayout->addWidget(btnSave);

        horizontalSpacer = new QSpacerItem(348, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnExcel = new QPushButton(dockWidgetContents);
        btnExcel->setObjectName(QStringLiteral("btnExcel"));

        horizontalLayout->addWidget(btnExcel);

        horizontalSpacer_4 = new QSpacerItem(348, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        horizontalSpacer_2 = new QSpacerItem(138, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        plot = new QCustomPlot(dockWidgetContents);
        plot->setObjectName(QStringLiteral("plot"));

        gridLayout->addWidget(plot, 1, 0, 1, 1);

        PlotViewDockWidget->setWidget(dockWidgetContents);

        retranslateUi(PlotViewDockWidget);

        QMetaObject::connectSlotsByName(PlotViewDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *PlotViewDockWidget)
    {
        PlotViewDockWidget->setWindowTitle(QApplication::translate("PlotViewDockWidget", "\345\256\236\346\227\266\345\233\276\350\241\250", Q_NULLPTR));
        labFps->setText(QApplication::translate("PlotViewDockWidget", "FPS: 0, Total Data points: 0", Q_NULLPTR));
        btnSave->setText(QApplication::translate("PlotViewDockWidget", "\344\277\235\345\255\230\345\233\276\345\203\217", Q_NULLPTR));
        btnExcel->setText(QApplication::translate("PlotViewDockWidget", "\344\277\235\345\255\230\345\210\260excel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlotViewDockWidget: public Ui_PlotViewDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_DOCKWIDGET_H
