// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "statusnotifieritemdbus.h"

#include <QApplication>
#include <QDBusConnection>
#include <QImage>
#include <QMenu>
#include <QPixmap>

#include "mainwin.h"
#include "qtui.h"
#include "statusnotifieritem.h"
#include "statusnotifieritemadaptor.h"
#include "statusnotifierwatcher.h"

#ifdef Q_OS_WIN64
__inline int toInt(WId wid)
{
    return (int)((__int64)wid);
}

#else
__inline int toInt(WId wid)
{
    return (int)wid;
}

#endif

// Marshall the ImageStruct data into a D-BUS argument
const QDBusArgument& operator<<(QDBusArgument& argument, const DBusImageStruct& icon)
{
    argument.beginStructure();
    argument << icon.width;
    argument << icon.height;
    argument << icon.data;
    argument.endStructure();
    return argument;
}

// Retrieve the ImageStruct data from the D-BUS argument
const QDBusArgument& operator>>(const QDBusArgument& argument, DBusImageStruct& icon)
{
    qint32 width;
    qint32 height;
    QByteArray data;

    argument.beginStructure();
    argument >> width;
    argument >> height;
    argument >> data;
    argument.endStructure();

    icon.width = width;
    icon.height = height;
    icon.data = data;

    return argument;
}

// Marshall the ImageVector data into a D-BUS argument
const QDBusArgument& operator<<(QDBusArgument& argument, const DBusImageVector& iconVector)
{
    argument.beginArray(qMetaTypeId<DBusImageStruct>());
    for (const auto& i : iconVector) {
        argument << i;
    }
    argument.endArray();
    return argument;
}

// Retrieve the ImageVector data from the D-BUS argument
const QDBusArgument& operator>>(const QDBusArgument& argument, DBusImageVector& iconVector)
{
    argument.beginArray();
    iconVector.clear();

    while (!argument.atEnd()) {
        DBusImageStruct element;
        argument >> element;
        iconVector.append(element);
    }

    argument.endArray();

    return argument;
}

// Marshall the ToolTipStruct data into a D-BUS argument
const QDBusArgument& operator<<(QDBusArgument& argument, const DBusToolTipStruct& toolTip)
{
    argument.beginStructure();
    argument << toolTip.icon;
    argument << toolTip.image;
    argument << toolTip.title;
    argument << toolTip.subTitle;
    argument.endStructure();
    return argument;
}

// Retrieve the ToolTipStruct data from the D-BUS argument
const QDBusArgument& operator>>(const QDBusArgument& argument, DBusToolTipStruct& toolTip)
{
    QString icon;
    DBusImageVector image;
    QString title;
    QString subTitle;

    argument.beginStructure();
    argument >> icon;
    argument >> image;
    argument >> title;
    argument >> subTitle;
    argument.endStructure();

    toolTip.icon = icon;
    toolTip.image = image;
    toolTip.title = title;
    toolTip.subTitle = subTitle;

    return argument;
}

int StatusNotifierItemDBus::s_serviceCount = 0;

StatusNotifierItemDBus::StatusNotifierItemDBus(StatusNotifierItem* parent)
    : QObject(parent)
    , m_statusNotifierItem(parent)
    , m_dbus(
          QDBusConnection::connectToBus(QDBusConnection::SessionBus,
                                        QString("org.kde.StatusNotifierItem-%1-%2").arg(QCoreApplication::applicationPid()).arg(++s_serviceCount)))
{
    new StatusNotifierItemAdaptor(this);
}

StatusNotifierItemDBus::~StatusNotifierItemDBus()
{
    unregisterTrayIcon();
}

QDBusConnection StatusNotifierItemDBus::dbusConnection() const
{
    return m_dbus;
}

// FIXME: prevent double registrations, also test this on platforms != KDE
//
void StatusNotifierItemDBus::registerTrayIcon()
{
    m_dbus.registerObject("/StatusNotifierItem", this);
}

