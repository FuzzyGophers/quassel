// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <vector>

#include <QDateTime>
#include <QFile>
#include <QMetaType>
#include <QObject>
#include <QString>

/**
 * The Logger class encapsulates the various configured logging backends.
 */
class COMMON_EXPORT Logger : public QObject
{
    Q_OBJECT

public:
    Logger(QObject* parent = nullptr);
    ~Logger() override;

    enum class LogLevel
    {
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    struct COMMON_EXPORT LogEntry
    {
        QDateTime timeStamp;
        LogLevel logLevel;
        QString message;

        /**
         * Gets this log entry in a printable format, with timestamp and log level
         *
         * @return the log entry, formatted with timestamp and log level
         */
        QString toString() const;
    };

    /**
     * Initial setup, to be called ones command line options are available.
     *
     * Sets up the log file if appropriate. Outputs the log messages already accumulated since
     * construction. If @c keepMessages is false, deletes the accumulated messages afterwards,
     * and won't store further ones.
     *
     * @param keepMessages Whether messages should be kept
     * @throws ExitException, if command line options are invalid
     */
    void setup(bool keepMessages);

    /**
     * Accesses the stores log messages, e.g. for consumption by DebugLogWidget.
     *
     * @returns The accumuates log messages
     */
    std::vector<Logger::LogEntry> messages() const;

    static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message);

    /**
     * Takes the given message with the given log level, formats it and emits the @a messageLogged() signal.
     *
     * @note This method is thread-safe.
     *
     * @param logLevel The log leve of the message
     * @param message  The message
     */
    void handleMessage(LogLevel logLevel, const QString& message);

signals:
    /**
     * Emitted whenever a message was logged.
     *
     * @param message The message that was logged
     */
    void messageLogged(const Logger::LogEntry& message);

private slots:
    void onMessageLogged(const Logger::LogEntry& message);

private:
    void handleMessage(QtMsgType type, const QString& message);
    void outputMessage(const LogEntry& message);

private:
    LogLevel _outputLevel{LogLevel::Info};
    QFile _logFile;
    bool _syslogEnabled{false};

    std::vector<LogEntry> _messages;
    bool _keepMessages{true};
    bool _initialized{false};
    QByteArray _prgname;
};

Q_DECLARE_METATYPE(Logger::LogEntry)
