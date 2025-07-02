/****************************************************************************
** Meta object code from reading C++ file 'networkconfig.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/networkconfig.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkconfig.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13NetworkConfigE_t {};
} // unnamed namespace

template <> constexpr inline auto NetworkConfig::qt_create_metaobjectdata<qt_meta_tag_ZN13NetworkConfigE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NetworkConfig",
        "pingTimeoutEnabledSet",
        "",
        "pingIntervalSet",
        "autoWhoEnabledSet",
        "autoWhoIntervalSet",
        "autoWhoDelaySet",
        "standardCtcpSet",
        "pingTimeoutEnabled",
        "setPingTimeoutEnabled",
        "requestSetPingTimeoutEnabled",
        "b",
        "pingInterval",
        "setPingInterval",
        "requestSetPingInterval",
        "i",
        "maxPingCount",
        "setMaxPingCount",
        "requestSetMaxPingCount",
        "autoWhoEnabled",
        "setAutoWhoEnabled",
        "requestSetAutoWhoEnabled",
        "autoWhoInterval",
        "setAutoWhoInterval",
        "requestSetAutoWhoInterval",
        "autoWhoNickLimit",
        "setAutoWhoNickLimit",
        "requestSetAutoWhoNickLimit",
        "autoWhoDelay",
        "setAutoWhoDelay",
        "requestSetAutoWhoDelay",
        "standardCtcp",
        "setStandardCtcp",
        "requestSetStandardCtcp"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'pingTimeoutEnabledSet'
        QtMocHelpers::SignalData<void(bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Signal 'pingIntervalSet'
        QtMocHelpers::SignalData<void(int)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'autoWhoEnabledSet'
        QtMocHelpers::SignalData<void(bool)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Signal 'autoWhoIntervalSet'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'autoWhoDelaySet'
        QtMocHelpers::SignalData<void(int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'standardCtcpSet'
        QtMocHelpers::SignalData<void(bool)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'pingTimeoutEnabled'
        QtMocHelpers::SlotData<bool() const>(8, 2, QMC::AccessPublic, QMetaType::Bool),
        // Slot 'setPingTimeoutEnabled'
        QtMocHelpers::SlotData<void(bool)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'requestSetPingTimeoutEnabled'
        QtMocHelpers::SlotData<void(bool)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 11 },
        }}),
        // Slot 'pingInterval'
        QtMocHelpers::SlotData<int() const>(12, 2, QMC::AccessPublic, QMetaType::Int),
        // Slot 'setPingInterval'
        QtMocHelpers::SlotData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'requestSetPingInterval'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'maxPingCount'
        QtMocHelpers::SlotData<int() const>(16, 2, QMC::AccessPublic, QMetaType::Int),
        // Slot 'setMaxPingCount'
        QtMocHelpers::SlotData<void(int)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'requestSetMaxPingCount'
        QtMocHelpers::SlotData<void(int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'autoWhoEnabled'
        QtMocHelpers::SlotData<bool() const>(19, 2, QMC::AccessPublic, QMetaType::Bool),
        // Slot 'setAutoWhoEnabled'
        QtMocHelpers::SlotData<void(bool)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'requestSetAutoWhoEnabled'
        QtMocHelpers::SlotData<void(bool)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 11 },
        }}),
        // Slot 'autoWhoInterval'
        QtMocHelpers::SlotData<int() const>(22, 2, QMC::AccessPublic, QMetaType::Int),
        // Slot 'setAutoWhoInterval'
        QtMocHelpers::SlotData<void(int)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'requestSetAutoWhoInterval'
        QtMocHelpers::SlotData<void(int)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'autoWhoNickLimit'
        QtMocHelpers::SlotData<int() const>(25, 2, QMC::AccessPublic, QMetaType::Int),
        // Slot 'setAutoWhoNickLimit'
        QtMocHelpers::SlotData<void(int)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'requestSetAutoWhoNickLimit'
        QtMocHelpers::SlotData<void(int)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'autoWhoDelay'
        QtMocHelpers::SlotData<int() const>(28, 2, QMC::AccessPublic, QMetaType::Int),
        // Slot 'setAutoWhoDelay'
        QtMocHelpers::SlotData<void(int)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'requestSetAutoWhoDelay'
        QtMocHelpers::SlotData<void(int)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'standardCtcp'
        QtMocHelpers::SlotData<bool() const>(31, 2, QMC::AccessPublic, QMetaType::Bool),
        // Slot 'setStandardCtcp'
        QtMocHelpers::SlotData<void(bool)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'requestSetStandardCtcp'
        QtMocHelpers::SlotData<void(bool)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'pingTimeoutEnabled'
        QtMocHelpers::PropertyData<bool>(8, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'pingInterval'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'maxPingCount'
        QtMocHelpers::PropertyData<int>(16, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoWhoEnabled'
        QtMocHelpers::PropertyData<bool>(19, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoWhoInterval'
        QtMocHelpers::PropertyData<int>(22, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoWhoNickLimit'
        QtMocHelpers::PropertyData<int>(25, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoWhoDelay'
        QtMocHelpers::PropertyData<int>(28, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'standardCtcp'
        QtMocHelpers::PropertyData<bool>(31, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NetworkConfig, qt_meta_tag_ZN13NetworkConfigE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NetworkConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NetworkConfigE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NetworkConfigE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13NetworkConfigE_t>.metaTypes,
    nullptr
} };

void NetworkConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NetworkConfig *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->pingTimeoutEnabledSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->pingIntervalSet((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->autoWhoEnabledSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->autoWhoIntervalSet((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->autoWhoDelaySet((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->standardCtcpSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: { bool _r = _t->pingTimeoutEnabled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setPingTimeoutEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->requestSetPingTimeoutEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: { int _r = _t->pingInterval();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->setPingInterval((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->requestSetPingInterval((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: { int _r = _t->maxPingCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->setMaxPingCount((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->requestSetMaxPingCount((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: { bool _r = _t->autoWhoEnabled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->setAutoWhoEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->requestSetAutoWhoEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: { int _r = _t->autoWhoInterval();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->setAutoWhoInterval((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->requestSetAutoWhoInterval((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 21: { int _r = _t->autoWhoNickLimit();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 22: _t->setAutoWhoNickLimit((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 23: _t->requestSetAutoWhoNickLimit((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 24: { int _r = _t->autoWhoDelay();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->setAutoWhoDelay((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 26: _t->requestSetAutoWhoDelay((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 27: { bool _r = _t->standardCtcp();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->setStandardCtcp((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 29: _t->requestSetStandardCtcp((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NetworkConfig::*)(bool )>(_a, &NetworkConfig::pingTimeoutEnabledSet, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkConfig::*)(int )>(_a, &NetworkConfig::pingIntervalSet, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkConfig::*)(bool )>(_a, &NetworkConfig::autoWhoEnabledSet, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkConfig::*)(int )>(_a, &NetworkConfig::autoWhoIntervalSet, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkConfig::*)(int )>(_a, &NetworkConfig::autoWhoDelaySet, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkConfig::*)(bool )>(_a, &NetworkConfig::standardCtcpSet, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->pingTimeoutEnabled(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->pingInterval(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->maxPingCount(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->autoWhoEnabled(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->autoWhoInterval(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->autoWhoNickLimit(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->autoWhoDelay(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->standardCtcp(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPingTimeoutEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 1: _t->setPingInterval(*reinterpret_cast<int*>(_v)); break;
        case 2: _t->setMaxPingCount(*reinterpret_cast<int*>(_v)); break;
        case 3: _t->setAutoWhoEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setAutoWhoInterval(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setAutoWhoNickLimit(*reinterpret_cast<int*>(_v)); break;
        case 6: _t->setAutoWhoDelay(*reinterpret_cast<int*>(_v)); break;
        case 7: _t->setStandardCtcp(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *NetworkConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NetworkConfigE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int NetworkConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 30;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void NetworkConfig::pingTimeoutEnabledSet(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void NetworkConfig::pingIntervalSet(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void NetworkConfig::autoWhoEnabledSet(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void NetworkConfig::autoWhoIntervalSet(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void NetworkConfig::autoWhoDelaySet(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void NetworkConfig::standardCtcpSet(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
