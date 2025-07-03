// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RECEIVEFILEDLG_H
#define RECEIVEFILEDLG_H

#include "ui_receivefiledlg.h"

class Transfer;

class ReceiveFileDlg : public QDialog
{
    Q_OBJECT

public:
    ReceiveFileDlg(const Transfer* transfer, QWidget* parent = nullptr);

private slots:
    void on_buttonBox_clicked(QAbstractButton* button);

private:
    Ui::ReceiveFileDlg ui;
    const Transfer* _transfer;
};

#endif
