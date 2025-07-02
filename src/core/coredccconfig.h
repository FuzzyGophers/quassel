// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "dccconfig.h"

class CoreSession;

/**
 * Core-side specialization for DccConfig.
 *
 * Adds the ability to load/save the settings from/to the database.
 */
class CoreDccConfig : public DccConfig
{
    Q_OBJECT
public:
    /**
     * Constructor.
     *
     * @param[in] session Pointer to the parent CoreSession (takes ownership)
     */
    CoreDccConfig(CoreSession* session);

public slots:
    /**
     * Saves the config to the database.
     */
    void save();

private:
    CoreSession* _coreSession{nullptr};  ///< Pointer to the parent CoreSession
};
