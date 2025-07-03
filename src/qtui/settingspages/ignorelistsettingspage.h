// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef IGNORELISTSETTINGSPAGE_H
#define IGNORELISTSETTINGSPAGE_H

#include <QButtonGroup>
#include <QStyledItemDelegate>

#include "clientignorelistmanager.h"
#include "ignorelistmodel.h"
#include "settingspage.h"

#include "ui_ignorelisteditdlg.h"
#include "ui_ignorelistsettingspage.h"

class QEvent;
class QPainter;
class QAbstractItemModel;

// the delegate is used to draw the checkbox in column 0
class IgnoreListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    IgnoreListDelegate(QWidget* parent = nullptr)
        : QStyledItemDelegate(parent)
    {}
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
};

class IgnoreListEditDlg : public QDialog
{
    Q_OBJECT

public:
    IgnoreListEditDlg(const IgnoreListManager::IgnoreListItem& item, QWidget* parent = nullptr, bool enabled = false);
    inline IgnoreListManager::IgnoreListItem ignoreListItem() { return _ignoreListItem; }
    void enableOkButton(bool state);

private slots:
    void widgetHasChanged();
    void aboutToAccept() { _ignoreListItem = _clonedIgnoreListItem; }

private:
    IgnoreListManager::IgnoreListItem _ignoreListItem;
    IgnoreListManager::IgnoreListItem _clonedIgnoreListItem;
    bool _hasChanged;
    Ui::IgnoreListEditDlg ui;
    QButtonGroup _typeButtonGroup;
    QButtonGroup _strictnessButtonGroup;
    QButtonGroup _scopeButtonGroup;
};

class IgnoreListSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    IgnoreListSettingsPage(QWidget* parent = nullptr);
    ~IgnoreListSettingsPage() override;
    inline bool hasDefaults() const override { return false; }
    inline bool needsCoreConnection() const override { return true; }
    void editIgnoreRule(const QString& ignoreRule);

public slots:
    void save() override;
    void load() override;
    void defaults() override;
    void newIgnoreRule(const QString& rule = {});

private slots:
    void enableDialog(bool);
    void deleteSelectedIgnoreRule();
    void editSelectedIgnoreRule();
    void selectionChanged(const QItemSelection& selection, const QItemSelection&);

private:
    IgnoreListDelegate* _delegate;
    Ui::IgnoreListSettingsPage ui;
    IgnoreListModel _ignoreListModel;
};

#endif  // IGNORELISTSETTINGSPAGE_H
