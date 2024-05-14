#-------------------------------------------------
#
# Project created by QtCreator 2024-01-25T15:01:21
#
#-------------------------------------------------

QT       += core gui printsupport axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

CONFIG += c++14

TARGET = SpeedAnalysis
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

RC_ICONS = ./ress/icons/analys.ico

SOURCES += \
    main.cpp

INCLUDEPATH += $$PWD/ThirdLib
include ($$PWD/ThirdLib/ThirdLib.pri)

INCLUDEPATH += $$PWD/DeviceManager
include ($$PWD/DeviceManager/DeviceManager.pri)

INCLUDEPATH += $$PWD/Model
include ($$PWD/Model/Model.pri)

INCLUDEPATH += $$PWD/Ui
include ($$PWD/Ui/Ui.pri)

INCLUDEPATH += $$PWD/MsgProcess
include ($$PWD/MsgProcess/MsgProcess.pri)

INCLUDEPATH += $$PWD/ExcelProcess
include ($$PWD/ExcelProcess/ExcelProcess.pri)

RESOURCES += \
    ress.qrc

DISTFILES +=
