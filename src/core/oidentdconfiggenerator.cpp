// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef HAVE_UMASK
#    include <sys/stat.h>
#    include <sys/types.h>
#endif /* HAVE_UMASK */

#include <QString>

#include "corenetwork.h"
#include "oidentdconfiggenerator.h"

OidentdConfigGenerator::OidentdConfigGenerator(QObject* parent)
    : QObject(parent)
{
    if (!_initialized)
        init();
}

OidentdConfigGenerator::~OidentdConfigGenerator()
{
    _quasselConfig.clear();
    writeConfig();
    _configFile->deleteLater();
}

bool OidentdConfigGenerator::init()
{
    _configDir.setPath(QDir::homePath());
    _configFileName = ".oidentd.conf";

    if (Quassel::isOptionSet("oidentd-conffile"))
        _configPath = Quassel::optionValue("oidentd-conffile");
    else
        _configPath = _configDir.absoluteFilePath(_configFileName);

    _configTag = " stanza created by Quassel";

    _configFile = new QFile(_configPath);

    // Rx has to match Template in order for cleanup to work.
    // Template should be enhanced with the "from" parameter as soon as Quassel gains
    // the ability to bind to an IP on client sockets.

    _quasselStanzaTemplate = QString("lport %1 { reply \"%2\" } #%3\n");
    _quasselStanzaRx = QRegularExpression(QString(R"(^lport .* \{ .* \} #%1\r?\n)").arg(_configTag));

    // initially remove all Quassel stanzas that might be present
    if (parseConfig(false) && writeConfig())
        _initialized = true;

    return _initialized;
}

QString OidentdConfigGenerator::sysIdentForIdentity(const CoreIdentity* identity) const
{
    // Make sure the identity's ident complies with strict mode if enabled
    const CoreNetwork* network = qobject_cast<CoreNetwork*>(sender());
    return network->coreSession()->strictCompliantIdent(identity);
}

bool OidentdConfigGenerator::addSocket(const CoreIdentity* identity,
                                       const QHostAddress& localAddress,
                                       quint16 localPort,
                                       const QHostAddress& peerAddress,
                                       quint16 peerPort,
                                       qint64 socketId)
{
    Q_UNUSED(localAddress)
    Q_UNUSED(peerAddress)
    Q_UNUSED(peerPort)
    Q_UNUSED(socketId)

    const QString ident = sysIdentForIdentity(identity);

    _quasselConfig.append(_quasselStanzaTemplate.arg(localPort).arg(ident).arg(_configTag).toLatin1());

    bool ret = writeConfig();

    return ret;
}

//! not yet implemented
bool OidentdConfigGenerator::removeSocket(const CoreIdentity* identity,
                                          const QHostAddress& localAddress,
                                          quint16 localPort,
                                          const QHostAddress& peerAddress,
                                          quint16 peerPort,
                                          qint64 socketId)
{
    Q_UNUSED(identity)
    Q_UNUSED(localAddress)
    Q_UNUSED(localPort)
    Q_UNUSED(peerAddress)
    Q_UNUSED(peerPort)
    Q_UNUSED(socketId)

    return true;
}

bool OidentdConfigGenerator::parseConfig(bool readQuasselStanzas)
{
    if (!_configFile->exists())
        return true;

    if (!_configFile->isOpen() && !_configFile->open(QIODevice::ReadOnly))
        return false;
    _mutex.lock();

    _parsedConfig.clear();
    _configFile->seek(0);
    while (!_configFile->atEnd()) {
        QByteArray line = _configFile->readLine();

        if (!lineByUs(line))
            _parsedConfig.append(line);
        else if (readQuasselStanzas)
            _quasselConfig.append(line);
    }

    _configFile->close();
    _mutex.unlock();
    return true;
}

bool OidentdConfigGenerator::writeConfig()
{
#ifdef HAVE_UMASK
    mode_t prev_umask = umask(S_IXUSR | S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH);  // == 0133, rw-r--r--
#endif
    bool not_open = (!_configFile->isOpen() && !_configFile->open(QIODevice::ReadWrite | QIODevice::Text));
#ifdef HAVE_UMASK
    umask(prev_umask);
#endif

    if (not_open)
        return false;

    _mutex.lock();

    _configFile->seek(0);
    _configFile->resize(0);
    _configFile->write(_parsedConfig);
    _configFile->write(_quasselConfig);

    _configFile->close();
    _mutex.unlock();
    return true;
}

bool OidentdConfigGenerator::lineByUs(const QByteArray& line)
{
    return _quasselStanzaRx.match(line).hasMatch();
}
