#include "info_dockwidget.h"
#include "ui_info_dockwidget.h"

InfoDockWidget::InfoDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::InfoDockWidget)
{
    ui->setupUi(this);
}

InfoDockWidget::~InfoDockWidget()
{
    delete ui;
}
