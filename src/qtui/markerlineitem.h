// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef MARKERLINEITEM_H_
#define MARKERLINEITEM_H_

#include <QGraphicsObject>

#include "chatscene.h"

class ChatLine;

class MarkerLineItem : public QGraphicsObject
{
    Q_OBJECT

public:
    MarkerLineItem(qreal sceneWidth, QGraphicsItem* parent = nullptr);
    inline int type() const override { return ChatScene::MarkerLineType; }

    inline QRectF boundingRect() const override { return _boundingRect; }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    inline ChatLine* chatLine() const { return _chatLine; }

public slots:
    //! Set the ChatLine this MarkerLineItem is associated to
    void setChatLine(ChatLine* line);
    void sceneRectChanged(const QRectF&);

private slots:
    void styleChanged();

private:
    QRectF _boundingRect;
    QBrush _brush;
    ChatLine* _chatLine;
};

#endif
