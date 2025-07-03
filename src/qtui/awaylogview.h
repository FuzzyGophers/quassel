// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef AWAYLOGVIEW_H
#define AWAYLOGVIEW_H

#include "chatmonitorview.h"

class AwayLogFilter;

class AwayLogView : public ChatMonitorView
{
    Q_OBJECT

public:
    AwayLogView(AwayLogFilter* filter, QWidget* parent = nullptr);
    void addActionsToMenu(QMenu* menu, const QPointF& pos) override;
};

#endif  // AWAYLOGVIEW_H
