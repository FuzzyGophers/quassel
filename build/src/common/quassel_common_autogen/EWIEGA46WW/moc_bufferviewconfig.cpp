/****************************************************************************
** Meta object code from reading C++ file 'bufferviewconfig.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/bufferviewconfig.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bufferviewconfig.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16BufferViewConfigE_t {};
} // unnamed namespace

template <> constexpr inline auto BufferViewConfig::qt_create_metaobjectdata<qt_meta_tag_ZN16BufferViewConfigE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BufferViewConfig",
        "configChanged",
        "",
        "bufferViewNameSet",
        "bufferViewName",
        "networkIdSet",
        "NetworkId",
        "networkId",
        "bufferListSet",
        "bufferAdded",
        "BufferId",
        "bufferId",
        "pos",
        "bufferMoved",
        "bufferRemoved",
        "bufferPermanentlyRemoved",
        "initBufferList",
        "QVariantList",
        "initSetBufferList",
        "buffers",
        "initRemovedBuffers",
        "initSetRemovedBuffers",
        "initTemporarilyRemovedBuffers",
        "initSetTemporarilyRemovedBuffers",
        "setBufferViewName",
        "setNetworkId",
        "setAddNewBuffersAutomatically",
        "addNewBuffersAutomatically",
        "setSortAlphabetically",
        "sortAlphabetically",
        "setDisableDecoration",
        "disableDecoration",
        "setAllowedBufferTypes",
        "bufferTypes",
        "setMinimumActivity",
        "activity",
        "setHideInactiveBuffers",
        "hideInactiveBuffers",
        "setHideInactiveNetworks",
        "hideInactiveNetworks",
        "setShowSearch",
        "showSearch",
        "setBufferList",
        "QList<BufferId>",
        "addBuffer",
        "moveBuffer",
        "removeBuffer",
        "removeBufferPermanently",
        "requestSetBufferViewName",
        "requestAddBuffer",
        "requestMoveBuffer",
        "requestRemoveBuffer",
        "requestRemoveBufferPermanently",
        "allowedBufferTypes",
        "minimumActivity"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'configChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bufferViewNameSet'
        QtMocHelpers::SignalData<void(const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Signal 'networkIdSet'
        QtMocHelpers::SignalData<void(const NetworkId &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Signal 'bufferListSet'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bufferAdded'
        QtMocHelpers::SignalData<void(const BufferId &, int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::Int, 12 },
        }}),
        // Signal 'bufferMoved'
        QtMocHelpers::SignalData<void(const BufferId &, int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::Int, 12 },
        }}),
        // Signal 'bufferRemoved'
        QtMocHelpers::SignalData<void(const BufferId &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Signal 'bufferPermanentlyRemoved'
        QtMocHelpers::SignalData<void(const BufferId &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'initBufferList'
        QtMocHelpers::SlotData<QVariantList() const>(16, 2, QMC::AccessPublic, 0x80000000 | 17),
        // Slot 'initSetBufferList'
        QtMocHelpers::SlotData<void(const QVariantList &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 19 },
        }}),
        // Slot 'initRemovedBuffers'
        QtMocHelpers::SlotData<QVariantList() const>(20, 2, QMC::AccessPublic, 0x80000000 | 17),
        // Slot 'initSetRemovedBuffers'
        QtMocHelpers::SlotData<void(const QVariantList &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 19 },
        }}),
        // Slot 'initTemporarilyRemovedBuffers'
        QtMocHelpers::SlotData<QVariantList() const>(22, 2, QMC::AccessPublic, 0x80000000 | 17),
        // Slot 'initSetTemporarilyRemovedBuffers'
        QtMocHelpers::SlotData<void(const QVariantList &)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 19 },
        }}),
        // Slot 'setBufferViewName'
        QtMocHelpers::SlotData<void(const QString &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Slot 'setNetworkId'
        QtMocHelpers::SlotData<void(const NetworkId &)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'setAddNewBuffersAutomatically'
        QtMocHelpers::SlotData<void(bool)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 27 },
        }}),
        // Slot 'setSortAlphabetically'
        QtMocHelpers::SlotData<void(bool)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 29 },
        }}),
        // Slot 'setDisableDecoration'
        QtMocHelpers::SlotData<void(bool)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 31 },
        }}),
        // Slot 'setAllowedBufferTypes'
        QtMocHelpers::SlotData<void(int)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 33 },
        }}),
        // Slot 'setMinimumActivity'
        QtMocHelpers::SlotData<void(int)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 35 },
        }}),
        // Slot 'setHideInactiveBuffers'
        QtMocHelpers::SlotData<void(bool)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 37 },
        }}),
        // Slot 'setHideInactiveNetworks'
        QtMocHelpers::SlotData<void(bool)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 39 },
        }}),
        // Slot 'setShowSearch'
        QtMocHelpers::SlotData<void(bool)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 41 },
        }}),
        // Slot 'setBufferList'
        QtMocHelpers::SlotData<void(const QList<BufferId> &)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 43, 19 },
        }}),
        // Slot 'addBuffer'
        QtMocHelpers::SlotData<void(const BufferId &, int)>(44, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::Int, 12 },
        }}),
        // Slot 'moveBuffer'
        QtMocHelpers::SlotData<void(const BufferId &, int)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::Int, 12 },
        }}),
        // Slot 'removeBuffer'
        QtMocHelpers::SlotData<void(const BufferId &)>(46, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'removeBufferPermanently'
        QtMocHelpers::SlotData<void(const BufferId &)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'requestSetBufferViewName'
        QtMocHelpers::SlotData<void(const QString &)>(48, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Slot 'requestAddBuffer'
        QtMocHelpers::SlotData<void(const BufferId &, int)>(49, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::Int, 12 },
        }}),
        // Slot 'requestMoveBuffer'
        QtMocHelpers::SlotData<void(const BufferId &, int)>(50, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::Int, 12 },
        }}),
        // Slot 'requestRemoveBuffer'
        QtMocHelpers::SlotData<void(const BufferId &)>(51, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'requestRemoveBufferPermanently'
        QtMocHelpers::SlotData<void(const BufferId &)>(52, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'bufferViewName'
        QtMocHelpers::PropertyData<QString>(4, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'networkId'
        QtMocHelpers::PropertyData<NetworkId>(7, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'addNewBuffersAutomatically'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'sortAlphabetically'
        QtMocHelpers::PropertyData<bool>(29, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'hideInactiveBuffers'
        QtMocHelpers::PropertyData<bool>(37, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'hideInactiveNetworks'
        QtMocHelpers::PropertyData<bool>(39, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'disableDecoration'
        QtMocHelpers::PropertyData<bool>(31, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'allowedBufferTypes'
        QtMocHelpers::PropertyData<int>(53, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'minimumActivity'
        QtMocHelpers::PropertyData<int>(54, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'showSearch'
        QtMocHelpers::PropertyData<bool>(41, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BufferViewConfig, qt_meta_tag_ZN16BufferViewConfigE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BufferViewConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16BufferViewConfigE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16BufferViewConfigE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16BufferViewConfigE_t>.metaTypes,
    nullptr
} };

void BufferViewConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BufferViewConfig *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->configChanged(); break;
        case 1: _t->bufferViewNameSet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->networkIdSet((*reinterpret_cast< std::add_pointer_t<NetworkId>>(_a[1]))); break;
        case 3: _t->bufferListSet(); break;
        case 4: _t->bufferAdded((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->bufferMoved((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->bufferRemoved((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 7: _t->bufferPermanentlyRemoved((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 8: { QVariantList _r = _t->initBufferList();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->initSetBufferList((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 10: { QVariantList _r = _t->initRemovedBuffers();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->initSetRemovedBuffers((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 12: { QVariantList _r = _t->initTemporarilyRemovedBuffers();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->initSetTemporarilyRemovedBuffers((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 14: _t->setBufferViewName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->setNetworkId((*reinterpret_cast< std::add_pointer_t<NetworkId>>(_a[1]))); break;
        case 16: _t->setAddNewBuffersAutomatically((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->setSortAlphabetically((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: _t->setDisableDecoration((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 19: _t->setAllowedBufferTypes((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->setMinimumActivity((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 21: _t->setHideInactiveBuffers((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: _t->setHideInactiveNetworks((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 23: _t->setShowSearch((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 24: _t->setBufferList((*reinterpret_cast< std::add_pointer_t<QList<BufferId>>>(_a[1]))); break;
        case 25: _t->addBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 26: _t->moveBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 27: _t->removeBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 28: _t->removeBufferPermanently((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 29: _t->requestSetBufferViewName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 30: _t->requestAddBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 31: _t->requestMoveBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 32: _t->requestRemoveBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 33: _t->requestRemoveBufferPermanently((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< NetworkId >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< NetworkId >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<BufferId> >(); break;
            }
            break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 26:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 27:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 28:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 30:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 31:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 33:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BufferViewConfig::*)()>(_a, &BufferViewConfig::configChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferViewConfig::*)(const QString & )>(_a, &BufferViewConfig::bufferViewNameSet, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferViewConfig::*)(const NetworkId & )>(_a, &BufferViewConfig::networkIdSet, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferViewConfig::*)()>(_a, &BufferViewConfig::bufferListSet, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferViewConfig::*)(const BufferId & , int )>(_a, &BufferViewConfig::bufferAdded, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferViewConfig::*)(const BufferId & , int )>(_a, &BufferViewConfig::bufferMoved, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferViewConfig::*)(const BufferId & )>(_a, &BufferViewConfig::bufferRemoved, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferViewConfig::*)(const BufferId & )>(_a, &BufferViewConfig::bufferPermanentlyRemoved, 7))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NetworkId >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->bufferViewName(); break;
        case 1: *reinterpret_cast<NetworkId*>(_v) = _t->networkId(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->addNewBuffersAutomatically(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->sortAlphabetically(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->hideInactiveBuffers(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->hideInactiveNetworks(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->disableDecoration(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->allowedBufferTypes(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->minimumActivity(); break;
        case 9: *reinterpret_cast<bool*>(_v) = _t->showSearch(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBufferViewName(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setNetworkId(*reinterpret_cast<NetworkId*>(_v)); break;
        case 2: _t->setAddNewBuffersAutomatically(*reinterpret_cast<bool*>(_v)); break;
        case 3: _t->setSortAlphabetically(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setHideInactiveBuffers(*reinterpret_cast<bool*>(_v)); break;
        case 5: _t->setHideInactiveNetworks(*reinterpret_cast<bool*>(_v)); break;
        case 6: _t->setDisableDecoration(*reinterpret_cast<bool*>(_v)); break;
        case 7: _t->setAllowedBufferTypes(*reinterpret_cast<int*>(_v)); break;
        case 8: _t->setMinimumActivity(*reinterpret_cast<int*>(_v)); break;
        case 9: _t->setShowSearch(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *BufferViewConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BufferViewConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16BufferViewConfigE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int BufferViewConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void BufferViewConfig::configChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BufferViewConfig::bufferViewNameSet(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void BufferViewConfig::networkIdSet(const NetworkId & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void BufferViewConfig::bufferListSet()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BufferViewConfig::bufferAdded(const BufferId & _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void BufferViewConfig::bufferMoved(const BufferId & _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void BufferViewConfig::bufferRemoved(const BufferId & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void BufferViewConfig::bufferPermanentlyRemoved(const BufferId & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}
QT_WARNING_POP
