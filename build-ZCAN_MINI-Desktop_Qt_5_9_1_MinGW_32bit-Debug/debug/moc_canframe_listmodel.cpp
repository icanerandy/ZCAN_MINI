/****************************************************************************
** Meta object code from reading C++ file 'canframe_listmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZCAN_MINI/Model/canframe_listmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canframe_listmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CanFrameListModel_t {
    QByteArrayData data[8];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CanFrameListModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CanFrameListModel_t qt_meta_stringdata_CanFrameListModel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CanFrameListModel"
QT_MOC_LITERAL(1, 18, 6), // "newMsg"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 18), // "ZCAN_Receive_Data*"
QT_MOC_LITERAL(4, 45, 8), // "can_data"
QT_MOC_LITERAL(5, 54, 3), // "len"
QT_MOC_LITERAL(6, 58, 20), // "ZCAN_ReceiveFD_Data*"
QT_MOC_LITERAL(7, 79, 10) // "canfd_data"

    },
    "CanFrameListModel\0newMsg\0\0ZCAN_Receive_Data*\0"
    "can_data\0len\0ZCAN_ReceiveFD_Data*\0"
    "canfd_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CanFrameListModel[] = {

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
       1,    2,   24,    2, 0x0a /* Public */,
       1,    2,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt,    4,    5,
    QMetaType::Void, 0x80000000 | 6, QMetaType::UInt,    7,    5,

       0        // eod
};

void CanFrameListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CanFrameListModel *_t = static_cast<CanFrameListModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newMsg((*reinterpret_cast< ZCAN_Receive_Data*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 1: _t->newMsg((*reinterpret_cast< ZCAN_ReceiveFD_Data*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject CanFrameListModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_CanFrameListModel.data,
      qt_meta_data_CanFrameListModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CanFrameListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanFrameListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CanFrameListModel.stringdata0))
        return static_cast<void*>(const_cast< CanFrameListModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int CanFrameListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
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