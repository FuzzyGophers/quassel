// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QTreeView>

/**
 * This class handles Touch Events for TreeViews
 */
class UISUPPORT_EXPORT TreeViewTouch : public QTreeView
{
    Q_OBJECT

public:
    explicit TreeViewTouch(QWidget* parent = nullptr);

protected:
    /**
     * Handles Events
     *
     * @param[in,out] an event
     * @returns true if event got handled, false if event got ignored
     */
    bool event(QEvent* event) override;

    /**
     * Handles Mouse Move Events
     *
     * Suppresses Events during Touch-Scroll
     *
     * @param[in,out] An Event
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * Handles Mouse Press Events
     *
     * Suppresses Events during Touch-Scroll
     *
     * @param[in,out] An Event
     */
    void mousePressEvent(QMouseEvent* event) override;

private:
    bool _touchScrollInProgress = false;
    bool _firstTouchUpdateHappened = false;
};
