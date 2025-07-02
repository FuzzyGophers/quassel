// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QString>
#include <QStringList>

#include "network.h"

class COMMON_EXPORT PresetNetworks
{
public:
    static QStringList names(bool onlyDefault = false);
    static QStringList defaultChannels(const QString& networkName);
    static NetworkInfo networkInfo(const QString& networkName);

private:
    static QString _networksIniPath;
};
