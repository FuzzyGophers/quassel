// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-FileCopyrightText: 1997 Robey Pointer <robeypointer@gmail.com>
// SPDX-FileCopyrightText: 2005 Ismail Donmez <ismail@kde.org>
// SPDX-FileCopyrightText: 2009 Travis McHenry <tmchenryaz@cox.net>
// SPDX-FileCopyrightText: 2009 Johannes Huber <johu@gmx.de>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CIPHER_H
#define CIPHER_H

#include <QtCrypto>

class Cipher
{
public:
    Cipher();
    explicit Cipher(QByteArray key, QString cipherType = QString("blowfish"));
    QByteArray decrypt(QByteArray cipher);
    QByteArray decryptTopic(QByteArray cipher);
    bool encrypt(QByteArray& cipher);
    QByteArray initKeyExchange();
    QByteArray parseInitKeyX(QByteArray key);
    bool parseFinishKeyX(QByteArray key);
    bool setKey(QByteArray key);
    QByteArray key() { return m_key; }
    bool setType(const QString& type);
    QString type() { return m_type; }
    static bool neededFeaturesAvailable();
    inline bool usesCBC() { return m_cbc; }

private:
    // direction is true for encrypt, false for decrypt
    QByteArray blowfishCBC(QByteArray cipherText, bool direction);
    QByteArray blowfishECB(QByteArray cipherText, bool direction);
    QByteArray b64ToByte(QByteArray text);
    QByteArray byteToB64(QByteArray text);

    QCA::Initializer init;
    QByteArray m_key;
    QCA::DHPrivateKey m_tempKey;
    QCA::BigInteger m_primeNum;
    QString m_type;
    bool m_cbc;
};

#endif  // CIPHER_H
