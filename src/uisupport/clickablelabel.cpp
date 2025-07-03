// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clickablelabel.h"

#include <QDebug>
#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->pos().x() > size().width() || event->pos().y() > size().height())
        return;

    event->accept();
    emit clicked();
}
