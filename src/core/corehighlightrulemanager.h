// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "highlightrulemanager.h"

class CoreSession;
struct RawMessage;

/**
 * Core-side specialization for HighlightRuleManager.
 *
 * Adds the ability to load/save the settings from/to the database.
 */
class CoreHighlightRuleManager : public HighlightRuleManager
{
    Q_OBJECT

    using HighlightRuleManager::match;

public:
    /**
     * Constructor.
     *
     * @param[in] session Pointer to the parent CoreSession (takes ownership)
     */
    explicit CoreHighlightRuleManager(CoreSession* session);

    bool match(const RawMessage& msg, const QString& currentNick, const QStringList& identityNicks);

public slots:
    inline void requestToggleHighlightRule(int highlightRule) override { toggleHighlightRule(highlightRule); }
    inline void requestRemoveHighlightRule(int highlightRule) override { removeHighlightRule(highlightRule); }
    inline void requestAddHighlightRule(int id,
                                        const QString& name,
                                        bool isRegEx,
                                        bool isCaseSensitive,
                                        bool isEnabled,
                                        bool isInverse,
                                        const QString& sender,
                                        const QString& chanName) override
    {
        addHighlightRule(id, name, isRegEx, isCaseSensitive, isEnabled, isInverse, sender, chanName);
    }

private slots:
    /**
     * Saves the config to the database.
     */
    void save();

private:
    CoreSession* _coreSession{nullptr};  ///< Pointer to the parent CoreSession
};
