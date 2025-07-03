// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QString>
#include <QWidget>

#include "logger.h"

#include "ui_debuglogdlg.h"

class DebugLogDlg : public QDialog
{
    Q_OBJECT

public:
    DebugLogDlg(QWidget* parent = nullptr);

private slots:
    void logUpdated(const Logger::LogEntry& msg);

private:
    QString toString(const Logger::LogEntry& msg);

private:
    Ui::DebugLogDlg ui;
};
