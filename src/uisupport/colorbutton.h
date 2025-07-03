// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QToolButton>

class UISUPPORT_EXPORT ColorButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor USER true)

public:
    explicit ColorButton(QWidget* parent = nullptr);
    explicit ColorButton(const QColor& c, QWidget* parent = nullptr);

    void setColor(const QColor& color);
    QColor color() const;

signals:
    void colorChanged(const QColor&);

private slots:
    void chooseColor();

private:
    QColor _color;
};
