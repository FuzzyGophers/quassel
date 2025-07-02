// SPDX-License-Identifier: GPL-2.0-or-later

#include "proxyline.h"

#include "ircdecoder.h"

ProxyLine ProxyLine::parseProxyLine(const QByteArray& line)
{
    ProxyLine result;

    int start = 0;
    if (line.startsWith("PROXY")) {
        start = 5;
    }
    IrcDecoder::skipEmptyParts(line, start);
    QByteArray protocol = IrcDecoder::extractFragment(line, start);
    if (protocol == "TCP4") {
        result.protocol = QAbstractSocket::IPv4Protocol;
    } else if (protocol == "TCP6") {
        result.protocol = QAbstractSocket::IPv6Protocol;
    } else {
        result.protocol = QAbstractSocket::UnknownNetworkLayerProtocol;
    }

    if (result.protocol != QAbstractSocket::UnknownNetworkLayerProtocol) {
        bool ok;
        IrcDecoder::skipEmptyParts(line, start);
        result.sourceHost = QHostAddress(QString::fromLatin1(IrcDecoder::extractFragment(line, start)));
        IrcDecoder::skipEmptyParts(line, start);
        result.sourcePort = QString::fromLatin1(IrcDecoder::extractFragment(line, start)).toUShort(&ok);
        if (!ok) result.sourcePort = 0;
        IrcDecoder::skipEmptyParts(line, start);
        result.targetHost = QHostAddress(QString::fromLatin1(IrcDecoder::extractFragment(line, start)));
        IrcDecoder::skipEmptyParts(line, start);
        result.targetPort = QString::fromLatin1(IrcDecoder::extractFragment(line, start)).toUShort(&ok);
        if (!ok) result.targetPort = 0;
    }

    return result;
}


QDebug operator<<(QDebug dbg, const ProxyLine& p) {
    dbg.nospace();
    dbg << "(protocol = " << p.protocol;
    if (p.protocol == QAbstractSocket::UnknownNetworkLayerProtocol) {
        dbg << ")";
    } else {
        dbg << ", sourceHost = " << p.sourceHost << ", sourcePort = " << p.sourcePort << ", targetHost = " << p.targetHost << ", targetPort = " << p.targetPort << ")";
    }
    return dbg.space();
}
