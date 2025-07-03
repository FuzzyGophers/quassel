
// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "blanksettingspage.h"

#include "qtui.h"
#include "uisettings.h"


BlankSettingsPage::BlankSettingsPage(QWidget *parent)
  : SettingsPage(tr("Behaviour"), tr("Blank"), parent) {
  ui.setupUi(this);

  connect(ui.exampleCheckbox, SIGNAL(clicked(bool)), this, SLOT(widgetHasChanged()));
}

bool BlankSettingsPage::hasDefaults() const {
  return true;
}

void BlankSettingsPage::defaults() {
  ui.exampleCheckbox->setChecked(true);

  widgetHasChanged();
}

void BlankSettingsPage::load() {
  UiSettings uiSettings;

  settings["exampleCheckbox"] = uiSettings.value("exampleCheckbox", QVariant(false));
  ui.exampleCheckbox->setChecked(settings["exampleCheckbox"].toBool());

  setChangedState(false);
}

void BlankSettingsPage::save() {
  UiSettings uiSettings;
  uiSettings.setValue("exampleCheckbox", ui.exampleCheckbox->isChecked());

  load();
  setChangedState(false);
}

void BlankSettingsPage::widgetHasChanged() {
  bool changed = testHasChanged();
  if(changed != hasChanged()) setChangedState(changed);
}

bool BlankSettingsPage::testHasChanged() {
  if(settings["exampleCheckbox"].toBool() != ui.exampleCheckbox->isChecked()) return true;

  return false;
}




