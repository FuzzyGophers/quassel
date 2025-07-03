// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ircuser.h"

#ifdef HAVE_QCA2
#    include "cipher.h"
#endif

class CoreIrcUser : public IrcUser
{
    Q_OBJECT

public:
    CoreIrcUser(const QString& hostmask, Network* network);
    ~CoreIrcUser() override;

#ifdef HAVE_QCA2
    Cipher* cipher() const;
#endif

#ifdef HAVE_QCA2
private:
    mutable Cipher* _cipher;
#endif
};
