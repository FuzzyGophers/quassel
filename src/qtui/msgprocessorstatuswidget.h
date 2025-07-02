// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef MSGPROCESSORSTATUSWIDGET_H_
#define MSGPROCESSORSTATUSWIDGET_H_

#include "ui_msgprocessorstatuswidget.h"

class MsgProcessorStatusWidget : public QWidget
{
    Q_OBJECT

public:
    MsgProcessorStatusWidget(QWidget* parent = nullptr);

public slots:
    void setProgress(int value, int max);

private:
    Ui::MsgProcessorStatusWidget ui;
};

#endif
