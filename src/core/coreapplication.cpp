// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreapplication.h"

CoreApplication::CoreApplication(int& argc, char** argv)
    : QCoreApplication(argc, argv)
{
    Quassel::registerQuitHandler([this]() {
        connect(_core.get(), &Core::shutdownComplete, this, &CoreApplication::onShutdownComplete);
        _core->shutdown();
    });
}

void CoreApplication::init()
{
    _core = std::make_unique<Core>();
    _core->init();
}

void CoreApplication::onShutdownComplete()
{
    connect(_core.get(), &QObject::destroyed, QCoreApplication::instance(), &QCoreApplication::quit);
    _core.release()->deleteLater();
}
