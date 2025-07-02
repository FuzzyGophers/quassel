/****************************************************************************
** Meta object code from reading C++ file 'dccconfig.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/dccconfig.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dccconfig.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9DccConfigE_t {};
} // unnamed namespace

template <> constexpr inline auto DccConfig::qt_create_metaobjectdata<qt_meta_tag_ZN9DccConfigE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DccConfig",
        "setDccEnabled",
        "",
        "enabled",
        "setOutgoingIp",
        "QHostAddress",
        "outgoingIp",
        "setIpDetectionMode",
        "DccConfig::IpDetectionMode",
        "ipDetectionMode",
        "setPortSelectionMode",
        "DccConfig::PortSelectionMode",
        "portSelectionMode",
        "setMinPort",
        "port",
        "setMaxPort",
        "setChunkSize",
        "chunkSize",
        "setSendTimeout",
        "timeout",
        "setUsePassiveDcc",
        "use",
        "setUseFastSend",
        "dccEnabled",
        "minPort",
        "maxPort",
        "sendTimeout",
        "usePassiveDcc",
        "useFastSend",
        "IpDetectionMode",
        "Automatic",
        "Manual",
        "PortSelectionMode"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'setDccEnabled'
        QtMocHelpers::SlotData<void(bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Slot 'setOutgoingIp'
        QtMocHelpers::SlotData<void(const QHostAddress &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'setIpDetectionMode'
        QtMocHelpers::SlotData<void(DccConfig::IpDetectionMode)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'setPortSelectionMode'
        QtMocHelpers::SlotData<void(DccConfig::PortSelectionMode)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'setMinPort'
        QtMocHelpers::SlotData<void(quint16)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UShort, 14 },
        }}),
        // Slot 'setMaxPort'
        QtMocHelpers::SlotData<void(quint16)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UShort, 14 },
        }}),
        // Slot 'setChunkSize'
        QtMocHelpers::SlotData<void(int)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 17 },
        }}),
        // Slot 'setSendTimeout'
        QtMocHelpers::SlotData<void(int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 19 },
        }}),
        // Slot 'setUsePassiveDcc'
        QtMocHelpers::SlotData<void(bool)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 21 },
        }}),
        // Slot 'setUseFastSend'
        QtMocHelpers::SlotData<void(bool)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 21 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'dccEnabled'
        QtMocHelpers::PropertyData<bool>(23, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'outgoingIp'
        QtMocHelpers::PropertyData<QHostAddress>(6, 0x80000000 | 5, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'ipDetectionMode'
        QtMocHelpers::PropertyData<DccConfig::IpDetectionMode>(9, 0x80000000 | 8, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'portSelectionMode'
        QtMocHelpers::PropertyData<DccConfig::PortSelectionMode>(12, 0x80000000 | 11, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'minPort'
        QtMocHelpers::PropertyData<quint16>(24, QMetaType::UShort, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'maxPort'
        QtMocHelpers::PropertyData<quint16>(25, QMetaType::UShort, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'chunkSize'
        QtMocHelpers::PropertyData<int>(17, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'sendTimeout'
        QtMocHelpers::PropertyData<int>(26, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'usePassiveDcc'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'useFastSend'
        QtMocHelpers::PropertyData<bool>(28, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'IpDetectionMode'
        QtMocHelpers::EnumData<IpDetectionMode>(29, 29, QMC::EnumIsScoped).add({
            {   30, IpDetectionMode::Automatic },
            {   31, IpDetectionMode::Manual },
        }),
        // enum 'PortSelectionMode'
        QtMocHelpers::EnumData<PortSelectionMode>(32, 32, QMC::EnumIsScoped).add({
            {   30, PortSelectionMode::Automatic },
            {   31, PortSelectionMode::Manual },
        }),
    };
    return QtMocHelpers::metaObjectData<DccConfig, qt_meta_tag_ZN9DccConfigE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DccConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9DccConfigE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9DccConfigE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9DccConfigE_t>.metaTypes,
    nullptr
} };

void DccConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DccConfig *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->setDccEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->setOutgoingIp((*reinterpret_cast< std::add_pointer_t<QHostAddress>>(_a[1]))); break;
        case 2: _t->setIpDetectionMode((*reinterpret_cast< std::add_pointer_t<DccConfig::IpDetectionMode>>(_a[1]))); break;
        case 3: _t->setPortSelectionMode((*reinterpret_cast< std::add_pointer_t<DccConfig::PortSelectionMode>>(_a[1]))); break;
        case 4: _t->setMinPort((*reinterpret_cast< std::add_pointer_t<quint16>>(_a[1]))); break;
        case 5: _t->setMaxPort((*reinterpret_cast< std::add_pointer_t<quint16>>(_a[1]))); break;
        case 6: _t->setChunkSize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->setSendTimeout((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->setUsePassiveDcc((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->setUseFastSend((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QHostAddress >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DccConfig::IpDetectionMode >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DccConfig::PortSelectionMode >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DccConfig::IpDetectionMode >(); break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DccConfig::PortSelectionMode >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostAddress >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isDccEnabled(); break;
        case 1: *reinterpret_cast<QHostAddress*>(_v) = _t->outgoingIp(); break;
        case 2: *reinterpret_cast<DccConfig::IpDetectionMode*>(_v) = _t->ipDetectionMode(); break;
        case 3: *reinterpret_cast<DccConfig::PortSelectionMode*>(_v) = _t->portSelectionMode(); break;
        case 4: *reinterpret_cast<quint16*>(_v) = _t->minPort(); break;
        case 5: *reinterpret_cast<quint16*>(_v) = _t->maxPort(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->chunkSize(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->sendTimeout(); break;
        case 8: *reinterpret_cast<bool*>(_v) = _t->usePassiveDcc(); break;
        case 9: *reinterpret_cast<bool*>(_v) = _t->useFastSend(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDccEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 1: _t->setOutgoingIp(*reinterpret_cast<QHostAddress*>(_v)); break;
        case 2: _t->setIpDetectionMode(*reinterpret_cast<DccConfig::IpDetectionMode*>(_v)); break;
        case 3: _t->setPortSelectionMode(*reinterpret_cast<DccConfig::PortSelectionMode*>(_v)); break;
        case 4: _t->setMinPort(*reinterpret_cast<quint16*>(_v)); break;
        case 5: _t->setMaxPort(*reinterpret_cast<quint16*>(_v)); break;
        case 6: _t->setChunkSize(*reinterpret_cast<int*>(_v)); break;
        case 7: _t->setSendTimeout(*reinterpret_cast<int*>(_v)); break;
        case 8: _t->setUsePassiveDcc(*reinterpret_cast<bool*>(_v)); break;
        case 9: _t->setUseFastSend(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DccConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DccConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9DccConfigE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int DccConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
