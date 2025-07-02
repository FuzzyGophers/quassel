// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include "abstractui.h"
#include "singleton.h"

class ActionCollection;
class ContextMenuActionProvider;
class ToolBarActionProvider;
class UiStyle;

#ifdef Q_OS_WIN
#    include <windows.h>
#endif

class UISUPPORT_EXPORT GraphicalUi : public AbstractUi, protected Singleton<GraphicalUi>
{
    Q_OBJECT

public:
    //! Access global ActionCollections.
    /** These ActionCollections are associated with the main window, i.e. they contain global
     *  actions (and thus, shortcuts). Widgets providing application-wide shortcuts should
     *  create appropriate Action objects using GraphicalUi::actionCollection(cat)->add\<Action\>().
     *  @param category The category (default: "General")
     */
    static ActionCollection* actionCollection(const QString& category = "General", const QString& translatedCategory = QString());
    static QHash<QString, ActionCollection*> actionCollections();

    //! Load custom shortcuts from ShortcutSettings
    /** @note This method assumes that all configurable actions are defined when being called
     */
    static void loadShortcuts();

    //! Save custom shortcuts to ShortcutSettings
    static void saveShortcuts();

    inline static ContextMenuActionProvider* contextMenuActionProvider();
    inline static ToolBarActionProvider* toolBarActionProvider();
    inline static UiStyle* uiStyle();
    inline static QWidget* mainWidget();

    //! Force the main widget to the front and focus it
    static void activateMainWidget();

    //! Hide main widget
    static void hideMainWidget();

    //! Toggle main widget
    static void toggleMainWidget();

    //! Check if the main widget is visible
    static bool isMainWidgetVisible();

protected:
    GraphicalUi(QObject* parent = nullptr);
    void init() override;

    //! This is the widget we associate global actions with, typically the main window
    void setMainWidget(QWidget*);

    //! Check if the mainWidget is visible and optionally toggle its visibility
    /** We use Qt's visibility checks to determine if the mainWidget should be activated or hidden.
     *  @param performToggle If true, toggle the window's state in addition to checking visibility
     *  @return True if the window is currently *not* visible (needs activation)
     */
    bool checkMainWidgetVisibility(bool performToggle);

    //! Minimize or restore main widget
    virtual void minimizeRestore(bool show);

    //! Whether it is allowed to hide the mainWidget
    /** The default implementation returns false, meaning that we won't hide the mainWidget even
     *  if requested. This is to prevent hiding in case we don't have a tray icon to restore from.
     */
    virtual inline bool isHidingMainWidgetAllowed() const;

    void setContextMenuActionProvider(ContextMenuActionProvider*);
    void setToolBarActionProvider(ToolBarActionProvider*);
    void setUiStyle(UiStyle*);

    bool eventFilter(QObject* obj, QEvent* event) override;

protected slots:
    void disconnectedFromCore() override;

private:
    static QWidget* _mainWidget;
    static QHash<QString, ActionCollection*> _actionCollections;
    static ContextMenuActionProvider* _contextMenuActionProvider;
    static ToolBarActionProvider* _toolBarActionProvider;
    static UiStyle* _uiStyle;

#ifdef Q_OS_WIN
    DWORD _dwTickCount;
#endif
};

// inlines

inline ContextMenuActionProvider* GraphicalUi::contextMenuActionProvider()
{
    return _contextMenuActionProvider;
}

inline ToolBarActionProvider* GraphicalUi::toolBarActionProvider()
{
    return _toolBarActionProvider;
}

inline UiStyle* GraphicalUi::uiStyle()
{
    return _uiStyle;
}

inline QWidget* GraphicalUi::mainWidget()
{
    return _mainWidget;
}

inline bool GraphicalUi::isHidingMainWidgetAllowed() const
{
    return false;
}
