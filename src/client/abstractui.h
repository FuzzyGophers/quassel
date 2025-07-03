// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QObject>
#include <QVariantMap>

class MessageFilter;
class MessageModel;
class AbstractMessageProcessor;
class AbstractActionProvider;

class QAction;
class QMenu;

class CLIENT_EXPORT AbstractUi : public QObject
{
    Q_OBJECT

public:
    AbstractUi(QObject* parent = nullptr)
        : QObject(parent)
    {}
    virtual void init() = 0;  // called after the client is initialized
    virtual MessageModel* createMessageModel(QObject* parent) = 0;
    virtual AbstractMessageProcessor* createMessageProcessor(QObject* parent) = 0;

public slots:
    virtual void connectedToCore() {}
    virtual void disconnectedFromCore() {}

signals:
    void connectToCore(const QVariantMap& connInfo);
    void disconnectFromCore();
};
