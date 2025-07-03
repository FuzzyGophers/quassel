// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <utility>

#include "uistyle.h"

class QssParser
{
    Q_DECLARE_TR_FUNCTIONS(QssParser)

public:
    QssParser();

    void processStyleSheet(QString& sheet);

    inline QPalette palette() const { return _palette; }
    inline QVector<QBrush> uiStylePalette() const { return _uiStylePalette; }
    inline const QHash<quint64, QTextCharFormat>& formats() const { return _formats; }
    inline const QHash<UiStyle::ItemFormatType, QTextCharFormat>& listItemFormats() const { return _listItemFormats; }

protected:
    using ColorTuple = QList<qreal>;

    void parseChatLineBlock(const QString& decl, const QString& contents);
    void parsePaletteBlock(const QString& decl, const QString& contents);
    void parseListItemBlock(const QString& decl, const QString& contents);

    std::pair<UiStyle::FormatType, UiStyle::MessageLabel> parseFormatType(const QString& decl);
    UiStyle::ItemFormatType parseItemFormatType(const QString& decl);

    QTextCharFormat parseFormat(const QString& qss);

    // Parse boolean properties
    bool parseBoolean(const QString& str, bool* ok = nullptr) const;

    // Parse color/brush-related properties
    QBrush parseBrush(const QString& str, bool* ok = nullptr);
    QColor parseColor(const QString& str);
    ColorTuple parseColorTuple(const QString& str);
    QGradientStops parseGradientStops(const QString& str);

    // Parse font-related properties
    void parseFont(const QString& str, QTextCharFormat* format);
    void parseFontStyle(const QString& str, QTextCharFormat* format);
    void parseFontWeight(const QString& str, QTextCharFormat* format);
    void parseFontSize(const QString& str, QTextCharFormat* format);
    void parseFontFamily(const QString& str, QTextCharFormat* format);

    QHash<QString, QPalette::ColorRole> _paletteColorRoles;
    QHash<QString, UiStyle::ColorRole> _uiStyleColorRoles;

private:
    QPalette _palette;
    QVector<QBrush> _uiStylePalette;
    QHash<quint64, QTextCharFormat> _formats;
    QHash<UiStyle::ItemFormatType, QTextCharFormat> _listItemFormats;
};
