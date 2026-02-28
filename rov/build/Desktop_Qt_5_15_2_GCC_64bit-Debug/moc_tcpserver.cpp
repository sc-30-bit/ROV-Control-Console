/****************************************************************************
** Meta object code from reading C++ file 'tcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../tcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tcpserver_t {
    QByteArrayData data[52];
    char stringdata0[608];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcpserver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcpserver_t qt_meta_stringdata_tcpserver = {
    {
QT_MOC_LITERAL(0, 0, 9), // "tcpserver"
QT_MOC_LITERAL(1, 10, 11), // "send_jy901s"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "send_ms5837"
QT_MOC_LITERAL(4, 35, 10), // "send_shtc3"
QT_MOC_LITERAL(5, 46, 13), // "send_thruster"
QT_MOC_LITERAL(6, 60, 11), // "send_yuntai"
QT_MOC_LITERAL(7, 72, 11), // "send_ipport"
QT_MOC_LITERAL(8, 84, 2), // "ip"
QT_MOC_LITERAL(9, 87, 4), // "port"
QT_MOC_LITERAL(10, 92, 8), // "send_msg"
QT_MOC_LITERAL(11, 101, 3), // "msg"
QT_MOC_LITERAL(12, 105, 4), // "warn"
QT_MOC_LITERAL(13, 110, 13), // "unpack_jy901s"
QT_MOC_LITERAL(14, 124, 9), // "data_hear"
QT_MOC_LITERAL(15, 134, 4), // "head"
QT_MOC_LITERAL(16, 139, 13), // "unpack_ms5837"
QT_MOC_LITERAL(17, 153, 12), // "unpack_shtc3"
QT_MOC_LITERAL(18, 166, 10), // "unpack_pwm"
QT_MOC_LITERAL(19, 177, 13), // "unpack_yuntai"
QT_MOC_LITERAL(20, 191, 13), // "unpack_buffer"
QT_MOC_LITERAL(21, 205, 6), // "buffer"
QT_MOC_LITERAL(22, 212, 21), // "send_data_from_server"
QT_MOC_LITERAL(23, 234, 9), // "data_send"
QT_MOC_LITERAL(24, 244, 8), // "pack_pid"
QT_MOC_LITERAL(25, 253, 12), // "const float*"
QT_MOC_LITERAL(26, 266, 8), // "pidarray"
QT_MOC_LITERAL(27, 275, 5), // "start"
QT_MOC_LITERAL(28, 281, 5), // "close"
QT_MOC_LITERAL(29, 287, 12), // "createPacket"
QT_MOC_LITERAL(30, 300, 17), // "contentDescriptor"
QT_MOC_LITERAL(31, 318, 20), // "const unsigned char*"
QT_MOC_LITERAL(32, 339, 4), // "data"
QT_MOC_LITERAL(33, 344, 10), // "dataLength"
QT_MOC_LITERAL(34, 355, 11), // "sendcontrol"
QT_MOC_LITERAL(35, 367, 5), // "light"
QT_MOC_LITERAL(36, 373, 8), // "poselock"
QT_MOC_LITERAL(37, 382, 4), // "boot"
QT_MOC_LITERAL(38, 387, 15), // "velocitykeeping"
QT_MOC_LITERAL(39, 403, 13), // "electromagnet"
QT_MOC_LITERAL(40, 417, 9), // "pushstick"
QT_MOC_LITERAL(41, 427, 12), // "autoduizheng"
QT_MOC_LITERAL(42, 440, 8), // "autospin"
QT_MOC_LITERAL(43, 449, 14), // "gamepad_ping_x"
QT_MOC_LITERAL(44, 464, 5), // "value"
QT_MOC_LITERAL(45, 470, 14), // "gamepad_ping_y"
QT_MOC_LITERAL(46, 485, 17), // "gamepad_ping_z_up"
QT_MOC_LITERAL(47, 503, 19), // "gamepad_ping_z_down"
QT_MOC_LITERAL(48, 523, 22), // "gamepad_zhuan_rollLeft"
QT_MOC_LITERAL(49, 546, 23), // "gamepad_zhuan_rollRight"
QT_MOC_LITERAL(50, 570, 19), // "gamepad_zhuan_pitch"
QT_MOC_LITERAL(51, 590, 17) // "gamepad_zhuan_yaw"

    },
    "tcpserver\0send_jy901s\0\0send_ms5837\0"
    "send_shtc3\0send_thruster\0send_yuntai\0"
    "send_ipport\0ip\0port\0send_msg\0msg\0warn\0"
    "unpack_jy901s\0data_hear\0head\0unpack_ms5837\0"
    "unpack_shtc3\0unpack_pwm\0unpack_yuntai\0"
    "unpack_buffer\0buffer\0send_data_from_server\0"
    "data_send\0pack_pid\0const float*\0"
    "pidarray\0start\0close\0createPacket\0"
    "contentDescriptor\0const unsigned char*\0"
    "data\0dataLength\0sendcontrol\0light\0"
    "poselock\0boot\0velocitykeeping\0"
    "electromagnet\0pushstick\0autoduizheng\0"
    "autospin\0gamepad_ping_x\0value\0"
    "gamepad_ping_y\0gamepad_ping_z_up\0"
    "gamepad_ping_z_down\0gamepad_zhuan_rollLeft\0"
    "gamepad_zhuan_rollRight\0gamepad_zhuan_pitch\0"
    "gamepad_zhuan_yaw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcpserver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  194,    2, 0x06 /* Public */,
       3,    0,  195,    2, 0x06 /* Public */,
       4,    0,  196,    2, 0x06 /* Public */,
       5,    0,  197,    2, 0x06 /* Public */,
       6,    0,  198,    2, 0x06 /* Public */,
       7,    2,  199,    2, 0x06 /* Public */,
      10,    1,  204,    2, 0x06 /* Public */,
      12,    0,  207,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    2,  208,    2, 0x0a /* Public */,
      16,    2,  213,    2, 0x0a /* Public */,
      17,    2,  218,    2, 0x0a /* Public */,
      18,    2,  223,    2, 0x0a /* Public */,
      19,    2,  228,    2, 0x0a /* Public */,
      20,    1,  233,    2, 0x0a /* Public */,
      22,    1,  236,    2, 0x0a /* Public */,
      24,    1,  239,    2, 0x0a /* Public */,
      27,    0,  242,    2, 0x0a /* Public */,
      28,    0,  243,    2, 0x0a /* Public */,
      29,    3,  244,    2, 0x0a /* Public */,
      34,    0,  251,    2, 0x0a /* Public */,
      35,    1,  252,    2, 0x0a /* Public */,
      36,    1,  255,    2, 0x0a /* Public */,
      37,    1,  258,    2, 0x0a /* Public */,
      38,    1,  261,    2, 0x0a /* Public */,
      39,    1,  264,    2, 0x0a /* Public */,
      40,    1,  267,    2, 0x0a /* Public */,
      41,    1,  270,    2, 0x0a /* Public */,
      42,    1,  273,    2, 0x0a /* Public */,
      43,    1,  276,    2, 0x0a /* Public */,
      45,    1,  279,    2, 0x0a /* Public */,
      46,    1,  282,    2, 0x0a /* Public */,
      47,    1,  285,    2, 0x0a /* Public */,
      48,    1,  288,    2, 0x0a /* Public */,
      49,    1,  291,    2, 0x0a /* Public */,
      50,    1,  294,    2, 0x0a /* Public */,
      51,    1,  297,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::QByteArray,   21,
    QMetaType::Void, QMetaType::QByteArray,   23,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QByteArray, QMetaType::UChar, 0x80000000 | 31, QMetaType::Int,   30,   32,   33,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   44,

       0        // eod
};

