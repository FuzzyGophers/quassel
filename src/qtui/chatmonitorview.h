// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CHATMONITORVIEW_H
#define CHATMONITORVIEW_H

#include "chatview.h"

class ChatMonitorFilter;

class ChatMonitorView : public ChatView
{
    Q_OBJECT

public:
    ChatMonitorView(ChatMonitorFilter* filter, QWidget* parent);

    void showFieldsChanged(bool checked);

protected:
    void addActionsToMenu(QMenu* menu, const QPointF& pos) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private slots:
    void showSettingsPage();
    virtual void coreConnectionStateChanged(bool connected);

protected:
    inline ChatMonitorFilter* filter() const { return _filter; }

private:
    ChatMonitorFilter* _filter;
};

#endif  // CHATMONITORVIEW_H
