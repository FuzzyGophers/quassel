// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CLIENTUSERINPUTHANDLER_H_
#define CLIENTUSERINPUTHANDLER_H_

#include <QRegularExpression>

#include "basichandler.h"

class BufferInfo;
struct NetworkId;

class ClientUserInputHandler : public BasicHandler
{
    Q_OBJECT

public:
    ClientUserInputHandler(QObject* parent = nullptr);

public slots:
    void handleUserInput(const BufferInfo& bufferInfo, const QString& msg);

signals:
    void sendInput(const BufferInfo&, const QString&);

private slots:
    void completionSuffixChanged(const QVariant&);

    void handleExec(const BufferInfo& bufferInfo, const QString& execString);
    void handleJoin(const BufferInfo& bufferInfo, const QString& text);
    void handleQuery(const BufferInfo& bufferInfo, const QString& text);
    void handleIgnore(const BufferInfo& bufferInfo, const QString& text);
    void handleList(const BufferInfo& bufferInfo, const QString& text);
    void defaultHandler(const QString& cmd, const BufferInfo& bufferInfo, const QString& text);

private:
    QRegularExpression _nickRx;

    //! Helper method for switching to new/existing buffers
    /** Immediately switches to the given buffer or schedules a switch for whenever
     * the buffer is created
     */
    void switchBuffer(const NetworkId& networkId, const QString& bufferName);
};

#endif
