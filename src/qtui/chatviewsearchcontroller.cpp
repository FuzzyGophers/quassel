// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "chatviewsearchcontroller.h"

#include <algorithm>

#include <QAbstractItemModel>
#include <QPainter>

#include "chatitem.h"
#include "chatline.h"
#include "chatlinemodel.h"
#include "chatscene.h"
#include "messagemodel.h"

ChatViewSearchController::ChatViewSearchController(QObject* parent)
    : QObject(parent)
{
}

void ChatViewSearchController::setSearchString(const QString& searchString)
{
    QString oldSearchString = _searchString;
    _searchString = searchString;
    if (_scene) {
        if (!searchString.startsWith(oldSearchString) || oldSearchString.isEmpty()) {
            // we can't reuse our all findings... clear the scene and do it all over
            updateHighlights();
        }
        else {
            // reuse all findings
            updateHighlights(true);
        }
    }
}

void ChatViewSearchController::setScene(ChatScene* scene)
{
    Q_ASSERT(scene);
    if (scene == _scene)
        return;

    if (_scene) {
        disconnect(_scene, nullptr, this, nullptr);
        disconnect(Client::messageModel(), nullptr, this, nullptr);
        qDeleteAll(_highlightItems);
        _highlightItems.clear();
    }

    _scene = scene;
    if (!scene)
        return;

    connect(_scene, &QObject::destroyed, this, &ChatViewSearchController::sceneDestroyed);
    connect(_scene, &ChatScene::layoutChanged, this, [this]() { repositionHighlights(); });
    connect(Client::messageModel(), &MessageModel::finishedBacklogFetch, this, [this]() { updateHighlights(); });
    updateHighlights();
}

void ChatViewSearchController::highlightNext()
{
    if (_highlightItems.isEmpty())
        return;

    if (_currentHighlight < _highlightItems.count()) {
        _highlightItems.at(_currentHighlight)->setHighlighted(false);
    }

    _currentHighlight++;
    if (_currentHighlight >= _highlightItems.count())
        _currentHighlight = 0;
    _highlightItems.at(_currentHighlight)->setHighlighted(true);
    emit newCurrentHighlight(_highlightItems.at(_currentHighlight));
}

void ChatViewSearchController::highlightPrev()
{
    if (_highlightItems.isEmpty())
        return;

    if (_currentHighlight < _highlightItems.count()) {
        _highlightItems.at(_currentHighlight)->setHighlighted(false);
    }

    _currentHighlight--;
    if (_currentHighlight < 0)
        _currentHighlight = _highlightItems.count() - 1;
    _highlightItems.at(_currentHighlight)->setHighlighted(true);
    emit newCurrentHighlight(_highlightItems.at(_currentHighlight));
}

void ChatViewSearchController::updateHighlights(bool reuse)
{
    if (!_scene)
        return;

    if (reuse) {
        QSet<ChatLine*> chatLines;
        foreach (SearchHighlightItem* highlightItem, _highlightItems) {
            auto* line = qgraphicsitem_cast<ChatLine*>(highlightItem->parentItem());
            if (line)
                chatLines << line;
        }
        foreach (ChatLine* line, chatLines) {
            updateHighlights(line);
        }
    }
    else {
        QPointF oldHighlightPos;
        if (!_highlightItems.isEmpty() && _currentHighlight < _highlightItems.count()) {
            oldHighlightPos = _highlightItems[_currentHighlight]->scenePos();
        }
        qDeleteAll(_highlightItems);
        _highlightItems.clear();
        Q_ASSERT(_highlightItems.isEmpty());

        if (searchString().isEmpty() || !(_searchSenders || _searchMsgs))
            return;

        checkMessagesForHighlight();

        if (!_highlightItems.isEmpty()) {
            if (!oldHighlightPos.isNull()) {
                int start = 0;
                int end = _highlightItems.count() - 1;
                QPointF startPos;
                QPointF endPos;
                while (true) {
                    startPos = _highlightItems[start]->scenePos();
                    endPos = _highlightItems[end]->scenePos();
                    if (startPos == oldHighlightPos) {
                        _currentHighlight = start;
                        break;
                    }
                    if (endPos == oldHighlightPos) {
                        _currentHighlight = end;
                        break;
                    }
                    if (end - start == 1) {
                        _currentHighlight = start;
                        break;
                    }
                    if (end == 0 && start == 0) {
                        // Sometimes we can run into an issue where the start and end are both set
                        // to zero.  Rather than endlessly spin this loop, bail out.  Search seems
                        // to work fine.
                        // [Test case]
                        // Unfortunately, this seems specific to the contents of a buffer.  First,
                        // find a buffer that you've encountered freezing, and keep track of what
                        // was loaded, where it was, and the two most recent search terms.
                        // For example...
                        // 1.  Load some backlog to a buffer
                        // 2.  Search for term with any number of matches
                        // 3.  Making sure to -type over existing words without first backspacing-,
                        //     search for another term with only one match
                        // Expected: Search results found, no freezing
                        // Actual:   Quassel hangs.  startPos and endPos = same place, start = 0,
                        //           end = 0, _currentHighlight appears to retain values from the
                        //           previous search.

                        // Reset _currentHighlight to start, otherwise it'll retain the value from
                        // previous search, resulting in an index-out-of-bounds error.
                        _currentHighlight = start;
                        // Escape from the loop!
                        break;
                    }
                    int pivot = (end + start) / 2;
                    QPointF pivotPos = _highlightItems[pivot]->scenePos();
                    if (startPos.y() == endPos.y()) {
                        if (oldHighlightPos.x() <= pivotPos.x())
                            end = pivot;
                        else
                            start = pivot;
                    }
                    else {
                        if (oldHighlightPos.y() <= pivotPos.y())
                            end = pivot;
                        else
                            start = pivot;
                    }
                }
            }
            else {
                _currentHighlight = _highlightItems.count() - 1;
            }
            _highlightItems[_currentHighlight]->setHighlighted(true);
            emit newCurrentHighlight(_highlightItems[_currentHighlight]);
        }
    }
}

