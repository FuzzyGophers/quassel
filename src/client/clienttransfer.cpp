// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clienttransfer.h"

#include <QFile>

ClientTransfer::ClientTransfer(const QUuid& uuid, QObject* parent)
    : Transfer(uuid, parent)
    , _file(nullptr)
{
    connect(this, &Transfer::statusChanged, this, &ClientTransfer::onStatusChanged);
}

quint64 ClientTransfer::transferred() const
{
    if (status() == Status::Completed)
        return fileSize();

    return _file ? _file->size() : 0;
}

void ClientTransfer::cleanUp()
{
    if (_file) {
        _file->close();
        _file->deleteLater();
        _file = nullptr;
    }
}

QString ClientTransfer::savePath() const
{
    return _savePath;
}

void ClientTransfer::accept(const QString& savePath) const
{
    _savePath = savePath;
    PeerPtr ptr = nullptr;
    REQUEST_OTHER(requestAccepted, ARG(ptr));
    emit accepted();
}

void ClientTransfer::reject() const
{
    PeerPtr ptr = nullptr;
    REQUEST_OTHER(requestRejected, ARG(ptr));
    emit rejected();
}

void ClientTransfer::dataReceived(PeerPtr, const QByteArray& data)
{
    // TODO: proper error handling (relay to core)
    if (!_file) {
        _file = new QFile(_savePath, this);
        if (!_file->open(QFile::WriteOnly | QFile::Truncate)) {
            qWarning() << Q_FUNC_INFO << "Could not open file:" << _file->errorString();
            return;
        }
    }

    if (!_file->isOpen())
        return;

    if (_file->write(data) < 0) {
        qWarning() << Q_FUNC_INFO << "Could not write to file:" << _file->errorString();
        return;
    }

    emit transferredChanged(transferred());
}

void ClientTransfer::onStatusChanged(Transfer::Status status)
{
    switch (status) {
    case Status::Completed:
        if (_file)
            _file->close();
        break;
    case Status::Failed:
        if (_file)
            _file->remove();
        break;
    default:
        ;
    }
}
