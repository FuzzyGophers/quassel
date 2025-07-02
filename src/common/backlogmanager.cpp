// SPDX-License-Identifier: GPL-2.0-or-later

#include "backlogmanager.h"

QVariantList BacklogManager::requestBacklog(BufferId bufferId, MsgId first, MsgId last, int limit, int additional)
{
    REQUEST(ARG(bufferId), ARG(first), ARG(last), ARG(limit), ARG(additional))
    return QVariantList();
}

QVariantList BacklogManager::requestBacklogFiltered(BufferId bufferId, MsgId first, MsgId last, int limit, int additional, int type, int flags)
{
    REQUEST(ARG(bufferId), ARG(first), ARG(last), ARG(limit), ARG(additional), ARG(type), ARG(flags))
    return QVariantList();
}

QVariantList BacklogManager::requestBacklogForward(BufferId bufferId, MsgId first, MsgId last, int limit, int type, int flags)
{
    REQUEST(ARG(bufferId), ARG(first), ARG(last), ARG(limit), ARG(type), ARG(flags))
    return QVariantList();
}

QVariantList BacklogManager::requestBacklogAll(MsgId first, MsgId last, int limit, int additional)
{
    REQUEST(ARG(first), ARG(last), ARG(limit), ARG(additional))
    return QVariantList();
}

QVariantList BacklogManager::requestBacklogAllFiltered(MsgId first, MsgId last, int limit, int additional, int type, int flags)
{
    REQUEST(ARG(first), ARG(last), ARG(limit), ARG(additional), ARG(type), ARG(flags))
    return QVariantList();
}
