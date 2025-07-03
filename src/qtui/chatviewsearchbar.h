// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CHATVIEWSEARCHBAR_H
#define CHATVIEWSEARCHBAR_H

#include <QTimer>
#include <QWidget>

#include "ui_chatviewsearchbar.h"

class QAction;

class ChatViewSearchBar : public QWidget
{
    Q_OBJECT

public:
    ChatViewSearchBar(QWidget* parent = nullptr);

    inline QLineEdit* searchEditLine() const { return ui.searchEditLine; }
    inline QCheckBox* caseSensitiveBox() const { return ui.caseSensitiveBox; }
    inline QCheckBox* searchSendersBox() const { return ui.searchSendersBox; }
    inline QCheckBox* searchMsgsBox() const { return ui.searchMsgsBox; }
    inline QCheckBox* searchOnlyRegularMsgsBox() const { return ui.searchOnlyRegularMsgsBox; }
    inline QToolButton* searchUpButton() const { return ui.searchUpButton; }
    inline QToolButton* searchDownButton() const { return ui.searchDownButton; }

public slots:
    void setVisible(bool) override;

signals:
    void searchChanged(const QString&);
    void hidden();

private slots:
    void delaySearch();
    void search();

private:
    Ui::ChatViewSearchBar ui;
    QTimer _searchDelayTimer;
};

#endif  // CHATVIEWSEARCHBAR_H
