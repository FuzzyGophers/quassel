// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QList>
#include <QSet>
#include <QString>
#include <QStringConverter>
#include <QRegularExpression>
#include <QVariant>

COMMON_EXPORT QString nickFromMask(const QString& mask);
COMMON_EXPORT QString userFromMask(const QString& mask);
COMMON_EXPORT QString hostFromMask(const QString& mask);
COMMON_EXPORT bool isChannelName(const QString& str);

COMMON_EXPORT QString stripFormatCodes(QString);
COMMON_EXPORT QString stripAcceleratorMarkers(const QString&);
COMMON_EXPORT QString secondsToString(int timeInSeconds);
COMMON_EXPORT QString decodeString(const QByteArray& input, const QStringDecoder* decoder = nullptr);
COMMON_EXPORT uint editingDistance(const QString& s1, const QString& s2);

template<typename T>
QSet<T> toQSet(const QList<T>& list)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    return list.toSet();
#else
    return {list.begin(), list.end()};
#endif
}

template<typename T>
QVariantList toVariantList(const QList<T>& list)
{
    QVariantList variants;
    for (int i = 0; i < list.size(); i++) {
        variants << QVariant::fromValue(list[i]);
    }
    return variants;
}

template<typename T>
QList<T> fromVariantList(const QVariantList& variants)
{
    QList<T> list;
    for (int i = 0; i < variants.size(); i++) {
        list << variants[i].value<T>();
    }
    return list;
}

COMMON_EXPORT QByteArray prettyDigest(const QByteArray& digest);
COMMON_EXPORT QString formatCurrentDateTimeInString(const QString& formatStr);
COMMON_EXPORT QString tryFormatUnixEpoch(const QString& possibleEpochDate,
                                        Qt::DateFormat dateFormat = Qt::DateFormat::TextDate,
                                        bool useUTC = false);
COMMON_EXPORT QString formatDateTimeToOffsetISO(const QDateTime& dateTime);

namespace detail {
template<typename... Args>
struct SelectOverloadHelper
{
    template<typename R, typename C>
    constexpr auto operator()(R (C::*func)(Args...)) const noexcept -> decltype(func)
    {
        return func;
    }
};
}

template<typename... Args>
constexpr detail::SelectOverloadHelper<Args...> selectOverload = {};
