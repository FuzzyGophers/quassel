/****************************************************************************
** Meta object code from reading C++ file 'backlogmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/backlogmanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backlogmanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14BacklogManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto BacklogManager::qt_create_metaobjectdata<qt_meta_tag_ZN14BacklogManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BacklogManager",
        "backlogRequested",
        "",
        "BufferId",
        "MsgId",
        "backlogAllRequested",
        "requestBacklog",
        "QVariantList",
        "bufferId",
        "first",
        "last",
        "limit",
        "additional",
        "requestBacklogFiltered",
        "type",
        "flags",
        "requestBacklogForward",
        "receiveBacklog",
        "receiveBacklogFiltered",
        "receiveBacklogForward",
        "requestBacklogAll",
        "requestBacklogAllFiltered",
        "receiveBacklogAll",
        "receiveBacklogAllFiltered"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'backlogRequested'
        QtMocHelpers::SignalData<void(BufferId, MsgId, MsgId, int, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 4, 2 }, { 0x80000000 | 4, 2 }, { QMetaType::Int, 2 },
            { QMetaType::Int, 2 },
        }}),
        // Signal 'backlogAllRequested'
        QtMocHelpers::SignalData<void(MsgId, MsgId, int, int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 2 }, { 0x80000000 | 4, 2 }, { QMetaType::Int, 2 }, { QMetaType::Int, 2 },
        }}),
        // Slot 'requestBacklog'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int, int)>(6, 2, QMC::AccessPublic, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
            { QMetaType::Int, 12 },
        }}),
        // Slot 'requestBacklog'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int)>(6, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
        }}),
        // Slot 'requestBacklog'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId)>(6, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 },
        }}),
        // Slot 'requestBacklog'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId)>(6, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 },
        }}),
        // Slot 'requestBacklog'
        QtMocHelpers::SlotData<QVariantList(BufferId)>(6, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 },
        }}),
        // Slot 'requestBacklogFiltered'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int, int, int, int)>(13, 2, QMC::AccessPublic, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
            { QMetaType::Int, 12 }, { QMetaType::Int, 14 }, { QMetaType::Int, 15 },
        }}),
        // Slot 'requestBacklogFiltered'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int, int, int)>(13, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
            { QMetaType::Int, 12 }, { QMetaType::Int, 14 },
        }}),
        // Slot 'requestBacklogFiltered'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int, int)>(13, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
            { QMetaType::Int, 12 },
        }}),
        // Slot 'requestBacklogFiltered'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int)>(13, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
        }}),
        // Slot 'requestBacklogFiltered'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId)>(13, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 },
        }}),
        // Slot 'requestBacklogFiltered'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId)>(13, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 },
        }}),
        // Slot 'requestBacklogFiltered'
        QtMocHelpers::SlotData<QVariantList(BufferId)>(13, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 },
        }}),
        // Slot 'requestBacklogForward'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int, int, int)>(16, 2, QMC::AccessPublic, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
            { QMetaType::Int, 14 }, { QMetaType::Int, 15 },
        }}),
        // Slot 'requestBacklogForward'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int, int)>(16, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
            { QMetaType::Int, 14 },
        }}),
        // Slot 'requestBacklogForward'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId, int)>(16, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
        }}),
        // Slot 'requestBacklogForward'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId, MsgId)>(16, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 },
        }}),
        // Slot 'requestBacklogForward'
        QtMocHelpers::SlotData<QVariantList(BufferId, MsgId)>(16, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 }, { 0x80000000 | 4, 9 },
        }}),
        // Slot 'requestBacklogForward'
        QtMocHelpers::SlotData<QVariantList(BufferId)>(16, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 3, 8 },
        }}),
        // Slot 'receiveBacklog'
        QtMocHelpers::SlotData<void(BufferId, MsgId, MsgId, int, int, QVariantList)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 4, 2 }, { 0x80000000 | 4, 2 }, { QMetaType::Int, 2 },
            { QMetaType::Int, 2 }, { 0x80000000 | 7, 2 },
        }}),
        // Slot 'receiveBacklogFiltered'
        QtMocHelpers::SlotData<void(BufferId, MsgId, MsgId, int, int, int, int, QVariantList)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 4, 2 }, { 0x80000000 | 4, 2 }, { QMetaType::Int, 2 },
            { QMetaType::Int, 2 }, { QMetaType::Int, 2 }, { QMetaType::Int, 2 }, { 0x80000000 | 7, 2 },
        }}),
        // Slot 'receiveBacklogForward'
        QtMocHelpers::SlotData<void(BufferId, MsgId, MsgId, int, int, int, QVariantList)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 4, 2 }, { 0x80000000 | 4, 2 }, { QMetaType::Int, 2 },
            { QMetaType::Int, 2 }, { QMetaType::Int, 2 }, { 0x80000000 | 7, 2 },
        }}),
        // Slot 'requestBacklogAll'
        QtMocHelpers::SlotData<QVariantList(MsgId, MsgId, int, int)>(20, 2, QMC::AccessPublic, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
        }}),
        // Slot 'requestBacklogAll'
        QtMocHelpers::SlotData<QVariantList(MsgId, MsgId, int)>(20, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
        }}),
        // Slot 'requestBacklogAll'
        QtMocHelpers::SlotData<QVariantList(MsgId, MsgId)>(20, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 },
        }}),
        // Slot 'requestBacklogAll'
        QtMocHelpers::SlotData<QVariantList(MsgId)>(20, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 },
        }}),
        // Slot 'requestBacklogAll'
        QtMocHelpers::SlotData<QVariantList()>(20, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7),
        // Slot 'requestBacklogAllFiltered'
        QtMocHelpers::SlotData<QVariantList(MsgId, MsgId, int, int, int, int)>(21, 2, QMC::AccessPublic, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
            { QMetaType::Int, 14 }, { QMetaType::Int, 15 },
        }}),
        // Slot 'requestBacklogAllFiltered'
        QtMocHelpers::SlotData<QVariantList(MsgId, MsgId, int, int, int)>(21, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
            { QMetaType::Int, 14 },
        }}),
        // Slot 'requestBacklogAllFiltered'
        QtMocHelpers::SlotData<QVariantList(MsgId, MsgId, int, int)>(21, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
        }}),
        // Slot 'requestBacklogAllFiltered'
        QtMocHelpers::SlotData<QVariantList(MsgId, MsgId, int)>(21, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 }, { QMetaType::Int, 11 },
        }}),
        // Slot 'requestBacklogAllFiltered'
        QtMocHelpers::SlotData<QVariantList(MsgId, MsgId)>(21, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 }, { 0x80000000 | 4, 10 },
        }}),
        // Slot 'requestBacklogAllFiltered'
        QtMocHelpers::SlotData<QVariantList(MsgId)>(21, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7, {{
            { 0x80000000 | 4, 9 },
        }}),
        // Slot 'requestBacklogAllFiltered'
        QtMocHelpers::SlotData<QVariantList()>(21, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 7),
        // Slot 'receiveBacklogAll'
        QtMocHelpers::SlotData<void(MsgId, MsgId, int, int, QVariantList)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 2 }, { 0x80000000 | 4, 2 }, { QMetaType::Int, 2 }, { QMetaType::Int, 2 },
            { 0x80000000 | 7, 2 },
        }}),
        // Slot 'receiveBacklogAllFiltered'
        QtMocHelpers::SlotData<void(MsgId, MsgId, int, int, int, int, QVariantList)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 2 }, { 0x80000000 | 4, 2 }, { QMetaType::Int, 2 }, { QMetaType::Int, 2 },
            { QMetaType::Int, 2 }, { QMetaType::Int, 2 }, { 0x80000000 | 7, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BacklogManager, qt_meta_tag_ZN14BacklogManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BacklogManager::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14BacklogManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14BacklogManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14BacklogManagerE_t>.metaTypes,
    nullptr
} };

void BacklogManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BacklogManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->backlogRequested((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 1: _t->backlogAllRequested((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 2: { QVariantList _r = _t->requestBacklog((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariantList _r = _t->requestBacklog((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariantList _r = _t->requestBacklog((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariantList _r = _t->requestBacklog((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: { QVariantList _r = _t->requestBacklog((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantList _r = _t->requestBacklogFiltered((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[7])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantList _r = _t->requestBacklogFiltered((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantList _r = _t->requestBacklogFiltered((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->requestBacklogFiltered((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantList _r = _t->requestBacklogFiltered((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantList _r = _t->requestBacklogFiltered((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: { QVariantList _r = _t->requestBacklogFiltered((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 14: { QVariantList _r = _t->requestBacklogForward((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 15: { QVariantList _r = _t->requestBacklogForward((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 16: { QVariantList _r = _t->requestBacklogForward((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 17: { QVariantList _r = _t->requestBacklogForward((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantList _r = _t->requestBacklogForward((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 19: { QVariantList _r = _t->requestBacklogForward((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 20: _t->receiveBacklog((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[6]))); break;
        case 21: _t->receiveBacklogFiltered((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[8]))); break;
        case 22: _t->receiveBacklogForward((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[7]))); break;
        case 23: { QVariantList _r = _t->requestBacklogAll((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 24: { QVariantList _r = _t->requestBacklogAll((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 25: { QVariantList _r = _t->requestBacklogAll((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 26: { QVariantList _r = _t->requestBacklogAll((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 27: { QVariantList _r = _t->requestBacklogAll();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 28: { QVariantList _r = _t->requestBacklogAllFiltered((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 29: { QVariantList _r = _t->requestBacklogAllFiltered((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 30: { QVariantList _r = _t->requestBacklogAllFiltered((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 31: { QVariantList _r = _t->requestBacklogAllFiltered((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 32: { QVariantList _r = _t->requestBacklogAllFiltered((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 33: { QVariantList _r = _t->requestBacklogAllFiltered((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 34: { QVariantList _r = _t->requestBacklogAllFiltered();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 35: _t->receiveBacklogAll((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[5]))); break;
        case 36: _t->receiveBacklogAllFiltered((*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[7]))); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
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
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 26:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 28:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 29:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 30:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 31:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 33:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 35:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 36:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BacklogManager::*)(BufferId , MsgId , MsgId , int , int )>(_a, &BacklogManager::backlogRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BacklogManager::*)(MsgId , MsgId , int , int )>(_a, &BacklogManager::backlogAllRequested, 1))
            return;
    }
}

const QMetaObject *BacklogManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BacklogManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14BacklogManagerE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int BacklogManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void BacklogManager::backlogRequested(BufferId _t1, MsgId _t2, MsgId _t3, int _t4, int _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3, _t4, _t5);
}

// SIGNAL 1
void BacklogManager::backlogAllRequested(MsgId _t1, MsgId _t2, int _t3, int _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3, _t4);
}
QT_WARNING_POP
