// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "chatline.h"

#include <QAbstractItemModel>
#include <QDateTime>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QString>
#include <QStyleOptionGraphicsItem>
#include <QTextCharFormat>

class QAbstractItemModel;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;
class QPainter;
class QStyleOptionGraphicsItem;

#include "bufferinfo.h"
#include "buffersyncer.h"
#include "chatitem.h"
#include "chatview.h"
#include "client.h"
#include "columnhandleitem.h"
#include "messagemodel.h"
#include "networkmodel.h"
#include "qtui.h"
#include "qtuisettings.h"
#include "qtuistyle.h"

ChatLine::ChatLine(int row,
                   QAbstractItemModel* model,
                   const qreal& width,
                   const qreal& timestampWidth,
                   const qreal& senderWidth,
                   const qreal& contentsWidth,
                   const QPointF& senderPos,
                   const QPointF& contentsPos,
                   QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , _row(row)  // needs to be set before the items
    , _model(model)
    , _contentsItem(contentsPos, contentsWidth, this)
    , _senderItem(QRectF(senderPos, QSizeF(senderWidth, _contentsItem.height())), this)
    , _timestampItem(QRectF(0, 0, timestampWidth, _contentsItem.height()), this)
    , _width(width)
    , _height(_contentsItem.height())
    , _selection(0)
    , _mouseGrabberItem(nullptr)
    , _hoverItem(nullptr)
{
    Q_ASSERT(model);
    QModelIndex index = model->index(row, ChatLineModel::ContentsColumn);
    setZValue(0);
    setAcceptHoverEvents(true);
    setHighlighted(index.data(MessageModel::FlagsRole).toInt() & Message::Highlight);
}

ChatLine::~ChatLine()
{
    if (chatView())
        chatView()->setHasCache(this, false);
}

ChatItem* ChatLine::item(ChatLineModel::ColumnType column)
{
    switch (column) {
    case ChatLineModel::TimestampColumn:
        return &_timestampItem;
    case ChatLineModel::SenderColumn:
        return &_senderItem;
    case ChatLineModel::ContentsColumn:
        return &_contentsItem;
    default:
        return nullptr;
    }
}

ChatItem* ChatLine::itemAt(const QPointF& pos)
{
    if (_contentsItem.boundingRect().contains(pos))
        return &_contentsItem;
    if (_senderItem.boundingRect().contains(pos))
        return &_senderItem;
    if (_timestampItem.boundingRect().contains(pos))
        return &_timestampItem;
    return nullptr;
}

void ChatLine::clearCache()
{
    _timestampItem.clearCache();
    _senderItem.clearCache();
    _contentsItem.clearCache();
}

void ChatLine::setMouseGrabberItem(ChatItem* item)
{
    _mouseGrabberItem = item;
}

bool ChatLine::sceneEvent(QEvent* event)
{
    if (event->type() == QEvent::GrabMouse) {
        // get mouse cursor pos relative to us
        ChatView* view = chatScene()->chatView();
        QPointF linePos = mapFromScene(view->mapToScene(view->mapFromGlobal(QCursor::pos())));
        setMouseGrabberItem(itemAt(linePos));
    }
    else if (event->type() == QEvent::UngrabMouse) {
        setMouseGrabberItem(nullptr);
    }
    return QGraphicsItem::sceneEvent(event);
}

void ChatLine::setFirstColumn(const qreal& timestampWidth, const qreal& senderWidth, const QPointF& senderPos)
{
    _timestampItem.setGeometry(timestampWidth, _height);
    _senderItem.setGeometry(senderWidth, _height);
    _senderItem.setPos(senderPos);
}

void ChatLine::setSecondColumn(const qreal& senderWidth, const qreal& contentsWidth, const QPointF& contentsPos, qreal& linePos)
{
    // linepos is the *bottom* position for the line
    qreal height = _contentsItem.setGeometryByWidth(contentsWidth);
    linePos -= height;
    bool needGeometryChange = (height != _height);

    _timestampItem.setHeight(height);
    _senderItem.setGeometry(senderWidth, height);
    _contentsItem.setPos(contentsPos);

    if (needGeometryChange)
        prepareGeometryChange();

    _height = height;

    setPos(0, linePos);
}

void ChatLine::setGeometryByWidth(const qreal& width, const qreal& contentsWidth, qreal& linePos)
{
    // linepos is the *bottom* position for the line
    qreal height = _contentsItem.setGeometryByWidth(contentsWidth);
    linePos -= height;
    bool needGeometryChange = (height != _height || width != _width);

    if (height != _height) {
        _timestampItem.setHeight(height);
        _senderItem.setHeight(height);
    }

    if (needGeometryChange) {
        prepareGeometryChange();
        _height = height;
        _width = width;
    }

    setPos(0, linePos);  // set pos is _very_ cheap if nothing changes.
}

void ChatLine::setSelected(bool selected, ChatLineModel::ColumnType minColumn)
{
    if (selected) {
        quint8 sel = (_selection & Highlighted) | Selected | minColumn;
        if (sel != _selection) {
            _selection = sel;
            for (int i = 0; i < minColumn; i++)
                item((ChatLineModel::ColumnType)i)->clearSelection();
            for (int i = minColumn; i <= ChatLineModel::ContentsColumn; i++)
                item((ChatLineModel::ColumnType)i)->setFullSelection();
            update();
        }
    }
    else {
        quint8 sel = _selection & Highlighted;
        if (sel != _selection) {
            _selection = sel;
            for (int i = 0; i <= ChatLineModel::ContentsColumn; i++)
                item((ChatLineModel::ColumnType)i)->clearSelection();
            update();
        }
    }
}

void ChatLine::setHighlighted(bool highlighted)
{
    if (highlighted)
        _selection |= Highlighted;
    else
        _selection &= ~Highlighted;
    update();
}

void ChatLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const QAbstractItemModel* model_ = model();
    QModelIndex myIdx = model_->index(row(), 0);
    Message::Type type = (Message::Type)myIdx.data(MessageModel::TypeRole).toInt();
    auto label = myIdx.data(ChatLineModel::MsgLabelRole).value<UiStyle::MessageLabel>();

    QTextCharFormat msgFmt = QtUi::style()->format({UiStyle::formatType(type), {}, {}}, label);
    if (msgFmt.hasProperty(QTextFormat::BackgroundBrush)) {
        painter->fillRect(boundingRect(), msgFmt.background());
    }

    if (_selection & Selected) {
        QTextCharFormat selFmt = QtUi::style()->format({UiStyle::formatType(type), {}, {}}, label | UiStyle::MessageLabel::Selected);
        if (selFmt.hasProperty(QTextFormat::BackgroundBrush)) {
            qreal left = item((ChatLineModel::ColumnType)(_selection & ItemMask))->pos().x();
            QRectF selectRect(left, 0, width() - left, height());
            painter->fillRect(selectRect, selFmt.background());
        }
    }

    // draw chatitems
    // the items draw themselves at the correct position
    timestampItem()->paint(painter, option, widget);
    senderItem()->paint(painter, option, widget);
    contentsItem()->paint(painter, option, widget);
}

// We need to dispatch all mouse-related events to the appropriate (mouse grabbing) ChatItem

ChatItem* ChatLine::mouseEventTargetItem(const QPointF& pos)
{
    if (mouseGrabberItem())
        return mouseGrabberItem();
    return itemAt(pos);
}

void ChatLine::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    ChatItem* item = mouseEventTargetItem(event->pos());
    if (item)
        item->mouseMoveEvent(event);
}

void ChatLine::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    ChatItem* item = mouseEventTargetItem(event->pos());
    if (item)
        item->mousePressEvent(event);
}

void ChatLine::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    ChatItem* item = mouseEventTargetItem(event->pos());
    if (item)
        item->mouseReleaseEvent(event);
}

void ChatLine::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    ChatItem* item = mouseEventTargetItem(event->pos());
    if (item && !_hoverItem) {
        _hoverItem = item;
        item->hoverEnterEvent(event);
    }
}

void ChatLine::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    if (_hoverItem) {
        _hoverItem->hoverLeaveEvent(event);
        _hoverItem = nullptr;
    }
}

void ChatLine::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    ChatItem* item = mouseEventTargetItem(event->pos());
    if (item)
        item->hoverMoveEvent(event);
}
