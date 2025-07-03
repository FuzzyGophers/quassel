// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ignorelistmanager.h"

class CoreSession;
struct RawMessage;

class CoreIgnoreListManager : public IgnoreListManager
{
    Q_OBJECT

public:
    explicit CoreIgnoreListManager(CoreSession* parent);

    StrictnessType match(const RawMessage& rawMsg, const QString& networkName);

public slots:
    inline void requestToggleIgnoreRule(const QString& ignoreRule) override { toggleIgnoreRule(ignoreRule); }
    inline void requestRemoveIgnoreListItem(const QString& ignoreRule) override { removeIgnoreListItem(ignoreRule); }
    inline void requestAddIgnoreListItem(
        int type, const QString& ignoreRule, bool isRegEx, int strictness, int scope, const QString& scopeRule, bool isActive) override
    {
        addIgnoreListItem(type, ignoreRule, isRegEx, strictness, scope, scopeRule, isActive);
    }

private slots:
    void save() const;

    // private:
    //  void loadDefaults();
};
