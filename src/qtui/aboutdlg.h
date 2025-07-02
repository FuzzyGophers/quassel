// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef ABOUTDLG_H_
#define ABOUTDLG_H_

#include <QDialog>

#include "ui_aboutdlg.h"

class AboutData;

class AboutDlg : public QDialog
{
    Q_OBJECT

public:
    AboutDlg(QWidget* parent = nullptr);

private:
    Ui::AboutDlg ui;

    QString about() const;
    QString authors() const;
    QString contributors() const;
    QString thanksTo() const;

    AboutData* _aboutData;
};

#endif
