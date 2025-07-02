// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QLabel>

class UISUPPORT_EXPORT ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    ClickableLabel(QWidget* parent = nullptr);

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
};
