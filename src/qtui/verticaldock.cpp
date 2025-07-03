// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "verticaldock.h"

#include <QDebug>
#include <QLayout>
#include <QPainter>
#include <qdrawutil.h>

VerticalDockTitle::VerticalDockTitle(QDockWidget* parent)
    : QWidget(parent)
{
}

QSize VerticalDockTitle::sizeHint() const
{
    return {8, 15};
}

QSize VerticalDockTitle::minimumSizeHint() const
{
    return {8, 10};
}

void VerticalDockTitle::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    if (rect().isValid() && rect().height() > minimumSizeHint().height()) {
        for (int i = 0; i < 2; i++) {
            QPoint topLeft = rect().topLeft() + QPoint(3 + i * 2, 2);
            QPoint bottomRight = rect().topLeft() + QPoint(3 + i * 2, rect().height() - 2);
            qDrawShadeLine(&painter, topLeft, bottomRight, palette());
        }
    }
}

// ==============================
//  Vertical Dock
// ==============================
VerticalDock::VerticalDock(const QString& title, QWidget* parent, Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags)
{
    setDefaultTitleWidget();
}

VerticalDock::VerticalDock(QWidget* parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags)
{
    setDefaultTitleWidget();
    setContentsMargins(0, 0, 0, 0);
}

void VerticalDock::setDefaultTitleWidget()
{
    QWidget* oldDockTitle = titleBarWidget();
    QWidget* newDockTitle = new VerticalDockTitle(this);

    setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    setFeatures(features() | QDockWidget::DockWidgetVerticalTitleBar);
    setTitleBarWidget(newDockTitle);

    if (oldDockTitle)
        oldDockTitle->deleteLater();
}

void VerticalDock::showTitle(bool show)
{
    QWidget* oldDockTitle = titleBarWidget();
    QWidget* newDockTitle = nullptr;

    if (show)
        newDockTitle = new VerticalDockTitle(this);
    else
        newDockTitle = new EmptyDockTitle(this);

    setTitleBarWidget(newDockTitle);
    if (oldDockTitle)
        oldDockTitle->deleteLater();
}
