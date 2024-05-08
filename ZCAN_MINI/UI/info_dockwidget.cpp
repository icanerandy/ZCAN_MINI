#include "info_dockwidget.h"
#include "ui_info_dockwidget.h"

InfoDockWidget::InfoDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::InfoDockWidget)
{
    ui->setupUi(this);

    timer.start(500);
    connect(&timer, &QTimer::timeout, this, [=] {
        QDateTime date_time = QDateTime::currentDateTime();
        ui->labTime->setText(date_time.toString());
    });

    connect(ui->editTester, &QtMaterialTextField::textChanged, nullptr, [=] () {
        emit sig_testerChanged(ui->editTester->text());
    });

    connect(ui->editDeviceName, &QtMaterialTextField::textChanged, nullptr, [=] () {
        emit sig_deviceNameChanged(ui->editDeviceName->text());
    });
}

InfoDockWidget::~InfoDockWidget()
{
    delete ui;
}
