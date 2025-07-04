// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qtmultimedianotificationbackend.h"

#include <memory>

#include <QFileDialog>
#include <QUrl>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlayer>

#include "clientsettings.h"
#include "icon.h"
#include "mainwin.h"
#include "qtui.h"

QtMultimediaNotificationBackend::QtMultimediaNotificationBackend(QObject* parent)
    : AbstractNotificationBackend(parent)
{
    NotificationSettings notificationSettings;
    notificationSettings.notify("QtMultimedia/Enabled", this, &QtMultimediaNotificationBackend::enabledChanged);
    notificationSettings.notify("QtMultimedia/AudioFile", this, &QtMultimediaNotificationBackend::audioFileChanged);

    createMediaObject(notificationSettings.value("QtMultimedia/AudioFile", QString()).toString());

    _enabled = notificationSettings.value("QtMultimedia/Enabled", true).toBool();
}

void QtMultimediaNotificationBackend::notify(const Notification& notification)
{
    if (_enabled && (notification.type == Highlight || notification.type == PrivMsg)) {
        if (_media && _audioOutput) {
            _media->stop();
            _media->play();
        }
        else {
            QApplication::beep();
        }
    }
}

void QtMultimediaNotificationBackend::close(uint notificationId)
{
    Q_UNUSED(notificationId);
}

void QtMultimediaNotificationBackend::enabledChanged(const QVariant& v)
{
    _enabled = v.toBool();
}

void QtMultimediaNotificationBackend::audioFileChanged(const QVariant& v)
{
    createMediaObject(v.toString());
}

SettingsPage* QtMultimediaNotificationBackend::createConfigWidget() const
{
    return new ConfigWidget();
}

void QtMultimediaNotificationBackend::createMediaObject(const QString& file)
{
    if (file.isEmpty()) {
        _media.reset();
        _audioOutput.reset();
        return;
    }

    _media = std::make_unique<QMediaPlayer>();
    _audioOutput = std::make_unique<QAudioOutput>();
    _media->setAudioOutput(_audioOutput.get());
    _media->setSource(QUrl::fromLocalFile(file));
}

/***************************************************************************/

QtMultimediaNotificationBackend::ConfigWidget::ConfigWidget(QWidget* parent)
    : SettingsPage("Internal", "QtMultimediaNotification", parent)
{
    ui.setupUi(this);
    ui.enabled->setIcon(icon::get("media-playback-start"));
    ui.play->setIcon(icon::get("media-playback-start"));
    ui.open->setIcon(icon::get("document-open"));

    _audioAvailable = true;  // Assume available; adjust if needed based on runtime checks

    connect(ui.enabled, &QAbstractButton::toggled, this, &ConfigWidget::widgetChanged);
    connect(ui.filename, &QLineEdit::textChanged, this, &ConfigWidget::widgetChanged);
}

void QtMultimediaNotificationBackend::ConfigWidget::widgetChanged()
{
    if (!_audioAvailable) {
        ui.play->setEnabled(ui.enabled->isChecked());
        ui.open->setEnabled(false);
        ui.filename->setEnabled(false);
        ui.filename->setText({});
    }
    else {
        ui.play->setEnabled(ui.enabled->isChecked() && !ui.filename->text().isEmpty());

        bool changed = (_enabled != ui.enabled->isChecked() || _filename != ui.filename->text());

        if (changed != hasChanged())
            setChangedState(changed);
    }
}

bool QtMultimediaNotificationBackend::ConfigWidget::hasDefaults() const
{
    return true;
}

void QtMultimediaNotificationBackend::ConfigWidget::defaults()
{
    ui.enabled->setChecked(false);
    ui.filename->setText({});
    widgetChanged();
}

void QtMultimediaNotificationBackend::ConfigWidget::load()
{
    NotificationSettings s;
    _enabled = s.value("QtMultimedia/Enabled", false).toBool();
    _filename = s.value("QtMultimedia/AudioFile", QString()).toString();

    ui.enabled->setChecked(_enabled);
    ui.filename->setText(_filename);

    setChangedState(false);
}

void QtMultimediaNotificationBackend::ConfigWidget::save()
{
    NotificationSettings s;
    s.setValue("QtMultimedia/Enabled", ui.enabled->isChecked());
    s.setValue("QtMultimedia/AudioFile", ui.filename->text());
    load();
}

void QtMultimediaNotificationBackend::ConfigWidget::on_open_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select Audio File"));
    if (!file.isEmpty()) {
        ui.filename->setText(file);
        ui.play->setEnabled(true);
        widgetChanged();
    }
}

void QtMultimediaNotificationBackend::ConfigWidget::on_play_clicked()
{
    if (_audioAvailable) {
        if (!ui.filename->text().isEmpty()) {
            _audioPreview = std::make_unique<QMediaPlayer>();
            _audioPreviewOutput = std::make_unique<QAudioOutput>();
            _audioPreview->setAudioOutput(_audioPreviewOutput.get());
            _audioPreview->setSource(QUrl::fromLocalFile(ui.filename->text()));
            _audioPreview->play();
        }
    }
    else {
        QApplication::beep();
    }
}
