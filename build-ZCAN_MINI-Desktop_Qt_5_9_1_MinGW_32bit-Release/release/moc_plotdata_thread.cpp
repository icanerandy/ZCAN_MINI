/****************************************************************************
** Meta object code from reading C++ file 'plotdata_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZCAN_MINI/Thread/plotdata_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotdata_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlotDataThread_t {
    QByteArrayData data[8];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlotDataThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlotDataThread_t qt_meta_stringdata_PlotDataThread = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PlotDataThread"
QT_MOC_LITERAL(1, 15, 11), // "slot_newMsg"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 23), // "ZCAN_Receive_Data*const"
QT_MOC_LITERAL(4, 52, 8), // "can_data"
QT_MOC_LITERAL(5, 61, 3), // "len"
QT_MOC_LITERAL(6, 65, 25), // "ZCAN_ReceiveFD_Data*const"
QT_MOC_LITERAL(7, 91, 10) // "canfd_data"

    },
    "PlotDataThread\0slot_newMsg\0\0"
    "ZCAN_Receive_Data*const\0can_data\0len\0"
    "ZCAN_ReceiveFD_Data*const\0canfd_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlotDataThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x08 /* Private */,
       1,    2,   29,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt,    4,    5,
    QMetaType::Void, 0x80000000 | 6, QMetaType::UInt,    7,    5,

       0        // eod
};

void PlotDataThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlotDataThread *_t = static_cast<PlotDataThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_newMsg((*reinterpret_cast< const ZCAN_Receive_Data*const(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2]))); break;
        case 1: _t->slot_newMsg((*reinterpret_cast< const ZCAN_ReceiveFD_Data*const(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject PlotDataThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PlotDataThread.data,
      qt_meta_data_PlotDataThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlotDataThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotDataThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlotDataThread.stringdata0))
        return static_cast<void*>(const_cast< PlotDataThread*>(this));
    return QThread::qt_metacast(_clname);
}

int PlotDataThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE