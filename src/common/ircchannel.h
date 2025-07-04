// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QHash>
#include <QSet>
#include <QString>
#include <QStringConverter>
#include <QStringList>
#include <QVariantMap>

#include "syncableobject.h"

class IrcUser;
class Network;

class COMMON_EXPORT IrcChannel : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString topic READ topic WRITE setTopic)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(bool encrypted READ encrypted WRITE setEncrypted)

public:
    IrcChannel(const QString& channelname, Network* network);

    bool isKnownUser(IrcUser* ircuser) const;
    bool isValidChannelUserMode(const QString& mode) const;

    inline QString name() const { return _name; }
    inline QString topic() const { return _topic; }
    inline QString password() const { return _password; }
    inline bool encrypted() const { return _encrypted; }
    inline Network* network() const { return _network; }

    inline QList<IrcUser*> ircUsers() const { return _userModes.keys(); }

    QString userModes(IrcUser* ircuser) const;
    QString userModes(const QString& nick) const;

    bool hasMode(const QChar& mode) const;
    QString modeValue(const QChar& mode) const;
    QStringList modeValueList(const QChar& mode) const;
    QString channelModeString() const;

    inline const QStringEncoder& codecForEncoding() const { return _encoder; }
    inline const QStringDecoder& codecForDecoding() const { return _decoder; }
    void setCodecForEncoding(const QString& codecName);
    void setCodecForEncoding(QStringConverter::Encoding encoding);
    void setCodecForDecoding(const QString& codecName);
    void setCodecForDecoding(QStringConverter::Encoding encoding);

    QString decodeString(const QByteArray& text) const;
    QByteArray encodeString(const QString& string) const;

public slots:
    void setTopic(const QString& topic);
    void setPassword(const QString& password);
    void setEncrypted(bool encrypted);

    void joinIrcUsers(const QList<IrcUser*>& users, const QStringList& modes);
    void joinIrcUsers(const QStringList& nicks, const QStringList& modes);
    void joinIrcUser(IrcUser* ircuser);

    void part(IrcUser* ircuser);
    void part(const QString& nick);

    void setUserModes(IrcUser* ircuser, const QString& modes);
    void setUserModes(const QString& nick, const QString& modes);

    void addUserMode(IrcUser* ircuser, const QString& mode);
    void addUserMode(const QString& nick, const QString& mode);

    void removeUserMode(IrcUser* ircuser, const QString& mode);
    void removeUserMode(const QString& nick, const QString& mode);

    void addChannelMode(const QChar& mode, const QString& value);
    void removeChannelMode(const QChar& mode, const QString& value);

    // init geters
    QVariantMap initUserModes() const;
    QVariantMap initChanModes() const;

    // init seters
    void initSetUserModes(const QVariantMap& usermodes);
    void initSetChanModes(const QVariantMap& chanModes);

signals:
    void topicSet(const QString& topic);  // needed by NetworkModel
    void encryptedSet(bool encrypted);
    //   void passwordSet(const QString &password);
    //   void userModesSet(QString nick, QString modes);
    //   void userModeAdded(QString nick, QString mode);
    //   void userModeRemoved(QString nick, QString mode);
    //   void channelModeAdded(const QChar &mode, const QString &value);
    //   void channelModeRemoved(const QChar &mode, const QString &value);

    void ircUsersJoined(const QList<IrcUser*>& ircusers);
    //   void ircUsersJoined(QStringList nicks, QStringList modes);
    void ircUserParted(IrcUser* ircuser);
    void ircUserNickSet(IrcUser* ircuser, QString nick);
    void ircUserModeAdded(IrcUser* ircuser, QString mode);
    void ircUserModeRemoved(IrcUser* ircuser, QString mode);
    void ircUserModesSet(IrcUser* ircuser, QString modes);

    void parted();  // convenience signal emitted before channels destruction

private slots:
    void ircUserDestroyed();
    void ircUserNickSet(QString nick);

private:
    bool _initialized;
    QString _name;
    QString _topic;
    QString _password;
    bool _encrypted;

    QHash<IrcUser*, QString> _userModes;

    Network* _network;

    QStringEncoder _encoder;
    QStringDecoder _decoder;

    QHash<QChar, QStringList> _A_channelModes;
    QHash<QChar, QString> _B_channelModes;
    QHash<QChar, QString> _C_channelModes;
    QSet<QChar> _D_channelModes;
};
