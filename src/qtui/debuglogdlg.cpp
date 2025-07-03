// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "debuglogdlg.h"

#include "quassel.h"

DebugLogDlg::DebugLogDlg(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);

    ui.textEdit->setReadOnly(true);

    connect(Quassel::instance()->logger(), &Logger::messageLogged, this, &DebugLogDlg::logUpdated);

    QString content;
    for (auto&& message : Quassel::instance()->logger()->messages()) {
        content += toString(message);
    }
    ui.textEdit->setPlainText(content);
}

QString DebugLogDlg::toString(const Logger::LogEntry& msg)
{
    return msg.toString() + "\n";
}

void DebugLogDlg::logUpdated(const Logger::LogEntry& msg)
{
    ui.textEdit->moveCursor(QTextCursor::End);
    ui.textEdit->insertPlainText(toString(msg));
    ui.textEdit->moveCursor(QTextCursor::End);
}
