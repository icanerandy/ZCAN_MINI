/****************************************************************************
** Meta object code from reading C++ file 'recmsg_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZCAN_MINI/Thread/recmsg_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recmsg_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecMsgThread_t {
    QByteArrayData data[8];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecMsgThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecMsgThread_t qt_meta_stringdata_RecMsgThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RecMsgThread"
QT_MOC_LITERAL(1, 13, 6), // "newMsg"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 23), // "ZCAN_Receive_Data*const"
QT_MOC_LITERAL(4, 45, 8), // "can_data"
QT_MOC_LITERAL(5, 54, 3), // "len"
QT_MOC_LITERAL(6, 58, 25), // "ZCAN_ReceiveFD_Data*const"
QT_MOC_LITERAL(7, 84, 10) // "canfd_data"

    },
    "RecMsgThread\0newMsg\0\0ZCAN_Receive_Data*const\0"
    "can_data\0len\0ZCAN_ReceiveFD_Data*const\0"
    "canfd_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecMsgThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       1,    2,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt,    4,    5,
    QMetaType::Void, 0x80000000 | 6, QMetaType::UInt,    7,    5,

       0        // eod
};

void RecMsgThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RecMsgThread *_t = static_cast<RecMsgThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newMsg((*reinterpret_cast< const ZCAN_Receive_Data*const(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2]))); break;
        case 1: _t->newMsg((*reinterpret_cast< const ZCAN_ReceiveFD_Data*const(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RecMsgThread::*_t)(const ZCAN_Receive_Data * const , const uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RecMsgThread::newMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RecMsgThread::*_t)(const ZCAN_ReceiveFD_Data * const , const uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RecMsgThread::newMsg)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject RecMsgThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_RecMsgThread.data,
      qt_meta_data_RecMsgThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RecMsgThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecMsgThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecMsgThread.stringdata0))
        return static_cast<void*>(const_cast< RecMsgThread*>(this));
    return QThread::qt_metacast(_clname);
}

int RecMsgThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void RecMsgThread::newMsg(const ZCAN_Receive_Data * const _t1, const uint _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RecMsgThread::newMsg(const ZCAN_ReceiveFD_Data * const _t1, const uint _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
