// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include "bufferviewconfig.h"

class CLIENT_EXPORT ClientBufferViewConfig : public BufferViewConfig
{
    Q_OBJECT

public:
    ClientBufferViewConfig(int bufferViewId, QObject* parent = nullptr);

    inline bool isLocked() { return _locked || sortAlphabetically(); }
    inline void setLocked(bool locked) { _locked = locked; }
    inline void lock() { setLocked(true); };
    inline void unlock() { setLocked(false); };

private slots:
    void ensureDecoration();  // remove this in next release

private:
    bool _locked;
};
