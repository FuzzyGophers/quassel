// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef DEBUGMESSAGEMODELFILTER_H
#define DEBUGMESSAGEMODELFILTER_H

#include <QSortFilterProxyModel>

class DebugMessageModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    DebugMessageModelFilter(QObject* parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex& index, int role) const override;
};

#endif  // DEBUGMESSAGEMODELFILTER_H
