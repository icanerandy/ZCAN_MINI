/****************************************************************************
** Meta object code from reading C++ file 'dbcview_dockwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZCAN_MINI/Ui/dbcview_dockwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbcview_dockwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DBCViewDockWidget_t {
    QByteArrayData data[10];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DBCViewDockWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DBCViewDockWidget_t qt_meta_stringdata_DBCViewDockWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DBCViewDockWidget"
QT_MOC_LITERAL(1, 18, 9), // "sig_paint"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 6), // "msg_id"
QT_MOC_LITERAL(4, 36, 17), // "CppCAN::CANSignal"
QT_MOC_LITERAL(5, 54, 10), // "ref_speed_"
QT_MOC_LITERAL(6, 65, 10), // "rel_speed_"
QT_MOC_LITERAL(7, 76, 23), // "slot_btnReadDBC_clicked"
QT_MOC_LITERAL(8, 100, 26), // "slot_message_model_clicked"
QT_MOC_LITERAL(9, 127, 5) // "index"

    },
    "DBCViewDockWidget\0sig_paint\0\0msg_id\0"
    "CppCAN::CANSignal\0ref_speed_\0rel_speed_\0"
    "slot_btnReadDBC_clicked\0"
    "slot_message_model_clicked\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DBCViewDockWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   36,    2, 0x08 /* Private */,
       8,    1,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::ULongLong, 0x80000000 | 4, 0x80000000 | 4,    3,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    9,

       0        // eod
};

void DBCViewDockWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DBCViewDockWidget *_t = static_cast<DBCViewDockWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_paint((*reinterpret_cast< const unsigned long long(*)>(_a[1])),(*reinterpret_cast< const CppCAN::CANSignal(*)>(_a[2])),(*reinterpret_cast< const CppCAN::CANSignal(*)>(_a[3]))); break;
        case 1: _t->slot_btnReadDBC_clicked(); break;
        case 2: _t->slot_message_model_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DBCViewDockWidget::*_t)(const unsigned long long , const CppCAN::CANSignal & , const CppCAN::CANSignal & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DBCViewDockWidget::sig_paint)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DBCViewDockWidget::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_DBCViewDockWidget.data,
      qt_meta_data_DBCViewDockWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DBCViewDockWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DBCViewDockWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DBCViewDockWidget.stringdata0))
        return static_cast<void*>(const_cast< DBCViewDockWidget*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int DBCViewDockWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DBCViewDockWidget::sig_paint(const unsigned long long _t1, const CppCAN::CANSignal & _t2, const CppCAN::CANSignal & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
