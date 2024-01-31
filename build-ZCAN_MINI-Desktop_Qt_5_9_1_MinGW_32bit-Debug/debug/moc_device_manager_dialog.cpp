/****************************************************************************
** Meta object code from reading C++ file 'device_manager_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZCAN_MINI/Ui/device_manager_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'device_manager_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceManagerDialog_t {
    QByteArrayData data[10];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceManagerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceManagerDialog_t qt_meta_stringdata_DeviceManagerDialog = {
    {
QT_MOC_LITERAL(0, 0, 19), // "DeviceManagerDialog"
QT_MOC_LITERAL(1, 20, 40), // "slot_comboDeviceType_currentI..."
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 5), // "index"
QT_MOC_LITERAL(4, 68, 41), // "slot_comboDeviceIndex_current..."
QT_MOC_LITERAL(5, 110, 26), // "slot_btnOpenDevice_clicked"
QT_MOC_LITERAL(6, 137, 27), // "slot_btnStartDevice_clicked"
QT_MOC_LITERAL(7, 165, 26), // "slot_btnStopDevice_clicked"
QT_MOC_LITERAL(8, 192, 27), // "slot_btnCloseDevice_clicked"
QT_MOC_LITERAL(9, 220, 26) // "slot_btnDeviceInfo_clicked"

    },
    "DeviceManagerDialog\0"
    "slot_comboDeviceType_currentIndexChanged\0"
    "\0index\0slot_comboDeviceIndex_currentIndexChanged\0"
    "slot_btnOpenDevice_clicked\0"
    "slot_btnStartDevice_clicked\0"
    "slot_btnStopDevice_clicked\0"
    "slot_btnCloseDevice_clicked\0"
    "slot_btnDeviceInfo_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceManagerDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    1,   52,    2, 0x08 /* Private */,
       5,    0,   55,    2, 0x08 /* Private */,
       6,    0,   56,    2, 0x08 /* Private */,
       7,    0,   57,    2, 0x08 /* Private */,
       8,    0,   58,    2, 0x08 /* Private */,
       9,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DeviceManagerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeviceManagerDialog *_t = static_cast<DeviceManagerDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_comboDeviceType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_comboDeviceIndex_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_btnOpenDevice_clicked(); break;
        case 3: _t->slot_btnStartDevice_clicked(); break;
        case 4: _t->slot_btnStopDevice_clicked(); break;
        case 5: _t->slot_btnCloseDevice_clicked(); break;
        case 6: _t->slot_btnDeviceInfo_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject DeviceManagerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DeviceManagerDialog.data,
      qt_meta_data_DeviceManagerDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DeviceManagerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceManagerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceManagerDialog.stringdata0))
        return static_cast<void*>(const_cast< DeviceManagerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DeviceManagerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
