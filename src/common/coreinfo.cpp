// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreinfo.h"

CoreInfo::CoreInfo(QObject* parent)
    : SyncableObject(parent)
{}

QVariantMap CoreInfo::coreData() const
{
    return _coreData;
}

void CoreInfo::setCoreData(const QVariantMap& coreData)
{
    _coreData = coreData;
    SYNC(ARG(coreData));
    emit coreDataChanged(coreData);
}

void CoreInfo::setConnectedClientData(const int peerCount, const QVariantList peerData)
{
    _coreData["sessionConnectedClients"] = peerCount;
    _coreData["sessionConnectedClientData"] = peerData;
    setCoreData(_coreData);
}

void CoreInfo::reset()
{
    // Clear any stored data
    _coreData.clear();
    // Propagate changes to listeners
    emit coreDataChanged(_coreData);
}
