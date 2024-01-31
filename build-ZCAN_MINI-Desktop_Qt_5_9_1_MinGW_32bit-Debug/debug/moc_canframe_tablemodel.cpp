/****************************************************************************
** Meta object code from reading C++ file 'canframe_tablemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZCAN_MINI/Model/canframe_tablemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canframe_tablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CanFrameTableModel_t {
    QByteArrayData data[12];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CanFrameTableModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CanFrameTableModel_t qt_meta_stringdata_CanFrameTableModel = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CanFrameTableModel"
QT_MOC_LITERAL(1, 19, 12), // "rowsInserted"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 6), // "newMsg"
QT_MOC_LITERAL(4, 40, 18), // "ZCAN_Receive_Data*"
QT_MOC_LITERAL(5, 59, 8), // "can_data"
QT_MOC_LITERAL(6, 68, 3), // "len"
QT_MOC_LITERAL(7, 72, 20), // "ZCAN_ReceiveFD_Data*"
QT_MOC_LITERAL(8, 93, 10), // "canfd_data"
QT_MOC_LITERAL(9, 104, 15), // "slot_visibleCol"
QT_MOC_LITERAL(10, 120, 10), // "QList<int>"
QT_MOC_LITERAL(11, 131, 15) // "visible_columns"

    },
    "CanFrameTableModel\0rowsInserted\0\0"
    "newMsg\0ZCAN_Receive_Data*\0can_data\0"
    "len\0ZCAN_ReceiveFD_Data*\0canfd_data\0"
    "slot_visibleCol\0QList<int>\0visible_columns"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CanFrameTableModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   35,    2, 0x0a /* Public */,
       3,    2,   40,    2, 0x0a /* Public */,
       9,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::UInt,    5,    6,
    QMetaType::Void, 0x80000000 | 7, QMetaType::UInt,    8,    6,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void CanFrameTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CanFrameTableModel *_t = static_cast<CanFrameTableModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rowsInserted(); break;
        case 1: _t->newMsg((*reinterpret_cast< ZCAN_Receive_Data*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 2: _t->newMsg((*reinterpret_cast< ZCAN_ReceiveFD_Data*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->slot_visibleCol((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CanFrameTableModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CanFrameTableModel::rowsInserted)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CanFrameTableModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_CanFrameTableModel.data,
      qt_meta_data_CanFrameTableModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CanFrameTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanFrameTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CanFrameTableModel.stringdata0))
        return static_cast<void*>(const_cast< CanFrameTableModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int CanFrameTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CanFrameTableModel::rowsInserted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
