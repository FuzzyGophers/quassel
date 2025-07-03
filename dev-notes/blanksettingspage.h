// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef _BLANKSETTINGSPAGE_H_
#define _BLANKSETTINGSPAGE_H_

#include <QHash>

#include "settingspage.h"
#include "ui_blanksettingspage.h"

class BlankSettingsPage : public SettingsPage {
  Q_OBJECT

  public:
    BlankSettingsPage(QWidget *parent = 0);

    bool hasDefaults() const;

  public slots:
    void save();
    void load();
    void defaults();

  private slots:
    void widgetHasChanged();

  private:
    Ui::BlankSettingsPage ui;
    QHash<QString, QVariant> settings;

    bool testHasChanged();
};

#endif
