// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef COREEVENTMANAGER_H
#define COREEVENTMANAGER_H

#include "corenetwork.h"
#include "coresession.h"
#include "eventmanager.h"

class CoreEventManager : public EventManager
{
    Q_OBJECT

public:
    CoreEventManager(CoreSession* session)
        : EventManager(session)
        , _coreSession(session)
    {}

protected:
    inline Network* networkById(NetworkId id) const override { return _coreSession->network(id); }

private:
    CoreSession* _coreSession;
};

#endif
