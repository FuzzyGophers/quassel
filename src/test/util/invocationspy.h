// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "test-util-export.h"

#include <chrono>

#include <QObject>
#include <QSignalSpy>

#include <boost/optional.hpp>

namespace test {

/**
 * Waits while spinning the event loop until notified, or timed out.
 *
 * Based on QSignalSpy (hence the name), but provides an API that is much more useful
 * for writing asynchronous test cases.
 */
class TEST_UTIL_EXPORT InvocationSpy : public QObject
{
    Q_OBJECT

public:
    InvocationSpy(QObject* parent = nullptr);

    /**
     * Notifies the spy, which will cause it to return from wait().
     */
    void notify();

    /**
     * Waits for the spy to be notified within the given timeout.
     *
     * @param timeout Timeout for waiting
     * @returns true if the spy was notified, and false if it timed out.
     */
    virtual bool wait(std::chrono::milliseconds timeout = std::chrono::seconds{60});

signals:
    /// Internally used signal
    void notified();

private:
    QSignalSpy _internalSpy;
};

// -----------------------------------------------------------------------------------------------------------------------------------------

/**
 * Spy that allows to be notified with a value.
 *
 * Works like @a InvocationSpy, but takes a value when notified. After successful notification, the value
 * can be accessed and used for test case expectations.
 */
template<typename T>
class ValueSpy : public InvocationSpy
{
public:
    using InvocationSpy::InvocationSpy;

    /**
     * Notifies the spy with the given value.
     *
     * @param value The notification value
     */
    void notify(const T& value)
    {
        _value = value;
        InvocationSpy::notify();
    }

    /**
     * Provides the value the spy was last notified with.
     *
     * @note The value is only valid if wait() returned with true.
     * @returns The value given to notify(), or boost::none if the spy wasn't notified
     */
    T value() const { return *_value; }

private:
    boost::optional<T> _value;
};

// -----------------------------------------------------------------------------------------------------------------------------------------

/**
 * Spy that is notified by one (or multiple) signal(s).
 *
 * Unlike QSignalSpy, this class is not bound to a particular signal. Instead, SignalSpy::connect() must be called
 * to define the signal prior to calling wait(). connect() can also be called more than once, in which case any of
 * the connected signals will trigger the spy.
 *
 * Before wait() returns, it disconnects all existing signals, so the spy can be reused without having to explicitly
 * reset it.
 */
class TEST_UTIL_EXPORT SignalSpy : private InvocationSpy
{
public:
    using InvocationSpy::InvocationSpy;

    /**
     * Connects a signal to wait for.
     *
     * @param sender The signal's sender
     * @param sig The signal
     */
    template<typename TSender, typename TSignal>
    void connect(const TSender* sender, TSignal sig)
    {
        _connections.emplace_back(QObject::connect(sender, sig, this, &SignalSpy::notify));
    }

    /**
     * Waits for the spy to be notified with any of the connected signals within the given timeout.
     *
     * Any connections will be cleared before this function returns. When reusing the spy, one needs
     * to connect signals before calling wait() again.
     *
     * @param timeout Timeout for waiting
     * @returns true if a signal was received, and false if it timed out.
     */
    bool wait(std::chrono::milliseconds timeout = std::chrono::seconds{60}) override;

private:
    std::vector<QMetaObject::Connection> _connections;
};

}  // namespace test
