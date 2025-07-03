// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreircuser.h"

#include "corenetwork.h"

CoreIrcUser::CoreIrcUser(const QString& hostmask, Network* network)
    : IrcUser(hostmask, network)
{
#ifdef HAVE_QCA2
    _cipher = nullptr;

    // Get the cipher key from CoreNetwork if present
    auto* coreNetwork = qobject_cast<CoreNetwork*>(network);
    if (coreNetwork) {
        QByteArray key = coreNetwork->readChannelCipherKey(nick().toLower());
        if (!key.isEmpty()) {
            if (!_cipher) {
                _cipher = new Cipher();
            }
            setEncrypted(_cipher->setKey(key));
        }
    }
#endif
}

CoreIrcUser::~CoreIrcUser()
{
#ifdef HAVE_QCA2
    // Store the cipher key in CoreNetwork, including empty keys if a cipher
    // exists. There is no need to store the empty key if no cipher exists; no
    // key was present when instantiating and no key was set during the
    // channel's lifetime.
    auto* coreNetwork = qobject_cast<CoreNetwork*>(network());
    if (coreNetwork && _cipher) {
        coreNetwork->storeChannelCipherKey(nick().toLower(), _cipher->key());
    }

    delete _cipher;
#endif
}

#ifdef HAVE_QCA2
Cipher* CoreIrcUser::cipher() const
{
    if (!_cipher)
        _cipher = new Cipher();

    return _cipher;
}

#endif
