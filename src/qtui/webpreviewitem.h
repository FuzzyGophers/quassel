// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef WEBPREVIEWITEM_H
#define WEBPREVIEWITEM_H

#if defined HAVE_WEBKIT || defined HAVE_WEBENGINE

#    include <QGraphicsItem>

class WebPreviewItem : public QGraphicsItem
{
public:
    WebPreviewItem(const QUrl& url);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    inline QRectF boundingRect() const override { return _boundingRect; }

private:
    QRectF _boundingRect;
};

#endif  // #ifdef HAVE_WEBKIT || HAVE_WEBENGINE

#endif  // WEBPREVIEWITEM_H
