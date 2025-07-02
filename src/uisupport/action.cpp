// SPDX-License-Identifier: GPL-2.0-or-later

#include "action.h"

#include <QApplication>

Action::Action(QObject* parent)
    : QWidgetAction(parent)
{
    setProperty("isShortcutConfigurable", true);
    connect(this, &QAction::triggered, this, &Action::slotTriggered);
}

Action::Action(const QString& text, QObject* parent, const QKeySequence& shortcut)
    : Action(parent)
{
    setText(text);
    setShortcut(shortcut);
}

Action::Action(const QIcon& icon, const QString& text, QObject* parent, const QKeySequence& shortcut)
    : Action(text, parent, shortcut)
{
    setIcon(icon);
}

void Action::slotTriggered()
{
    emit triggered(QApplication::mouseButtons(), QApplication::keyboardModifiers());
}

bool Action::isShortcutConfigurable() const
{
    return property("isShortcutConfigurable").toBool();
}

void Action::setShortcutConfigurable(bool b)
{
    setProperty("isShortcutConfigurable", b);
}

QKeySequence Action::shortcut(ShortcutTypes type) const
{
    Q_ASSERT(type);
    if (type == DefaultShortcut) {
        auto sequence = property("defaultShortcuts").value<QList<QKeySequence>>();
        return sequence.isEmpty() ? QKeySequence() : sequence.first();
    }

    return shortcuts().isEmpty() ? QKeySequence() : shortcuts().first();
}

void Action::setShortcut(const QShortcut& shortcut, ShortcutTypes type)
{
    setShortcut(shortcut.key(), type);
}

void Action::setShortcut(const QKeySequence& key, ShortcutTypes type)
{
    Q_ASSERT(type);

    if (type & DefaultShortcut) {
        setProperty("defaultShortcuts", QVariant::fromValue(QList<QKeySequence>() << key));
    }
    if (type & ActiveShortcut)
        QAction::setShortcut(key);
}
