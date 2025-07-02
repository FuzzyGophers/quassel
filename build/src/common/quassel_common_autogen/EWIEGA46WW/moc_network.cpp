/****************************************************************************
** Meta object code from reading C++ file 'network.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/network.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7NetworkE_t {};
} // unnamed namespace

template <> constexpr inline auto Network::qt_create_metaobjectdata<qt_meta_tag_ZN7NetworkE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Network",
        "aboutToBeDestroyed",
        "",
        "networkNameSet",
        "networkName",
        "currentServerSet",
        "currentServer",
        "connectedSet",
        "isConnected",
        "connectionStateSet",
        "Network::ConnectionState",
        "connectionError",
        "errorMsg",
        "myNickSet",
        "mynick",
        "identitySet",
        "IdentityId",
        "configChanged",
        "useCustomMessageRateSet",
        "useCustomRate",
        "messageRateBurstSizeSet",
        "burstSize",
        "messageRateDelaySet",
        "messageDelay",
        "unlimitedMessageRateSet",
        "unlimitedRate",
        "capAdded",
        "capability",
        "capAcknowledged",
        "capRemoved",
        "ircUserAdded",
        "IrcUser*",
        "ircChannelAdded",
        "IrcChannel*",
        "setNetworkName",
        "setCurrentServer",
        "setConnected",
        "setConnectionState",
        "state",
        "setMyNick",
        "setLatency",
        "latency",
        "setIdentity",
        "setServerList",
        "QVariantList",
        "serverList",
        "setUseRandomServer",
        "setPerform",
        "setSkipCaps",
        "skipCaps",
        "setUseAutoIdentify",
        "setAutoIdentifyService",
        "setAutoIdentifyPassword",
        "setUseSasl",
        "setSaslAccount",
        "setSaslPassword",
        "setUseAutoReconnect",
        "setAutoReconnectInterval",
        "setAutoReconnectRetries",
        "setUnlimitedReconnectRetries",
        "setRejoinChannels",
        "setUseCustomMessageRate",
        "setMessageRateBurstSize",
        "setMessageRateDelay",
        "setUnlimitedMessageRate",
        "addSupport",
        "param",
        "value",
        "removeSupport",
        "addCap",
        "acknowledgeCap",
        "removeCap",
        "clearCaps",
        "addIrcUser",
        "hostmask",
        "addIrcChannel",
        "channel",
        "initSupports",
        "QVariantMap",
        "initCaps",
        "initCapsEnabled",
        "initServerList",
        "initIrcUsersAndChannels",
        "initSetSupports",
        "supports",
        "initSetCaps",
        "caps",
        "initSetCapsEnabled",
        "capsEnabled",
        "initSetServerList",
        "initSetIrcUsersAndChannels",
        "usersAndChannels",
        "updateNickFromMask",
        "mask",
        "ircUserNickChanged",
        "newnick",
        "requestConnect",
        "requestDisconnect",
        "requestSetNetworkInfo",
        "NetworkInfo",
        "info",
        "emitConnectionError",
        "removeIrcUser",
        "ircuser",
        "removeIrcChannel",
        "ircChannel",
        "removeChansAndUsers",
        "myNick",
        "codecForServer",
        "codecForEncoding",
        "codecForDecoding",
        "identityId",
        "connectionState",
        "useRandomServer",
        "perform",
        "useAutoIdentify",
        "autoIdentifyService",
        "autoIdentifyPassword",
        "useSasl",
        "saslAccount",
        "saslPassword",
        "useAutoReconnect",
        "autoReconnectInterval",
        "autoReconnectRetries",
        "unlimitedReconnectRetries",
        "rejoinChannels",
        "useCustomMessageRate",
        "msgRateBurstSize",
        "msgRateMessageDelay",
        "unlimitedMessageRate",
        "ConnectionState",
        "Disconnected",
        "Connecting",
        "Initializing",
        "Initialized",
        "Reconnecting",
        "Disconnecting"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'aboutToBeDestroyed'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'networkNameSet'
        QtMocHelpers::SignalData<void(const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Signal 'currentServerSet'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'connectedSet'
        QtMocHelpers::SignalData<void(bool)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 8 },
        }}),
        // Signal 'connectionStateSet'
        QtMocHelpers::SignalData<void(Network::ConnectionState)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 2 },
        }}),
        // Signal 'connectionError'
        QtMocHelpers::SignalData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Signal 'myNickSet'
        QtMocHelpers::SignalData<void(const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 },
        }}),
        // Signal 'identitySet'
        QtMocHelpers::SignalData<void(IdentityId)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 2 },
        }}),
        // Signal 'configChanged'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'useCustomMessageRateSet'
        QtMocHelpers::SignalData<void(const bool)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 19 },
        }}),
        // Signal 'messageRateBurstSizeSet'
        QtMocHelpers::SignalData<void(const quint32)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 21 },
        }}),
        // Signal 'messageRateDelaySet'
        QtMocHelpers::SignalData<void(const quint32)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 23 },
        }}),
        // Signal 'unlimitedMessageRateSet'
        QtMocHelpers::SignalData<void(const bool)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 25 },
        }}),
        // Signal 'capAdded'
        QtMocHelpers::SignalData<void(const QString &)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Signal 'capAcknowledged'
        QtMocHelpers::SignalData<void(const QString &)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Signal 'capRemoved'
        QtMocHelpers::SignalData<void(const QString &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Signal 'ircUserAdded'
        QtMocHelpers::SignalData<void(IrcUser *)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 31, 2 },
        }}),
        // Signal 'ircChannelAdded'
        QtMocHelpers::SignalData<void(IrcChannel *)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 33, 2 },
        }}),
        // Slot 'setNetworkName'
        QtMocHelpers::SlotData<void(const QString &)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Slot 'setCurrentServer'
        QtMocHelpers::SlotData<void(const QString &)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'setConnected'
        QtMocHelpers::SlotData<void(bool)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 8 },
        }}),
        // Slot 'setConnectionState'
        QtMocHelpers::SlotData<void(int)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 38 },
        }}),
        // Slot 'setMyNick'
        QtMocHelpers::SlotData<void(const QString &)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 },
        }}),
        // Slot 'setLatency'
        QtMocHelpers::SlotData<void(int)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 41 },
        }}),
        // Slot 'setIdentity'
        QtMocHelpers::SlotData<void(IdentityId)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 2 },
        }}),
        // Slot 'setServerList'
        QtMocHelpers::SlotData<void(const QVariantList &)>(43, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 44, 45 },
        }}),
        // Slot 'setUseRandomServer'
        QtMocHelpers::SlotData<void(bool)>(46, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'setPerform'
        QtMocHelpers::SlotData<void(const QStringList &)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 2 },
        }}),
        // Slot 'setSkipCaps'
        QtMocHelpers::SlotData<void(const QStringList &)>(48, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 49 },
        }}),
        // Slot 'setUseAutoIdentify'
        QtMocHelpers::SlotData<void(bool)>(50, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'setAutoIdentifyService'
        QtMocHelpers::SlotData<void(const QString &)>(51, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'setAutoIdentifyPassword'
        QtMocHelpers::SlotData<void(const QString &)>(52, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'setUseSasl'
        QtMocHelpers::SlotData<void(bool)>(53, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'setSaslAccount'
        QtMocHelpers::SlotData<void(const QString &)>(54, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'setSaslPassword'
        QtMocHelpers::SlotData<void(const QString &)>(55, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'setUseAutoReconnect'
        QtMocHelpers::SlotData<void(bool)>(56, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'setAutoReconnectInterval'
        QtMocHelpers::SlotData<void(quint32)>(57, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 2 },
        }}),
        // Slot 'setAutoReconnectRetries'
        QtMocHelpers::SlotData<void(quint16)>(58, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UShort, 2 },
        }}),
        // Slot 'setUnlimitedReconnectRetries'
        QtMocHelpers::SlotData<void(bool)>(59, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'setRejoinChannels'
        QtMocHelpers::SlotData<void(bool)>(60, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 2 },
        }}),
        // Slot 'setUseCustomMessageRate'
        QtMocHelpers::SlotData<void(bool)>(61, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 19 },
        }}),
        // Slot 'setMessageRateBurstSize'
        QtMocHelpers::SlotData<void(quint32)>(62, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 21 },
        }}),
        // Slot 'setMessageRateDelay'
        QtMocHelpers::SlotData<void(quint32)>(63, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 23 },
        }}),
        // Slot 'setUnlimitedMessageRate'
        QtMocHelpers::SlotData<void(bool)>(64, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 25 },
        }}),
        // Slot 'addSupport'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(65, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 66 }, { QMetaType::QString, 67 },
        }}),
        // Slot 'addSupport'
        QtMocHelpers::SlotData<void(const QString &)>(65, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 66 },
        }}),
        // Slot 'removeSupport'
        QtMocHelpers::SlotData<void(const QString &)>(68, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 66 },
        }}),
        // Slot 'addCap'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(69, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 27 }, { QMetaType::QString, 67 },
        }}),
        // Slot 'addCap'
        QtMocHelpers::SlotData<void(const QString &)>(69, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Slot 'acknowledgeCap'
        QtMocHelpers::SlotData<void(const QString &)>(70, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Slot 'removeCap'
        QtMocHelpers::SlotData<void(const QString &)>(71, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Slot 'clearCaps'
        QtMocHelpers::SlotData<void()>(72, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'addIrcUser'
        QtMocHelpers::SlotData<void(const QString &)>(73, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 74 },
        }}),
        // Slot 'addIrcChannel'
        QtMocHelpers::SlotData<void(const QString &)>(75, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 76 },
        }}),
        // Slot 'initSupports'
        QtMocHelpers::SlotData<QVariantMap() const>(77, 2, QMC::AccessPublic, 0x80000000 | 78),
        // Slot 'initCaps'
        QtMocHelpers::SlotData<QVariantMap() const>(79, 2, QMC::AccessPublic, 0x80000000 | 78),
        // Slot 'initCapsEnabled'
        QtMocHelpers::SlotData<QVariantList() const>(80, 2, QMC::AccessPublic, 0x80000000 | 44),
        // Slot 'initServerList'
        QtMocHelpers::SlotData<QVariantList() const>(81, 2, QMC::AccessPublic, 0x80000000 | 44),
        // Slot 'initIrcUsersAndChannels'
        QtMocHelpers::SlotData<QVariantMap() const>(82, 2, QMC::AccessPublic, 0x80000000 | 78),
        // Slot 'initSetSupports'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(83, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 78, 84 },
        }}),
        // Slot 'initSetCaps'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(85, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 78, 86 },
        }}),
        // Slot 'initSetCapsEnabled'
        QtMocHelpers::SlotData<void(const QVariantList &)>(87, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 44, 88 },
        }}),
        // Slot 'initSetServerList'
        QtMocHelpers::SlotData<void(const QVariantList &)>(89, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 44, 45 },
        }}),
        // Slot 'initSetIrcUsersAndChannels'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(90, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 78, 91 },
        }}),
        // Slot 'updateNickFromMask'
        QtMocHelpers::SlotData<IrcUser *(const QString &)>(92, 2, QMC::AccessPublic, 0x80000000 | 31, {{
            { QMetaType::QString, 93 },
        }}),
        // Slot 'ircUserNickChanged'
        QtMocHelpers::SlotData<void(QString)>(94, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 95 },
        }}),
        // Slot 'requestConnect'
        QtMocHelpers::SlotData<void() const>(96, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'requestDisconnect'
        QtMocHelpers::SlotData<void() const>(97, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'requestSetNetworkInfo'
        QtMocHelpers::SlotData<void(const NetworkInfo &)>(98, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 99, 100 },
        }}),
        // Slot 'emitConnectionError'
        QtMocHelpers::SlotData<void(const QString &)>(101, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'removeIrcUser'
        QtMocHelpers::SlotData<void(IrcUser *)>(102, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 31, 103 },
        }}),
        // Slot 'removeIrcChannel'
        QtMocHelpers::SlotData<void(IrcChannel *)>(104, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 33, 105 },
        }}),
        // Slot 'removeChansAndUsers'
        QtMocHelpers::SlotData<void()>(106, 2, QMC::AccessProtected, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'networkName'
        QtMocHelpers::PropertyData<QString>(4, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'currentServer'
        QtMocHelpers::PropertyData<QString>(6, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'myNick'
        QtMocHelpers::PropertyData<QString>(107, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'latency'
        QtMocHelpers::PropertyData<int>(41, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'codecForServer'
        QtMocHelpers::PropertyData<QString>(108, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'codecForEncoding'
        QtMocHelpers::PropertyData<QString>(109, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'codecForDecoding'
        QtMocHelpers::PropertyData<QString>(110, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'identityId'
        QtMocHelpers::PropertyData<IdentityId>(111, 0x80000000 | 16, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag),
        // property 'isConnected'
        QtMocHelpers::PropertyData<bool>(8, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'connectionState'
        QtMocHelpers::PropertyData<int>(112, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'useRandomServer'
        QtMocHelpers::PropertyData<bool>(113, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'perform'
        QtMocHelpers::PropertyData<QStringList>(114, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'skipCaps'
        QtMocHelpers::PropertyData<QStringList>(49, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'useAutoIdentify'
        QtMocHelpers::PropertyData<bool>(115, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoIdentifyService'
        QtMocHelpers::PropertyData<QString>(116, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoIdentifyPassword'
        QtMocHelpers::PropertyData<QString>(117, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'useSasl'
        QtMocHelpers::PropertyData<bool>(118, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'saslAccount'
        QtMocHelpers::PropertyData<QString>(119, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'saslPassword'
        QtMocHelpers::PropertyData<QString>(120, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'useAutoReconnect'
        QtMocHelpers::PropertyData<bool>(121, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoReconnectInterval'
        QtMocHelpers::PropertyData<quint32>(122, QMetaType::UInt, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoReconnectRetries'
        QtMocHelpers::PropertyData<quint16>(123, QMetaType::UShort, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'unlimitedReconnectRetries'
        QtMocHelpers::PropertyData<bool>(124, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'rejoinChannels'
        QtMocHelpers::PropertyData<bool>(125, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'useCustomMessageRate'
        QtMocHelpers::PropertyData<bool>(126, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'msgRateBurstSize'
        QtMocHelpers::PropertyData<quint32>(127, QMetaType::UInt, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'msgRateMessageDelay'
        QtMocHelpers::PropertyData<quint32>(128, QMetaType::UInt, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'unlimitedMessageRate'
        QtMocHelpers::PropertyData<bool>(129, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'ConnectionState'
        QtMocHelpers::EnumData<ConnectionState>(130, 130, QMC::EnumFlags{}).add({
            {  131, ConnectionState::Disconnected },
            {  132, ConnectionState::Connecting },
            {  133, ConnectionState::Initializing },
            {  134, ConnectionState::Initialized },
            {  135, ConnectionState::Reconnecting },
            {  136, ConnectionState::Disconnecting },
        }),
    };
    return QtMocHelpers::metaObjectData<Network, qt_meta_tag_ZN7NetworkE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Network::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7NetworkE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7NetworkE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7NetworkE_t>.metaTypes,
    nullptr
} };

void Network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Network *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->aboutToBeDestroyed(); break;
        case 1: _t->networkNameSet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->currentServerSet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->connectedSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->connectionStateSet((*reinterpret_cast< std::add_pointer_t<Network::ConnectionState>>(_a[1]))); break;
        case 5: _t->connectionError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->myNickSet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->identitySet((*reinterpret_cast< std::add_pointer_t<IdentityId>>(_a[1]))); break;
        case 8: _t->configChanged(); break;
        case 9: _t->useCustomMessageRateSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->messageRateBurstSizeSet((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 11: _t->messageRateDelaySet((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 12: _t->unlimitedMessageRateSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->capAdded((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->capAcknowledged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->capRemoved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->ircUserAdded((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1]))); break;
        case 17: _t->ircChannelAdded((*reinterpret_cast< std::add_pointer_t<IrcChannel*>>(_a[1]))); break;
        case 18: _t->setNetworkName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->setCurrentServer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->setConnected((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->setConnectionState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->setMyNick((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->setLatency((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->setIdentity((*reinterpret_cast< std::add_pointer_t<IdentityId>>(_a[1]))); break;
        case 25: _t->setServerList((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 26: _t->setUseRandomServer((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 27: _t->setPerform((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 28: _t->setSkipCaps((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 29: _t->setUseAutoIdentify((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 30: _t->setAutoIdentifyService((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 31: _t->setAutoIdentifyPassword((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 32: _t->setUseSasl((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 33: _t->setSaslAccount((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 34: _t->setSaslPassword((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 35: _t->setUseAutoReconnect((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 36: _t->setAutoReconnectInterval((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 37: _t->setAutoReconnectRetries((*reinterpret_cast< std::add_pointer_t<quint16>>(_a[1]))); break;
        case 38: _t->setUnlimitedReconnectRetries((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 39: _t->setRejoinChannels((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 40: _t->setUseCustomMessageRate((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 41: _t->setMessageRateBurstSize((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 42: _t->setMessageRateDelay((*reinterpret_cast< std::add_pointer_t<quint32>>(_a[1]))); break;
        case 43: _t->setUnlimitedMessageRate((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 44: _t->addSupport((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 45: _t->addSupport((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 46: _t->removeSupport((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 47: _t->addCap((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 48: _t->addCap((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 49: _t->acknowledgeCap((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 50: _t->removeCap((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 51: _t->clearCaps(); break;
        case 52: _t->addIrcUser((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 53: _t->addIrcChannel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 54: { QVariantMap _r = _t->initSupports();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 55: { QVariantMap _r = _t->initCaps();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 56: { QVariantList _r = _t->initCapsEnabled();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 57: { QVariantList _r = _t->initServerList();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 58: { QVariantMap _r = _t->initIrcUsersAndChannels();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 59: _t->initSetSupports((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 60: _t->initSetCaps((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 61: _t->initSetCapsEnabled((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 62: _t->initSetServerList((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 63: _t->initSetIrcUsersAndChannels((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 64: { IrcUser* _r = _t->updateNickFromMask((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< IrcUser**>(_a[0]) = std::move(_r); }  break;
        case 65: _t->ircUserNickChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 66: _t->requestConnect(); break;
        case 67: _t->requestDisconnect(); break;
        case 68: _t->requestSetNetworkInfo((*reinterpret_cast< std::add_pointer_t<NetworkInfo>>(_a[1]))); break;
        case 69: _t->emitConnectionError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 70: _t->removeIrcUser((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1]))); break;
        case 71: _t->removeIrcChannel((*reinterpret_cast< std::add_pointer_t<IrcChannel*>>(_a[1]))); break;
        case 72: _t->removeChansAndUsers(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< IdentityId >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< IrcUser* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< IrcChannel* >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< IdentityId >(); break;
            }
            break;
        case 68:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< NetworkInfo >(); break;
            }
            break;
        case 70:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< IrcUser* >(); break;
            }
            break;
        case 71:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< IrcChannel* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Network::*)()>(_a, &Network::aboutToBeDestroyed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const QString & )>(_a, &Network::networkNameSet, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const QString & )>(_a, &Network::currentServerSet, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(bool )>(_a, &Network::connectedSet, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(Network::ConnectionState )>(_a, &Network::connectionStateSet, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const QString & )>(_a, &Network::connectionError, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const QString & )>(_a, &Network::myNickSet, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(IdentityId )>(_a, &Network::identitySet, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)()>(_a, &Network::configChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const bool )>(_a, &Network::useCustomMessageRateSet, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const quint32 )>(_a, &Network::messageRateBurstSizeSet, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const quint32 )>(_a, &Network::messageRateDelaySet, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const bool )>(_a, &Network::unlimitedMessageRateSet, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const QString & )>(_a, &Network::capAdded, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const QString & )>(_a, &Network::capAcknowledged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(const QString & )>(_a, &Network::capRemoved, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(IrcUser * )>(_a, &Network::ircUserAdded, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (Network::*)(IrcChannel * )>(_a, &Network::ircChannelAdded, 17))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IdentityId >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->networkName(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->currentServer(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->myNick(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->latency(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->codecForServer(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->codecForEncoding(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->codecForDecoding(); break;
        case 7: *reinterpret_cast<IdentityId*>(_v) = _t->identity(); break;
        case 8: *reinterpret_cast<bool*>(_v) = _t->isConnected(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->connectionState(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->useRandomServer(); break;
        case 11: *reinterpret_cast<QStringList*>(_v) = _t->perform(); break;
        case 12: *reinterpret_cast<QStringList*>(_v) = _t->skipCaps(); break;
        case 13: *reinterpret_cast<bool*>(_v) = _t->useAutoIdentify(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->autoIdentifyService(); break;
        case 15: *reinterpret_cast<QString*>(_v) = _t->autoIdentifyPassword(); break;
        case 16: *reinterpret_cast<bool*>(_v) = _t->useSasl(); break;
        case 17: *reinterpret_cast<QString*>(_v) = _t->saslAccount(); break;
        case 18: *reinterpret_cast<QString*>(_v) = _t->saslPassword(); break;
        case 19: *reinterpret_cast<bool*>(_v) = _t->useAutoReconnect(); break;
        case 20: *reinterpret_cast<quint32*>(_v) = _t->autoReconnectInterval(); break;
        case 21: *reinterpret_cast<quint16*>(_v) = _t->autoReconnectRetries(); break;
        case 22: *reinterpret_cast<bool*>(_v) = _t->unlimitedReconnectRetries(); break;
        case 23: *reinterpret_cast<bool*>(_v) = _t->rejoinChannels(); break;
        case 24: *reinterpret_cast<bool*>(_v) = _t->useCustomMessageRate(); break;
        case 25: *reinterpret_cast<quint32*>(_v) = _t->messageRateBurstSize(); break;
        case 26: *reinterpret_cast<quint32*>(_v) = _t->messageRateDelay(); break;
        case 27: *reinterpret_cast<bool*>(_v) = _t->unlimitedMessageRate(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setNetworkName(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setCurrentServer(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setMyNick(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setLatency(*reinterpret_cast<int*>(_v)); break;
        case 4: _t->setCodecForServer(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setCodecForEncoding(*reinterpret_cast<QString*>(_v)); break;
        case 6: _t->setCodecForDecoding(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setIdentity(*reinterpret_cast<IdentityId*>(_v)); break;
        case 8: _t->setConnected(*reinterpret_cast<bool*>(_v)); break;
        case 9: _t->setConnectionState(*reinterpret_cast<int*>(_v)); break;
        case 10: _t->setUseRandomServer(*reinterpret_cast<bool*>(_v)); break;
        case 11: _t->setPerform(*reinterpret_cast<QStringList*>(_v)); break;
        case 12: _t->setSkipCaps(*reinterpret_cast<QStringList*>(_v)); break;
        case 13: _t->setUseAutoIdentify(*reinterpret_cast<bool*>(_v)); break;
        case 14: _t->setAutoIdentifyService(*reinterpret_cast<QString*>(_v)); break;
        case 15: _t->setAutoIdentifyPassword(*reinterpret_cast<QString*>(_v)); break;
        case 16: _t->setUseSasl(*reinterpret_cast<bool*>(_v)); break;
        case 17: _t->setSaslAccount(*reinterpret_cast<QString*>(_v)); break;
        case 18: _t->setSaslPassword(*reinterpret_cast<QString*>(_v)); break;
        case 19: _t->setUseAutoReconnect(*reinterpret_cast<bool*>(_v)); break;
        case 20: _t->setAutoReconnectInterval(*reinterpret_cast<quint32*>(_v)); break;
        case 21: _t->setAutoReconnectRetries(*reinterpret_cast<quint16*>(_v)); break;
        case 22: _t->setUnlimitedReconnectRetries(*reinterpret_cast<bool*>(_v)); break;
        case 23: _t->setRejoinChannels(*reinterpret_cast<bool*>(_v)); break;
        case 24: _t->setUseCustomMessageRate(*reinterpret_cast<bool*>(_v)); break;
        case 25: _t->setMessageRateBurstSize(*reinterpret_cast<quint32*>(_v)); break;
        case 26: _t->setMessageRateDelay(*reinterpret_cast<quint32*>(_v)); break;
        case 27: _t->setUnlimitedMessageRate(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7NetworkE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int Network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 73)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 73;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 73)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 73;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void Network::aboutToBeDestroyed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Network::networkNameSet(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Network::currentServerSet(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Network::connectedSet(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Network::connectionStateSet(Network::ConnectionState _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Network::connectionError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void Network::myNickSet(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void Network::identitySet(IdentityId _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void Network::configChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Network::useCustomMessageRateSet(const bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void Network::messageRateBurstSizeSet(const quint32 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void Network::messageRateDelaySet(const quint32 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}

// SIGNAL 12
void Network::unlimitedMessageRateSet(const bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}

// SIGNAL 13
void Network::capAdded(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1);
}

// SIGNAL 14
void Network::capAcknowledged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1);
}

// SIGNAL 15
void Network::capRemoved(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1);
}

// SIGNAL 16
void Network::ircUserAdded(IrcUser * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 16, nullptr, _t1);
}

// SIGNAL 17
void Network::ircChannelAdded(IrcChannel * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 17, nullptr, _t1);
}
QT_WARNING_POP
