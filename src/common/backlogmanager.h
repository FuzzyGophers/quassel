// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include "syncableobject.h"
#include "types.h"

class COMMON_EXPORT BacklogManager : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

public:
    BacklogManager(QObject* parent = nullptr)
        : SyncableObject(parent)
    {}

public slots:
    virtual QVariantList requestBacklog(BufferId bufferId, MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0);
    virtual QVariantList requestBacklogFiltered(
        BufferId bufferId, MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0, int type = -1, int flags = -1);
    virtual QVariantList requestBacklogForward(
        BufferId bufferId, MsgId first = -1, MsgId last = -1, int limit = -1, int type = -1, int flags = -1);
    inline virtual void receiveBacklog(BufferId, MsgId, MsgId, int, int, QVariantList){};
    inline virtual void receiveBacklogFiltered(BufferId, MsgId, MsgId, int, int, int, int, QVariantList){};
    inline virtual void receiveBacklogForward(BufferId, MsgId, MsgId, int, int, int, QVariantList){};

    virtual QVariantList requestBacklogAll(MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0);
    virtual QVariantList requestBacklogAllFiltered(
        MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0, int type = -1, int flags = -1);
    inline virtual void receiveBacklogAll(MsgId, MsgId, int, int, QVariantList){};
    inline virtual void receiveBacklogAllFiltered(MsgId, MsgId, int, int, int, int, QVariantList){};

signals:
    void backlogRequested(BufferId, MsgId, MsgId, int, int);
    void backlogAllRequested(MsgId, MsgId, int, int);
};
