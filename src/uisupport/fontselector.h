// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QLabel>
#include <QWidget>

class UISUPPORT_EXPORT FontSelector : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont)

public:
    FontSelector(QWidget* parent = nullptr);

    inline const QFont& selectedFont() const { return _font; }

public slots:
    void setSelectedFont(const QFont& font);

signals:
    void fontChanged(const QFont&);

protected:
    void changeEvent(QEvent* e) override;

protected slots:
    void chooseFont();

private:
    QFont _font;
    QLabel* _demo;
};