void ChatViewSearchController::checkMessagesForHighlight(int start, int end)
{
    QAbstractItemModel* model = _scene->model();
    Q_ASSERT(model);

    if (end == -1) {
        end = model->rowCount() - 1;
        if (end == -1)
            return;
    }

    QModelIndex index;
    for (int row = start; row <= end; row++) {
        if (_searchOnlyRegularMsgs) {
            index = model->index(row, 0);
            if (!checkType((Message::Type)index.data(MessageModel::TypeRole).toInt()))
                continue;
        }
        highlightLine(_scene->chatLine(row));
    }
}

void ChatViewSearchController::updateHighlights(ChatLine* line)
{
    QList<ChatItem*> checkItems;
    if (_searchSenders)
        checkItems << line->item(MessageModel::SenderColumn);

    if (_searchMsgs)
        checkItems << line->item(MessageModel::ContentsColumn);

    QHash<quint64, QHash<quint64, QRectF>> wordRects;
    foreach (ChatItem* item, checkItems) {
        foreach (QRectF wordRect, item->findWords(searchString(), caseSensitive())) {
            wordRects[(quint64)(wordRect.x() + item->x())][(quint64)(wordRect.y())] = wordRect;
        }
    }

    bool deleteAll = false;
    QAbstractItemModel* model = _scene->model();
    Q_ASSERT(model);
    if (_searchOnlyRegularMsgs) {
        QModelIndex index = model->index(line->row(), 0);
        if (!checkType((Message::Type)index.data(MessageModel::TypeRole).toInt()))
            deleteAll = true;
    }

    foreach (QGraphicsItem* child, line->childItems()) {
        auto* highlightItem = qgraphicsitem_cast<SearchHighlightItem*>(child);
        if (!highlightItem)
            continue;

        if (!deleteAll && wordRects.contains((quint64)(highlightItem->pos().x()))
            && wordRects[(quint64)(highlightItem->pos().x())].contains((quint64)(highlightItem->pos().y()))) {
            QRectF& wordRect = wordRects[(quint64)(highlightItem->pos().x())][(quint64)(highlightItem->pos().y())];
            highlightItem->updateGeometry(wordRect.width(), wordRect.height());
        }
        else {
            int pos = _highlightItems.indexOf(highlightItem);
            if (pos == _currentHighlight) {
                highlightPrev();
            }
            else if (pos < _currentHighlight) {
                _currentHighlight--;
            }

            _highlightItems.removeAt(pos);
            delete highlightItem;
        }
    }
}

void ChatViewSearchController::highlightLine(ChatLine* line)
{
    QList<ChatItem*> checkItems;
    if (_searchSenders)
        checkItems << line->item(MessageModel::SenderColumn);

    if (_searchMsgs)
        checkItems << line->item(MessageModel::ContentsColumn);

    foreach (ChatItem* item, checkItems) {
        foreach (QRectF wordRect, item->findWords(searchString(), caseSensitive())) {
            _highlightItems << new SearchHighlightItem(wordRect.adjusted(item->x(), 0, item->x(), 0), line);
        }
    }
}

void ChatViewSearchController::repositionHighlights()
{
    QSet<ChatLine*> chatLines;
    foreach (SearchHighlightItem* item, _highlightItems) {
        auto* line = qgraphicsitem_cast<ChatLine*>(item->parentItem());
        if (line)
            chatLines << line;
    }
    foreach (ChatLine* line, chatLines) {
        repositionHighlights(line);
    }
}

