/****************************************************************************
** Meta object code from reading C++ file 'gamescreen.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Qt_Project/gamescreen.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamescreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameScreen_t {
    QByteArrayData data[71];
    char stringdata0[1132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameScreen_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameScreen_t qt_meta_stringdata_GameScreen = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameScreen"
QT_MOC_LITERAL(1, 11, 10), // "pingSignal"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 22), // "on_GameScreen_finished"
QT_MOC_LITERAL(4, 46, 6), // "result"
QT_MOC_LITERAL(5, 53, 27), // "on_pushButton_Score_clicked"
QT_MOC_LITERAL(6, 81, 26), // "on_pushButton_Play_clicked"
QT_MOC_LITERAL(7, 108, 9), // "loadCards"
QT_MOC_LITERAL(8, 118, 12), // "QPushButton*"
QT_MOC_LITERAL(9, 131, 29), // "on_pushButton_Abandon_clicked"
QT_MOC_LITERAL(10, 161, 25), // "on_pushButton_Bid_clicked"
QT_MOC_LITERAL(11, 187, 9), // "showCards"
QT_MOC_LITERAL(12, 197, 12), // "disableCards"
QT_MOC_LITERAL(13, 210, 7), // "sendBid"
QT_MOC_LITERAL(14, 218, 8), // "sendMove"
QT_MOC_LITERAL(15, 227, 31), // "on_pushButton_ViewCards_clicked"
QT_MOC_LITERAL(16, 259, 33), // "on_pushButton_BackAuction_cli..."
QT_MOC_LITERAL(17, 293, 24), // "on_tableBids_cellClicked"
QT_MOC_LITERAL(18, 318, 3), // "row"
QT_MOC_LITERAL(19, 322, 6), // "column"
QT_MOC_LITERAL(20, 329, 26), // "on_pushButton_Pass_clicked"
QT_MOC_LITERAL(21, 356, 28), // "on_pushButton_Double_clicked"
QT_MOC_LITERAL(22, 385, 30), // "on_pushButton_Redouble_clicked"
QT_MOC_LITERAL(23, 416, 10), // "addToTable"
QT_MOC_LITERAL(24, 427, 10), // "visibleAll"
QT_MOC_LITERAL(25, 438, 3), // "vis"
QT_MOC_LITERAL(26, 442, 14), // "serverInfoSlot"
QT_MOC_LITERAL(27, 457, 17), // "clientconnection*"
QT_MOC_LITERAL(28, 475, 15), // "lobbyUpdateSlot"
QT_MOC_LITERAL(29, 491, 12), // "bidStartSlot"
QT_MOC_LITERAL(30, 504, 14), // "bidRequestSlot"
QT_MOC_LITERAL(31, 519, 13), // "bidUpdateSlot"
QT_MOC_LITERAL(32, 533, 3), // "bid"
QT_MOC_LITERAL(33, 537, 10), // "bidEndSlot"
QT_MOC_LITERAL(34, 548, 13), // "playStartSlot"
QT_MOC_LITERAL(35, 562, 15), // "moveRequestSlot"
QT_MOC_LITERAL(36, 578, 14), // "moveUpdateSlot"
QT_MOC_LITERAL(37, 593, 12), // "trickEndSlot"
QT_MOC_LITERAL(38, 606, 11), // "playEndSlot"
QT_MOC_LITERAL(39, 618, 9), // "scoreSlot"
QT_MOC_LITERAL(40, 628, 20), // "disconnectPlayerSlot"
QT_MOC_LITERAL(41, 649, 11), // "gameEndSlot"
QT_MOC_LITERAL(42, 661, 4), // "ping"
QT_MOC_LITERAL(43, 666, 8), // "pongSlot"
QT_MOC_LITERAL(44, 675, 15), // "on_pb_1_clicked"
QT_MOC_LITERAL(45, 691, 15), // "on_pb_2_clicked"
QT_MOC_LITERAL(46, 707, 15), // "on_pb_3_clicked"
QT_MOC_LITERAL(47, 723, 15), // "on_pb_4_clicked"
QT_MOC_LITERAL(48, 739, 15), // "on_pb_5_clicked"
QT_MOC_LITERAL(49, 755, 15), // "on_pb_6_clicked"
QT_MOC_LITERAL(50, 771, 15), // "on_pb_7_clicked"
QT_MOC_LITERAL(51, 787, 15), // "on_pb_8_clicked"
QT_MOC_LITERAL(52, 803, 15), // "on_pb_9_clicked"
QT_MOC_LITERAL(53, 819, 16), // "on_pb_10_clicked"
QT_MOC_LITERAL(54, 836, 16), // "on_pb_11_clicked"
QT_MOC_LITERAL(55, 853, 16), // "on_pb_12_clicked"
QT_MOC_LITERAL(56, 870, 16), // "on_pb_13_clicked"
QT_MOC_LITERAL(57, 887, 16), // "on_pb_14_clicked"
QT_MOC_LITERAL(58, 904, 16), // "on_pb_15_clicked"
QT_MOC_LITERAL(59, 921, 16), // "on_pb_16_clicked"
QT_MOC_LITERAL(60, 938, 16), // "on_pb_17_clicked"
QT_MOC_LITERAL(61, 955, 16), // "on_pb_18_clicked"
QT_MOC_LITERAL(62, 972, 16), // "on_pb_19_clicked"
QT_MOC_LITERAL(63, 989, 16), // "on_pb_20_clicked"
QT_MOC_LITERAL(64, 1006, 16), // "on_pb_21_clicked"
QT_MOC_LITERAL(65, 1023, 16), // "on_pb_22_clicked"
QT_MOC_LITERAL(66, 1040, 16), // "on_pb_23_clicked"
QT_MOC_LITERAL(67, 1057, 16), // "on_pb_24_clicked"
QT_MOC_LITERAL(68, 1074, 16), // "on_pb_25_clicked"
QT_MOC_LITERAL(69, 1091, 16), // "on_pb_26_clicked"
QT_MOC_LITERAL(70, 1108, 23) // "on_GameScreen_destroyed"

    },
    "GameScreen\0pingSignal\0\0on_GameScreen_finished\0"
    "result\0on_pushButton_Score_clicked\0"
    "on_pushButton_Play_clicked\0loadCards\0"
    "QPushButton*\0on_pushButton_Abandon_clicked\0"
    "on_pushButton_Bid_clicked\0showCards\0"
    "disableCards\0sendBid\0sendMove\0"
    "on_pushButton_ViewCards_clicked\0"
    "on_pushButton_BackAuction_clicked\0"
    "on_tableBids_cellClicked\0row\0column\0"
    "on_pushButton_Pass_clicked\0"
    "on_pushButton_Double_clicked\0"
    "on_pushButton_Redouble_clicked\0"
    "addToTable\0visibleAll\0vis\0serverInfoSlot\0"
    "clientconnection*\0lobbyUpdateSlot\0"
    "bidStartSlot\0bidRequestSlot\0bidUpdateSlot\0"
    "bid\0bidEndSlot\0playStartSlot\0"
    "moveRequestSlot\0moveUpdateSlot\0"
    "trickEndSlot\0playEndSlot\0scoreSlot\0"
    "disconnectPlayerSlot\0gameEndSlot\0ping\0"
    "pongSlot\0on_pb_1_clicked\0on_pb_2_clicked\0"
    "on_pb_3_clicked\0on_pb_4_clicked\0"
    "on_pb_5_clicked\0on_pb_6_clicked\0"
    "on_pb_7_clicked\0on_pb_8_clicked\0"
    "on_pb_9_clicked\0on_pb_10_clicked\0"
    "on_pb_11_clicked\0on_pb_12_clicked\0"
    "on_pb_13_clicked\0on_pb_14_clicked\0"
    "on_pb_15_clicked\0on_pb_16_clicked\0"
    "on_pb_17_clicked\0on_pb_18_clicked\0"
    "on_pb_19_clicked\0on_pb_20_clicked\0"
    "on_pb_21_clicked\0on_pb_22_clicked\0"
    "on_pb_23_clicked\0on_pb_24_clicked\0"
    "on_pb_25_clicked\0on_pb_26_clicked\0"
    "on_GameScreen_destroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameScreen[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      63,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  329,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,  332,    2, 0x08 /* Private */,
       5,    0,  335,    2, 0x08 /* Private */,
       6,    0,  336,    2, 0x08 /* Private */,
       7,    2,  337,    2, 0x08 /* Private */,
       9,    0,  342,    2, 0x08 /* Private */,
      10,    0,  343,    2, 0x08 /* Private */,
      11,    1,  344,    2, 0x08 /* Private */,
      12,    2,  347,    2, 0x08 /* Private */,
      13,    2,  352,    2, 0x08 /* Private */,
      14,    2,  357,    2, 0x08 /* Private */,
      15,    0,  362,    2, 0x08 /* Private */,
      16,    0,  363,    2, 0x08 /* Private */,
      17,    2,  364,    2, 0x08 /* Private */,
      20,    0,  369,    2, 0x08 /* Private */,
      21,    0,  370,    2, 0x08 /* Private */,
      22,    0,  371,    2, 0x08 /* Private */,
      23,    2,  372,    2, 0x08 /* Private */,
      24,    1,  377,    2, 0x08 /* Private */,
      24,    0,  380,    2, 0x28 /* Private | MethodCloned */,
      26,    6,  381,    2, 0x08 /* Private */,
      28,    1,  394,    2, 0x08 /* Private */,
      29,    1,  397,    2, 0x08 /* Private */,
      30,    0,  400,    2, 0x08 /* Private */,
      31,    1,  401,    2, 0x08 /* Private */,
      33,    1,  404,    2, 0x08 /* Private */,
      34,    1,  407,    2, 0x08 /* Private */,
      35,    1,  410,    2, 0x08 /* Private */,
      36,    1,  413,    2, 0x08 /* Private */,
      37,    1,  416,    2, 0x08 /* Private */,
      38,    1,  419,    2, 0x08 /* Private */,
      39,    1,  422,    2, 0x08 /* Private */,
      40,    1,  425,    2, 0x08 /* Private */,
      41,    1,  428,    2, 0x08 /* Private */,
      42,    0,  431,    2, 0x08 /* Private */,
      43,    1,  432,    2, 0x08 /* Private */,
      44,    0,  435,    2, 0x08 /* Private */,
      45,    0,  436,    2, 0x08 /* Private */,
      46,    0,  437,    2, 0x08 /* Private */,
      47,    0,  438,    2, 0x08 /* Private */,
      48,    0,  439,    2, 0x08 /* Private */,
      49,    0,  440,    2, 0x08 /* Private */,
      50,    0,  441,    2, 0x08 /* Private */,
      51,    0,  442,    2, 0x08 /* Private */,
      52,    0,  443,    2, 0x08 /* Private */,
      53,    0,  444,    2, 0x08 /* Private */,
      54,    0,  445,    2, 0x08 /* Private */,
      55,    0,  446,    2, 0x08 /* Private */,
      56,    0,  447,    2, 0x08 /* Private */,
      57,    0,  448,    2, 0x08 /* Private */,
      58,    0,  449,    2, 0x08 /* Private */,
      59,    0,  450,    2, 0x08 /* Private */,
      60,    0,  451,    2, 0x08 /* Private */,
      61,    0,  452,    2, 0x08 /* Private */,
      62,    0,  453,    2, 0x08 /* Private */,
      63,    0,  454,    2, 0x08 /* Private */,
      64,    0,  455,    2, 0x08 /* Private */,
      65,    0,  456,    2, 0x08 /* Private */,
      66,    0,  457,    2, 0x08 /* Private */,
      67,    0,  458,    2, 0x08 /* Private */,
      68,    0,  459,    2, 0x08 /* Private */,
      69,    0,  460,    2, 0x08 /* Private */,
      70,    0,  461,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 27, QMetaType::QString, QMetaType::Int,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   32,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GameScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameScreen *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pingSignal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->on_GameScreen_finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_Score_clicked(); break;
        case 3: _t->on_pushButton_Play_clicked(); break;
        case 4: _t->loadCards((*reinterpret_cast< QPushButton*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->on_pushButton_Abandon_clicked(); break;
        case 6: _t->on_pushButton_Bid_clicked(); break;
        case 7: _t->showCards((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->disableCards((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->sendBid((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->sendMove((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->on_pushButton_ViewCards_clicked(); break;
        case 12: _t->on_pushButton_BackAuction_clicked(); break;
        case 13: _t->on_tableBids_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->on_pushButton_Pass_clicked(); break;
        case 15: _t->on_pushButton_Double_clicked(); break;
        case 16: _t->on_pushButton_Redouble_clicked(); break;
        case 17: _t->addToTable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->visibleAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->visibleAll(); break;
        case 20: _t->serverInfoSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< clientconnection*(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 21: _t->lobbyUpdateSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 22: _t->bidStartSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 23: _t->bidRequestSlot(); break;
        case 24: _t->bidUpdateSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 25: _t->bidEndSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 26: _t->playStartSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 27: _t->moveRequestSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 28: _t->moveUpdateSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 29: _t->trickEndSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 30: _t->playEndSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 31: _t->scoreSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 32: _t->disconnectPlayerSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 33: _t->gameEndSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 34: _t->ping(); break;
        case 35: _t->pongSlot((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 36: _t->on_pb_1_clicked(); break;
        case 37: _t->on_pb_2_clicked(); break;
        case 38: _t->on_pb_3_clicked(); break;
        case 39: _t->on_pb_4_clicked(); break;
        case 40: _t->on_pb_5_clicked(); break;
        case 41: _t->on_pb_6_clicked(); break;
        case 42: _t->on_pb_7_clicked(); break;
        case 43: _t->on_pb_8_clicked(); break;
        case 44: _t->on_pb_9_clicked(); break;
        case 45: _t->on_pb_10_clicked(); break;
        case 46: _t->on_pb_11_clicked(); break;
        case 47: _t->on_pb_12_clicked(); break;
        case 48: _t->on_pb_13_clicked(); break;
        case 49: _t->on_pb_14_clicked(); break;
        case 50: _t->on_pb_15_clicked(); break;
        case 51: _t->on_pb_16_clicked(); break;
        case 52: _t->on_pb_17_clicked(); break;
        case 53: _t->on_pb_18_clicked(); break;
        case 54: _t->on_pb_19_clicked(); break;
        case 55: _t->on_pb_20_clicked(); break;
        case 56: _t->on_pb_21_clicked(); break;
        case 57: _t->on_pb_22_clicked(); break;
        case 58: _t->on_pb_23_clicked(); break;
        case 59: _t->on_pb_24_clicked(); break;
        case 60: _t->on_pb_25_clicked(); break;
        case 61: _t->on_pb_26_clicked(); break;
        case 62: _t->on_GameScreen_destroyed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< clientconnection* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameScreen::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameScreen::pingSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameScreen::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_GameScreen.data,
    qt_meta_data_GameScreen,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameScreen.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int GameScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 63)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 63;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 63)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 63;
    }
    return _id;
}

// SIGNAL 0
void GameScreen::pingSignal(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