void tcpserver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tcpserver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_jy901s(); break;
        case 1: _t->send_ms5837(); break;
        case 2: _t->send_shtc3(); break;
        case 3: _t->send_thruster(); break;
        case 4: _t->send_yuntai(); break;
        case 5: _t->send_ipport((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->send_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->warn(); break;
        case 8: _t->unpack_jy901s((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->unpack_ms5837((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->unpack_shtc3((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->unpack_pwm((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->unpack_yuntai((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->unpack_buffer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 14: _t->send_data_from_server((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 15: _t->pack_pid((*reinterpret_cast< const float*(*)>(_a[1]))); break;
        case 16: _t->start(); break;
        case 17: _t->close(); break;
        case 18: { QByteArray _r = _t->createPacket((*reinterpret_cast< unsigned char(*)>(_a[1])),(*reinterpret_cast< const unsigned char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->sendcontrol(); break;
        case 20: _t->light((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->poselock((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: _t->boot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->velocitykeeping((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 24: _t->electromagnet((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 25: _t->pushstick((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->autoduizheng((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->autospin((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 28: _t->gamepad_ping_x((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->gamepad_ping_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->gamepad_ping_z_up((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 31: _t->gamepad_ping_z_down((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 32: _t->gamepad_zhuan_rollLeft((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 33: _t->gamepad_zhuan_rollRight((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 34: _t->gamepad_zhuan_pitch((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 35: _t->gamepad_zhuan_yaw((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tcpserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpserver::send_jy901s)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (tcpserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpserver::send_ms5837)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (tcpserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpserver::send_shtc3)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (tcpserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpserver::send_thruster)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (tcpserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpserver::send_yuntai)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (tcpserver::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpserver::send_ipport)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (tcpserver::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpserver::send_msg)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (tcpserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpserver::warn)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tcpserver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_tcpserver.data,
    qt_meta_data_tcpserver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tcpserver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcpserver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tcpserver.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int tcpserver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 36;
    }
    return _id;
}

// SIGNAL 0
void tcpserver::send_jy901s()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void tcpserver::send_ms5837()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void tcpserver::send_shtc3()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void tcpserver::send_thruster()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void tcpserver::send_yuntai()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void tcpserver::send_ipport(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void tcpserver::send_msg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void tcpserver::warn()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
