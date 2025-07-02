/****************************************************************************
** Meta object code from reading C++ file 'remotepeer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/remotepeer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'remotepeer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10RemotePeerE_t {};
} // unnamed namespace

template <> constexpr inline auto RemotePeer::qt_create_metaobjectdata<qt_meta_tag_ZN10RemotePeerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "RemotePeer",
        "transferProgress",
        "",
        "current",
        "max",
        "socketError",
        "QAbstractSocket::SocketError",
        "error",
        "errorString",
        "statusMessage",
        "msg",
        "protocolVersionMismatch",
        "actual",
        "expected",
        "close",
        "reason",
        "onSocketStateChanged",
        "QAbstractSocket::SocketState",
        "state",
        "onSocketError",
        "onReadyRead",
        "onCompressionError",
        "Compressor::Error",
        "sendHeartBeat",
        "changeHeartBeatInterval",
        "secs"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'transferProgress'
        QtMocHelpers::SignalData<void(int, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::Int, 4 },
        }}),
        // Signal 'socketError'
        QtMocHelpers::SignalData<void(QAbstractSocket::SocketError, const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'statusMessage'
        QtMocHelpers::SignalData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Signal 'protocolVersionMismatch'
        QtMocHelpers::SignalData<void(int, int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::Int, 13 },
        }}),
        // Slot 'close'
        QtMocHelpers::SlotData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'close'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Slot 'onSocketStateChanged'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketState)>(16, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Slot 'onSocketError'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(19, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCompressionError'
        QtMocHelpers::SlotData<void(Compressor::Error)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 22, 7 },
        }}),
        // Slot 'sendHeartBeat'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'changeHeartBeatInterval'
        QtMocHelpers::SlotData<void(int)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 25 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<RemotePeer, qt_meta_tag_ZN10RemotePeerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject RemotePeer::staticMetaObject = { {
    QMetaObject::SuperData::link<Peer::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10RemotePeerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10RemotePeerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10RemotePeerE_t>.metaTypes,
    nullptr
} };

void RemotePeer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RemotePeer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->transferProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->socketError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->statusMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->protocolVersionMismatch((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->close((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->close(); break;
        case 6: _t->onSocketStateChanged((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketState>>(_a[1]))); break;
        case 7: _t->onSocketError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 8: _t->onReadyRead(); break;
        case 9: _t->onCompressionError((*reinterpret_cast< std::add_pointer_t<Compressor::Error>>(_a[1]))); break;
        case 10: _t->sendHeartBeat(); break;
        case 11: _t->changeHeartBeatInterval((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (RemotePeer::*)(int , int )>(_a, &RemotePeer::transferProgress, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (RemotePeer::*)(QAbstractSocket::SocketError , const QString & )>(_a, &RemotePeer::socketError, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (RemotePeer::*)(const QString & )>(_a, &RemotePeer::statusMessage, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (RemotePeer::*)(int , int )>(_a, &RemotePeer::protocolVersionMismatch, 3))
            return;
    }
}

const QMetaObject *RemotePeer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RemotePeer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10RemotePeerE_t>.strings))
        return static_cast<void*>(this);
    return Peer::qt_metacast(_clname);
}

int RemotePeer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Peer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void RemotePeer::transferProgress(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void RemotePeer::socketError(QAbstractSocket::SocketError _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void RemotePeer::statusMessage(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void RemotePeer::protocolVersionMismatch(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}
QT_WARNING_POP
