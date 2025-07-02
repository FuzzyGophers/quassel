// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef TITLESETTER_H
#define TITLESETTER_H

#include "abstractitemview.h"

class MainWin;

class TitleSetter : public AbstractItemView
{
    Q_OBJECT

public:
    TitleSetter(MainWin* parent);

protected slots:
    void currentChanged(const QModelIndex& current, const QModelIndex& previous) override;
    void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight) override;

private:
    MainWin* _mainWin;
    void changeWindowTitle(const QModelIndex& index);
};

#endif
