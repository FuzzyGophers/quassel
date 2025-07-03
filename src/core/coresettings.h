// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "settings.h"

class CoreSettings : public Settings
{
public:
    CoreSettings(QString group = "Core");

    void setStorageSettings(const QVariant& data);
    QVariant storageSettings(const QVariant& def = {}) const;

    void setAuthSettings(const QVariant& data);
    QVariant authSettings(const QVariant& def = {}) const;

    QVariant oldDbSettings() const;  // FIXME remove

    void setCoreState(const QVariant& data);
    QVariant coreState(const QVariant& def = {}) const;
};
