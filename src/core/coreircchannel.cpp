// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreircchannel.h"

#include "corenetwork.h"

CoreIrcChannel::CoreIrcChannel(const QString& channelname, Network* network)
    : IrcChannel(channelname, network)
    , _receivedWelcomeMsg(false)
{
#ifdef HAVE_QCA2
    _cipher = nullptr;

    // Get the cipher key from CoreNetwork if present
    auto* coreNetwork = qobject_cast<CoreNetwork*>(network);
    if (coreNetwork) {
        QByteArray key = coreNetwork->readChannelCipherKey(channelname);
        if (!key.isEmpty()) {
            setEncrypted(cipher()->setKey(key));
        }
    }
#endif
}

CoreIrcChannel::~CoreIrcChannel()
{
#ifdef HAVE_QCA2
    // Store the cipher key in CoreNetwork, including empty keys if a cipher
    // exists. There is no need to store the empty key if no cipher exists; no
    // key was present when instantiating and no key was set during the
    // channel's lifetime.
    auto* coreNetwork = qobject_cast<CoreNetwork*>(network());
    if (coreNetwork && _cipher) {
        coreNetwork->storeChannelCipherKey(name(), _cipher->key());
    }

    delete _cipher;
#endif
}

#ifdef HAVE_QCA2
Cipher* CoreIrcChannel::cipher() const
{
    if (!_cipher)
        _cipher = new Cipher();

    return _cipher;
}

void CoreIrcChannel::setEncrypted(bool e)
{
    IrcChannel::setEncrypted(e);

    if (!Cipher::neededFeaturesAvailable())
        return;

    if (e) {
        if (topic().isEmpty())
            return;

        QByteArray decrypted = cipher()->decryptTopic(topic().toLatin1());
        setTopic(decodeString(decrypted));
    }
}

#endif
