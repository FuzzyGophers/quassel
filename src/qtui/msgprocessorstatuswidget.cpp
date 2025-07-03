// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "msgprocessorstatuswidget.h"

MsgProcessorStatusWidget::MsgProcessorStatusWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    hide();
}

void MsgProcessorStatusWidget::setProgress(int value, int max)
{
    if (max <= 0 || value == max) {
        hide();
    }
    else {
        if (isHidden())
            show();
        ui.progressBar->setMaximum(max);
        ui.progressBar->setValue(value);
    }
}
