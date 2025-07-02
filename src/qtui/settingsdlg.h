// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>

#include "settingspage.h"

#include "ui_settingsdlg.h"

class SettingsDlg : public QDialog
{
    Q_OBJECT

public:
    SettingsDlg(QWidget* parent = nullptr);
    void registerSettingsPage(SettingsPage*);
    void unregisterSettingsPage(SettingsPage*);

    inline SettingsPage* currentPage() const { return _currentPage; }

public slots:
    void selectPage(SettingsPage* sp);  // const QString &category, const QString &title);

private slots:
    void coreConnectionStateChanged();
    void itemSelected();
    void buttonClicked(QAbstractButton*);
    bool applyChanges();
    void undoChanges();
    void reload();
    void loadDefaults();
    void setButtonStates();
    void setItemState(QTreeWidgetItem*);

private:
    Ui::SettingsDlg ui;

    SettingsPage* _currentPage{nullptr};
    QHash<SettingsPage*, bool> pageIsLoaded;

    enum
    {
        SettingsPageRole = Qt::UserRole
    };
};

#endif
