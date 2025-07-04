// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "aliasmanager.h"

#include <QDebug>
#include <QRegularExpression>
#include <QStringList>

#include "network.h"

int AliasManager::indexOf(const QString& name) const
{
    for (int i = 0; i < _aliases.count(); i++) {
        if (_aliases[i].name == name)
            return i;
    }
    return -1;
}

QVariantMap AliasManager::initAliases() const
{
    QVariantMap aliases;
    QStringList names;
    QStringList expansions;

    for (int i = 0; i < _aliases.count(); i++) {
        names << _aliases[i].name;
        expansions << _aliases[i].expansion;
    }

    aliases["names"] = names;
    aliases["expansions"] = expansions;
    return aliases;
}

void AliasManager::initSetAliases(const QVariantMap& aliases)
{
    QStringList names = aliases["names"].toStringList();
    QStringList expansions = aliases["expansions"].toStringList();

    if (names.count() != expansions.count()) {
        qWarning() << "AliasesManager::initSetAliases: received" << names.count() << "alias names but only" << expansions.count()
                   << "expansions!";
        return;
    }

    _aliases.clear();
    for (int i = 0; i < names.count(); i++) {
        _aliases << Alias(names[i], expansions[i]);
    }
}

void AliasManager::addAlias(const QString& name, const QString& expansion)
{
    if (contains(name)) {
        return;
    }

    _aliases << Alias(name, expansion);

    SYNC(ARG(name), ARG(expansion))
}

AliasManager::AliasList AliasManager::defaults()
{
    AliasList aliases;
    aliases << Alias("j", "/join $0") << Alias("ns", "/quote nickserv $0") << Alias("nickserv", "/quote nickserv $0")
            << Alias("cs", "/quote chanserv $0") << Alias("chanserv", "/quote chanserv $0") << Alias("hs", "/quote hostserv $0")
            << Alias("hostserv", "/quote hostserv $0") << Alias("wii", "/whois $0 $0") << Alias("back", "/quote away")
            << Alias("raw", "/quote $0");

#ifdef Q_OS_LINUX
    // let's add aliases for scripts that only run on linux
    aliases << Alias("inxi", "/exec inxi $0") << Alias("sysinfo", "/exec inxi -d");
#endif

    return aliases;
}

AliasManager::CommandList AliasManager::processInput(const BufferInfo& info, const QString& msg)
{
    CommandList result;
    processInput(info, msg, result);
    return result;
}

void AliasManager::processInput(const BufferInfo& info, const QString& msg_, CommandList& list)
{
    QString msg = msg_;

    // leading slashes indicate there's a command to call unless there is another one in the first section (like a path /proc/cpuinfo)
    // For those habitally tied to irssi, "/ " also makes the rest of the line a literal message
    int secondSlashPos = msg.indexOf('/', 1);
    int firstSpacePos = msg.indexOf(' ');
    if (!msg.startsWith('/') || firstSpacePos == 1 || (secondSlashPos != -1 && (secondSlashPos < firstSpacePos || firstSpacePos == -1))) {
        if (msg.startsWith("//"))
            msg.remove(0, 1);  // "//asdf" is transformed to "/asdf"
        else if (msg.startsWith("/ "))
            msg.remove(0, 2);  // "/ /asdf" is transformed to "/asdf"
        msg.prepend("/SAY ");  // make sure we only send proper commands to the core
    }
    else {
        // check for aliases
        QString cmd = msg.section(' ', 0, 0).remove(0, 1).toUpper();
        for (int i = 0; i < count(); i++) {
            if ((*this)[i].name.toUpper() == cmd) {
                expand((*this)[i].expansion, info, msg.section(' ', 1), list);
                return;
            }
        }
    }

    list.append(qMakePair(info, msg));
}

void AliasManager::expand(const QString& alias, const BufferInfo& bufferInfo, const QString& msg, CommandList& list)
{
    const Network* net = network(bufferInfo.networkId());
    if (!net) {
        // FIXME send error as soon as we have a method for that!
        return;
    }

    QRegularExpression paramRangeR(R"(\$(\d+)\.\.(\d*))");
    QStringList commands = alias.split(QRegularExpression("; ?"));
    QStringList params = msg.split(' ');
    QStringList expandedCommands;
    for (int i = 0; i < commands.count(); i++) {
        QString command = commands[i];

        // replace ranges like $1..3
        if (!params.isEmpty()) {
            QRegularExpressionMatch match;
            int pos = 0;
            while ((match = paramRangeR.match(command, pos)).hasMatch()) {
                pos = match.capturedStart();
                int start = match.captured(1).toInt();
                bool ok;
                int end = match.captured(2).toInt(&ok);
                if (!ok) {
                    end = params.count();
                }
                if (end < start)
                    command = command.replace(pos, match.capturedLength(), QString());
                else {
                    command = command.replace(pos, match.capturedLength(), QStringList(params.mid(start - 1, end - start + 1)).join(" "));
                }
                pos += match.capturedLength();
            }
        }

        for (int j = params.count(); j > 0; j--) {
            // Find the referenced IRC user...
            IrcUser* ircUser = net->ircUser(params[j - 1]);
            // ...and replace components, using short-circuit evaluation as ircUser might be null

            // Account, or "*" if blank/nonexistent/logged out
            command = command.replace(QString("$%1:account").arg(j),
                                      (ircUser && !ircUser->account().isEmpty()) ? ircUser->account() : QString("*"));

            // Hostname, or "*" if blank/nonexistent
            command = command.replace(QString("$%1:hostname").arg(j),
                                      (ircUser && !ircUser->host().isEmpty()) ? ircUser->host() : QString("*"));

            // Identd
            // Ident if verified, or "*" if blank/unknown/unverified (prefixed with "~")
            command = command.replace(QString("$%1:identd").arg(j),
                                      (ircUser && !ircUser->user().isEmpty() && !ircUser->user().startsWith("~")) ? ircUser->user()
                                                                                                                  : QString("*"));

            // Ident, or "*" if blank/nonexistent
            command = command.replace(QString("$%1:ident").arg(j), (ircUser && !ircUser->user().isEmpty()) ? ircUser->user() : QString("*"));

            // Nickname
            // Must be replaced last to avoid interfering with more specific aliases
            command = command.replace(QString("$%1").arg(j), params[j - 1]);
        }
        command = command.replace("$0", msg);
        command = command.replace("$channelname", bufferInfo.bufferName());  // legacy
        command = command.replace("$channel", bufferInfo.bufferName());
        command = command.replace("$currentnick", net->myNick());  // legacy
        command = command.replace("$nick", net->myNick());
        expandedCommands << command;
    }

    while (!expandedCommands.isEmpty()) {
        QString command;
        if (expandedCommands[0].trimmed().toLower().startsWith("/wait ")) {
            command = expandedCommands.join("; ");
            expandedCommands.clear();
        }
        else {
            command = expandedCommands.takeFirst();
        }
        list.append(qMakePair(bufferInfo, command));
    }
}
