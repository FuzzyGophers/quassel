// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "markerlineitem.h"

#include <QPainter>

#include "qtui.h"

MarkerLineItem::MarkerLineItem(qreal sceneWidth, QGraphicsItem* parent)
    : QGraphicsObject(parent)
    , _boundingRect(0, 0, sceneWidth, 1)
    , _chatLine(nullptr)
{
    setVisible(false);
    setZValue(8);
    styleChanged();  // init brush and height
    connect(QtUi::style(), &UiStyle::changed, this, &MarkerLineItem::styleChanged);
}

void MarkerLineItem::setChatLine(ChatLine* line)
{
    _chatLine = line;
    if (!line)
        setVisible(false);
}

void MarkerLineItem::styleChanged()
{
    _brush = QtUi::style()->brush(UiStyle::ColorRole::MarkerLine);

    // if this is a solid color, we assume 1px because wesurely  don't surely don't want to fill the entire chatline.
    // else, use the height of a single line of text to play around with gradients etc.
    qreal height = 1.;
    if (_brush.style() != Qt::SolidPattern)
        height = QtUi::style()->fontMetrics(QtUiStyle::FormatType::PlainMsg, UiStyle::MessageLabel::None)->lineSpacing();

    prepareGeometryChange();
    _boundingRect = QRectF(0, 0, scene() ? scene()->width() : 100, height);
}

void MarkerLineItem::sceneRectChanged(const QRectF& rect)
{
    prepareGeometryChange();
    _boundingRect.setWidth(rect.width());
}

void MarkerLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillRect(boundingRect(), _brush);
}
