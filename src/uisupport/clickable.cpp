// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clickable.h"

#include <QDesktopServices>
#include <QModelIndex>
#include <QRegularExpressionMatch>
#include <QUrl>

#include "buffermodel.h"
#include "client.h"

void Clickable::activate(NetworkId networkId, const QString& text) const
{
    if (!isValid())
        return;

    QString str = text.mid(start(), length());

    switch (type()) {
    case Clickable::Url:
        if (!str.contains("://"))
            str = "http://" + str;
        QDesktopServices::openUrl(QUrl::fromEncoded(str.toUtf8(), QUrl::TolerantMode));
        break;
    case Clickable::Channel:
        Client::bufferModel()->switchToOrJoinBuffer(networkId, str);
        break;
    default:
        break;
    }
}

// NOTE: This method is not threadsafe and not reentrant!
//       (RegExps are not constant while matching, and they are static here for efficiency)
ClickableList ClickableList::fromString(const QString& str)
{
    // For matching URLs
    static QString scheme(R"((?:(?:mailto:|(?:[+.-]?\w)+://)|www(?=\.\S+\.)))");
    static QString authority(R"((?:(?:[,.;@:]?[-\w]+)+\.?|\[[0-9a-f:.]+\])(?::\d+)?)");
    static QString urlChars("(?:[,.;:]*[\\w~@/?&=+$()!%#*-])");
    static QString urlEnd("(?:>|[,.;:\"]*\\s|\\b|$)");  // NOLINT(modernize-raw-string-literal)

    static QRegularExpression regExp[] = {
        // URL
        QRegularExpression(QString("\\b(%1%2(?:/%3*)?)%4").arg(scheme, authority, urlChars, urlEnd),
                           QRegularExpression::CaseInsensitiveOption),

        // Channel name
        // We don't match for channel names starting with + or &, because that gives us a lot of false positives.
        QRegularExpression(R"(((?:#|![A-Z0-9]{5})[^,:\s]+(?::[^,:\s]+)?)\b)", QRegularExpression::CaseInsensitiveOption)

        // TODO: Nicks, we'll need a filtering for only matching known nicknames further down if we do this
    };

    static const int regExpCount = 2;  // number of regexps in the array above

    qint16 matches[] = {0, 0, 0};
    qint16 matchEnd[] = {0, 0, 0};

    ClickableList result;
    // QString str = data(ChatLineModel::DisplayRole).toString();

    qint16 idx = 0;
    qint16 minidx;
    int type = -1;

    do {
        type = -1;
        minidx = str.length();
        for (int i = 0; i < regExpCount; i++) {
            if (matches[i] < 0 || matchEnd[i] > str.length())
                continue;
            if (idx >= matchEnd[i]) {
                QRegularExpressionMatch match = regExp[i].match(str, qMax(matchEnd[i], idx));
                matches[i] = match.hasMatch() ? match.capturedStart(1) : -1;
                if (matches[i] >= 0)
                    matchEnd[i] = matches[i] + match.captured(1).length();
            }
            if (matches[i] >= 0 && matches[i] < minidx) {
                minidx = matches[i];
                type = i;
            }
        }
        if (type >= 0) {
            idx = matchEnd[type];
            QString match = str.mid(matches[type], matchEnd[type] - matches[type]);
            if (type == Clickable::Url && str.at(idx - 1) == ')') {  // special case: closing paren only matches if we had an open one
                if (!match.contains('(')) {
                    matchEnd[type]--;
                    match.chop(1);
                }
            }
            if (type == Clickable::Channel) {
                // don't make clickable if it could be a #number
                QRegularExpression numberCheck("^#\\d+$", QRegularExpression::CaseInsensitiveOption);
                if (numberCheck.match(match).hasMatch())
                    continue;
            }
            result.emplace_back((Clickable::Type)type, matches[type], matchEnd[type] - matches[type]);
        }
    } while (type >= 0);
    return result;
}

Clickable ClickableList::atCursorPos(int idx)
{
    for (const Clickable& click : *this) {
        if (idx >= click.start() && idx < click.start() + click.length())
            return click;
    }
    return Clickable();
}
