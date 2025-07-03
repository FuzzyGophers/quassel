// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QLineEdit>

class QToolButton;

class UISUPPORT_EXPORT ClearableLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ClearableLineEdit(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void updateClearButton(const QString& text);

private:
    QToolButton* clearButton;
};
