// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "chatviewsearchbar.h"

#include "action.h"
#include "actioncollection.h"
#include "icon.h"
#include "qtui.h"

ChatViewSearchBar::ChatViewSearchBar(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.hideButton->setIcon(icon::get("dialog-close"));
    ui.searchUpButton->setIcon(icon::get("go-up"));
    ui.searchDownButton->setIcon(icon::get("go-down"));
    _searchDelayTimer.setSingleShot(true);

    layout()->setContentsMargins(0, 0, 0, 0);

    hide();

    ActionCollection* coll = QtUi::actionCollection("General");

    QAction* toggleSearchBar = coll->action("ToggleSearchBar");
    connect(toggleSearchBar, &QAction::toggled, this, &QWidget::setVisible);

    auto* hideSearchBar = new Action{{}, this, toggleSearchBar, &QAction::setChecked};
    hideSearchBar->setShortcut(Qt::Key_Escape);
    hideSearchBar->setShortcutConfigurable(false);
    coll->addAction("HideSearchBar", hideSearchBar);

    connect(ui.hideButton, &QAbstractButton::clicked, toggleSearchBar, &QAction::toggle);
    connect(ui.searchEditLine, &QLineEdit::textChanged, this, &ChatViewSearchBar::delaySearch);
    connect(&_searchDelayTimer, &QTimer::timeout, this, &ChatViewSearchBar::search);
}

void ChatViewSearchBar::setVisible(bool visible)
{
    // clearing the search field also removes the highlight items from the scene
    // this should be done before the SearchBar is hidden, as the hiding triggers
    // a resize event which can lead to strange side effects.
    ui.searchEditLine->clear();
    QWidget::setVisible(visible);
    if (visible)
        ui.searchEditLine->setFocus();
    else
        emit hidden();
}

void ChatViewSearchBar::delaySearch()
{
    _searchDelayTimer.start(300);
}

void ChatViewSearchBar::search()
{
    emit searchChanged(ui.searchEditLine->text());
}
