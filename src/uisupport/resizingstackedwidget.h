// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QStackedWidget>

class UISUPPORT_EXPORT ResizingStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    ResizingStackedWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;

private slots:
    void indexChanged(int index);
};
