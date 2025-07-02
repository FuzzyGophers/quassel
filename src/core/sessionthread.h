// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>

#include <QThread>

#include "types.h"

class CoreSession;
class Peer;
class InternalPeer;
class RemotePeer;

class SessionThread : public QObject
{
    Q_OBJECT

public:
    SessionThread(UserId user, bool restoreState, bool strictIdentEnabled, QObject* parent = nullptr);
    ~SessionThread() override;

public slots:
    void addClient(Peer* peer);
    void shutdown();

private slots:
    void onSessionInitialized();
    void onSessionDestroyed();

signals:
    void initialized();
    void shutdownSession();
    void shutdownComplete(SessionThread*);

    void addClientToWorker(Peer* peer);

private:
    QThread _sessionThread;
    bool _sessionInitialized{false};

    std::vector<Peer*> _clientQueue;
};
