// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "util.h"

#include <algorithm>
#include <array>
#include <utility>

#include <QCoreApplication>
#include <QDateTime>
#include <QTimeZone>
#include <QDebug>
#include <QRegularExpression>
#include <QVector>

QString nickFromMask(const QString& mask)
{
    return mask.left(mask.indexOf('!'));
}

QString userFromMask(const QString& mask)
{
    const int offset = mask.indexOf('!') + 1;
    if (offset <= 0)
        return {};
    const int length = mask.indexOf('@', offset) - offset;
    return mask.mid(offset, length >= 0 ? length : -1);
}

QString hostFromMask(const QString& mask)
{
    const int excl = mask.indexOf('!');
    if (excl < 0)
        return {};
    const int offset = mask.indexOf('@', excl + 1) + 1;
    return offset > 0 && offset < mask.size() ? mask.mid(offset) : QString{};
}

bool isChannelName(const QString& str)
{
    if (str.isEmpty())
        return false;
    static constexpr std::array<quint8, 4> prefixes{{'#', '&', '!', '+'}};
    return std::any_of(prefixes.cbegin(), prefixes.cend(), [&str](quint8 c) { return QChar(c) == str[0]; });
}

QString stripFormatCodes(QString message)
{
    static QRegularExpression regEx{"\x03(\\d\\d?(,\\d\\d?)?)?|\x04([\\da-fA-F]{6}(,[\\da-fA-F]{6})?)?|[\x02\x0f\x11\x12\x16\x1d\x1e\x1f]"};
    return message.remove(regEx);
}

QString stripAcceleratorMarkers(const QString& label_)
{
    QString label = label_;
    int p = 0;
    forever
    {
        p = label.indexOf('&', p);
        if (p < 0 || p + 1 >= label.length())
            break;

        if (label.at(p + 1).isLetterOrNumber() || label.at(p + 1) == '&')
            label.remove(p, 1);

        ++p;
    }
    return label;
}

static const QSet<QStringConverter::Encoding> utf8DetectionBlacklist = {
    QStringConverter::Latin1,
    // Add other encodings if needed (e.g., QStringConverter::System)
};

QString decodeString(const QByteArray& input, const QStringDecoder* decoder)
{
    // Skip UTF-8 detection if the decoder is valid and blacklisted
    if (decoder && utf8DetectionBlacklist.contains(QStringConverter::encodingForName(decoder->name()).value_or(QStringConverter::Utf8))) {
        QStringDecoder decoderInstance(QStringConverter::encodingForName(decoder->name()).value_or(QStringConverter::Utf8));
		QString result = decoderInstance(input);
		if (decoderInstance.hasError()) {
            qWarning() << "Decoding error with" << decoder->name() << "for input:" << input;
        }
        return result;
    }

    // Manual UTF-8 validation
    bool isUtf8 = true;
    int cnt = 0;
    for (uchar c : input) {
        if (cnt) {
            // Check multibyte char continuation (10yyyyyy)
            if ((c & 0xc0) != 0x80) {
                isUtf8 = false;
                break;
            }
            cnt--;
            continue;
        }
        if ((c & 0x80) == 0x00)
            continue; // 7-bit ASCII
        if ((c & 0xf8) == 0xf0) {
            cnt = 3; // 4-byte char
            continue;
        }
        if ((c & 0xf0) == 0xe0) {
            cnt = 2; // 3-byte char
            continue;
        }
        if ((c & 0xe0) == 0xc0) {
            cnt = 1; // 2-byte char
            continue;
        }
        isUtf8 = false;
        break; // Invalid UTF-8
    }

    if (isUtf8 && cnt == 0) {
        QString s = QString::fromUtf8(input);
        return s;
    }

    // Use provided decoder or fall back to Latin1
    QStringDecoder defaultDecoder(decoder ? QStringConverter::encodingForName(decoder->name()).value_or(QStringConverter::Latin1) : QStringConverter::Latin1);
    QString result = defaultDecoder(input);
    if (defaultDecoder.hasError()) {
        qWarning() << "Decoding error with" << (decoder ? decoder->name() : "Latin1") << "for input:" << input;
    }
    return result;
}

