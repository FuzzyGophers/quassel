// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "presetnetworks.h"

#include <QSettings>

#include "quassel.h"

QString PresetNetworks::_networksIniPath = QString();

// ====================
//  Public:
// ====================
QStringList PresetNetworks::names(bool onlyDefault)
{
    // lazily find the file, make sure to not call one of the other preset functions first (they'll fail else)
    if (_networksIniPath.isNull()) {
        _networksIniPath = Quassel::findDataFilePath("networks.ini");
        if (_networksIniPath.isNull()) {
            _networksIniPath = "";  // now we won't check again, as it's not null anymore
            return QStringList();
        }
    }
    if (!_networksIniPath.isEmpty()) {
        QSettings s(_networksIniPath, QSettings::IniFormat);
        QStringList networks = s.childGroups();
        if (!networks.isEmpty()) {
            // we sort the list case-insensitive
            QMap<QString, QString> sorted;
            foreach (QString net, networks) {
                if (onlyDefault && !s.value(QString("%1/Default").arg(net)).toBool())
                    continue;
                sorted[net.toLower()] = net;
            }
            return sorted.values();
        }
    }
    return QStringList();
}

QStringList PresetNetworks::defaultChannels(const QString& networkName)
{
    if (_networksIniPath.isEmpty())  // be sure to have called presetNetworks() first, else this always fails
        return QStringList();
    QSettings s(_networksIniPath, QSettings::IniFormat);
    return s.value(QString("%1/DefaultChannels").arg(networkName)).toStringList();
}

NetworkInfo PresetNetworks::networkInfo(const QString& networkName)
{
    NetworkInfo info;
    if (!_networksIniPath.isEmpty()) {
        info.networkName = networkName;
        QSettings s(_networksIniPath, QSettings::IniFormat);
        s.beginGroup(info.networkName);
        foreach (QString server, s.value("Servers").toStringList()) {
            bool ssl = false;
            QStringList splitserver = server.split(':', Qt::SkipEmptyParts);
            if (splitserver.count() != 2) {
                qWarning() << "Invalid server entry in networks.conf:" << server;
                continue;
            }
            if (splitserver[1].at(0) == '+')
                ssl = true;
            uint port = splitserver[1].toUInt();
            if (!port) {
                qWarning() << "Invalid port entry in networks.conf:" << server;
                continue;
            }
            // TODO Should networks.conf be modified to allow requiring SSL?
            info.serverList << Network::Server(splitserver[0].trimmed(), port, QString(), ssl, false);
        }
    }
    return info;
}
