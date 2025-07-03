// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qtuisettings.h"
#include "uistyle.h"

class ChatScene;
class ChatView;

class ChatViewSettings : public QtUiSettings
{
public:
    Q_ENUMS(OperationMode)
public:
    enum OperationMode
    {
        InvalidMode = 0,
        OptIn = 1,
        OptOut = 2
    };
    Q_DECLARE_FLAGS(OperationModes, OperationMode)

    ChatViewSettings(const QString& id = "__default__");
    ChatViewSettings(ChatScene* scene);
    ChatViewSettings(ChatView* view);

    bool showWebPreview() const;
    void enableWebPreview(bool enabled);

    /**
     * Gets if a custom timestamp format is used.
     *
     * @returns True if custom timestamp format used, otherwise false
     */
    bool useCustomTimestampFormat() const;
    /**
     * Sets whether a custom timestamp format is used.
     *
     * @param[in] enabled True if custom timestamp format used, otherwise false
     */
    void setUseCustomTimestampFormat(bool enabled);

    /**
     * Gets the format string for chat log timestamps.
     *
     * @returns String representing timestamp format, e.g. "[hh:mm:ss]" or " hh:mm:ss"
     */
    QString timestampFormatString() const;
    // Include a space in the default TimestampFormat to give the timestamp a small bit of padding
    // between the border of the chat buffer window and the numbers.  Helps with readability.
    /**
     * Sets the format string for chat log timestamps
     *
     * @param[in] format String representing timestamp format, e.g. "[hh:mm:ss]" or " hh:mm:ss"
     */
    void setTimestampFormatString(const QString& format);

    /**
     * Gets how prefix modes are shown before sender names
     *
     * @returns SenderPrefixMode of what format to use for showing sender prefix modes
     */
    UiStyle::SenderPrefixMode senderPrefixDisplay() const;

    /**
     * Gets if brackets are shown around sender names
     *
     * @returns True if sender brackets enabled, otherwise false
     */
    bool showSenderBrackets() const;
    /**
     * Sets whether brackets are shown around around sender names.
     *
     * @param[in] enabled True if enabling sender brackets, otherwise false
     */
    void enableSenderBrackets(bool enabled);

    QString webSearchUrlFormatString() const;
    void setWebSearchUrlFormatString(const QString& format);
};

Q_DECLARE_METATYPE(ChatViewSettings::OperationMode)
