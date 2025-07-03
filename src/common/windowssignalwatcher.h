// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>

#include "abstractsignalwatcher.h"
#include "singleton.h"

class WindowsSignalWatcher : public AbstractSignalWatcher, private Singleton<WindowsSignalWatcher>
{
    Q_OBJECT

public:
    WindowsSignalWatcher(QObject* parent = nullptr);

    static void signalHandler(int signal);
};