uint editingDistance(const QString& s1, const QString& s2)
{
    uint n = s1.size() + 1;
    uint m = s2.size() + 1;
    QVector<QVector<uint>> matrix(n, QVector<uint>(m, 0));

    for (uint i = 0; i < n; i++)
        matrix[i][0] = i;

    for (uint i = 0; i < m; i++)
        matrix[0][i] = i;

    uint min;
    for (uint i = 1; i < n; i++) {
        for (uint j = 1; j < m; j++) {
            uint deleteChar = matrix[i - 1][j] + 1;
            uint insertChar = matrix[i][j - 1] + 1;

            if (deleteChar < insertChar)
                min = deleteChar;
            else
                min = insertChar;

            if (s1[i - 1] == s2[j - 1]) {
                uint inheritChar = matrix[i - 1][j - 1];
                if (inheritChar < min)
                    min = inheritChar;
            }

            matrix[i][j] = min;
        }
    }
    return matrix[n - 1][m - 1];
}

QString secondsToString(int timeInSeconds)
{
    static QVector<std::pair<int, QString>> timeUnit{std::make_pair(365 * 24 * 60 * 60,
                                                                    QCoreApplication::translate("Quassel::secondsToString()", "year")),
                                                     std::make_pair(24 * 60 * 60,
                                                                    QCoreApplication::translate("Quassel::secondsToString()", "day")),
                                                     std::make_pair(60 * 60, QCoreApplication::translate("Quassel::secondsToString()", "h")),
                                                     std::make_pair(60, QCoreApplication::translate("Quassel::secondsToString()", "min")),
                                                     std::make_pair(1, QCoreApplication::translate("Quassel::secondsToString()", "sec"))};

    if (timeInSeconds != 0) {
        QStringList returnString;
        for (const auto& tu : timeUnit) {
            int n = timeInSeconds / tu.first;
            if (n > 0) {
                returnString += QString("%1 %2").arg(QString::number(n), tu.second);
            }
            timeInSeconds = timeInSeconds % tu.first;
        }
        return returnString.join(", ");
    }

    return QString("%1 %2").arg(QString::number(timeInSeconds), timeUnit.last().second);
}

QByteArray prettyDigest(const QByteArray& digest)
{
    QByteArray hexDigest = digest.toHex().toUpper();
    QByteArray prettyDigest;
    prettyDigest.fill(':', hexDigest.size() + (hexDigest.size() / 2) - 1);

    for (int i = 0; i * 2 < hexDigest.size(); i++) {
        prettyDigest.replace(i * 3, 2, hexDigest.mid(i * 2, 2));
    }
    return prettyDigest;
}

QString formatCurrentDateTimeInString(const QString& formatStr)
{
    QString formattedStr = QString(formatStr);
    if (formattedStr.isEmpty())
        return formattedStr;

    QRegularExpression regExpMatchTime("%%(.*)%%");
    regExpMatchTime.setPatternOptions(QRegularExpression::PatternOption::NoPatternOption);

    int numIterations = 0;
    int index = regExpMatchTime.match(formattedStr).capturedStart();
    int matchLength;
    QString matchedFormat;
    while (index >= 0 && numIterations < 512) {
        matchLength = regExpMatchTime.match(formattedStr, index).capturedLength(0);
        matchedFormat = regExpMatchTime.match(formattedStr, index).captured(1);
        if (matchedFormat.length() > 0) {
            formattedStr.replace(index, matchLength, QDateTime::currentDateTime().toString(matchedFormat));
            matchLength -= 4;
        }
        else if (matchLength == 4) {
            formattedStr.remove(index, 2);
            matchLength -= 2;
        }
        else {
            qDebug() << "Unexpected time format when parsing string, no matchedFormat, matchLength "
                        "should be 4, actually is"
                     << matchLength;
        }
        index = regExpMatchTime.match(formattedStr, index + matchLength).capturedStart();
        numIterations++;
    }

    return formattedStr;
}

QString tryFormatUnixEpoch(const QString& possibleEpochDate, Qt::DateFormat dateFormat, bool useUTC)
{
    qint64 secsSinceEpoch = possibleEpochDate.toLongLong();
    if (secsSinceEpoch == 0) {
        return possibleEpochDate;
    }

    QDateTime date;
    date.setSecsSinceEpoch(secsSinceEpoch);

    if (useUTC) {
        if (dateFormat == Qt::DateFormat::ISODate) {
            return date.toUTC().toString(dateFormat).replace(10, 1, " ");
        }
        else {
            return date.toUTC().toString(dateFormat);
        }
    }
    else if (dateFormat == Qt::DateFormat::ISODate) {
        return formatDateTimeToOffsetISO(date);
    }
    else {
        return date.toString(dateFormat);
    }
}

QString formatDateTimeToOffsetISO(const QDateTime& dateTime)
{
    if (!dateTime.isValid()) {
        return "formatDateTimeToISO() invalid date/time";
    }
    return dateTime.toOffsetFromUtc(dateTime.offsetFromUtc()).toString(Qt::ISODate).replace(10, 1, " ");
}
