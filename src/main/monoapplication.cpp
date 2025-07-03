// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "monoapplication.h"

#include "client.h"
#include "core.h"
#include "coreapplication.h"
#include "internalpeer.h"
#include "qtui.h"

class InternalPeer;

MonolithicApplication::MonolithicApplication(int& argc, char** argv)
    : QtUiApplication(argc, argv)
{
#if QT_VERSION >= 0x050700
    QGuiApplication::setDesktopFileName(Quassel::buildInfo().applicationName);
#endif
}

void MonolithicApplication::init()
{
    QtUiApplication::init();

    connect(Client::coreConnection(), &CoreConnection::connectToInternalCore, this, &MonolithicApplication::onConnectionRequest);

    // If port is set, start internal core directly so external clients can connect
    // This is useful in case the mono client re-gains remote connection capability,
    // in which case the internal core would not have to be started by default.
    if (Quassel::isOptionSet("port")) {
        startInternalCore();
    }
}

Quassel::QuitHandler MonolithicApplication::quitHandler()
{
    return [this]() {
        qInfo() << "Client shutting down...";
        connect(_client.get(), &QObject::destroyed, this, &MonolithicApplication::onClientDestroyed);
        _client.release()->deleteLater();
    };
}

void MonolithicApplication::onClientDestroyed()
{
    if (_core) {
        connect(_core, &Core::shutdownComplete, this, &MonolithicApplication::onCoreShutdown);
        _core->shutdown();
    }
    else {
        QCoreApplication::quit();
    }
}

void MonolithicApplication::onCoreShutdown()
{
    if (_core) {
        connect(_core, &QObject::destroyed, QCoreApplication::instance(), &QCoreApplication::quit);
        _coreThread.quit();
        _coreThread.wait();
    }
    else {
        QCoreApplication::quit();
    }
}

void MonolithicApplication::startInternalCore()
{
    if (_core) {
        // Already started
        return;
    }

    // Start internal core in a separate thread, so it doesn't block the UI
    _core = new Core{};
    _core->moveToThread(&_coreThread);
    connect(&_coreThread, &QThread::started, _core.data(), &Core::initAsync);
    connect(&_coreThread, &QThread::finished, _core.data(), &QObject::deleteLater);

    connect(this, &MonolithicApplication::connectInternalPeer, _core, &Core::connectInternalPeer);
    connect(_core, &Core::sessionStateReceived, Client::coreConnection(), &CoreConnection::internalSessionStateReceived);

    connect(_core.data(), &Core::dbUpgradeInProgress, Client::instance(), &Client::onDbUpgradeInProgress);
    connect(_core.data(), &Core::exitRequested, Client::instance(), &Client::onExitRequested);

    _coreThread.start();
}

void MonolithicApplication::onConnectionRequest(QPointer<InternalPeer> peer)
{
    if (!_core) {
        startInternalCore();
    }

    // While starting the core may take a while, the object itself is instantiated synchronously and the connections
    // established, so it's safe to emit this immediately. The core will take care of queueing the request until
    // initialization is complete.
    emit connectInternalPeer(peer);
}