// FIXME: see above
void StatusNotifierItemDBus::unregisterTrayIcon()
{
    if (m_dbus.isConnected()) {
        m_dbus.unregisterObject("/StatusNotifierItem");
    }
}

QString StatusNotifierItemDBus::service() const
{
    return m_dbus.baseService();
}

// DBUS slots
// Values and calls have been adapted to Quassel

QString StatusNotifierItemDBus::Category() const
{
    return QString("Communications");  // no need to make this configurable for Quassel
}

QString StatusNotifierItemDBus::Title() const
{
    return m_statusNotifierItem->title();
}

QString StatusNotifierItemDBus::Id() const
{
    return QString("QuasselIRC");
}

QString StatusNotifierItemDBus::Status() const
{
    return m_statusNotifierItem->metaObject()
        ->enumerator(m_statusNotifierItem->metaObject()->indexOfEnumerator("State"))
        .valueToKey(m_statusNotifierItem->state());
}

int StatusNotifierItemDBus::WindowId() const
{
    return toInt(QtUi::mainWindow()->winId());
}

// Icon
// We don't need to support serialized icon data in Quassel

QString StatusNotifierItemDBus::IconName() const
{
    return m_statusNotifierItem->iconName();
}

DBusImageVector StatusNotifierItemDBus::IconPixmap() const
{
    return DBusImageVector();
}

QString StatusNotifierItemDBus::OverlayIconName() const
{
    return QString();
}

DBusImageVector StatusNotifierItemDBus::OverlayIconPixmap() const
{
    return DBusImageVector();
}

// Requesting attention icon and movie

QString StatusNotifierItemDBus::AttentionIconName() const
{
    return m_statusNotifierItem->attentionIconName();
}

DBusImageVector StatusNotifierItemDBus::AttentionIconPixmap() const
{
    return DBusImageVector();
}

QString StatusNotifierItemDBus::AttentionMovieName() const
{
    return QString();
}

// ToolTip

DBusToolTipStruct StatusNotifierItemDBus::ToolTip() const
{
    DBusToolTipStruct toolTip;
    toolTip.icon = m_statusNotifierItem->toolTipIconName();
    toolTip.image = DBusImageVector();
    toolTip.title = m_statusNotifierItem->toolTipTitle();
    toolTip.subTitle = m_statusNotifierItem->toolTipSubTitle();

    return toolTip;
}

QString StatusNotifierItemDBus::IconThemePath() const
{
    return m_statusNotifierItem->iconThemePath();
}

// Menu

QDBusObjectPath StatusNotifierItemDBus::Menu() const
{
    return QDBusObjectPath(m_statusNotifierItem->menuObjectPath());
}

// Interaction

void StatusNotifierItemDBus::ContextMenu(int x, int y)
{
    if (!m_statusNotifierItem->trayMenu()) {
        return;
    }

    // TODO: nicer placement, possible?
    if (!m_statusNotifierItem->trayMenu()->isVisible()) {
        m_statusNotifierItem->trayMenu()->popup(QPoint(x, y));
    }
    else {
        m_statusNotifierItem->trayMenu()->hide();
    }
}

void StatusNotifierItemDBus::Activate(int x, int y)
{
    m_statusNotifierItem->activated(QPoint(x, y));
}

void StatusNotifierItemDBus::SecondaryActivate(int x, int y)
{
    Q_UNUSED(x)
    Q_UNUSED(y)
    // emit m_statusNotifierItem->secondaryActivateRequested(QPoint(x,y));
}

void StatusNotifierItemDBus::Scroll(int delta, const QString& orientation)
{
    Q_UNUSED(delta)
    Q_UNUSED(orientation)
    // Qt::Orientation dir = (orientation.toLower() == "horizontal" ? Qt::Horizontal : Qt::Vertical);
    // emit m_statusNotifierItem->scrollRequested(delta, dir);
}
