// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QDateTime>

#include "messagefilter.h"

class ChatMonitorFilter : public MessageFilter
{
    Q_OBJECT

public:
    enum SenderFields
    {
        NoField = 0x00,
        NetworkField = 0x01,
        BufferField = 0x02,
        SenderField = 0x04,
        AllFields = 0xff
    };

    ChatMonitorFilter(MessageModel* model, QObject* parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    QString idString() const override { return "ChatMonitor"; }
    QVariant data(const QModelIndex& index, int role) const override;

    int showFields() const { return _showFields; }
    bool showOwnMessages() const { return _showOwnMessages; }

public slots:
    void addShowField(int field);
    void removeShowField(int field);
    void setShowOwnMessages(bool show);

private slots:
    void showFieldsSettingChanged(const QVariant& newValue);
    void showOwnMessagesSettingChanged(const QVariant& newValue);
    void alwaysOwnSettingChanged(const QVariant& newValue);
    void showHighlightsSettingChanged(const QVariant& newValue);
    void operationModeSettingChanged(const QVariant& newValue);
    void buffersSettingChanged(const QVariant& newValue);
    void showBacklogSettingChanged(const QVariant& newValue);
    void includeReadSettingChanged(const QVariant& newValue);
    /**
     * Updates the local setting cache of whether or not to show sender brackets
     *
     * @param[in] newValue  If true, sender brackets are enabled, otherwise false.
     */
    void showSenderBracketsSettingChanged(const QVariant& newValue);

private:
    int _showFields;
    bool _showOwnMessages;
    bool _alwaysOwn;
    QList<BufferId> _bufferIds;
    bool _showHighlights;
    int _operationMode;
    bool _showBacklog;
    bool _includeRead;
    bool _showSenderBrackets;  /// If true, show brackets around sender names
};
