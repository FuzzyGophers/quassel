/****************************************************************************
** Meta object code from reading C++ file 'peer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/peer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'peer.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN4PeerE_t {};
} // unnamed namespace

template <> constexpr inline auto Peer::qt_create_metaobjectdata<qt_meta_tag_ZN4PeerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Peer",
        "disconnected",
        "",
        "secureStateChanged",
        "secure",
        "lagUpdated",
        "msecs",
        "dispatch",
        "QuasselProtocol::RegisterClient",
        "QuasselProtocol::ClientDenied",
        "QuasselProtocol::ClientRegistered",
        "QuasselProtocol::SetupData",
        "QuasselProtocol::SetupFailed",
        "QuasselProtocol::SetupDone",
        "QuasselProtocol::Login",
        "QuasselProtocol::LoginFailed",
        "QuasselProtocol::LoginSuccess",
        "QuasselProtocol::SessionState",
        "QuasselProtocol::SyncMessage",
        "QuasselProtocol::RpcCall",
        "QuasselProtocol::InitRequest",
        "QuasselProtocol::InitData",
        "close",
        "reason"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'disconnected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'secureStateChanged'
        QtMocHelpers::SignalData<void(bool)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 4 },
        }}),
        // Signal 'secureStateChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Signal 'lagUpdated'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::RegisterClient &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::ClientDenied &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::ClientRegistered &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::SetupData &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::SetupFailed &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::SetupDone &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::Login &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::LoginFailed &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 15, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::LoginSuccess &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::SessionState &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::SyncMessage &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 18, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::RpcCall &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 19, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::InitRequest &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 2 },
        }}),
        // Slot 'dispatch'
        QtMocHelpers::SlotData<void(const QuasselProtocol::InitData &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 21, 2 },
        }}),
        // Slot 'close'
        QtMocHelpers::SlotData<void(const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 23 },
        }}),
        // Slot 'close'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Peer, qt_meta_tag_ZN4PeerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Peer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4PeerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4PeerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4PeerE_t>.metaTypes,
    nullptr
} };

void Peer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Peer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->disconnected(); break;
        case 1: _t->secureStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->secureStateChanged(); break;
        case 3: _t->lagUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::RegisterClient>>(_a[1]))); break;
        case 5: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::ClientDenied>>(_a[1]))); break;
        case 6: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::ClientRegistered>>(_a[1]))); break;
        case 7: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::SetupData>>(_a[1]))); break;
        case 8: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::SetupFailed>>(_a[1]))); break;
        case 9: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::SetupDone>>(_a[1]))); break;
        case 10: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::Login>>(_a[1]))); break;
        case 11: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::LoginFailed>>(_a[1]))); break;
        case 12: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::LoginSuccess>>(_a[1]))); break;
        case 13: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::SessionState>>(_a[1]))); break;
        case 14: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::SyncMessage>>(_a[1]))); break;
        case 15: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::RpcCall>>(_a[1]))); break;
        case 16: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::InitRequest>>(_a[1]))); break;
        case 17: _t->dispatch((*reinterpret_cast< std::add_pointer_t<QuasselProtocol::InitData>>(_a[1]))); break;
        case 18: _t->close((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->close(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::SyncMessage >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::RpcCall >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::InitRequest >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QuasselProtocol::InitData >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Peer::*)()>(_a, &Peer::disconnected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Peer::*)(bool )>(_a, &Peer::secureStateChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Peer::*)(int )>(_a, &Peer::lagUpdated, 3))
            return;
    }
}

const QMetaObject *Peer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Peer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4PeerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Peer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void Peer::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Peer::secureStateChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 3
void Peer::lagUpdated(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
