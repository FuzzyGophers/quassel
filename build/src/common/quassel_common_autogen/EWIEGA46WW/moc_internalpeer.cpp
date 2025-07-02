/****************************************************************************
** Meta object code from reading C++ file 'internalpeer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/internalpeer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'internalpeer.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12InternalPeerE_t {};
} // unnamed namespace

template <> constexpr inline auto InternalPeer::qt_create_metaobjectdata<qt_meta_tag_ZN12InternalPeerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "InternalPeer",
        "dispatchMessage",
        "",
        "QuasselProtocol::SyncMessage",
        "msg",
        "QuasselProtocol::RpcCall",
        "QuasselProtocol::InitRequest",
        "QuasselProtocol::InitData",
        "close",
        "reason",
        "peerDisconnected",
        "handleMessage"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'dispatchMessage'
        QtMocHelpers::SignalData<void(const QuasselProtocol::SyncMessage &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'dispatchMessage'
        QtMocHelpers::SignalData<void(const QuasselProtocol::RpcCall &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 4 },
        }}),
        // Signal 'dispatchMessage'
        QtMocHelpers::SignalData<void(const QuasselProtocol::InitRequest &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 4 },
        }}),
        // Signal 'dispatchMessage'
        QtMocHelpers::SignalData<void(const QuasselProtocol::InitData &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 4 },
        }}),
        // Slot 'close'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'close'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Slot 'peerDisconnected'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleMessage'
        QtMocHelpers::SlotData<void(const QuasselProtocol::SyncMessage &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'handleMessage'
        QtMocHelpers::SlotData<void(const QuasselProtocol::RpcCall &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 5, 4 },
        }}),
        // Slot 'handleMessage'
        QtMocHelpers::SlotData<void(const QuasselProtocol::InitRequest &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 4 },
        }}),
        // Slot 'handleMessage'
        QtMocHelpers::SlotData<void(const QuasselProtocol::InitData &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 7, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InternalPeer, qt_meta_tag_ZN12InternalPeerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject InternalPeer::staticMetaObject = { {
    QMetaObject::SuperData::link<Peer::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12InternalPeerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12InternalPeerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12InternalPeerE_t>.metaTypes,
    nullptr
} };

void InternalPeer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<InternalPeer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->dispatchMessage((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::SyncMessage>>(_a[1]))); break;
        case 1: _t->dispatchMessage((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::RpcCall>>(_a[1]))); break;
        case 2: _t->dispatchMessage((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::InitRequest>>(_a[1]))); break;
        case 3: _t->dispatchMessage((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::InitData>>(_a[1]))); break;
        case 4: _t->close((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->close(); break;
        case 6: _t->peerDisconnected(); break;
        case 7: _t->handleMessage((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::SyncMessage>>(_a[1]))); break;
        case 8: _t->handleMessage((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::RpcCall>>(_a[1]))); break;
        case 9: _t->handleMessage((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::InitRequest>>(_a[1]))); break;
        case 10: _t->handleMessage((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::InitData>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::SyncMessage >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::RpcCall >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::InitRequest >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::InitData >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::SyncMessage >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::RpcCall >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::InitRequest >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::InitData >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (InternalPeer::*)(const QuasselProtocol::SyncMessage & )>(_a, &InternalPeer::dispatchMessage, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (InternalPeer::*)(const QuasselProtocol::RpcCall & )>(_a, &InternalPeer::dispatchMessage, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (InternalPeer::*)(const QuasselProtocol::InitRequest & )>(_a, &InternalPeer::dispatchMessage, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (InternalPeer::*)(const QuasselProtocol::InitData & )>(_a, &InternalPeer::dispatchMessage, 3))
            return;
    }
}

const QMetaObject *InternalPeer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InternalPeer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12InternalPeerE_t>.strings))
        return static_cast<void*>(this);
    return Peer::qt_metacast(_clname);
}

int InternalPeer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Peer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void InternalPeer::dispatchMessage(const QuasselProtocol::SyncMessage & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void InternalPeer::dispatchMessage(const QuasselProtocol::RpcCall & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void InternalPeer::dispatchMessage(const QuasselProtocol::InitRequest & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void InternalPeer::dispatchMessage(const QuasselProtocol::InitData & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
