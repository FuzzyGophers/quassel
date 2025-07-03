// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "invocationspy.h"

namespace test {

InvocationSpy::InvocationSpy(QObject* parent)
    : QObject(parent)
    , _internalSpy{this, &InvocationSpy::notified}
{}

void InvocationSpy::notify()
{
    emit notified();
}

bool InvocationSpy::wait(std::chrono::milliseconds timeout)
{
    if (_internalSpy.count() > 0) {
        _internalSpy.clear();
        return true;
    }
    bool result = _internalSpy.wait(timeout.count());
    _internalSpy.clear();
    return result;
}

// -----------------------------------------------------------------------------------------------------------------------------------------

bool SignalSpy::wait(std::chrono::milliseconds timeout)
{
    bool result = InvocationSpy::wait(timeout);
    for (auto&& connection : _connections) {
        QObject::disconnect(connection);
    }
    _connections.clear();
    return result;
}

}  // namespace test
