// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QDialog>

#include "ui_resourcetreedlg.h"

class ResourceTreeDlg : public QDialog
{
    Q_OBJECT

public:
    ResourceTreeDlg(QWidget* parent = nullptr);

private:
    Ui::ResourceTreeDlg ui;
};
