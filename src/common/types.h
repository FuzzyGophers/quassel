// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <type_traits>

#include <QDataStream>
#include <QDebug>
#include <QHostAddress>
#include <QString>
#include <QTextStream>
#include <QVariant>

class SignedId
{
protected:
    qint32 id;

public:
    inline SignedId(int _id = 0) { id = _id; }
    inline qint32 toInt() const { return id; }
    inline bool isValid() const { return id > 0; }

    inline bool operator==(const SignedId& other) const { return id == other.id; }
    inline bool operator!=(const SignedId& other) const { return id != other.id; }
    inline bool operator<(const SignedId& other) const { return id < other.id; }
    inline bool operator<=(const SignedId& other) const { return id <= other.id; }
    inline bool operator>(const SignedId& other) const { return id > other.id; }
    inline bool operator>=(const SignedId& other) const { return id >= other.id; }
    inline bool operator==(int i) const { return id == i; }
    inline bool operator!=(int i) const { return id != i; }
    inline bool operator<(int i) const { return id < i; }
    inline bool operator>(int i) const { return id > i; }
    inline bool operator<=(int i) const { return id <= i; }

    inline SignedId operator++(int)
    {
        id++;
        return *this;
    }
    // inline operator int() const { return toInt(); } // no automatic conversion!

    friend QDataStream& operator>>(QDataStream& in, SignedId& signedId);
};

inline QDataStream& operator<<(QDataStream& out, const SignedId& signedId)
{
    out << signedId.toInt();
    return out;
}
inline QDataStream& operator>>(QDataStream& in, SignedId& signedId)
{
    in >> signedId.id;
    return in;
}
inline QTextStream& operator<<(QTextStream& out, const SignedId& signedId)
{
    out << QString::number(signedId.toInt());
    return out;
}
inline QDebug operator<<(QDebug dbg, const SignedId& signedId)
{
    dbg.space() << signedId.toInt();
    return dbg;
}
inline uint qHash(const SignedId& id)
{
    return qHash(id.toInt());
}

class SignedId64
{
protected:
    qint64 id;

public:
    inline SignedId64(qint64 _id = 0) { id = _id; }
    inline qint64 toQint64() const { return id; }
    inline bool isValid() const { return id > 0; }

    inline bool operator==(const SignedId64& other) const { return id == other.id; }
    inline bool operator!=(const SignedId64& other) const { return id != other.id; }
    inline bool operator<(const SignedId64& other) const { return id < other.id; }
    inline bool operator<=(const SignedId64& other) const { return id <= other.id; }
    inline bool operator>(const SignedId64& other) const { return id > other.id; }
    inline bool operator>=(const SignedId64& other) const { return id >= other.id; }
    inline bool operator==(qint64 i) const { return id == i; }
    inline bool operator!=(qint64 i) const { return id != i; }
    inline bool operator<(qint64 i) const { return id < i; }
    inline bool operator>(qint64 i) const { return id > i; }
    inline bool operator<=(qint64 i) const { return id <= i; }

    inline SignedId64 operator++(int)
    {
        id++;
        return *this;
    }
    // inline operator int() const { return toQint64(); } // no automatic conversion!

    friend QDataStream& operator>>(QDataStream& in, SignedId64& signedId);
};

QDataStream& operator<<(QDataStream& out, const SignedId64& signedId);
QDataStream& operator>>(QDataStream& in, SignedId64& signedId);
inline QTextStream& operator<<(QTextStream& out, const SignedId64& signedId)
{
    out << QString::number(signedId.toQint64());
    return out;
}
inline QDebug operator<<(QDebug dbg, const SignedId64& signedId)
{
    dbg.space() << signedId.toQint64();
    return dbg;
}
inline uint qHash(const SignedId64& id)
{
    return qHash(id.toQint64());
}

struct UserId : public SignedId
{
    inline UserId(int _id = 0)
        : SignedId(_id)
    {
    }
    // inline operator QVariant() const { return QVariant::fromValue(*this); }  // no automatic conversion!
};

struct MsgId : public SignedId64
{
    inline MsgId(qint64 _id = 0)
        : SignedId64(_id)
    {
    }
    // inline operator QVariant() const { return QVariant::fromValue(*this); }
};

struct BufferId : public SignedId
{
    inline BufferId(int _id = 0)
        : SignedId(_id)
    {
    }
    // inline operator QVariant() const { return QVariant::fromValue(*this); }
};

struct NetworkId : public SignedId
{
    inline NetworkId(int _id = 0)
        : SignedId(_id)
    {
    }
    // inline operator QVariant() const { return QVariant::fromValue(*this); }
};

struct IdentityId : public SignedId
{
    inline IdentityId(int _id = 0)
        : SignedId(_id)
    {
    }
    // inline operator QVariant() const { return QVariant::fromValue(*this); }
};

struct AccountId : public SignedId
{
    inline AccountId(int _id = 0)
        : SignedId(_id)
    {
    }
};

Q_DECLARE_METATYPE(UserId)
Q_DECLARE_METATYPE(MsgId)
Q_DECLARE_METATYPE(BufferId)
Q_DECLARE_METATYPE(NetworkId)
Q_DECLARE_METATYPE(IdentityId)
Q_DECLARE_METATYPE(AccountId)

Q_DECLARE_METATYPE(QHostAddress)

// a few typedefs
using MsgIdList = QList<MsgId>;
using BufferIdList = QList<BufferId>;

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
/**
 * Catch-all stream serialization operator for enum types.
 *
 * @param[in,out] out   Stream to serialize to
 * @param[in]     value Value to serialize
 * @returns A reference to the stream
 */
template<typename T, typename = typename std::enable_if<std::is_enum<T>::value>::type>
QDataStream& operator<<(QDataStream& out, T value)
{
    out << static_cast<typename std::underlying_type<T>::type>(value);
    return out;
}

/**
 * Catch-all stream serialization operator for enum types.
 *
 * @param[in,out] in    Stream to deserialize from
 * @param[out]    value Value to deserialize into
 * @returns A reference to the stream
 */
template<typename T, typename = typename std::enable_if<std::is_enum<T>::value>::type>
QDataStream& operator>>(QDataStream& in, T& value)
{
    typename std::underlying_type<T>::type v;
    in >> v;
    value = static_cast<T>(v);
    return in;
}
#endif

// STL-compliant hash functor for Qt types
template<typename T>
struct Hash
{
    uint operator()(const T& t) const { return qHash(t); }
};

// Exceptions

/**
 * Thrown during initialization to enforce exiting the application before the event loop is started
 */
struct ExitException
{
    int exitCode;
    QString errorString;

    ExitException(int code = EXIT_FAILURE, QString error = {})
        : exitCode(code)
        , errorString(std::move(error))
    {
    }
};
