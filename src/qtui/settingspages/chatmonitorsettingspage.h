// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef _CHATMONITORSETTINGSPAGE_H_
#define _CHATMONITORSETTINGSPAGE_H_

#include <QHash>

#include "settingspage.h"

#include "ui_chatmonitorsettingspage.h"

class BufferViewConfig;

class ChatMonitorSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    ChatMonitorSettingsPage(QWidget* parent = nullptr);
    bool hasDefaults() const override;

public slots:
    void save() override;
    void load() override;
    void loadSettings();
    void defaults() override;

private slots:
    void widgetHasChanged();
    void on_activateBuffer_clicked();
    void on_deactivateBuffer_clicked();
    void switchOperationMode(int idx);

    /**
     * Sets the local cache of the current backlog requester type, used to determine if showing
     * backlog in the Chat Monitor will work
     *
     * @seealso BacklogSettings::setRequesterType()
     */
    void setRequesterType(const QVariant&);

    /**
     * Event handler for Show Backlog Unavailable Details button
     */
    void on_showBacklogUnavailableDetails_clicked();
private:
    Ui::ChatMonitorSettingsPage ui;
    QHash<QString, QVariant> settings;
    bool testHasChanged();
    void toggleBuffers(BufferView* inView, BufferViewConfig* inCfg, BufferView* outView, BufferViewConfig* outCfg);

    BufferViewConfig* _configAvailable;
    BufferViewConfig* _configActive;
};

#endif
