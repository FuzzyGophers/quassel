// SPDX-License-Identifier: GPL-2.0-or-later

#include "ircencoder.h"

QByteArray IrcEncoder::writeMessage(const QHash<IrcTagKey, QString>& tags,
                                   const QByteArray& prefix,
                                   const QString& cmd,
                                   const QList<QByteArray>& params)
{
    QByteArray msg;
    writeTags(msg, tags);
    writePrefix(msg, prefix);
    writeCommand(msg, cmd);
    writeParams(msg, params);
    return msg;
}

void IrcEncoder::writeTagValue(QByteArray& msg, const QString& value)
{
    QString it = value;
    msg += it.replace("\\", R"(\\)")
             .replace(";", R"(\:)")
             .replace(" ", R"(\s)")
             .replace("\r", R"(\r)")
             .replace("\n", R"(\n)")
             .toUtf8();
}

void IrcEncoder::writeTags(QByteArray& msg, const QHash<IrcTagKey, QString>& tags)
{
    if (!tags.isEmpty()) {
        msg += "@";
        bool isFirstTag = true;
        for (const IrcTagKey& key : tags.keys()) {
            if (!isFirstTag) {
                // We join tags with semicolons
                msg += ";";
            }
            if (key.clientTag) {
                msg += "+";
            }
            if (!key.vendor.isEmpty()) {
                msg += key.vendor.toUtf8();
                msg += "/";
            }
            msg += key.key.toUtf8();
            if (!tags[key].isEmpty()) {
                msg += "=";
                writeTagValue(msg, tags[key]);
            }

            isFirstTag = false;
        }
        msg += " ";
    }
}

void IrcEncoder::writePrefix(QByteArray& msg, const QByteArray& prefix)
{
    if (!prefix.isEmpty()) {
        msg += ":" + prefix + " ";
    }
}

void IrcEncoder::writeCommand(QByteArray& msg, const QString& cmd)
{
    msg += cmd.toUpper().toUtf8();
}

void IrcEncoder::writeParams(QByteArray& msg, const QList<QByteArray>& params)
{
    for (int i = 0; i < params.size(); i++) {
        msg += " ";

        bool isLastParam = i == params.size() - 1;
        if (isLastParam && (params[i].isEmpty() || params[i].contains(' ') || params[i][0] == ':'))
            msg += ":";

        msg += params[i];
    }
}
