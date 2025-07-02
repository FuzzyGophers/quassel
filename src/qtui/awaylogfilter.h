// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef AWAYLOGFILTER_H
#define AWAYLOGFILTER_H

#include "chatmonitorfilter.h"

class AwayLogFilter : public ChatMonitorFilter
{
    Q_OBJECT

public:
    AwayLogFilter(MessageModel* model, QObject* parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    QString idString() const override { return "AwayLog"; }
    QVariant data(const QModelIndex& index, int role) const override;
};

#endif  // AWAYLOGFILTER_H
