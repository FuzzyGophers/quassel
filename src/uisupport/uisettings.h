// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include "clientsettings.h"
#include "uistyle.h"

class UISUPPORT_EXPORT UiSettings : public ClientSettings
{
public:
    UiSettings(QString group = "Ui");

    virtual void setValue(const QString& key, const QVariant& data);
    virtual QVariant value(const QString& key, const QVariant& def = {}) const;

    /**
     * Gets if a value exists in settings
     *
     * @param[in] key ID of local settings key
     * @returns True if key exists in settings, otherwise false
     */
    bool valueExists(const QString& key) const;

    void remove(const QString& key);
};

class UISUPPORT_EXPORT UiStyleSettings : public UiSettings
{
public:
    UiStyleSettings();
    UiStyleSettings(const QString& subGroup);

    void setCustomFormat(UiStyle::FormatType, const QTextCharFormat& format);
    QTextCharFormat customFormat(UiStyle::FormatType) const;

    void removeCustomFormat(UiStyle::FormatType);
    QList<UiStyle::FormatType> availableFormats() const;
};

class UISUPPORT_EXPORT SessionSettings : public UiSettings
{
public:
    SessionSettings(QString sessionId, QString group = "Session");

    void setValue(const QString& key, const QVariant& data) override;
    QVariant value(const QString& key, const QVariant& def = {}) const override;

    void removeKey(const QString& key);
    void removeSession();

    void cleanup();
    void sessionAging();

    int sessionAge();
    void setSessionAge(int age);
    QString sessionId() const;
    void setSessionId(QString sessionId);

private:
    QString _sessionId;
};

class UISUPPORT_EXPORT ShortcutSettings : public UiSettings
{
public:
    ShortcutSettings();

    //! Remove all stored shortcuts
    void clear();

    QStringList savedShortcuts() const;

    void saveShortcut(const QString& name, const QKeySequence& shortcut);
    QKeySequence loadShortcut(const QString& name) const;
};