void ChatViewSearchController::repositionHighlights(ChatLine* line)
{
    QList<SearchHighlightItem*> searchHighlights;
    foreach (QGraphicsItem* child, line->childItems()) {
        auto* highlightItem = qgraphicsitem_cast<SearchHighlightItem*>(child);
        if (highlightItem)
            searchHighlights << highlightItem;
    }

    if (searchHighlights.isEmpty())
        return;

    QList<QPointF> wordPos;
    if (_searchSenders) {
        foreach (QRectF wordRect, line->senderItem()->findWords(searchString(), caseSensitive())) {
            wordPos << QPointF(wordRect.x() + line->senderItem()->x(), wordRect.y());
        }
    }
    if (_searchMsgs) {
        foreach (QRectF wordRect, line->contentsItem()->findWords(searchString(), caseSensitive())) {
            wordPos << QPointF(wordRect.x() + line->contentsItem()->x(), wordRect.y());
        }
    }

    std::sort(searchHighlights.begin(), searchHighlights.end(), SearchHighlightItem::firstInLine);

    Q_ASSERT(wordPos.count() == searchHighlights.count());
    for (int i = 0; i < searchHighlights.count(); i++) {
        searchHighlights.at(i)->setPos(wordPos.at(i));
    }
}

void ChatViewSearchController::sceneDestroyed()
{
    // WARNING: don't call any methods on scene!
    _scene = nullptr;
    // the items will be automatically deleted when the scene is destroyed
    // so we just have to clear the list;
    _highlightItems.clear();
}

void ChatViewSearchController::setCaseSensitive(bool caseSensitive)
{
    if (_caseSensitive == caseSensitive)
        return;

    _caseSensitive = caseSensitive;

    // we can reuse the original search results if the new search
    // parameters are a restriction of the original one
    updateHighlights(caseSensitive);
}

void ChatViewSearchController::setSearchSenders(bool searchSenders)
{
    if (_searchSenders == searchSenders)
        return;

    _searchSenders = searchSenders;
    // we can reuse the original search results if the new search
    // parameters are a restriction of the original one
    updateHighlights(!searchSenders);
}

void ChatViewSearchController::setSearchMsgs(bool searchMsgs)
{
    if (_searchMsgs == searchMsgs)
        return;

    _searchMsgs = searchMsgs;

    // we can reuse the original search results if the new search
    // parameters are a restriction of the original one
    updateHighlights(!searchMsgs);
}

void ChatViewSearchController::setSearchOnlyRegularMsgs(bool searchOnlyRegularMsgs)
{
    if (_searchOnlyRegularMsgs == searchOnlyRegularMsgs)
        return;

    _searchOnlyRegularMsgs = searchOnlyRegularMsgs;

    // we can reuse the original search results if the new search
    // parameters are a restriction of the original one
    updateHighlights(searchOnlyRegularMsgs);
}

// ==================================================
//  SearchHighlightItem
// ==================================================
SearchHighlightItem::SearchHighlightItem(QRectF wordRect, QGraphicsItem* parent)
    : QObject()
    , QGraphicsItem(parent)
    , _highlighted(false)
    , _alpha(70)
    , _timeLine(150)
{
    setPos(wordRect.x(), wordRect.y());
    updateGeometry(wordRect.width(), wordRect.height());

    connect(&_timeLine, &QTimeLine::valueChanged, this, &SearchHighlightItem::updateHighlight);
}

void SearchHighlightItem::setHighlighted(bool highlighted)
{
    _highlighted = highlighted;

    if (highlighted)
        _timeLine.setDirection(QTimeLine::Forward);
    else
        _timeLine.setDirection(QTimeLine::Backward);

    if (_timeLine.state() != QTimeLine::Running)
        _timeLine.start();

    update();
}

void SearchHighlightItem::updateHighlight(qreal value)
{
    _alpha = 70 + (int)(80 * value);
    update();
}

void SearchHighlightItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(QColor(0, 0, 0), 1.5));
    painter->setBrush(QColor(254, 237, 45, _alpha));
    painter->setRenderHints(QPainter::Antialiasing);
    qreal radius = boundingRect().height() * 0.30;
    painter->drawRoundedRect(boundingRect(), radius, radius);
}

void SearchHighlightItem::updateGeometry(qreal width, qreal height)
{
    prepareGeometryChange();
    qreal sizedelta = height * 0.1;
    _boundingRect = QRectF(-sizedelta, -sizedelta, width + 2 * sizedelta, height + 2 * sizedelta);
    update();
}

bool SearchHighlightItem::firstInLine(QGraphicsItem* item1, QGraphicsItem* item2)
{
    if (item1->pos().y() != item2->pos().y())
        return item1->pos().y() < item2->pos().y();
    else
        return item1->pos().x() < item2->pos().x();
}
