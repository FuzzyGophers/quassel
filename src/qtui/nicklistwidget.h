// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef NICKLISTWIDGET_H_
#define NICKLISTWIDGET_H_

#include <QDockWidget>
#include <QHash>

#include "abstractitemview.h"
#include "buffermodel.h"
#include "types.h"

#include "ui_nicklistwidget.h"

class Buffer;
class NickView;
class QDockWidget;

class NickListWidget : public AbstractItemView
{
    Q_OBJECT

public:
    NickListWidget(QWidget* parent = nullptr);

public slots:
    void showWidget(bool visible);
    void setVisible(bool visible) override;

signals:
    void nickSelectionChanged(const QModelIndexList&);

protected:
    QSize sizeHint() const override;
    void hideEvent(QHideEvent*) override;
    void showEvent(QShowEvent*) override;

protected slots:
    void currentChanged(const QModelIndex& current, const QModelIndex& previous) override;
    void rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end) override;

private:
    void removeBuffer(BufferId bufferId);
    void onNickSelectionChanged();

private:
    Ui::NickListWidget ui;
    QHash<BufferId, NickView*> nickViews;

    QDockWidget* dock() const;
};

// ==============================
//  NickList Dock
// ==============================
class NickListDock : public QDockWidget
{
    Q_OBJECT

public:
    NickListDock(const QString& title, QWidget* parent = nullptr);
    // ~NickListDock();

    void setLocked(bool locked);

    // virtual bool event(QEvent *event);
};

#endif
