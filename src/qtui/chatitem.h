// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CHATITEM_H_
#define CHATITEM_H_

#include <utility>

#include <QAction>
#include <QObject>
#include <QTextLayout>

#include "chatlinemodel.h"
#include "chatscene.h"
#include "clickable.h"
#include "qtui.h"
#include "uistyle.h"

class ChatLine;
class ChatView;

/* All external positions are relative to the parent ChatLine */
/* Yes, that's also true for the boundingRect() and related things */

class ChatItem
{
protected:
    // boundingRect is relative to the parent ChatLine
    ChatItem(const QRectF& boundingRect, ChatLine* parent);
    virtual ~ChatItem();

public:
    const QAbstractItemModel* model() const;
    ChatLine* chatLine() const;
    ChatScene* chatScene() const;
    ChatView* chatView() const;
    int row() const;
    virtual ChatLineModel::ColumnType column() const = 0;

    // The boundingRect() is relative to the parent ChatLine
    inline QRectF boundingRect() const;
    inline qreal width() const;
    inline qreal height() const;
    inline QPointF pos() const;
    inline qreal x() const;
    inline qreal y() const;

    QPointF mapToLine(const QPointF&) const;
    QPointF mapFromLine(const QPointF&) const;
    QPointF mapToScene(const QPointF&) const;
    QPointF mapFromScene(const QPointF&) const;

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
    virtual inline int type() const { return ChatScene::ChatItemType; }

    QVariant data(int role) const;

    // selection stuff, to be called by the scene
    QString selection() const;
    void clearSelection();
    void setFullSelection();
    void continueSelecting(const QPointF& pos);
    bool hasSelection() const;
    bool isPosOverSelection(const QPointF& pos) const;

    QList<QRectF> findWords(const QString& searchWord, Qt::CaseSensitivity caseSensitive);

    virtual void addActionsToMenu(QMenu* menu, const QPointF& itemPos);
    virtual void handleClick(const QPointF& pos, ChatScene::ClickMode);

    void initLayoutHelper(QTextLayout* layout, QTextOption::WrapMode, Qt::Alignment = Qt::AlignLeft) const;

    //! Remove internally cached data
    /** This removes e.g. the cached QTextLayout to avoid wasting space for nonvisible ChatLines
     */
    virtual void clearCache();

protected:
    enum SelectionMode
    {
        NoSelection,
        PartialSelection,
        FullSelection
    };

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent*) {}
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent*) {}
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent*) {}

    QTextLayout* layout() const;

    virtual void initLayout(QTextLayout* layout) const;
    virtual void doLayout(QTextLayout*) const;
    virtual UiStyle::FormatList formatList() const;

    void paintBackground(QPainter*);
    virtual QVector<QTextLayout::FormatRange> additionalFormats() const;
    void overlayFormat(UiStyle::FormatList& fmtList, quint16 start, quint16 end, UiStyle::FormatType overlayFmt) const;

    inline qint16 selectionStart() const { return _selectionStart; }
    inline void setSelectionStart(qint16 start) { _selectionStart = start; }
    inline qint16 selectionEnd() const { return _selectionEnd; }
    inline void setSelectionEnd(qint16 end) { _selectionEnd = end; }
    inline SelectionMode selectionMode() const { return _selectionMode; }
    inline void setSelectionMode(SelectionMode mode) { _selectionMode = mode; }
    void setSelection(SelectionMode mode, qint16 selectionStart, qint16 selectionEnd);

    virtual bool hasActiveClickable() const;
    virtual std::pair<quint16, quint16> activeClickableRange() const;

    qint16 posToCursor(const QPointF& pos) const;

    inline void setGeometry(qreal width, qreal height)
    {
        clearCache();
        _boundingRect.setSize(QSizeF(width, height));
    }
    inline void setHeight(const qreal& height)
    {
        clearCache();
        _boundingRect.setHeight(height);
    }
    inline void setWidth(const qreal& width)
    {
        clearCache();
        _boundingRect.setWidth(width);
    }
    inline void setPos(const QPointF& pos) { _boundingRect.moveTopLeft(pos); }

private:
    ChatLine* _parent;
    QRectF _boundingRect;

    SelectionMode _selectionMode;
    qint16 _selectionStart, _selectionEnd;

    mutable QTextLayout* _cachedLayout;

    // internal selection stuff
    void setSelection(int start, int length);

    friend class ChatLine;
};

// ************************************************************
// TimestampChatItem
// ************************************************************

