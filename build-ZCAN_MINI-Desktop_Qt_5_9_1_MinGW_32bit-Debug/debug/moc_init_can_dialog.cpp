/****************************************************************************
** Meta object code from reading C++ file 'init_can_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZCAN_MINI/Ui/init_can_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'init_can_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InitCanDialog_t {
    QByteArrayData data[11];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InitCanDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InitCanDialog_t qt_meta_stringdata_InitCanDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "InitCanDialog"
QT_MOC_LITERAL(1, 14, 38), // "slot_comboProtocol_currentInd..."
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 5), // "index"
QT_MOC_LITERAL(4, 60, 43), // "slot_comboCanfdStandard_curre..."
QT_MOC_LITERAL(5, 104, 42), // "slot_comboCanfdSpeedUp_curren..."
QT_MOC_LITERAL(6, 147, 34), // "slot_comboAbit_currentIndexCh..."
QT_MOC_LITERAL(7, 182, 34), // "slot_comboDbit_currentIndexCh..."
QT_MOC_LITERAL(8, 217, 38), // "slot_comboWorkMode_currentInd..."
QT_MOC_LITERAL(9, 256, 40), // "slot_comboResistance_currentI..."
QT_MOC_LITERAL(10, 297, 16) // "on_btnOk_clicked"

    },
    "InitCanDialog\0slot_comboProtocol_currentIndexChanged\0"
    "\0index\0slot_comboCanfdStandard_currentIndexChanged\0"
    "slot_comboCanfdSpeedUp_currentIndexChanged\0"
    "slot_comboAbit_currentIndexChanged\0"
    "slot_comboDbit_currentIndexChanged\0"
    "slot_comboWorkMode_currentIndexChanged\0"
    "slot_comboResistance_currentIndexChanged\0"
    "on_btnOk_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InitCanDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    1,   57,    2, 0x08 /* Private */,
       5,    1,   60,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       8,    1,   69,    2, 0x08 /* Private */,
       9,    1,   72,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void InitCanDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InitCanDialog *_t = static_cast<InitCanDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_comboProtocol_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_comboCanfdStandard_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_comboCanfdSpeedUp_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_comboAbit_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_comboDbit_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_comboWorkMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_comboResistance_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_btnOk_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject InitCanDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InitCanDialog.data,
      qt_meta_data_InitCanDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *InitCanDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InitCanDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InitCanDialog.stringdata0))
        return static_cast<void*>(const_cast< InitCanDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int InitCanDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE