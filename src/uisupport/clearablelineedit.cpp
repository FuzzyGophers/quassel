// SPDX-License-Identifier: GPL-2.0-or-later

#include "clearablelineedit.h"

#include <QStyle>
#include <QToolButton>

#include "icon.h"

ClearableLineEdit::ClearableLineEdit(QWidget* parent)
    : QLineEdit(parent)
{
    clearButton = new QToolButton(this);
    clearButton->setIcon(icon::get("edit-clear-locationbar-rtl"));
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    clearButton->hide();

    connect(clearButton, &QAbstractButton::clicked, this, &QLineEdit::clear);
    connect(this, &QLineEdit::textChanged, this, &ClearableLineEdit::updateClearButton);

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));
}

void ClearableLineEdit::resizeEvent(QResizeEvent*)
{
    QSize size = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - size.width(), (rect().bottom() + 1 - size.height()) / 2);
}

void ClearableLineEdit::updateClearButton(const QString& text)
{
    clearButton->setVisible(!text.isEmpty());
}
