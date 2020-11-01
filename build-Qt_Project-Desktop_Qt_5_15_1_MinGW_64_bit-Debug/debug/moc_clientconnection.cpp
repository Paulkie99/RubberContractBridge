/****************************************************************************
** Meta object code from reading C++ file 'clientconnection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Qt_Project/clientconnection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_clientconnection_t {
    QByteArrayData data[24];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_clientconnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_clientconnection_t qt_meta_stringdata_clientconnection = {
    {
QT_MOC_LITERAL(0, 0, 16), // "clientconnection"
QT_MOC_LITERAL(1, 17, 24), // "connectSuccessfullSignal"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 14), // "bidStartSignal"
QT_MOC_LITERAL(4, 58, 16), // "bidRequestSignal"
QT_MOC_LITERAL(5, 75, 15), // "bidUpdateSignal"
QT_MOC_LITERAL(6, 91, 17), // "lobbyUpdateSignal"
QT_MOC_LITERAL(7, 109, 22), // "authUnsuccessfulSignal"
QT_MOC_LITERAL(8, 132, 20), // "authSuccessfulSignal"
QT_MOC_LITERAL(9, 153, 12), // "bidEndSignal"
QT_MOC_LITERAL(10, 166, 15), // "playStartSignal"
QT_MOC_LITERAL(11, 182, 17), // "moveRequestSignal"
QT_MOC_LITERAL(12, 200, 16), // "moveUpdateSignal"
QT_MOC_LITERAL(13, 217, 14), // "trickEndSignal"
QT_MOC_LITERAL(14, 232, 13), // "playEndSignal"
QT_MOC_LITERAL(15, 246, 11), // "scoreSignal"
QT_MOC_LITERAL(16, 258, 22), // "disconnectPlayerSignal"
QT_MOC_LITERAL(17, 281, 25), // "connectUnsuccessfulSignal"
QT_MOC_LITERAL(18, 307, 13), // "gameEndSignal"
QT_MOC_LITERAL(19, 321, 10), // "pongSignal"
QT_MOC_LITERAL(20, 332, 11), // "onConnected"
QT_MOC_LITERAL(21, 344, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(22, 366, 7), // "message"
QT_MOC_LITERAL(23, 374, 6) // "closed"

    },
    "clientconnection\0connectSuccessfullSignal\0"
    "\0bidStartSignal\0bidRequestSignal\0"
    "bidUpdateSignal\0lobbyUpdateSignal\0"
    "authUnsuccessfulSignal\0authSuccessfulSignal\0"
    "bidEndSignal\0playStartSignal\0"
    "moveRequestSignal\0moveUpdateSignal\0"
    "trickEndSignal\0playEndSignal\0scoreSignal\0"
    "disconnectPlayerSignal\0connectUnsuccessfulSignal\0"
    "gameEndSignal\0pongSignal\0onConnected\0"
    "onTextMessageReceived\0message\0closed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_clientconnection[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06 /* Public */,
       3,    1,  122,    2, 0x06 /* Public */,
       4,    0,  125,    2, 0x06 /* Public */,
       5,    1,  126,    2, 0x06 /* Public */,
       6,    1,  129,    2, 0x06 /* Public */,
       7,    1,  132,    2, 0x06 /* Public */,
       8,    0,  135,    2, 0x06 /* Public */,
       9,    1,  136,    2, 0x06 /* Public */,
      10,    1,  139,    2, 0x06 /* Public */,
      11,    1,  142,    2, 0x06 /* Public */,
      12,    1,  145,    2, 0x06 /* Public */,
      13,    1,  148,    2, 0x06 /* Public */,
      14,    1,  151,    2, 0x06 /* Public */,
      15,    1,  154,    2, 0x06 /* Public */,
      16,    1,  157,    2, 0x06 /* Public */,
      17,    1,  160,    2, 0x06 /* Public */,
      18,    1,  163,    2, 0x06 /* Public */,
      19,    1,  166,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    0,  169,    2, 0x08 /* Private */,
      21,    1,  170,    2, 0x08 /* Private */,
      23,    0,  173,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,

       0        // eod
};

void clientconnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<clientconnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectSuccessfullSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->bidStartSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 2: _t->bidRequestSignal(); break;
        case 3: _t->bidUpdateSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 4: _t->lobbyUpdateSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 5: _t->authUnsuccessfulSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 6: _t->authSuccessfulSignal(); break;
        case 7: _t->bidEndSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 8: _t->playStartSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 9: _t->moveRequestSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 10: _t->moveUpdateSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 11: _t->trickEndSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 12: _t->playEndSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 13: _t->scoreSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 14: _t->disconnectPlayerSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 15: _t->connectUnsuccessfulSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 16: _t->gameEndSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 17: _t->pongSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 18: _t->onConnected(); break;
        case 19: _t->onTextMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->closed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::connectSuccessfullSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::bidStartSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::bidRequestSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::bidUpdateSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::lobbyUpdateSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::authUnsuccessfulSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::authSuccessfulSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::bidEndSignal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::playStartSignal)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::moveRequestSignal)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::moveUpdateSignal)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::trickEndSignal)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::playEndSignal)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::scoreSignal)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::disconnectPlayerSignal)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::connectUnsuccessfulSignal)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::gameEndSignal)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (clientconnection::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&clientconnection::pongSignal)) {
                *result = 17;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject clientconnection::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_clientconnection.data,
    qt_meta_data_clientconnection,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *clientconnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *clientconnection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_clientconnection.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int clientconnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void clientconnection::connectSuccessfullSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void clientconnection::bidStartSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void clientconnection::bidRequestSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void clientconnection::bidUpdateSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void clientconnection::lobbyUpdateSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void clientconnection::authUnsuccessfulSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void clientconnection::authSuccessfulSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void clientconnection::bidEndSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void clientconnection::playStartSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void clientconnection::moveRequestSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void clientconnection::moveUpdateSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void clientconnection::trickEndSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void clientconnection::playEndSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void clientconnection::scoreSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void clientconnection::disconnectPlayerSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void clientconnection::connectUnsuccessfulSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void clientconnection::gameEndSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void clientconnection::pongSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
