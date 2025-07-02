/****************************************************************************
** Meta object code from reading C++ file 'ircuser.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/ircuser.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ircuser.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7IrcUserE_t {};
} // unnamed namespace

template <> constexpr inline auto IrcUser::qt_create_metaobjectdata<qt_meta_tag_ZN7IrcUserE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "IrcUser",
        "nickSet",
        "",
        "newnick",
        "awaySet",
        "away",
        "encryptedSet",
        "encrypted",
        "userModesSet",
        "modes",
        "userModesAdded",
        "userModesRemoved",
        "channelParted",
        "channel",
        "quited",
        "lastChannelActivityUpdated",
        "BufferId",
        "id",
        "newTime",
        "lastSpokenToUpdated",
        "setUser",
        "user",
        "setHost",
        "host",
        "setNick",
        "nick",
        "setRealName",
        "realName",
        "setAccount",
        "account",
        "setAway",
        "setAwayMessage",
        "awayMessage",
        "setIdleTime",
        "idleTime",
        "setLoginTime",
        "loginTime",
        "setServer",
        "server",
        "setIrcOperator",
        "ircOperator",
        "setLastAwayMessage",
        "lastAwayMessage",
        "setLastAwayMessageTime",
        "lastAwayMessageTime",
        "setWhoisServiceReply",
        "whoisServiceReply",
        "setSuserHost",
        "suserHost",
        "setEncrypted",
        "updateHostmask",
        "mask",
        "setUserModes",
        "joinChannel",
        "IrcChannel*",
        "skip_channel_join",
        "channelname",
        "partChannel",
        "quit",
        "addUserModes",
        "removeUserModes",
        "updateObjectName",
        "channelDestroyed",
        "channels",
        "userModes"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'nickSet'
        QtMocHelpers::SignalData<void(QString)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'awaySet'
        QtMocHelpers::SignalData<void(bool)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Signal 'encryptedSet'
        QtMocHelpers::SignalData<void(bool)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 7 },
        }}),
        // Signal 'userModesSet'
        QtMocHelpers::SignalData<void(QString)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Signal 'userModesAdded'
        QtMocHelpers::SignalData<void(QString)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Signal 'userModesRemoved'
        QtMocHelpers::SignalData<void(QString)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Signal 'channelParted'
        QtMocHelpers::SignalData<void(QString)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Signal 'quited'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lastChannelActivityUpdated'
        QtMocHelpers::SignalData<void(BufferId, const QDateTime &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 17 }, { QMetaType::QDateTime, 18 },
        }}),
        // Signal 'lastSpokenToUpdated'
        QtMocHelpers::SignalData<void(BufferId, const QDateTime &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 17 }, { QMetaType::QDateTime, 18 },
        }}),
        // Slot 'setUser'
        QtMocHelpers::SlotData<void(const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 21 },
        }}),
        // Slot 'setHost'
        QtMocHelpers::SlotData<void(const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 23 },
        }}),
        // Slot 'setNick'
        QtMocHelpers::SlotData<void(const QString &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 25 },
        }}),
        // Slot 'setRealName'
        QtMocHelpers::SlotData<void(const QString &)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Slot 'setAccount'
        QtMocHelpers::SlotData<void(const QString &)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 29 },
        }}),
        // Slot 'setAway'
        QtMocHelpers::SlotData<void(bool)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Slot 'setAwayMessage'
        QtMocHelpers::SlotData<void(const QString &)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 32 },
        }}),
        // Slot 'setIdleTime'
        QtMocHelpers::SlotData<void(const QDateTime &)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QDateTime, 34 },
        }}),
        // Slot 'setLoginTime'
        QtMocHelpers::SlotData<void(const QDateTime &)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QDateTime, 36 },
        }}),
        // Slot 'setServer'
        QtMocHelpers::SlotData<void(const QString &)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 38 },
        }}),
        // Slot 'setIrcOperator'
        QtMocHelpers::SlotData<void(const QString &)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 40 },
        }}),
        // Slot 'setLastAwayMessage'
        QtMocHelpers::SlotData<void(int)>(41, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 42 },
        }}),
        // Slot 'setLastAwayMessageTime'
        QtMocHelpers::SlotData<void(const QDateTime &)>(43, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QDateTime, 44 },
        }}),
        // Slot 'setWhoisServiceReply'
        QtMocHelpers::SlotData<void(const QString &)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 46 },
        }}),
        // Slot 'setSuserHost'
        QtMocHelpers::SlotData<void(const QString &)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 48 },
        }}),
        // Slot 'setEncrypted'
        QtMocHelpers::SlotData<void(bool)>(49, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 7 },
        }}),
        // Slot 'updateHostmask'
        QtMocHelpers::SlotData<void(const QString &)>(50, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 51 },
        }}),
        // Slot 'setUserModes'
        QtMocHelpers::SlotData<void(const QString &)>(52, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'joinChannel'
        QtMocHelpers::SlotData<void(IrcChannel *, bool)>(53, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 54, 13 }, { QMetaType::Bool, 55 },
        }}),
        // Slot 'joinChannel'
        QtMocHelpers::SlotData<void(IrcChannel *)>(53, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { 0x80000000 | 54, 13 },
        }}),
        // Slot 'joinChannel'
        QtMocHelpers::SlotData<void(const QString &)>(53, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 56 },
        }}),
        // Slot 'partChannel'
        QtMocHelpers::SlotData<void(IrcChannel *)>(57, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 54, 13 },
        }}),
        // Slot 'partChannel'
        QtMocHelpers::SlotData<void(const QString &)>(57, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 56 },
        }}),
        // Slot 'quit'
        QtMocHelpers::SlotData<void()>(58, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'addUserModes'
        QtMocHelpers::SlotData<void(const QString &)>(59, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'removeUserModes'
        QtMocHelpers::SlotData<void(const QString &)>(60, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'updateObjectName'
        QtMocHelpers::SlotData<void()>(61, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'channelDestroyed'
        QtMocHelpers::SlotData<void()>(62, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'user'
        QtMocHelpers::PropertyData<QString>(21, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'host'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'nick'
        QtMocHelpers::PropertyData<QString>(25, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'realName'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'account'
        QtMocHelpers::PropertyData<QString>(29, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'away'
        QtMocHelpers::PropertyData<bool>(5, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'awayMessage'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'idleTime'
        QtMocHelpers::PropertyData<QDateTime>(34, QMetaType::QDateTime, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'loginTime'
        QtMocHelpers::PropertyData<QDateTime>(36, QMetaType::QDateTime, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'server'
        QtMocHelpers::PropertyData<QString>(38, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'ircOperator'
        QtMocHelpers::PropertyData<QString>(40, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'lastAwayMessageTime'
        QtMocHelpers::PropertyData<QDateTime>(44, QMetaType::QDateTime, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'whoisServiceReply'
        QtMocHelpers::PropertyData<QString>(46, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'suserHost'
        QtMocHelpers::PropertyData<QString>(48, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'encrypted'
        QtMocHelpers::PropertyData<bool>(7, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'channels'
        QtMocHelpers::PropertyData<QStringList>(63, QMetaType::QStringList, QMC::DefaultPropertyFlags),
        // property 'userModes'
        QtMocHelpers::PropertyData<QString>(64, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<IrcUser, qt_meta_tag_ZN7IrcUserE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject IrcUser::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7IrcUserE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7IrcUserE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7IrcUserE_t>.metaTypes,
    nullptr
} };

void IrcUser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<IrcUser *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->nickSet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->awaySet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->encryptedSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->userModesSet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->userModesAdded((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->userModesRemoved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->channelParted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->quited(); break;
        case 8: _t->lastChannelActivityUpdated((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[2]))); break;
        case 9: _t->lastSpokenToUpdated((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[2]))); break;
        case 10: _t->setUser((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->setHost((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->setNick((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->setRealName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->setAccount((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->setAway((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 16: _t->setAwayMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->setIdleTime((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1]))); break;
        case 18: _t->setLoginTime((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1]))); break;
        case 19: _t->setServer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->setIrcOperator((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->setLastAwayMessage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->setLastAwayMessageTime((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1]))); break;
        case 23: _t->setWhoisServiceReply((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 24: _t->setSuserHost((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->setEncrypted((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 26: _t->updateHostmask((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: _t->setUserModes((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 28: _t->joinChannel((*reinterpret_cast< std::add_pointer_t<IrcChannel*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 29: _t->joinChannel((*reinterpret_cast< std::add_pointer_t<IrcChannel*>>(_a[1]))); break;
        case 30: _t->joinChannel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 31: _t->partChannel((*reinterpret_cast< std::add_pointer_t<IrcChannel*>>(_a[1]))); break;
        case 32: _t->partChannel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 33: _t->quit(); break;
        case 34: _t->addUserModes((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 35: _t->removeUserModes((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 36: _t->updateObjectName(); break;
        case 37: _t->channelDestroyed(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(QString )>(_a, &IrcUser::nickSet, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(bool )>(_a, &IrcUser::awaySet, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(bool )>(_a, &IrcUser::encryptedSet, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(QString )>(_a, &IrcUser::userModesSet, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(QString )>(_a, &IrcUser::userModesAdded, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(QString )>(_a, &IrcUser::userModesRemoved, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(QString )>(_a, &IrcUser::channelParted, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)()>(_a, &IrcUser::quited, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(BufferId , const QDateTime & )>(_a, &IrcUser::lastChannelActivityUpdated, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcUser::*)(BufferId , const QDateTime & )>(_a, &IrcUser::lastSpokenToUpdated, 9))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->user(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->host(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->nick(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->realName(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->account(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->isAway(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->awayMessage(); break;
        case 7: *reinterpret_cast<QDateTime*>(_v) = _t->idleTime(); break;
        case 8: *reinterpret_cast<QDateTime*>(_v) = _t->loginTime(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->server(); break;
        case 10: *reinterpret_cast<QString*>(_v) = _t->ircOperator(); break;
        case 11: *reinterpret_cast<QDateTime*>(_v) = _t->lastAwayMessageTime(); break;
        case 12: *reinterpret_cast<QString*>(_v) = _t->whoisServiceReply(); break;
        case 13: *reinterpret_cast<QString*>(_v) = _t->suserHost(); break;
        case 14: *reinterpret_cast<bool*>(_v) = _t->encrypted(); break;
        case 15: *reinterpret_cast<QStringList*>(_v) = _t->channels(); break;
        case 16: *reinterpret_cast<QString*>(_v) = _t->userModes(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUser(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setHost(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setNick(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setRealName(*reinterpret_cast<QString*>(_v)); break;
        case 4: _t->setAccount(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setAway(*reinterpret_cast<bool*>(_v)); break;
        case 6: _t->setAwayMessage(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setIdleTime(*reinterpret_cast<QDateTime*>(_v)); break;
        case 8: _t->setLoginTime(*reinterpret_cast<QDateTime*>(_v)); break;
        case 9: _t->setServer(*reinterpret_cast<QString*>(_v)); break;
        case 10: _t->setIrcOperator(*reinterpret_cast<QString*>(_v)); break;
        case 11: _t->setLastAwayMessageTime(*reinterpret_cast<QDateTime*>(_v)); break;
        case 12: _t->setWhoisServiceReply(*reinterpret_cast<QString*>(_v)); break;
        case 13: _t->setSuserHost(*reinterpret_cast<QString*>(_v)); break;
        case 14: _t->setEncrypted(*reinterpret_cast<bool*>(_v)); break;
        case 16: _t->setUserModes(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *IrcUser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IrcUser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7IrcUserE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int IrcUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void IrcUser::nickSet(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void IrcUser::awaySet(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void IrcUser::encryptedSet(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void IrcUser::userModesSet(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void IrcUser::userModesAdded(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void IrcUser::userModesRemoved(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void IrcUser::channelParted(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void IrcUser::quited()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void IrcUser::lastChannelActivityUpdated(BufferId _t1, const QDateTime & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}

// SIGNAL 9
void IrcUser::lastSpokenToUpdated(BufferId _t1, const QDateTime & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1, _t2);
}
QT_WARNING_POP
