// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef QTMULTIMEDIANOTIFICATIONBACKEND_H
#define QTMULTIMEDIANOTIFICATIONBACKEND_H

#include <memory>

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

#include "abstractnotificationbackend.h"
#include "settingspage.h"

#include "ui_qtmultimedianotificationconfigwidget.h"

class QtMultimediaNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT

public:
    QtMultimediaNotificationBackend(QObject* parent = nullptr);

    void notify(const Notification&) override;
    void close(uint notificationId) override;
    SettingsPage* createConfigWidget() const override;

private slots:
    void enabledChanged(const QVariant&);
    void audioFileChanged(const QVariant&);
    void createMediaObject(const QString& name);

private:
    class ConfigWidget;

    bool _enabled;
    std::unique_ptr<QMediaPlayer> _media;
    std::unique_ptr<QAudioOutput> _audioOutput;
};

class QtMultimediaNotificationBackend::ConfigWidget : public SettingsPage
{
    Q_OBJECT

public:
    ConfigWidget(QWidget* parent = nullptr);

    void save() override;
    void load() override;
    bool hasDefaults() const override;
    void defaults() override;

private slots:
    void widgetChanged();
    void on_open_clicked();
    void on_play_clicked();

private:
    Ui::QtMultimediaNotificationConfigWidget ui;

    bool _enabled;
    bool _audioAvailable;
    QString _filename;
    std::unique_ptr<QMediaPlayer> _audioPreview;
    std::unique_ptr<QAudioOutput> _audioPreviewOutput;
};

#endif // QTMULTIMEDIANOTIFICATIONBACKEND_H
