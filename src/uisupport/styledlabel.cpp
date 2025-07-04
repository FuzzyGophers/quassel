// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "styledlabel.h"

#include <QPainter>
#include <QTextDocument>
#include <QTextLayout>

#include "graphicalui.h"
#include "uistyle.h"

StyledLabel::StyledLabel(QWidget* parent)
    : QFrame(parent)
    , _alignment(Qt::AlignVCenter | Qt::AlignLeft)
{
    setMouseTracking(true);

    QTextOption opt = _layout.textOption();
    opt.setWrapMode(_wrapMode);
    opt.setAlignment(_alignment);
    _layout.setTextOption(opt);
}

void StyledLabel::setCustomFont(const QFont& font)
{
    setFont(font);
    _layout.setFont(font);
    setText(_layout.text());
}

void StyledLabel::setWrapMode(QTextOption::WrapMode mode)
{
    if (_wrapMode == mode)
        return;

    _wrapMode = mode;
    QTextOption opt = _layout.textOption();
    opt.setWrapMode(mode);
    _layout.setTextOption(opt);

    layout();
}

void StyledLabel::setAlignment(Qt::Alignment alignment)
{
    if (_alignment == alignment)
        return;

    _alignment = alignment;
    QTextOption opt = _layout.textOption();
    opt.setAlignment(alignment);
    _layout.setTextOption(opt);

    layout();
}

void StyledLabel::setResizeMode(ResizeMode mode)
{
    if (_resizeMode == mode)
        return;

    _resizeMode = mode;
    if (mode == DynamicResize)
        setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    else
        setWrapMode(QTextOption::NoWrap);
}

void StyledLabel::resizeEvent(QResizeEvent* event)
{
    QFrame::resizeEvent(event);

    layout();
}

QSize StyledLabel::sizeHint() const
{
    return _sizeHint;
}

void StyledLabel::updateSizeHint()
{
    QSize sh;
    int padding = frameWidth() * 2;
    sh = _layout.boundingRect().size().toSize() + QSize(padding, padding);

    if (_sizeHint != sh) {
        _sizeHint = sh;
        updateGeometry();
    }
}

void StyledLabel::setText(const QString& text)
{
    UiStyle::StyledString sstr = UiStyle::styleString(UiStyle::mircToInternal(text), UiStyle::FormatType::PlainMsg);
    UiStyle::FormatContainer layoutList = GraphicalUi::uiStyle()->toTextLayoutList(sstr.formatList,
                                                                                   sstr.plainText.length(),
                                                                                   UiStyle::MessageLabel::None);

    // Use default font rather than the style's
    QTextLayout::FormatRange fmtRange;
    fmtRange.format.setFont(font());
    fmtRange.start = 0;
    fmtRange.length = sstr.plainText.length();
    layoutList << fmtRange;

    // Mark URLs
    _clickables = ClickableList::fromString(sstr.plainText);
    for (const Clickable& click : _clickables) {
        if (click.type() == Clickable::Url) {
            QTextLayout::FormatRange range;
            range.start = click.start();
            range.length = click.length();
            range.format.setForeground(palette().link());
            layoutList << range;
        }
    }

    _layout.setText(sstr.plainText);
    UiStyle::setTextLayoutFormats(_layout, layoutList);

    layout();

    endHoverMode();
}

void StyledLabel::updateToolTip()
{
    if (frameRect().width() - 2 * frameWidth() < _layout.minimumWidth())
        setToolTip(QString("<qt>%1</qt>").arg(_layout.text().toHtmlEscaped()));  // only rich text gets wordwrapped!
    else
        setToolTip(QString());
}

void StyledLabel::layout()
{
    qreal h = 0;
    qreal w = contentsRect().width();

    _layout.beginLayout();
    forever
    {
        QTextLine line = _layout.createLine();
        if (!line.isValid())
            break;
        line.setLineWidth(w);
        line.setPosition(QPointF(0, h));
        h += line.height();
    }
    _layout.endLayout();

    updateSizeHint();
    updateToolTip();
    update();
}

void StyledLabel::paintEvent(QPaintEvent* e)
{
    QFrame::paintEvent(e);
    QPainter painter(this);

    qreal y = contentsRect().y() + (contentsRect().height() - _layout.boundingRect().height()) / 2;
    _layout.draw(&painter, QPointF(contentsRect().x(), y), _extraLayoutList);
}

int StyledLabel::posToCursor(const QPointF& pos)
{
    if (pos.y() < 0 || pos.y() > height())
        return -1;

    for (int l = _layout.lineCount() - 1; l >= 0; l--) {
        QTextLine line = _layout.lineAt(l);
        if (pos.y() >= line.y()) {
            return line.xToCursor(pos.x(), QTextLine::CursorOnCharacter);
        }
    }
    return -1;
}

void StyledLabel::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::NoButton) {
        Clickable click = _clickables.atCursorPos(posToCursor(event->position()));
        if (click.isValid())
            setHoverMode(click.start(), click.length());
        else
            endHoverMode();
    }
}

void StyledLabel::enterEvent(QEnterEvent*)
{
    if (resizeMode() == ResizeOnHover)
        setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
}

void StyledLabel::leaveEvent(QEvent*)
{
    endHoverMode();
    if (resizeMode() == ResizeOnHover)
        setWrapMode(QTextOption::NoWrap);
}

void StyledLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        Clickable click = _clickables.atCursorPos(posToCursor(event->position()));
        if (click.isValid())
            emit clickableActivated(click);
    }
}

void StyledLabel::setHoverMode(int start, int length)
{
    if (_extraLayoutList.count() >= 1 && _extraLayoutList.first().start == start && _extraLayoutList.first().length == length)
        return;

    QTextLayout::FormatRange range;
    range.start = start;
    range.length = length;
    range.format.setFontUnderline(true);
    _extraLayoutList.clear();
    _extraLayoutList << range;

    setCursor(Qt::PointingHandCursor);
    update();
}

void StyledLabel::endHoverMode()
{
    _extraLayoutList.clear();
    setCursor(Qt::ArrowCursor);
    update();
}
