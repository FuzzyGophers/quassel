// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef VERTICALDOCKTITLE_H
#define VERTICALDOCKTITLE_H

#include <QDockWidget>
#include <QSize>

class VerticalDockTitle : public QWidget
{
    Q_OBJECT

public:
    VerticalDockTitle(QDockWidget* parent);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void show(bool show_);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    bool _show;
};

class EmptyDockTitle : public QWidget
{
    Q_OBJECT

public:
    inline EmptyDockTitle(QDockWidget* parent)
        : QWidget(parent)
    {
    }

    inline QSize sizeHint() const override { return {0, 0}; }
};

class VerticalDock : public QDockWidget
{
    Q_OBJECT

public:
    VerticalDock(const QString& title, QWidget* parent = nullptr, Qt::WindowFlags flags = {});
    VerticalDock(QWidget* parent = nullptr, Qt::WindowFlags flags = {});

    void showTitle(bool show);
    void setDefaultTitleWidget();
};

#endif  // VERTICALDOCKTITLE_H
