// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef STATUSNOTIFIERITEMDBUS_H_
#define STATUSNOTIFIERITEMDBUS_H_

#include <QDBusArgument>
#include <QDBusConnection>
#include <QObject>
#include <QPixmap>
#include <QString>

// Custom message type for DBus
struct DBusImageStruct
{
    int width;
    int height;
    QByteArray data;
};

using DBusImageVector = QVector<DBusImageStruct>;

struct DBusToolTipStruct
{
    QString icon;
    DBusImageVector image;
    QString title;
    QString subTitle;
};

class StatusNotifierItem;

class StatusNotifierItemDBus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Category READ Category)
    Q_PROPERTY(QString Id READ Id)
    Q_PROPERTY(QString Title READ Title)
    Q_PROPERTY(QString Status READ Status)
    Q_PROPERTY(int WindowId READ WindowId)
    Q_PROPERTY(QString IconName READ IconName)
    Q_PROPERTY(DBusImageVector IconPixmap READ IconPixmap)
    Q_PROPERTY(QString OverlayIconName READ OverlayIconName)
    Q_PROPERTY(DBusImageVector OverlayIconPixmap READ OverlayIconPixmap)
    Q_PROPERTY(QString AttentionIconName READ AttentionIconName)
    Q_PROPERTY(DBusImageVector AttentionIconPixmap READ AttentionIconPixmap)
    Q_PROPERTY(QString AttentionMovieName READ AttentionMovieName)
    Q_PROPERTY(DBusToolTipStruct ToolTip READ ToolTip)
    Q_PROPERTY(QString IconThemePath READ IconThemePath)
    Q_PROPERTY(QDBusObjectPath Menu READ Menu)

    friend class StatusNotifierItem;

public:
    StatusNotifierItemDBus(StatusNotifierItem* parent);
    ~StatusNotifierItemDBus() override;

    /**
     * @return the dbus connection used by this object
     */
    QDBusConnection dbusConnection() const;

    /**
     * Register the StatusNotifierItem to DBus
     */
    void registerTrayIcon();

    /**
     * Unregister the StatusNotifierItem from DBus
     */
    void unregisterTrayIcon();

    /**
     * @return the service this object is registered on the bus under
     */
    QString service() const;

    /**
     * @return the category of the application associated to this item
     * @see Category
     */
    QString Category() const;

    /**
     * @return the id of this item
     */
    QString Id() const;

    /**
     * @return the title of this item
     */
    QString Title() const;

    /**
     * @return The status of this item
     * @see Status
     */
    QString Status() const;

    /**
     * @return The id of the main window of the application that controls the item
     */
    int WindowId() const;

    /**
     * @return the name of the main icon to be displayed
     * if image() is not empty this will always return an empty string
     */
    QString IconName() const;

    /**
     * @return a serialization of the icon data
     */
    DBusImageVector IconPixmap() const;

    /**
     * @return the name of the overlay of the main icon to be displayed
     * if image() is not empty this will always return an empty string
     */
    QString OverlayIconName() const;

    /**
     * @return a serialization of the icon data
     */
    DBusImageVector OverlayIconPixmap() const;

    /**
     * @return the name of the icon to be displayed when the application
     * is requesting the user's attention
     * if attentionImage() is not empty this will always return an empty string
     */
    QString AttentionIconName() const;

    /**
     * @return a serialization of the requesting attention icon data
     */
    DBusImageVector AttentionIconPixmap() const;

    /**
     * @return the name of the attention movie
     */
    QString AttentionMovieName() const;

    /**
     * all the data needed for a tooltip
     */
    DBusToolTipStruct ToolTip() const;

    /**
     * @return path to extra icon theme, to load application specific icons
     */
    QString IconThemePath() const;

    /**
     * @return object path to the dbusmenu object
     */
    QDBusObjectPath Menu() const;

public slots:
    // interaction
    /**
     * Shows the context menu associated to this item
     * at the desired screen position
     */
    void ContextMenu(int x, int y);

    /**
     * Shows the main widget and try to position it on top
     * of the other windows, if the widget is already visible, hide it.
     */
    void Activate(int x, int y);

    /**
     * The user activated the item in an alternate way (for instance with middle mouse button, this depends from the systray implementation)
     */
    void SecondaryActivate(int x, int y);

    /**
     * Inform this item that the mouse wheel was used on its representation
     */
    void Scroll(int delta, const QString& orientation);

signals:
    /**
     * Inform the systemtray that the own main icon has been changed,
     * so should be reloaded
     */
    void NewIcon();

    /**
     * Inform the systemtray that there is a new icon to be used as overlay
     */
    void NewOverlayIcon();

    /**
     * Inform the systemtray that the requesting attention icon
     * has been changed, so should be reloaded
     */
    void NewAttentionIcon();

    /**
     * Inform the systemtray that something in the tooltip has been changed
     */
    void NewToolTip();

    /**
     * Signal the new status when it has been changed
     * @see Status
     */
    void NewStatus(const QString& status);

private:
    StatusNotifierItem* m_statusNotifierItem;
    QDBusConnection m_dbus;
    static int s_serviceCount;
};

const QDBusArgument& operator<<(QDBusArgument& argument, const DBusImageStruct& icon);
const QDBusArgument& operator>>(const QDBusArgument& argument, DBusImageStruct& icon);

Q_DECLARE_METATYPE(DBusImageStruct)

const QDBusArgument& operator<<(QDBusArgument& argument, const DBusImageVector& iconVector);
const QDBusArgument& operator>>(const QDBusArgument& argument, DBusImageVector& iconVector);

Q_DECLARE_METATYPE(DBusImageVector)

const QDBusArgument& operator<<(QDBusArgument& argument, const DBusToolTipStruct& toolTip);
const QDBusArgument& operator>>(const QDBusArgument& argument, DBusToolTipStruct& toolTip);

Q_DECLARE_METATYPE(DBusToolTipStruct)

#endif
