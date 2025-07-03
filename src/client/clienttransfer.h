// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QUuid>

#include "transfer.h"

class QFile;

class ClientTransfer : public Transfer
{
    Q_OBJECT

public:
    ClientTransfer(const QUuid& uuid, QObject* parent = nullptr);

    QString savePath() const;

    quint64 transferred() const override;

public slots:
    // called on the client side
    void accept(const QString& savePath) const override;
    void reject() const override;

private slots:
    void dataReceived(PeerPtr peer, const QByteArray& data) override;
    void onStatusChanged(Transfer::Status status);

private:
    void cleanUp() override;

    mutable QString _savePath;

    QFile* _file;
};
