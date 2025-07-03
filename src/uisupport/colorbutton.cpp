// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "colorbutton.h"

#include <QColorDialog>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>

ColorButton::ColorButton(QWidget* parent)
    : QToolButton(parent)
{
    setText("");
    connect(this, &QAbstractButton::clicked, this, &ColorButton::chooseColor);
}

void ColorButton::setColor(const QColor& color)
{
    _color = color;
    QPixmap pixmap(QSize(32, 32));
    pixmap.fill(color);
    setIcon(pixmap);

    emit colorChanged(color);
}

QColor ColorButton::color() const
{
    return _color;
}

void ColorButton::chooseColor()
{
    QColor c = QColorDialog::getColor(color(), this);
    if (c.isValid()) {
        setColor(c);
    }
}
