// SPDX-License-Identifier: GPL-2.0-or-later

#include "nickhighlightmatcher.h"

#include <QDebug>
#include <QString>
#include <QStringList>

bool NickHighlightMatcher::match(const QString& string, const NetworkId& netId, const QString& currentNick, const QStringList& identityNicks) const
{
    // Never match for no nicknames
    if (_highlightMode == HighlightNickType::NoNick) {
        return false;
    }

    // Don't match until current nickname is known
    if (currentNick.isEmpty()) {
        return false;
    }

    // Make sure expression matcher is ready
    determineExpressions(netId, currentNick, identityNicks);

    // Check for a match
    if (_nickMatchCache[netId].matcher.isValid() && _nickMatchCache[netId].matcher.match(string)) {
        // Nick matcher is valid and match found
        return true;
    }

    return false;
}

void NickHighlightMatcher::determineExpressions(const NetworkId& netId, const QString& currentNick, const QStringList& identityNicks) const
{
    // Don't do anything for no nicknames
    if (_highlightMode == HighlightNickType::NoNick) {
        return;
    }

    // Only update if needed (check nickname config, current nick, identity nicks for change)
    if (_nickMatchCache.contains(netId) && _nickMatchCache[netId].nickCurrent == currentNick
        && _nickMatchCache[netId].identityNicks == identityNicks) {
        return;
    }

    // Add all nicknames
    QStringList nickList;
    if (_highlightMode == HighlightNickType::CurrentNick) {
        nickList << currentNick;
    }
    else if (_highlightMode == HighlightNickType::AllNicks) {
        nickList = identityNicks;
        if (!nickList.contains(currentNick))
            nickList.prepend(currentNick);
    }

    // Set up phrase matcher, joining with newlines
    _nickMatchCache[netId].matcher = ExpressionMatch(nickList.join("\n"), ExpressionMatch::MatchMode::MatchMultiPhrase, _isCaseSensitive);

    _nickMatchCache[netId].nickCurrent = currentNick;
    _nickMatchCache[netId].identityNicks = identityNicks;

    qDebug() << "Regenerated nickname matching cache for network ID" << netId;
}
