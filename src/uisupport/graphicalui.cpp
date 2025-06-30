/***************************************************************************
 *   Copyright (C) 2005-2022 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This contains code from KStatusNotifierItem, part of the KDE libs     *
 *   Copyright (C) 2009 Marco Martin <notmart@gmail.com>                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "graphicalui.h"

#include <QApplication>

#include "actioncollection.h"
#include "contextmenuactionprovider.h"
#include "toolbaractionprovider.h"
#include "uisettings.h"

QWidget* GraphicalUi::_mainWidget = nullptr;
QHash<QString, ActionCollection*> GraphicalUi::_actionCollections;
ContextMenuActionProvider* GraphicalUi::_contextMenuActionProvider = nullptr;
ToolBarActionProvider* GraphicalUi::_toolBarActionProvider = nullptr;
UiStyle* GraphicalUi::_uiStyle = nullptr;

#ifdef Q_OS_WIN
#    include <windows.h>
#endif

GraphicalUi::GraphicalUi(QObject* parent)
    : AbstractUi(parent)
    , Singleton<GraphicalUi>(this)
{
    Q_INIT_RESOURCE(pics);
    Q_INIT_RESOURCE(hicolor_icons);
#ifdef EMBED_DATA
    Q_INIT_RESOURCE(icons);
    Q_INIT_RESOURCE(iconthemes);
#endif

#ifdef Q_OS_WIN
    _dwTickCount = 0;
#endif
}

void GraphicalUi::init()
{
#ifdef Q_OS_WIN
    mainWidget()->installEventFilter(this);
#endif
}

ActionCollection* GraphicalUi::actionCollection(const QString& category, const QString& translatedCategory)
{
    if (_actionCollections.contains(category))
        return _actionCollections.value(category);
    auto* coll = new ActionCollection(_mainWidget);

    if (!translatedCategory.isEmpty())
        coll->setProperty("Category", translatedCategory);
    else
        coll->setProperty("Category", category);

    if (_mainWidget)
        coll->addAssociatedWidget(_mainWidget);
    _actionCollections.insert(category, coll);
    return coll;
}

QHash<QString, ActionCollection*> GraphicalUi::actionCollections()
{
    return _actionCollections;
}

void GraphicalUi::loadShortcuts()
{
    for (ActionCollection* coll : actionCollections())
        coll->readSettings();
}

void GraphicalUi::saveShortcuts()
{
    ShortcutSettings s;
    s.clear();
    for (ActionCollection* coll : actionCollections())
        coll->writeSettings();
}

void GraphicalUi::setMainWidget(QWidget* widget)
{
    _mainWidget = widget;
}

void GraphicalUi::setContextMenuActionProvider(ContextMenuActionProvider* provider)
{
    _contextMenuActionProvider = provider;
}

void GraphicalUi::setToolBarActionProvider(ToolBarActionProvider* provider)
{
    _toolBarActionProvider = provider;
}

void GraphicalUi::setUiStyle(UiStyle* style)
{
    _uiStyle = style;
}

void GraphicalUi::disconnectedFromCore()
{
    _contextMenuActionProvider->disconnectedFromCore();
    _toolBarActionProvider->disconnectedFromCore();
    AbstractUi::disconnectedFromCore();
}

bool GraphicalUi::eventFilter(QObject* obj, QEvent* event)
{
#ifdef Q_OS_WIN
    if (obj == mainWidget() && event->type() == QEvent::ActivationChange) {
        _dwTickCount = GetTickCount();
    }
#endif
    return AbstractUi::eventFilter(obj, event);
}

bool GraphicalUi::checkMainWidgetVisibility(bool perform)
{
    bool needsActivation = true;

    if (_mainWidget) {
        // Check if the main widget is visible and not minimized
        needsActivation = !(_mainWidget->isVisible() && !_mainWidget->isMinimized());
    }

    if (perform) {
        minimizeRestore(!needsActivation);
    }
    return needsActivation;
}

bool GraphicalUi::isMainWidgetVisible()
{
    return !instance()->checkMainWidgetVisibility(false);
}

void GraphicalUi::minimizeRestore(bool show)
{
    if (!_mainWidget) {
        return;
    }

    if (show) {
        _mainWidget->showNormal();
        _mainWidget->raise();
        _mainWidget->activateWindow();
    } else if (instance()->isHidingMainWidgetAllowed()) {
        _mainWidget->hide();
    }
}

void GraphicalUi::activateMainWidget()
{
    if (_mainWidget) {
        if (_mainWidget->windowState() & Qt::WindowMinimized) {
            _mainWidget->setWindowState((_mainWidget->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
        }
        _mainWidget->show();
        _mainWidget->raise();
        _mainWidget->activateWindow();
    }
}

void GraphicalUi::hideMainWidget()
{
    if (_mainWidget && instance()->isHidingMainWidgetAllowed()) {
        _mainWidget->hide();
    }
}

void GraphicalUi::toggleMainWidget()
{
    instance()->checkMainWidgetVisibility(true);
}
