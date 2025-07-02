// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>

#include "abstractsignalwatcher.h"

class QSocketNotifier;

/**
 * Signal watcher/handler for POSIX systems.
 *
 * Uses a local socket to notify the main thread in a safe way.
 */
class PosixSignalWatcher : public AbstractSignalWatcher
{
    Q_OBJECT

public:
    PosixSignalWatcher(QObject* parent = nullptr);

private:
    static void signalHandler(int signal);

    void registerSignal(int signal);

private slots:
    void onNotify(int sockfd);

private:
    static int _sockpair[2];
    QSocketNotifier* _notifier{nullptr};
};
