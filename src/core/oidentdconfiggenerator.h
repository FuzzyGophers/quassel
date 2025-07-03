// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef OIDENTDCONFIGGENERATOR_H
#define OIDENTDCONFIGGENERATOR_H

#include <QByteArray>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QHostAddress>
#include <QMutex>
#include <QObject>
#include <QRegularExpression>
#include <QString>

#include "coreidentity.h"
#include "quassel.h"

//!  Produces oidentd configuration files
/*!
  Upon IRC connect this class puts the clients' ident data into an oidentd configuration file.

  The default path is <~/.oidentd.conf>.

  For oidentd to incorporate this file, the global oidentd.conf has to state something like this:

  user "quassel" {
    default {
      allow spoof
      allow spoof_all
    }
  }

*/

class OidentdConfigGenerator : public QObject
{
    Q_OBJECT
public:
    explicit OidentdConfigGenerator(QObject* parent = nullptr);
    ~OidentdConfigGenerator() override;

public slots:
    bool addSocket(const CoreIdentity* identity,
                   const QHostAddress& localAddress,
                   quint16 localPort,
                   const QHostAddress& peerAddress,
                   quint16 peerPort,
                   qint64 socketId);
    bool removeSocket(const CoreIdentity* identity,
                      const QHostAddress& localAddress,
                      quint16 localPort,
                      const QHostAddress& peerAddress,
                      quint16 peerPort,
                      qint64 socketId);

private:
    QString sysIdentForIdentity(const CoreIdentity* identity) const;
    bool init();
    bool writeConfig();
    bool parseConfig(bool readQuasselStanzas = false);
    bool lineByUs(const QByteArray& line);

    bool _initialized{false};
    bool _strict;
    QDateTime _lastSync;
    QFile* _configFile;
    QByteArray _parsedConfig;
    QByteArray _quasselConfig;
    // Mutex isn't strictly necessary at the moment, since with the current invocation in Core only one instance at a time exists
    QMutex _mutex;

    QDir _configDir;
    QRegularExpression _quasselStanzaRx;
    QString _configFileName;
    QString _configPath;
    QString _configTag;
    QString _quasselStanzaTemplate;
};

#endif  // OIDENTDCONFIGGENERATOR_H
