// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef APPEARANCESETTINGSPAGE_H
#define APPEARANCESETTINGSPAGE_H

#include <QHash>
#include <QList>
#include <QLocale>
#include <QTextCharFormat>

#include "settings.h"
#include "settingspage.h"

#include "ui_appearancesettingspage.h"

class AppearanceSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    AppearanceSettingsPage(QWidget* parent = nullptr);

    inline bool hasDefaults() const override { return true; }

public slots:
    void save() override;
    void load() override;
    void defaults() override;

private slots:
    void widgetHasChanged();

    void chooseStyleSheet();

private:
    bool testHasChanged();
    void initStyleComboBox();
    void initLanguageComboBox();
    void initIconThemeComboBox();
    QLocale selectedLocale() const;
    QString selectedIconTheme() const;

    Ui::AppearanceSettingsPage ui;
    QHash<QString, QVariant> settings;
    QMap<QString, QLocale> _locales;

    inline QString settingsKey() const override { return QString("QtUi"); }
};

#endif
