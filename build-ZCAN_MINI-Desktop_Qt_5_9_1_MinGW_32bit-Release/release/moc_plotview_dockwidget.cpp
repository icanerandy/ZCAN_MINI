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
    QByteArrayData data[19];
    char stringdata0[269];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlotViewDockWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlotViewDockWidget_t qt_meta_stringdata_PlotViewDockWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PlotViewDockWidget"
QT_MOC_LITERAL(1, 19, 10), // "slot_paint"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "msg_id"
QT_MOC_LITERAL(4, 38, 17), // "CppCAN::CANSignal"
QT_MOC_LITERAL(5, 56, 9), // "ref_speed"
QT_MOC_LITERAL(6, 66, 9), // "rel_speed"
QT_MOC_LITERAL(7, 76, 20), // "slot_btnSave_clicked"
QT_MOC_LITERAL(8, 97, 7), // "checked"
QT_MOC_LITERAL(9, 105, 26), // "slot_customPlot_mousePress"
QT_MOC_LITERAL(10, 132, 12), // "QMouseEvent*"
QT_MOC_LITERAL(11, 145, 5), // "event"
QT_MOC_LITERAL(12, 151, 32), // "slot_customPlot_selectionChanged"
QT_MOC_LITERAL(13, 184, 21), // "slot_btnExcel_clicked"
QT_MOC_LITERAL(14, 206, 16), // "slot_legendClick"
QT_MOC_LITERAL(15, 223, 10), // "QCPLegend*"
QT_MOC_LITERAL(16, 234, 6), // "legend"
QT_MOC_LITERAL(17, 241, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(18, 264, 4) // "item"

    },
    "PlotViewDockWidget\0slot_paint\0\0msg_id\0"
    "CppCAN::CANSignal\0ref_speed\0rel_speed\0"
    "slot_btnSave_clicked\0checked\0"
    "slot_customPlot_mousePress\0QMouseEvent*\0"
    "event\0slot_customPlot_selectionChanged\0"
    "slot_btnExcel_clicked\0slot_legendClick\0"
    "QCPLegend*\0legend\0QCPAbstractLegendItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlotViewDockWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x08 /* Private */,
      12,    0,   57,    2, 0x08 /* Private */,
      13,    1,   58,    2, 0x08 /* Private */,
      14,    2,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::ULongLong, 0x80000000 | 4, 0x80000000 | 4,    3,    5,    6,
    QMetaType::Bool, QMetaType::Bool,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17,   16,   18,

       0        // eod
};

void PlotViewDockWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlotViewDockWidget *_t = static_cast<PlotViewDockWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_paint((*reinterpret_cast< const unsigned long long(*)>(_a[1])),(*reinterpret_cast< const CppCAN::CANSignal(*)>(_a[2])),(*reinterpret_cast< const CppCAN::CANSignal(*)>(_a[3]))); break;
        case 1: { bool _r = _t->slot_btnSave_clicked((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->slot_customPlot_mousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->slot_customPlot_selectionChanged(); break;
        case 4: _t->slot_btnExcel_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->slot_legendClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