//! A ChatItem for the timestamp column
class TimestampChatItem : public ChatItem
{
public:
    TimestampChatItem(const QRectF& boundingRect, ChatLine* parent)
        : ChatItem(boundingRect, parent)
    {
    }
    inline int type() const override { return ChatScene::TimestampChatItemType; }
    inline ChatLineModel::ColumnType column() const override { return ChatLineModel::TimestampColumn; }
};

// ************************************************************
// SenderChatItem
// ************************************************************
//! A ChatItem for the sender column
class SenderChatItem : public ChatItem
{
public:
    SenderChatItem(const QRectF& boundingRect, ChatLine* parent)
        : ChatItem(boundingRect, parent)
    {
    }
    inline ChatLineModel::ColumnType column() const override { return ChatLineModel::SenderColumn; }
    void handleClick(const QPointF& pos, ChatScene::ClickMode clickMode) override;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    inline int type() const override { return ChatScene::SenderChatItemType; }
    void initLayout(QTextLayout* layout) const override;
};

// ************************************************************
// ContentsChatItem
// ************************************************************
struct ContentsChatItemPrivate;

//! A ChatItem for the contents column
class ContentsChatItem : public ChatItem
{
    Q_DECLARE_TR_FUNCTIONS(ContentsChatItem)

public:
    ContentsChatItem(const QPointF& pos, const qreal& width, ChatLine* parent);
    ~ContentsChatItem() override;

    inline int type() const override { return ChatScene::ContentsChatItemType; }

    inline ChatLineModel::ColumnType column() const override { return ChatLineModel::ContentsColumn; }
    QFontMetricsF* fontMetrics() const;

    void clearCache() override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void handleClick(const QPointF& pos, ChatScene::ClickMode clickMode) override;

    bool hasActiveClickable() const override;
    std::pair<quint16, quint16> activeClickableRange() const override;

    void addActionsToMenu(QMenu* menu, const QPointF& itemPos) override;
    virtual void copyLinkToClipboard();

    void initLayout(QTextLayout* layout) const override;
    void doLayout(QTextLayout* layout) const override;
    UiStyle::FormatList formatList() const override;

private:
    class ActionProxy;
    class WrapColumnFinder;

    mutable ContentsChatItemPrivate* _data;
    ContentsChatItemPrivate* privateData() const;

    Clickable clickableAt(const QPointF& pos) const;

    void endHoverMode();
    void showWebPreview(const Clickable& click);
    void clearWebPreview();

    qreal setGeometryByWidth(qreal w);

    QFontMetricsF* _fontMetrics;

    // we need a receiver for Action signals
    static ActionProxy _actionProxy;

    friend class ChatLine;
    friend struct ContentsChatItemPrivate;
};

struct ContentsChatItemPrivate
{
    ContentsChatItem* contentsItem;
    ClickableList clickables;
    Clickable currentClickable;
    Clickable activeClickable;

    ContentsChatItemPrivate(ClickableList c, ContentsChatItem* parent)
        : contentsItem(parent)
        , clickables(std::move(c))
    {
    }
};

class ContentsChatItem::WrapColumnFinder
{
public:
    WrapColumnFinder(const ChatItem* parent);

    qint16 nextWrapColumn(qreal width);

private:
    const ChatItem* item;
    QTextLayout layout;
    QTextLine line;
    ChatLineModel::WrapList wrapList;
    qint16 wordidx;
    qint16 lineCount;
    qreal choppedTrailing;
};

//! Acts as a proxy for Action signals targeted at a ContentsChatItem
/** Since a ChatItem is not a QObject, hence cannot receive signals, we use a static ActionProxy
 *  as a receiver instead. This avoids having to handle ChatItem actions (e.g. context menu entries)
 *  outside the ChatItem.
 */
class ContentsChatItem::ActionProxy : public QObject
{
    Q_OBJECT

public slots:
    inline void copyLinkToClipboard() { item()->copyLinkToClipboard(); }

private:
    /// Returns the ContentsChatItem that should receive the action event.
    /** For efficiency reasons, values are not checked for validity. You gotta make sure that you set the data() member
     *  in the Action correctly.
     *  @return The ChatItem from which the sending Action originated
     */
    inline ContentsChatItem* item() const
    {
        return static_cast<ContentsChatItem*>(qobject_cast<QAction*>(sender())->data().value<void*>());
    }
};

/*************************************************************************************************/

// Inlines

QRectF ChatItem::boundingRect() const
{
    return _boundingRect;
}
qreal ChatItem::width() const
{
    return _boundingRect.width();
}
qreal ChatItem::height() const
{
    return _boundingRect.height();
}
QPointF ChatItem::pos() const
{
    return _boundingRect.topLeft();
}
qreal ChatItem::x() const
{
    return pos().x();
}
qreal ChatItem::y() const
{
    return pos().y();
}

#endif
