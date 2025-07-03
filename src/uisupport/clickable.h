// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <vector>

#include <QStackedWidget>

#include "types.h"

class QModelIndex;

class UISUPPORT_EXPORT Clickable
{
public:
    // Don't change these enums without also changing dependent methods!
    enum Type
    {
        Invalid = -1,
        Url = 0,
        Channel = 1,
        Nick = 2
    };

    explicit inline Clickable(Type type = Invalid, quint16 start = 0, quint16 length = 0)
        : _type(type)
        , _start(start)
        , _length(length)
    {
    }

    inline Type type() const { return _type; }
    inline quint16 start() const { return _start; }
    inline quint16 length() const { return _length; }

    inline bool isValid() const { return _type != Invalid; }

    void activate(NetworkId networkId, const QString& bufferName) const;

private:
    Type _type;
    quint16 _start;
    quint16 _length;
};

class UISUPPORT_EXPORT ClickableList : public std::vector<Clickable>
{
public:
    static ClickableList fromString(const QString&);

    Clickable atCursorPos(int idx);
};
