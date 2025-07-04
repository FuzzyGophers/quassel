// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef QTUISTYLE_H_
#define QTUISTYLE_H_

#include "qtuisettings.h"
#include "uistyle.h"

class QtUiStyle : public UiStyle
{
    Q_OBJECT

public:
    QtUiStyle(QObject* parent = nullptr);

    virtual inline qreal firstColumnSeparator() const { return 6; }
    virtual inline qreal secondColumnSeparator() const { return 6; }

public slots:
    /**
     * Generates initial settingsQss if it doesn't exist
     *
     * This allows for default fonts, colors, etc to specified.
     */

    void initializeSettingsQss();

    /**
     * Generates UI stylesheet based on selected fonts, colors, etc
     */
    void generateSettingsQss() const;

private slots:
    /**
     * Updates knowledge of whether or not to use the custom timestamp format
     */
    void updateUseCustomTimestampFormat();

    /**
     * Updates knowledge of the current timestamp format
     */
    void updateTimestampFormatString();

    /**
     * Updates knowledge of how to display sender prefix modes
     */
    void updateSenderPrefixDisplay();

    /**
     * Updates knowledge of whether or not to show sender brackets
     */
    void updateShowSenderBrackets();

private:
    QString fontDescription(const QFont& font) const;

    /**
     * Generate a Qt stylesheet color string from a given setting
     *
     * @param[in] key          Reference to settings key containing a QColor
     * @param[in] settings     UiSettings manager to search
     * @param[in] defaultColor Fallback color if not found; when unspecified default is black
     */
    QString color(const QString& key, UiSettings& settings, const QColor& defaultColor = QColor()) const;

    QString msgTypeQss(const QString& msgType, const QString& key, UiSettings& settings) const;

    /**
     * Generates the Qss color palette stylesheet for sender colors
     *
     * This must be called before generating any Qss dependent on these colors.
     *
     * @see QtUiStyle::senderQss()
     * @param[in] settings     Reference to current UI settings, used for loading color values
     * @return Quassel-theme-compatible Qss color palette
     */
    QString senderPaletteQss(UiSettings& settings) const;

    /**
     * Generate a snippet of Qss stylesheet for a given sender-hash index
     *
     * This depends on the color palette generated by QtUiStyle::senderPaletteQss()
     *
     * @param[in] i            Sender hash index from 0 - 15
     * @param[in] messageType  Type of message to filter, e.g. 'plain' or 'action'
     * @param[in] includeNick  Also apply foreground color to Nick
     * @return Snippet of Quassel-theme-compatible Qss stylesheet
     */
    QString senderQss(int i, const QString& messageType, bool includeNick = false) const;

    /**
     * Generate a snippet of Qss stylesheet for a given IRC nickname sender-hash index
     *
     * This depends on the color palette generated by QtUiStyle::senderPaletteQss()
     *
     * @param[in] i            Sender hash index from 0 - 15
     * @return Snippet of Quassel-theme-compatible Qss stylesheet
     */
    QString nickQss(int i) const;

    QString chatListItemQss(const QString& state, const QString& key, UiSettings& settings) const;
};

#endif
