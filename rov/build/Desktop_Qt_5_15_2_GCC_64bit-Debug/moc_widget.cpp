/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[27];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 13), // "form_pidarray"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "const float*"
QT_MOC_LITERAL(4, 35, 12), // "pidparameter"
QT_MOC_LITERAL(5, 48, 11), // "sendPicture"
QT_MOC_LITERAL(6, 60, 3), // "map"
QT_MOC_LITERAL(7, 64, 11), // "cameraIndex"
QT_MOC_LITERAL(8, 76, 9), // "sendVideo"
QT_MOC_LITERAL(9, 86, 10), // "videoFrame"
QT_MOC_LITERAL(10, 97, 12), // "timerStopped"
QT_MOC_LITERAL(11, 110, 12), // "receiveLogin"
QT_MOC_LITERAL(12, 123, 10), // "showframes"
QT_MOC_LITERAL(13, 134, 6), // "frame1"
QT_MOC_LITERAL(14, 141, 6), // "frame2"
QT_MOC_LITERAL(15, 148, 6), // "frame3"
QT_MOC_LITERAL(16, 155, 9), // "showshtc3"
QT_MOC_LITERAL(17, 165, 10), // "showms5837"
QT_MOC_LITERAL(18, 176, 10), // "showjys901"
QT_MOC_LITERAL(19, 187, 12), // "showthruster"
QT_MOC_LITERAL(20, 200, 10), // "showyuntai"
QT_MOC_LITERAL(21, 211, 7), // "showmsg"
QT_MOC_LITERAL(22, 219, 3), // "msg"
QT_MOC_LITERAL(23, 223, 11), // "showwarning"
QT_MOC_LITERAL(24, 235, 8), // "showinfo"
QT_MOC_LITERAL(25, 244, 2), // "ip"
QT_MOC_LITERAL(26, 247, 4) // "port"

    },
    "Widget\0form_pidarray\0\0const float*\0"
    "pidparameter\0sendPicture\0map\0cameraIndex\0"
    "sendVideo\0videoFrame\0timerStopped\0"
    "receiveLogin\0showframes\0frame1\0frame2\0"
    "frame3\0showshtc3\0showms5837\0showjys901\0"
    "showthruster\0showyuntai\0showmsg\0msg\0"
    "showwarning\0showinfo\0ip\0port"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    2,   87,    2, 0x06 /* Public */,
       8,    2,   92,    2, 0x06 /* Public */,
      10,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  100,    2, 0x0a /* Public */,
      12,    3,  101,    2, 0x0a /* Public */,
      16,    0,  108,    2, 0x0a /* Public */,
      17,    0,  109,    2, 0x0a /* Public */,
      18,    0,  110,    2, 0x0a /* Public */,
      19,    0,  111,    2, 0x0a /* Public */,
      20,    0,  112,    2, 0x0a /* Public */,
      21,    1,  113,    2, 0x0a /* Public */,
      23,    0,  116,    2, 0x08 /* Private */,
      24,    2,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int,    9,    7,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QPixmap, QMetaType::QPixmap,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   25,   26,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->form_pidarray((*reinterpret_cast< const float*(*)>(_a[1]))); break;
        case 1: _t->sendPicture((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sendVideo((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->timerStopped((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->receiveLogin(); break;
        case 5: _t->showframes((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QPixmap(*)>(_a[2])),(*reinterpret_cast< QPixmap(*)>(_a[3]))); break;
        case 6: _t->showshtc3(); break;
        case 7: _t->showms5837(); break;
        case 8: _t->showjys901(); break;
        case 9: _t->showthruster(); break;
        case 10: _t->showyuntai(); break;
        case 11: _t->showmsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->showwarning(); break;
        case 13: _t->showinfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Widget::*)(const float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::form_pidarray)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Widget::*)(QPixmap , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::sendPicture)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Widget::*)(QPixmap , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::sendVideo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Widget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::timerStopped)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Widget::form_pidarray(const float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Widget::sendPicture(QPixmap _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Widget::sendVideo(QPixmap _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Widget::timerStopped(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
