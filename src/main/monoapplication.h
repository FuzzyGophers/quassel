// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QPointer>
#include <QThread>

#include "qtuiapplication.h"

class Core;
class InternalPeer;

class MonolithicApplication : public QtUiApplication
{
    Q_OBJECT

public:
    MonolithicApplication(int&, char**);

    void init() override;

protected:
    Quassel::QuitHandler quitHandler() override;

signals:
    void connectInternalPeer(QPointer<InternalPeer> peer);

private slots:
    void onConnectionRequest(QPointer<InternalPeer> peer);
    void onClientDestroyed();
    void onCoreShutdown();

private:
    void startInternalCore();

private:
    QPointer<Core> _core;
    QThread _coreThread;
};
