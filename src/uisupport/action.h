// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <type_traits>

#include <QShortcut>
#include <QWidgetAction>

#include "util.h"

/// A specialized QWidgetAction, enhanced by some KDE features
/** This declares/implements a subset of KAction's API (notably we've left out global shortcuts
 *  for now), which should make it easy to plug in KDE support later on.
 */
class UISUPPORT_EXPORT Action : public QWidgetAction
{
    Q_OBJECT

    Q_PROPERTY(QKeySequence shortcut READ shortcut WRITE setShortcut)
    Q_PROPERTY(bool shortcutConfigurable READ isShortcutConfigurable WRITE setShortcutConfigurable)
    Q_FLAGS(ShortcutType)

public:
    enum ShortcutType
    {
        ActiveShortcut = 0x01,
        DefaultShortcut = 0x02
    };
    Q_DECLARE_FLAGS(ShortcutTypes, ShortcutType)

    explicit Action(QObject* parent);
    Action(const QString& text, QObject* parent, const QKeySequence& shortcut = 0);
    Action(const QIcon& icon, const QString& text, QObject* parent, const QKeySequence& shortcut = 0);

    template<typename Receiver, typename Slot>
    Action(const QString& text, QObject* parent, const Receiver* receiver, Slot slot, const QKeySequence& shortcut = 0)
        : Action(text, parent, shortcut)
    {
        static_assert(!std::is_same<Slot, const char*>::value, "Old-style connects not supported");

        setShortcut(shortcut);
        connect(this, &QAction::triggered, receiver, slot);
    }

    template<typename Receiver, typename Slot>
    Action(const QIcon& icon, const QString& text, QObject* parent, const Receiver* receiver, Slot slot, const QKeySequence& shortcut = 0)
        : Action(text, parent, receiver, slot, shortcut)
    {
        setIcon(icon);
    }

    QKeySequence shortcut(ShortcutTypes types = ActiveShortcut) const;
    void setShortcut(const QShortcut& shortcut, ShortcutTypes type = ShortcutTypes(ActiveShortcut | DefaultShortcut));
    void setShortcut(const QKeySequence& shortcut, ShortcutTypes type = ShortcutTypes(ActiveShortcut | DefaultShortcut));

    bool isShortcutConfigurable() const;
    void setShortcutConfigurable(bool configurable);

signals:
    void triggered(Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers);

private slots:
    void slotTriggered();
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Action::ShortcutTypes)
