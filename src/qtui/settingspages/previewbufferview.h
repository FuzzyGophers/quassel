// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef PREVIEWBUFFERVIEW_H
#define PREVIEWBUFFERVIEW_H

#include "bufferview.h"

class PreviewBufferView : public BufferView
{
    Q_OBJECT

public:
    PreviewBufferView(QWidget* parent = nullptr)
        : BufferView(parent)
    {
    }

protected:
    void keyPressEvent(QKeyEvent* event) override { QTreeView::keyPressEvent(event); }
    void contextMenuEvent(QContextMenuEvent*) override {}
};

#endif  // PREVIEWBUFFERVIEW_H
