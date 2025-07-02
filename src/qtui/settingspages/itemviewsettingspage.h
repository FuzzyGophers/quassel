// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef ITEMVIEWSETTINGSPAGE_H_
#define ITEMVIEWSETTINGSPAGE_H_

#include "settingspage.h"

#include "ui_itemviewsettingspage.h"

class ColorButton;
class QSignalMapper;
class QTreeWidgetItem;

class ItemViewSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    ItemViewSettingsPage(QWidget* parent = nullptr);

    inline bool hasDefaults() const override { return true; }

public slots:
    void save() override;

private slots:
    void updateBufferViewPreview(QWidget* button);

private:
    Ui::ItemViewSettingsPage ui;
    QTreeWidgetItem *_networkItem, *_defaultBufferItem, *_inactiveBufferItem, *_activeBufferItem, *_unreadBufferItem, *_highlightedBufferItem;

    inline QString settingsKey() const override { return QString("ItemViews"); }
};

#endif
