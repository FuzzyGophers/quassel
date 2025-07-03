// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CHATVIEWSEARCHCONTROLLER_H
#define CHATVIEWSEARCHCONTROLLER_H

#include <QGraphicsItem>
#include <QHash>
#include <QPointer>
#include <QString>
#include <QTimeLine>

#include "chatscene.h"
#include "message.h"

class QGraphicsItem;
class ChatLine;
class SearchHighlightItem;

class ChatViewSearchController : public QObject
{
    Q_OBJECT

public:
    ChatViewSearchController(QObject* parent = nullptr);

    inline const QString& searchString() const { return _searchString; }

    void setScene(ChatScene* scene);

public slots:
    void setSearchString(const QString& searchString);
    void setCaseSensitive(bool caseSensitive);
    void setSearchSenders(bool searchSenders);
    void setSearchMsgs(bool searchMsgs);
    void setSearchOnlyRegularMsgs(bool searchOnlyRegularMsgs);

    void highlightNext();
    void highlightPrev();

private slots:
    void sceneDestroyed();
    void updateHighlights(bool reuse = false);

    void repositionHighlights();
    void repositionHighlights(ChatLine* line);

signals:
    void newCurrentHighlight(QGraphicsItem* highlightItem);

private:
    QString _searchString;
    ChatScene* _scene{nullptr};
    QList<SearchHighlightItem*> _highlightItems;
    int _currentHighlight{0};

    bool _caseSensitive{false};
    bool _searchSenders{false};
    bool _searchMsgs{true};
    bool _searchOnlyRegularMsgs{true};

    inline Qt::CaseSensitivity caseSensitive() const { return _caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive; }

    inline bool checkType(Message::Type type) const { return type & (Message::Plain | Message::Notice | Message::Action); }

    void checkMessagesForHighlight(int start = 0, int end = -1);
    void highlightLine(ChatLine* line);
    void updateHighlights(ChatLine* line);
};

// Highlight Items
class SearchHighlightItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    SearchHighlightItem(QRectF wordRect, QGraphicsItem* parent = nullptr);
    inline QRectF boundingRect() const override { return _boundingRect; }
    void updateGeometry(qreal width, qreal height);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    enum
    {
        Type = ChatScene::SearchHighlightType
    };
    inline int type() const override { return Type; }

    void setHighlighted(bool highlighted);

    static bool firstInLine(QGraphicsItem* item1, QGraphicsItem* item2);

private slots:
    void updateHighlight(qreal value);

private:
    QRectF _boundingRect;
    bool _highlighted;
    int _alpha;
    QTimeLine _timeLine;
};

#endif  // CHATVIEWSEARCHCONTROLLER_H
