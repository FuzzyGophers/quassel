// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QGraphicsItem>
#include <QModelIndex>
#include <QRectF>

#include "chatitem.h"
#include "chatlinemodel.h"
#include "chatscene.h"

class QAbstractItemModel;
class QEvent;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;
class QPainter;
class QStyleOptionGraphicsItem;

class ChatLine : public QGraphicsItem
{
public:
    ChatLine(int row,
             QAbstractItemModel* model,
             const qreal& width,
             const qreal& timestampWidth,
             const qreal& senderWidth,
             const qreal& contentsWidth,
             const QPointF& senderPos,
             const QPointF& contentsPos,
             QGraphicsItem* parent = nullptr);

    ~ChatLine() override;

    inline QRectF boundingRect() const override { return {0, 0, _width, _height}; }

    inline QModelIndex index() const { return model()->index(row(), 0); }
    inline MsgId msgId() const { return index().data(MessageModel::MsgIdRole).value<MsgId>(); }
    inline Message::Type msgType() const { return (Message::Type)index().data(MessageModel::TypeRole).toInt(); }

    inline int row() const { return _row; }
    inline void setRow(int row) { _row = row; }

    inline const QAbstractItemModel* model() const { return _model; }
    inline ChatScene* chatScene() const { return qobject_cast<ChatScene*>(scene()); }
    inline ChatView* chatView() const { return chatScene() ? chatScene()->chatView() : nullptr; }

    inline qreal width() const { return _width; }
    inline qreal height() const { return _height; }

    ChatItem* item(ChatLineModel::ColumnType);
    ChatItem* itemAt(const QPointF& pos);
    inline ChatItem* timestampItem() { return &_timestampItem; }
    inline ChatItem* senderItem() { return &_senderItem; }
    inline ContentsChatItem* contentsItem() { return &_contentsItem; }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    enum
    {
        Type = ChatScene::ChatLineType
    };
    inline int type() const override { return Type; }

    // pos is relative to the parent ChatLine
    void setFirstColumn(const qreal& timestampWidth, const qreal& senderWidth, const QPointF& senderPos);
    // setSecondColumn and setGeometryByWidth both also relocate the chatline.
    // the _bottom_ position is passed via linePos. linePos is updated to the top of the chatLine.
    void setSecondColumn(const qreal& senderWidth, const qreal& contentsWidth, const QPointF& contentsPos, qreal& linePos);
    void setGeometryByWidth(const qreal& width, const qreal& contentsWidth, qreal& linePos);

    void setSelected(bool selected, ChatLineModel::ColumnType minColumn = ChatLineModel::ContentsColumn);
    void setHighlighted(bool highlighted);

    void clearCache();

protected:
    bool sceneEvent(QEvent* event) override;

    // These need to be relayed to the appropriate ChatItem
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

    ChatItem* mouseEventTargetItem(const QPointF& pos);

    inline ChatItem* mouseGrabberItem() const { return _mouseGrabberItem; }
    void setMouseGrabberItem(ChatItem* item);

private:
    int _row;
    QAbstractItemModel* _model;
    ContentsChatItem _contentsItem;
    SenderChatItem _senderItem;
    TimestampChatItem _timestampItem;
    qreal _width, _height;

    enum
    {
        ItemMask = 0x3f,
        Selected = 0x40,
        Highlighted = 0x80
    };
    // _selection[1..0] ... Min Selected Column (See MessageModel::ColumnType)
    // _selection[5..2] ... reserved for new column types
    // _selection[6] ...... Selected
    // _selection[7] ...... Highlighted
    quint8 _selection;  // save space, so we put both the col and the flags into one byte

    ChatItem* _mouseGrabberItem;
    ChatItem* _hoverItem;
};
