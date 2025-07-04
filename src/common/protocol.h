// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <utility>

#include <QByteArray>
#include <QDateTime>
#include <QVariantList>

#include "quassel.h"

namespace QuasselProtocol {

const quint32 magic = 0x42b33f00;

const quint32 proxyMagic = 0x50524f58;

enum Type
{
    InternalProtocol = 0x00,
    LegacyProtocol = 0x01,
    DataStreamProtocol = 0x02
};

enum Feature
{
    Encryption = 0x01,
    Compression = 0x02
};

enum class Handler
{
    SignalProxy,
    AuthHandler
};

/*** Handshake, handled by AuthHandler ***/

struct HandshakeMessage
{
    inline Handler handler() const { return Handler::AuthHandler; }
};

struct RegisterClient : public HandshakeMessage
{
    inline RegisterClient(Quassel::Features clientFeatures, QString clientVersion, QString buildDate, bool sslSupported = false)
        : features(std::move(clientFeatures))
        , clientVersion(std::move(clientVersion))
        , buildDate(std::move(buildDate))
        , sslSupported(sslSupported)
    {
    }

    Quassel::Features features;
    QString clientVersion;
    QString buildDate;

    // this is only used by the LegacyProtocol in compat mode
    bool sslSupported;
};

struct ClientDenied : public HandshakeMessage
{
    inline ClientDenied(QString errorString)
        : errorString(std::move(errorString))
    {
    }

    QString errorString;
};

struct ClientRegistered : public HandshakeMessage
{
    inline ClientRegistered(
        Quassel::Features coreFeatures, bool coreConfigured, QVariantList backendInfo, QVariantList authenticatorInfo, bool sslSupported)
        : features(std::move(coreFeatures))
        , coreConfigured(coreConfigured)
        , backendInfo(std::move(backendInfo))
        , authenticatorInfo(std::move(authenticatorInfo))
        , sslSupported(sslSupported)
    {
    }

    Quassel::Features features;
    bool coreConfigured;
    QVariantList backendInfo;  // TODO: abstract this better

    // The authenticatorInfo should be optional!
    QVariantList authenticatorInfo;

    // this is only used by the LegacyProtocol in compat mode
    bool sslSupported;
};

struct SetupData : public HandshakeMessage
{
    inline SetupData(QString adminUser,
                     QString adminPassword,
                     QString backend,
                     QVariantMap setupData,
                     QString authenticator = QString(),
                     QVariantMap authSetupData = QVariantMap())
        : adminUser(std::move(adminUser))
        , adminPassword(std::move(adminPassword))
        , backend(std::move(backend))
        , setupData(std::move(setupData))
        , authenticator(std::move(authenticator))
        , authSetupData(std::move(authSetupData))
    {
    }

    QString adminUser;
    QString adminPassword;
    QString backend;
    QVariantMap setupData;
    QString authenticator;
    QVariantMap authSetupData;
};

struct SetupFailed : public HandshakeMessage
{
    inline SetupFailed(QString errorString)
        : errorString(std::move(errorString))
    {
    }

    QString errorString;
};

struct SetupDone : public HandshakeMessage
{};

struct Login : public HandshakeMessage
{
    inline Login(QString user, QString password)
        : user(std::move(user))
        , password(std::move(password))
    {
    }

    QString user;
    QString password;
};

struct LoginFailed : public HandshakeMessage
{
    inline LoginFailed(QString errorString)
        : errorString(std::move(errorString))
    {
    }

    QString errorString;
};

struct LoginSuccess : public HandshakeMessage
{};

// TODO: more generic format
struct SessionState : public HandshakeMessage
{
    inline SessionState() = default;  // needed for QMetaType (for the mono client)
    inline SessionState(QVariantList identities, QVariantList bufferInfos, QVariantList networkIds)
        : identities(std::move(identities))
        , bufferInfos(std::move(bufferInfos))
        , networkIds(std::move(networkIds))
    {
    }

    QVariantList identities;
    QVariantList bufferInfos;
    QVariantList networkIds;
};

/*** handled by SignalProxy ***/

struct SignalProxyMessage
{
    inline Handler handler() const { return Handler::SignalProxy; }
};

struct SyncMessage : public SignalProxyMessage
{
    SyncMessage() = default;
    SyncMessage(QByteArray className, QString objectName, QByteArray slotName, QVariantList params)
        : className(std::move(className))
        , objectName(std::move(objectName))
        , slotName(std::move(slotName))
        , params(std::move(params))
    {
    }

    QByteArray className;
    QString objectName;
    QByteArray slotName;
    QVariantList params;
};

struct RpcCall : public SignalProxyMessage
{
    RpcCall() = default;
    RpcCall(QByteArray signalName, QVariantList params)
        : signalName(std::move(signalName))
        , params(std::move(params))
    {
    }

    QByteArray signalName;
    QVariantList params;
};

struct InitRequest : public SignalProxyMessage
{
    InitRequest() = default;
    InitRequest(QByteArray className, QString objectName)
        : className(std::move(className))
        , objectName(std::move(objectName))
    {
    }

    QByteArray className;
    QString objectName;
};

struct InitData : public SignalProxyMessage
{
    InitData() = default;
    InitData(QByteArray className, QString objectName, QVariantMap initData)
        : className(std::move(className))
        , objectName(std::move(objectName))
        , initData(std::move(initData))
    {
    }

    QByteArray className;
    QString objectName;
    QVariantMap initData;
};

/*** handled by RemoteConnection ***/

struct HeartBeat
{
    inline HeartBeat(QDateTime timestamp)
        : timestamp(std::move(timestamp))
    {
    }

    QDateTime timestamp;
};

struct HeartBeatReply
{
    inline HeartBeatReply(QDateTime timestamp)
        : timestamp(std::move(timestamp))
    {
    }

    QDateTime timestamp;
};

}  // namespace QuasselProtocol

// Required for InternalPeer
Q_DECLARE_METATYPE(QuasselProtocol::SyncMessage)
Q_DECLARE_METATYPE(QuasselProtocol::RpcCall)
Q_DECLARE_METATYPE(QuasselProtocol::InitRequest)
Q_DECLARE_METATYPE(QuasselProtocol::InitData)
