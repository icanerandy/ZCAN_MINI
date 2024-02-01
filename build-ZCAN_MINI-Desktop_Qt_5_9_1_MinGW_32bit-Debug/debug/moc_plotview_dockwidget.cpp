/****************************************************************************
** Meta object code from reading C++ file 'plotview_dockwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZCAN_MINI/Ui/plotview_dockwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotview_dockwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlotViewDockWidget_t {
    QByteArrayData data[8];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlotViewDockWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlotViewDockWidget_t qt_meta_stringdata_PlotViewDockWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PlotViewDockWidget"
QT_MOC_LITERAL(1, 19, 23), // "slot_checkState_Changed"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 14), // "Qt::CheckState"
QT_MOC_LITERAL(4, 59, 5), // "state"
QT_MOC_LITERAL(5, 65, 6), // "msg_id"
QT_MOC_LITERAL(6, 72, 17), // "CppCAN::CANSignal"
QT_MOC_LITERAL(7, 90, 6) // "signal"

    },
    "PlotViewDockWidget\0slot_checkState_Changed\0"
    "\0Qt::CheckState\0state\0msg_id\0"
    "CppCAN::CANSignal\0signal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlotViewDockWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::ULongLong, 0x80000000 | 6,    4,    5,    7,

       0        // eod
};

void PlotViewDockWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlotViewDockWidget *_t = static_cast<PlotViewDockWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_checkState_Changed((*reinterpret_cast< Qt::CheckState(*)>(_a[1])),(*reinterpret_cast< const unsigned long long(*)>(_a[2])),(*reinterpret_cast< const CppCAN::CANSignal(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject PlotViewDockWidget::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_PlotViewDockWidget.data,
      qt_meta_data_PlotViewDockWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlotViewDockWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotViewDockWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlotViewDockWidget.stringdata0))
        return static_cast<void*>(const_cast< PlotViewDockWidget*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int PlotViewDockWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
