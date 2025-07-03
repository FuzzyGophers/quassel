// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QSortFilterProxyModel>

#include "types.h"

class BufferViewOverlay;

class UISUPPORT_EXPORT BufferViewOverlayFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    BufferViewOverlayFilter(QAbstractItemModel* model, BufferViewOverlay* overlay = nullptr);

    void setOverlay(BufferViewOverlay* overlay);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;

private slots:
    void overlayDestroyed();

private:
    BufferViewOverlay* _overlay;
};
