// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include "syncableobject.h"

/*
 * gather various information about the core.
 */

class COMMON_EXPORT CoreInfo : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

    Q_PROPERTY(QVariantMap coreData READ coreData WRITE setCoreData)

public:
    explicit CoreInfo(QObject* parent = nullptr);
    inline QVariant& at(const QString& key) { return _coreData[key]; }

    void setConnectedClientData(int, QVariantList);

    /**
     * Reset the core info state, clearing anything saved
     */
    void reset();

signals:
    /**
     * Signals that core information has changed
     */
    void coreDataChanged(QVariantMap);

public slots:
    QVariantMap coreData() const;
    void setCoreData(const QVariantMap&);

private:
    QVariantMap _coreData;
};
