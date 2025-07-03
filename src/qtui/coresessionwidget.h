// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QMap>
#include <QWidget>

#include "ui_coresessionwidget.h"

class CoreSessionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoreSessionWidget(QWidget*);

    void setData(QMap<QString, QVariant>);

signals:
    void disconnectClicked(int);

private slots:
    void onDisconnectClicked();

private:
    Ui::CoreSessionWidget ui;
    int _peerId;
};
