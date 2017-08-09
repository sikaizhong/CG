/****************************************************************************
** Meta object code from reading C++ file 'DockWidgetTitleBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DockWidgetTitleBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DockWidgetTitleBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DockWidgetTitleBar_t {
    QByteArrayData data[6];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DockWidgetTitleBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DockWidgetTitleBar_t qt_meta_stringdata_DockWidgetTitleBar = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DockWidgetTitleBar"
QT_MOC_LITERAL(1, 19, 8), // "floating"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "stickyBtnToggled"
QT_MOC_LITERAL(4, 46, 6), // "toggle"
QT_MOC_LITERAL(5, 53, 15) // "floatBtnClicked"

    },
    "DockWidgetTitleBar\0floating\0\0"
    "stickyBtnToggled\0toggle\0floatBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DockWidgetTitleBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       3,    1,   32,    2, 0x09 /* Protected */,
       5,    0,   35,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    1,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,

       0        // eod
};

void DockWidgetTitleBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DockWidgetTitleBar *_t = static_cast<DockWidgetTitleBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->floating((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->stickyBtnToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->floatBtnClicked(); break;
        default: ;
        }
    }
}

const QMetaObject DockWidgetTitleBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DockWidgetTitleBar.data,
      qt_meta_data_DockWidgetTitleBar,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DockWidgetTitleBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DockWidgetTitleBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DockWidgetTitleBar.stringdata0))
        return static_cast<void*>(const_cast< DockWidgetTitleBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int DockWidgetTitleBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
