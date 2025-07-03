// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "itemviewsettingspage.h"

#include <QSignalMapper>

#include "colorbutton.h"
#include "qtui.h"
#include "qtuistyle.h"

ItemViewSettingsPage::ItemViewSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Chat & Nick Lists"), parent)
{
    ui.setupUi(this);

    _networkItem = new QTreeWidgetItem(ui.bufferViewPreview, QStringList(tr("Network")));
    _networkItem->setFlags(Qt::NoItemFlags);

    _inactiveBufferItem = new QTreeWidgetItem(_networkItem, QStringList(tr("Inactive")));
    _defaultBufferItem = new QTreeWidgetItem(_networkItem, QStringList(tr("Normal")));
    _unreadBufferItem = new QTreeWidgetItem(_networkItem, QStringList(tr("Unread messages")));
    _highlightedBufferItem = new QTreeWidgetItem(_networkItem, QStringList(tr("Highlight")));
    _activeBufferItem = new QTreeWidgetItem(_networkItem, QStringList(tr("Other activity")));

    ui.bufferViewPreview->expandAll();

    for (ColorButton* button : findChildren<ColorButton*>()) {
        connect(button, &ColorButton::colorChanged, button, [this, button]() { updateBufferViewPreview(button); });
    }

    initAutoWidgets();
}

void ItemViewSettingsPage::save()
{
    SettingsPage::save();
    QtUi::style()->generateSettingsQss();
    QtUi::style()->reload();
}

void ItemViewSettingsPage::updateBufferViewPreview(QWidget* widget)
{
    auto* button = qobject_cast<ColorButton*>(widget);
    if (!button)
        return;

    QString objName = button->objectName();
    if (objName == "defaultBufferColor") {
        _networkItem->setForeground(0, button->color());
        _defaultBufferItem->setForeground(0, button->color());
    }
    else if (objName == "inactiveBufferColor")
        _inactiveBufferItem->setForeground(0, button->color());
    else if (objName == "activeBufferColor")
        _activeBufferItem->setForeground(0, button->color());
    else if (objName == "unreadBufferColor")
        _unreadBufferItem->setForeground(0, button->color());
    else if (objName == "highlightedBufferColor")
        _highlightedBufferItem->setForeground(0, button->color());
}
