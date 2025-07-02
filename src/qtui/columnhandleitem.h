// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef COLUMNHANDLEITEM_H_
#define COLUMNHANDLEITEM_H_

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPropertyAnimation>

#include "chatscene.h"

class ColumnHandleItem : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    ColumnHandleItem(qreal width, QGraphicsItem* parent = nullptr);
    inline int type() const override { return ChatScene::ColumnHandleType; }

    inline qreal width() const { return _width; }
    inline QRectF boundingRect() const override { return _boundingRect; }
    inline qreal sceneLeft() const { return _sceneLeft; }
    inline qreal sceneRight() const { return _sceneRight; }

    inline qreal opacity() const { return _opacity; }

    void setXPos(qreal xpos);
    void setXLimits(qreal min, qreal max);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

public slots:
    void sceneRectChanged(const QRectF&);
    void setOpacity(qreal opacity);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void positionChanged(qreal x);

private:
    qreal _width;
    qreal _sceneLeft, _sceneRight;
    QRectF _boundingRect;
    bool _moving;
    qreal _offset;
    qreal _minXPos, _maxXPos;
    qreal _opacity;
    QPropertyAnimation* _animation;
};

#endif
