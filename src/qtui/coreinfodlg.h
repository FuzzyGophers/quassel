// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QDialog>

#include "coreinfo.h"
#include "coresessionwidget.h"

#include "ui_coreinfodlg.h"

class CoreInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CoreInfoDlg(QWidget* parent = nullptr);

public slots:
    void coreInfoChanged(const QVariantMap&);

protected:
    void timerEvent(QTimerEvent*) override { updateUptime(); }

private slots:
    /**
     * Requests resynchronization of CoreInfo object for legacy (pre-0.13) cores
     *
     * This provides compatibility with updating core information for legacy cores, and can be
     * removed after protocol break.
     */
    void refreshLegacyCoreInfo();

    /**
     * Handler for recreation of CoreInfo object, including first-time setup
     *
     * Applies existing CoreInfo information to the dialog, too.
     */
    void coreInfoResynchronized();

    void on_closeButton_clicked() { reject(); }
    void updateUptime();
    void disconnectClicked(int peerId);

    /**
     * Event handler for core unsupported Details button
     */
    void on_coreUnsupportedDetails_clicked();

private:
    Ui::CoreInfoDlg ui;
    QMap<int, CoreSessionWidget*> _widgets;
};
