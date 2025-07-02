/****************************************************************************
** Meta object code from reading C++ file 'signalproxy.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/signalproxy.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signalproxy.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11SignalProxyE_t {};
} // unnamed namespace

template <> constexpr inline auto SignalProxy::qt_create_metaobjectdata<qt_meta_tag_ZN11SignalProxyE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SignalProxy",
        "peerRemoved",
        "",
        "Peer*",
        "peer",
        "connected",
        "disconnected",
        "objectInitialized",
        "SyncableObject*",
        "heartBeatIntervalChanged",
        "secs",
        "maxHeartBeatCountChanged",
        "max",
        "lagUpdated",
        "lag",
        "secureStateChanged",
        "removePeerBySender",
        "objectRenamed",
        "classname",
        "newname",
        "oldname",
        "updateSecureState"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'peerRemoved'
        QtMocHelpers::SignalData<void(Peer *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'connected'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'disconnected'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'objectInitialized'
        QtMocHelpers::SignalData<void(SyncableObject *)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 2 },
        }}),
        // Signal 'heartBeatIntervalChanged'
        QtMocHelpers::SignalData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
        // Signal 'maxHeartBeatCountChanged'
        QtMocHelpers::SignalData<void(int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Signal 'lagUpdated'
        QtMocHelpers::SignalData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
        // Signal 'secureStateChanged'
        QtMocHelpers::SignalData<void(bool)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'removePeerBySender'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'objectRenamed'
        QtMocHelpers::SlotData<void(const QByteArray &, const QString &, const QString &)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QByteArray, 18 }, { QMetaType::QString, 19 }, { QMetaType::QString, 20 },
        }}),
        // Slot 'updateSecureState'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SignalProxy, qt_meta_tag_ZN11SignalProxyE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SignalProxy::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SignalProxyE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SignalProxyE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11SignalProxyE_t>.metaTypes,
    nullptr
} };

void SignalProxy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SignalProxy *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->peerRemoved((*reinterpret_cast< std::add_pointer_t<Peer*>>(_a[1]))); break;
        case 1: _t->connected(); break;
        case 2: _t->disconnected(); break;
        case 3: _t->objectInitialized((*reinterpret_cast< std::add_pointer_t<SyncableObject*>>(_a[1]))); break;
        case 4: _t->heartBeatIntervalChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->maxHeartBeatCountChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->lagUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->secureStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->removePeerBySender(); break;
        case 9: _t->objectRenamed((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 10: _t->updateSecureState(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SignalProxy::*)(Peer * )>(_a, &SignalProxy::peerRemoved, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalProxy::*)()>(_a, &SignalProxy::connected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalProxy::*)()>(_a, &SignalProxy::disconnected, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalProxy::*)(SyncableObject * )>(_a, &SignalProxy::objectInitialized, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalProxy::*)(int )>(_a, &SignalProxy::heartBeatIntervalChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalProxy::*)(int )>(_a, &SignalProxy::maxHeartBeatCountChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalProxy::*)(int )>(_a, &SignalProxy::lagUpdated, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalProxy::*)(bool )>(_a, &SignalProxy::secureStateChanged, 7))
            return;
    }
}

const QMetaObject *SignalProxy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SignalProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SignalProxyE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SignalProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SignalProxy::peerRemoved(Peer * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void SignalProxy::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SignalProxy::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SignalProxy::objectInitialized(SyncableObject * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void SignalProxy::heartBeatIntervalChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void SignalProxy::maxHeartBeatCountChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void SignalProxy::lagUpdated(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void SignalProxy::secureStateChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}
QT_WARNING_POP
