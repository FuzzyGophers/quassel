// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "fontselector.h"

#include <QEvent>
#include <QFontDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

FontSelector::FontSelector(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QHBoxLayout(this);
    QPushButton* chooseButton = new QPushButton(tr("Choose..."), this);
    connect(chooseButton, &QAbstractButton::clicked, this, &FontSelector::chooseFont);

    layout->addWidget(_demo = new QLabel("Font"));
    layout->addWidget(chooseButton);
    layout->setContentsMargins(0, 0, 0, 0);

    _demo->setFrameStyle(QFrame::StyledPanel);
    _demo->setFrameShadow(QFrame::Sunken);
    _demo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    _font = font();
}

void FontSelector::setSelectedFont(const QFont& font)
{
    _font = font;
    _demo->setText(QString("%1 %2pt").arg(font.family()).arg(font.pointSize()));
    _demo->setFont(font);
    emit fontChanged(font);
}

void FontSelector::chooseFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, _demo->font(), nullptr, QString(), QFontDialog::DontUseNativeDialog);
    if (ok) {
        setSelectedFont(font);
    }
}

void FontSelector::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::StyleChange) {
        _demo->setFont(_font);
    }
}
