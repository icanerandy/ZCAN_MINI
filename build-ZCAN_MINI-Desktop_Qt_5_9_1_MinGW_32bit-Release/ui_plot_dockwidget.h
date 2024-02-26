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
#include <QtWidgets/QHeaderView>
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
    QPushButton *btnSave;
    QSpacerItem *horizontalSpacer;
    QCustomPlot *plot;

    void setupUi(QDockWidget *PlotViewDockWidget)
    {
        if (PlotViewDockWidget->objectName().isEmpty())
            PlotViewDockWidget->setObjectName(QStringLiteral("PlotViewDockWidget"));
        PlotViewDockWidget->resize(846, 553);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnSave = new QPushButton(dockWidgetContents);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        gridLayout->addWidget(btnSave, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(739, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        plot = new QCustomPlot(dockWidgetContents);
        plot->setObjectName(QStringLiteral("plot"));

        gridLayout->addWidget(plot, 1, 0, 1, 2);

        PlotViewDockWidget->setWidget(dockWidgetContents);

        retranslateUi(PlotViewDockWidget);

        QMetaObject::connectSlotsByName(PlotViewDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *PlotViewDockWidget)
    {
        PlotViewDockWidget->setWindowTitle(QApplication::translate("PlotViewDockWidget", "\345\256\236\346\227\266\345\233\276\350\241\250", Q_NULLPTR));
        btnSave->setText(QApplication::translate("PlotViewDockWidget", "\344\277\235\345\255\230\345\233\276\345\203\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlotViewDockWidget: public Ui_PlotViewDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_DOCKWIDGET_H
