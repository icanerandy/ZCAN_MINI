#-------------------------------------------------
#
# Project created by QtCreator 2024-01-25T15:01:21
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

TARGET = ZCAN_MINI
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp

INCLUDEPATH += $$PWD/CanParser
include ($$PWD/CanParser/CanParser.pri)

INCLUDEPATH += $$PWD/VectorDBC
include ($$PWD/VectorDBC/VectorDBC.pri)

INCLUDEPATH += $$PWD/zlgcan_x86
include ($$PWD/zlgcan_x86/zlgcan_x86.pri)

INCLUDEPATH += $$PWD/DeviceManager
include ($$PWD/DeviceManager/DeviceManager.pri)

INCLUDEPATH += $$PWD/Model
include ($$PWD/Model/Model.pri)

INCLUDEPATH += $$PWD/Ui
include ($$PWD/Ui/Ui.pri)

INCLUDEPATH += $$PWD/Thread
include ($$PWD/Thread/Thread.pri)

INCLUDEPATH += $$PWD/QCustomPlot
include ($$PWD/QCustomPlot/Qcustomplot.pri)

INCLUDEPATH += $$PWD/QXlsx
include ($$PWD/QXlsx/QXlsx.pri)
