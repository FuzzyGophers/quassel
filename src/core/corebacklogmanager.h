// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "backlogmanager.h"

class CoreSession;

class CoreBacklogManager : public BacklogManager
{
    Q_OBJECT

public:
    CoreBacklogManager(CoreSession* coreSession = nullptr);

    CoreSession* coreSession() { return _coreSession; }

public slots:
    QVariantList requestBacklog(BufferId bufferId, MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0) override;
    QVariantList requestBacklogFiltered(
        BufferId bufferId, MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0, int type = -1, int flags = -1) override;
    QVariantList requestBacklogForward(
        BufferId bufferId, MsgId first = -1, MsgId last = -1, int limit = -1, int type = -1, int flags = -1) override;
    QVariantList requestBacklogAll(MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0) override;
    QVariantList requestBacklogAllFiltered(
        MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0, int type = -1, int flags = -1) override;

private:
    CoreSession* _coreSession;
};
