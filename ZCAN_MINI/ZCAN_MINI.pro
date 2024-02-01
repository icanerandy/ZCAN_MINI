#-------------------------------------------------
#
# Project created by QtCreator 2024-01-25T15:01:21
#
#-------------------------------------------------

QT       += core gui printsupport

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZCAN_MINI
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cc

INCLUDEPATH += $$PWD/Can_Parser
include ($$PWD/Can_Parser/Can_Parser.pri)

INCLUDEPATH += $$PWD/zlgcan_x86
include ($$PWD/zlgcan_x86/zlgcan_x86.pri)

INCLUDEPATH += $$PWD/Model
include ($$PWD/Model/Model.pri)

INCLUDEPATH += $$PWD/Ui
include ($$PWD/Ui/Ui.pri)

INCLUDEPATH += $$PWD/Device_Manager
include ($$PWD/Device_Manager/Device_Manager.pri)

INCLUDEPATH += $$PWD/Thread
include ($$PWD/Thread/Thread.pri)

INCLUDEPATH += $$PWD/QCustomPlot
include ($$PWD/QCustomPlot/qcustomplot.pri)
