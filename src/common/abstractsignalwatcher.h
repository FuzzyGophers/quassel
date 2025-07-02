// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QMetaType>
#include <QObject>

/**
 * Interface for watching external, asynchronous events like POSIX signals.
 *
 * Abstracts the platform-specific details away, since we're only interested
 * in the action to take.
 */
class AbstractSignalWatcher : public QObject
{
    Q_OBJECT

public:
    enum class Action
    {
        Reload,      ///< Configuration should be reloaded (e.g. SIGHUP)
        Terminate,   ///< Application should be terminated (e.g. SIGTERM)
        HandleCrash  ///< Application is crashing (e.g. SIGSEGV)
    };

    using QObject::QObject;

signals:
    /// An event/signal was received and the given action should be taken
    void handleSignal(AbstractSignalWatcher::Action action);
};

Q_DECLARE_METATYPE(AbstractSignalWatcher::Action)
