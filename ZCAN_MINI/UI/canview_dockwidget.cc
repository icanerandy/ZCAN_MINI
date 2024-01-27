#include "canview_dockwidget.h"
#include "ui_canview_dockwidget.h"

CanViewDockWidget::CanViewDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CanViewDockWidget)
{
    ui->setupUi(this);
}

CanViewDockWidget::~CanViewDockWidget()
{
    delete ui;
}
