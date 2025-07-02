// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QEnterEvent>
#include <QFrame>

#include "clickable.h"
#include "uistyle.h"

class UISUPPORT_EXPORT StyledLabel : public QFrame
{
    Q_OBJECT

public:
    enum ResizeMode
    {
        NoResize,
        DynamicResize,
        ResizeOnHover
    };

    StyledLabel(QWidget* parent = nullptr);

    void setText(const QString& text);
    void setCustomFont(const QFont& font);

    QSize sizeHint() const override;
    // virtual QSize minimumSizeHint() const;

    inline QTextOption::WrapMode wrapMode() const { return _wrapMode; }
    void setWrapMode(QTextOption::WrapMode mode);

    inline Qt::Alignment alignment() const { return _alignment; }
    void setAlignment(Qt::Alignment alignment);

    inline bool toolTipEnabled() const { return _toolTipEnabled; }
    void setToolTipEnabled(bool);

    inline ResizeMode resizeMode() const { return _resizeMode; }
    void setResizeMode(ResizeMode);

signals:
    void clickableActivated(const Clickable& click);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent*) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    int posToCursor(const QPointF& pos);

private:
    QSize _sizeHint;
    QTextOption::WrapMode _wrapMode{QTextOption::NoWrap};
    Qt::Alignment _alignment;
    QTextLayout _layout;
    ClickableList _clickables;
    bool _toolTipEnabled{true};
    ResizeMode _resizeMode{NoResize};

    QList<QTextLayout::FormatRange> _layoutList;
    QVector<QTextLayout::FormatRange> _extraLayoutList;

    void layout();
    void updateSizeHint();
    void updateToolTip();

    void setHoverMode(int start, int length);
    void endHoverMode();
};
