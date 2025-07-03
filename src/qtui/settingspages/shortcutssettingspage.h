// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SHORTCUTSSETTINGSPAGE_H
#define SHORTCUTSSETTINGSPAGE_H

#include <QSortFilterProxyModel>

#include "settingspage.h"

#include "ui_shortcutssettingspage.h"

class ActionCollection;
class ShortcutsModel;

class ShortcutsFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ShortcutsFilter(QObject* parent = nullptr);

public slots:
    void setFilterString(const QString& filterString);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;

private:
    QString _filterString;
};

class ShortcutsSettingsPage : public SettingsPage
{
    Q_OBJECT
public:
    ShortcutsSettingsPage(const QHash<QString, ActionCollection*>& actionCollections, QWidget* parent = nullptr);

    inline bool hasDefaults() const override { return true; }

public slots:
    void save() override;
    void load() override;
    void defaults() override;

private slots:
    void on_searchEdit_textChanged(const QString& text);
    void keySequenceChanged(const QKeySequence& seq, const QModelIndex& conflicting);
    void setWidgetStates();
    void toggledCustomOrDefault();

private:
    Ui::ShortcutsSettingsPage ui;
    ShortcutsModel* _shortcutsModel;
    ShortcutsFilter* _shortcutsFilter;
};

#endif  // SHORTCUTSSETTINGSPAGE_H
