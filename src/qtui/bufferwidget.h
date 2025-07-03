// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "abstractbuffercontainer.h"

#include "ui_bufferwidget.h"

class QGraphicsItem;
class ChatView;
class ChatViewSearchBar;
class ChatViewSearchController;

class BufferWidget : public AbstractBufferContainer
{
    Q_OBJECT

public:
    BufferWidget(QWidget* parent);
    ~BufferWidget() override;

    bool eventFilter(QObject* watched, QEvent* event) override;

    inline ChatViewSearchBar* searchBar() const { return ui.searchBar; }
    void addActionsToMenu(QMenu*, const QPointF& pos);
    virtual inline bool autoMarkerLineOnLostFocus() const { return _autoMarkerLineOnLostFocus; }

public slots:
    virtual void setMarkerLine(ChatView* view = nullptr, bool allowGoingBack = true);
    virtual void jumpToMarkerLine(ChatView* view = nullptr, bool requestBacklog = true);

protected:
    AbstractChatView* createChatView(BufferId) override;
    void removeChatView(BufferId) override;
    inline bool autoMarkerLine() const override { return _autoMarkerLine; }

protected slots:
    void currentChanged(const QModelIndex& current, const QModelIndex& previous) override;
    void showChatView(BufferId) override;

private slots:
    void scrollToHighlight(QGraphicsItem* highlightItem);
    void zoomIn();
    void zoomOut();
    void zoomOriginal();

    void setAutoMarkerLine(const QVariant&);
    void setAutoMarkerLineOnLostFocus(const QVariant&);
    /**
     * Sets the local cache of whether or not a buffer should fetch backlog upon show to provide a
     * scrollable amount of backlog
     *
     * @seealso BacklogSettings::setEnsureBacklogOnBufferShow()
     */
    void setEnsureBacklogOnBufferShow(const QVariant&);

private:
    Ui::BufferWidget ui;
    QHash<BufferId, QWidget*> _chatViews;

    ChatViewSearchController* _chatViewSearchController;

    bool _autoMarkerLine;
    bool _autoMarkerLineOnLostFocus;
    bool _ensureBacklogOnBufferShow; ///< If a buffer fetches backlog upon show until scrollable
};
