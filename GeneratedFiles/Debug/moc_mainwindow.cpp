/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mainwindow_t {
    QByteArrayData data[15];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mainwindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mainwindow_t qt_meta_stringdata_mainwindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "mainwindow"
QT_MOC_LITERAL(1, 11, 12), // "OpenImageDir"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "SaveImageDir"
QT_MOC_LITERAL(4, 38, 11), // "ResliceMode"
QT_MOC_LITERAL(5, 50, 4), // "mode"
QT_MOC_LITERAL(6, 55, 9), // "ThickMode"
QT_MOC_LITERAL(7, 65, 10), // "ResetViews"
QT_MOC_LITERAL(8, 76, 7), // "AddSeed"
QT_MOC_LITERAL(9, 84, 10), // "RemoveSeed"
QT_MOC_LITERAL(10, 95, 16), // "AutoSegmentation"
QT_MOC_LITERAL(11, 112, 19), // "MannualSegmentation"
QT_MOC_LITERAL(12, 132, 19), // "ChangeToRGBColorMap"
QT_MOC_LITERAL(13, 152, 17), // "CalcHeterogeneity"
QT_MOC_LITERAL(14, 170, 9) // "ShowAbout"

    },
    "mainwindow\0OpenImageDir\0\0SaveImageDir\0"
    "ResliceMode\0mode\0ThickMode\0ResetViews\0"
    "AddSeed\0RemoveSeed\0AutoSegmentation\0"
    "MannualSegmentation\0ChangeToRGBColorMap\0"
    "CalcHeterogeneity\0ShowAbout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mainwindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    1,   76,    2, 0x08 /* Private */,
       6,    1,   79,    2, 0x08 /* Private */,
       7,    0,   82,    2, 0x08 /* Private */,
       8,    0,   83,    2, 0x08 /* Private */,
       9,    0,   84,    2, 0x08 /* Private */,
      10,    0,   85,    2, 0x08 /* Private */,
      11,    0,   86,    2, 0x08 /* Private */,
      12,    1,   87,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mainwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mainwindow *_t = static_cast<mainwindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OpenImageDir(); break;
        case 1: _t->SaveImageDir(); break;
        case 2: _t->ResliceMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ThickMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->ResetViews(); break;
        case 5: _t->AddSeed(); break;
        case 6: _t->RemoveSeed(); break;
        case 7: _t->AutoSegmentation(); break;
        case 8: _t->MannualSegmentation(); break;
        case 9: _t->ChangeToRGBColorMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->CalcHeterogeneity(); break;
        case 11: _t->ShowAbout(); break;
        default: ;
        }
    }
}

const QMetaObject mainwindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mainwindow.data,
      qt_meta_data_mainwindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mainwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mainwindow.stringdata0))
        return static_cast<void*>(const_cast< mainwindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mainwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
