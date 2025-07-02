// SPDX-License-Identifier: GPL-2.0-or-later

#include "resizingstackedwidget.h"

ResizingStackedWidget::ResizingStackedWidget(QWidget* parent)
    : QStackedWidget(parent)
{
    connect(this, &QStackedWidget::currentChanged, this, &ResizingStackedWidget::indexChanged);
}

QSize ResizingStackedWidget::sizeHint() const
{
    QWidget* widget = currentWidget();
    if (!widget)
        return {};
    return widget->sizeHint();
}

void ResizingStackedWidget::indexChanged(int index)
{
    Q_UNUSED(index)
    updateGeometry();
}
