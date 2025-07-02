// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ircchannel.h"

#ifdef HAVE_QCA2
#    include "cipher.h"
#endif

class CoreIrcChannel : public IrcChannel
{
    Q_OBJECT

public:
    CoreIrcChannel(const QString& channelname, Network* network);
    ~CoreIrcChannel() override;

#ifdef HAVE_QCA2
    Cipher* cipher() const;
    void setEncrypted(bool);
#endif

    inline bool receivedWelcomeMsg() const { return _receivedWelcomeMsg; }
    inline void setReceivedWelcomeMsg() { _receivedWelcomeMsg = true; }

private:
    bool _receivedWelcomeMsg;

#ifdef HAVE_QCA2
    mutable Cipher* _cipher;
#endif
};
