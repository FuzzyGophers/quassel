/****************************************************************************
** Meta object code from reading C++ file 'eventmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/eventmanager.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eventmanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12EventManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto EventManager::qt_create_metaobjectdata<qt_meta_tag_ZN12EventManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "EventManager",
        "registerObject",
        "",
        "object",
        "Priority",
        "priority",
        "methodPrefix",
        "filterPrefix",
        "registerEventHandler",
        "EventType",
        "event",
        "const char*",
        "slot",
        "isFilter",
        "QList<EventType>",
        "events",
        "registerEventFilter",
        "postEvent",
        "Event*",
        "EventFlag",
        "Self",
        "Fake",
        "Netsplit",
        "Backlog",
        "Silent",
        "Stopped",
        "EventFlags",
        "Invalid",
        "GenericEvent",
        "EventGroupMask",
        "NetworkEvent",
        "NetworkConnecting",
        "NetworkInitializing",
        "NetworkInitialized",
        "NetworkReconnecting",
        "NetworkDisconnecting",
        "NetworkDisconnected",
        "NetworkSplitJoin",
        "NetworkSplitQuit",
        "NetworkIncoming",
        "IrcServerEvent",
        "IrcServerIncoming",
        "IrcServerParseError",
        "IrcEvent",
        "IrcEventAuthenticate",
        "IrcEventAccount",
        "IrcEventAway",
        "IrcEventCap",
        "IrcEventChghost",
        "IrcEventInvite",
        "IrcEventJoin",
        "IrcEventKick",
        "IrcEventMode",
        "IrcEventNick",
        "IrcEventNotice",
        "IrcEventPart",
        "IrcEventPing",
        "IrcEventPong",
        "IrcEventPrivmsg",
        "IrcEventQuit",
        "IrcEventTagmsg",
        "IrcEventTopic",
        "IrcEventError",
        "IrcEventSetname",
        "IrcEventWallops",
        "IrcEventRawPrivmsg",
        "IrcEventRawNotice",
        "IrcEventUnknown",
        "IrcEventNumeric",
        "IrcEventNumericMask",
        "MessageEvent",
        "CtcpEvent",
        "CtcpEventFlush",
        "KeyEvent"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'registerObject'
        QtMocHelpers::SlotData<void(QObject *, Priority, const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QObjectStar, 3 }, { 0x80000000 | 4, 5 }, { QMetaType::QString, 6 }, { QMetaType::QString, 7 },
        }}),
        // Slot 'registerObject'
        QtMocHelpers::SlotData<void(QObject *, Priority, const QString &)>(1, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QObjectStar, 3 }, { 0x80000000 | 4, 5 }, { QMetaType::QString, 6 },
        }}),
        // Slot 'registerObject'
        QtMocHelpers::SlotData<void(QObject *, Priority)>(1, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QObjectStar, 3 }, { 0x80000000 | 4, 5 },
        }}),
        // Slot 'registerObject'
        QtMocHelpers::SlotData<void(QObject *)>(1, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QObjectStar, 3 },
        }}),
        // Slot 'registerEventHandler'
        QtMocHelpers::SlotData<void(EventType, QObject *, const char *, Priority, bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 }, { QMetaType::QObjectStar, 3 }, { 0x80000000 | 11, 12 }, { 0x80000000 | 4, 5 },
            { QMetaType::Bool, 13 },
        }}),
        // Slot 'registerEventHandler'
        QtMocHelpers::SlotData<void(EventType, QObject *, const char *, Priority)>(8, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { 0x80000000 | 9, 10 }, { QMetaType::QObjectStar, 3 }, { 0x80000000 | 11, 12 }, { 0x80000000 | 4, 5 },
        }}),
        // Slot 'registerEventHandler'
        QtMocHelpers::SlotData<void(EventType, QObject *, const char *)>(8, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { 0x80000000 | 9, 10 }, { QMetaType::QObjectStar, 3 }, { 0x80000000 | 11, 12 },
        }}),
        // Slot 'registerEventHandler'
        QtMocHelpers::SlotData<void(QList<EventType>, QObject *, const char *, Priority, bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { QMetaType::QObjectStar, 3 }, { 0x80000000 | 11, 12 }, { 0x80000000 | 4, 5 },
            { QMetaType::Bool, 13 },
        }}),
        // Slot 'registerEventHandler'
        QtMocHelpers::SlotData<void(QList<EventType>, QObject *, const char *, Priority)>(8, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { QMetaType::QObjectStar, 3 }, { 0x80000000 | 11, 12 }, { 0x80000000 | 4, 5 },
        }}),
        // Slot 'registerEventHandler'
        QtMocHelpers::SlotData<void(QList<EventType>, QObject *, const char *)>(8, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { QMetaType::QObjectStar, 3 }, { 0x80000000 | 11, 12 },
        }}),
        // Slot 'registerEventFilter'
        QtMocHelpers::SlotData<void(EventType, QObject *, const char *)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 }, { QMetaType::QObjectStar, 3 }, { 0x80000000 | 11, 12 },
        }}),
        // Slot 'registerEventFilter'
        QtMocHelpers::SlotData<void(QList<EventType>, QObject *, const char *)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { QMetaType::QObjectStar, 3 }, { 0x80000000 | 11, 12 },
        }}),
        // Slot 'postEvent'
        QtMocHelpers::SlotData<void(Event *)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 18, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'EventFlag'
        QtMocHelpers::EnumData<EventFlag>(19, 19, QMC::EnumFlags{}).add({
            {   20, EventFlag::Self },
            {   21, EventFlag::Fake },
            {   22, EventFlag::Netsplit },
            {   23, EventFlag::Backlog },
            {   24, EventFlag::Silent },
            {   25, EventFlag::Stopped },
        }),
        // enum 'EventFlags'
        QtMocHelpers::EnumData<EventFlags>(26, 19, QMC::EnumFlags{}).add({
            {   20, EventFlag::Self },
            {   21, EventFlag::Fake },
            {   22, EventFlag::Netsplit },
            {   23, EventFlag::Backlog },
            {   24, EventFlag::Silent },
            {   25, EventFlag::Stopped },
        }),
        // enum 'EventType'
        QtMocHelpers::EnumData<EventType>(9, 9, QMC::EnumFlags{}).add({
            {   27, EventType::Invalid },
            {   28, EventType::GenericEvent },
            {   29, EventType::EventGroupMask },
            {   30, EventType::NetworkEvent },
            {   31, EventType::NetworkConnecting },
            {   32, EventType::NetworkInitializing },
            {   33, EventType::NetworkInitialized },
            {   34, EventType::NetworkReconnecting },
            {   35, EventType::NetworkDisconnecting },
            {   36, EventType::NetworkDisconnected },
            {   37, EventType::NetworkSplitJoin },
            {   38, EventType::NetworkSplitQuit },
            {   39, EventType::NetworkIncoming },
            {   40, EventType::IrcServerEvent },
            {   41, EventType::IrcServerIncoming },
            {   42, EventType::IrcServerParseError },
            {   43, EventType::IrcEvent },
            {   44, EventType::IrcEventAuthenticate },
            {   45, EventType::IrcEventAccount },
            {   46, EventType::IrcEventAway },
            {   47, EventType::IrcEventCap },
            {   48, EventType::IrcEventChghost },
            {   49, EventType::IrcEventInvite },
            {   50, EventType::IrcEventJoin },
            {   51, EventType::IrcEventKick },
            {   52, EventType::IrcEventMode },
            {   53, EventType::IrcEventNick },
            {   54, EventType::IrcEventNotice },
            {   55, EventType::IrcEventPart },
            {   56, EventType::IrcEventPing },
            {   57, EventType::IrcEventPong },
            {   58, EventType::IrcEventPrivmsg },
            {   59, EventType::IrcEventQuit },
            {   60, EventType::IrcEventTagmsg },
            {   61, EventType::IrcEventTopic },
            {   62, EventType::IrcEventError },
            {   63, EventType::IrcEventSetname },
            {   64, EventType::IrcEventWallops },
            {   65, EventType::IrcEventRawPrivmsg },
            {   66, EventType::IrcEventRawNotice },
            {   67, EventType::IrcEventUnknown },
            {   68, EventType::IrcEventNumeric },
            {   69, EventType::IrcEventNumericMask },
            {   70, EventType::MessageEvent },
            {   71, EventType::CtcpEvent },
            {   72, EventType::CtcpEventFlush },
            {   73, EventType::KeyEvent },
        }),
    };
    return QtMocHelpers::metaObjectData<EventManager, qt_meta_tag_ZN12EventManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject EventManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12EventManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12EventManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12EventManagerE_t>.metaTypes,
    nullptr
} };

void EventManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EventManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->registerObject((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Priority>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 1: _t->registerObject((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Priority>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 2: _t->registerObject((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Priority>>(_a[2]))); break;
        case 3: _t->registerObject((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1]))); break;
        case 4: _t->registerEventHandler((*reinterpret_cast< std::add_pointer_t<EventType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<Priority>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5]))); break;
        case 5: _t->registerEventHandler((*reinterpret_cast< std::add_pointer_t<EventType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<Priority>>(_a[4]))); break;
        case 6: _t->registerEventHandler((*reinterpret_cast< std::add_pointer_t<EventType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3]))); break;
        case 7: _t->registerEventHandler((*reinterpret_cast< std::add_pointer_t<QList<EventType>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<Priority>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5]))); break;
        case 8: _t->registerEventHandler((*reinterpret_cast< std::add_pointer_t<QList<EventType>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<Priority>>(_a[4]))); break;
        case 9: _t->registerEventHandler((*reinterpret_cast< std::add_pointer_t<QList<EventType>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3]))); break;
        case 10: _t->registerEventFilter((*reinterpret_cast< std::add_pointer_t<EventType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3]))); break;
        case 11: _t->registerEventFilter((*reinterpret_cast< std::add_pointer_t<QList<EventType>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3]))); break;
        case 12: _t->postEvent((*reinterpret_cast< std::add_pointer_t<Event*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *EventManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EventManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12EventManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EventManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
