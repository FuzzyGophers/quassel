// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include "client.h"
#include "message.h"
#include "networkmodel.h"

class CLIENT_EXPORT AbstractMessageProcessor : public QObject
{
    Q_OBJECT

public:
    AbstractMessageProcessor(QObject* parent);
    virtual void reset() = 0;

public slots:
    virtual void process(Message& msg) = 0;
    virtual void process(QList<Message>& msgs) = 0;
    virtual void networkRemoved(NetworkId id) = 0;

protected:
    // updateBufferActivity also sets the Message::Redirected flag which is later used
    // to determine where a message should be displayed. therefore it's crucial that it
    // is called before inserting the message into the model
    inline void preProcess(Message& msg) { Client::networkModel()->updateBufferActivity(msg); }
};
