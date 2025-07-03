// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "webpreviewitem.h"

#ifdef HAVE_WEBENGINE
#    include <QWebEngineSettings>
#    include <QWebEngineView>
#elif defined HAVE_WEBKIT
#    include <QWebSettings>
#    include <QWebView>
#endif

#if defined HAVE_WEBKIT || defined HAVE_WEBENGINE

#    include <QGraphicsProxyWidget>
#    include <QPainter>

#    ifdef HAVE_WEBENGINE
// QGraphicsProxyWidget does not stay synced with QWebEngineView, therefore we modify QWebEngineView
// and manually trigger an update of the proxyItem on UpdateRequest Event. See: http://stackoverflow.com/a/30920209
// and http://lists.qt-project.org/pipermail/development/2016-March/025280.html (At least in Qt5.6)
class CustomWebView : public QWebEngineView
{
private:
    QGraphicsProxyWidget* proxyItem;

public:
    CustomWebView(QGraphicsProxyWidget* pItem) { proxyItem = pItem; }
    bool event(QEvent* event) override
    {
        if (event->type() == QEvent::UpdateRequest) {
            proxyItem->update();
        }

        return QWebEngineView::event(event);
    }
};
#    endif

WebPreviewItem::WebPreviewItem(const QUrl& url)
    : QGraphicsItem(nullptr)
    ,  // needs to be a top level item as we otherwise cannot guarantee that it's on top of other chatlines
    _boundingRect(0, 0, 400, 300)
{
    qreal frameWidth = 5;

    QGraphicsProxyWidget* proxyItem = new QGraphicsProxyWidget(this);
#    ifdef HAVE_WEBENGINE
    QWebEngineView* webView = new CustomWebView(proxyItem);
    webView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, false);
#    elif defined HAVE_WEBKIT
    QWebView* webView = new QWebView;
    webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
#    endif
    webView->load(url);
    webView->setDisabled(true);
    webView->resize(1000, 750);
    proxyItem->setWidget(webView);
    proxyItem->setAcceptHoverEvents(false);

    qreal xScale = (_boundingRect.width() - 2 * frameWidth) / webView->width();
    qreal yScale = (_boundingRect.height() - 2 * frameWidth) / webView->height();
    proxyItem->setTransform(QTransform::fromScale(xScale, yScale), true);
    proxyItem->setPos(frameWidth, frameWidth);

    setZValue(30);
}

void WebPreviewItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setClipRect(boundingRect());
    painter->setPen(QPen(Qt::black, 5));
    painter->setBrush(Qt::black);
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawRoundedRect(boundingRect(), 10, 10);
}

#endif  //#ifdef HAVE_WEBKIT || HAVE_WEBENGINE
