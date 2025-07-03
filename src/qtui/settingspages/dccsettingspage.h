// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "dccconfig.h"
#include "settingspage.h"

#include "ui_dccsettingspage.h"

/**
 * A settingspage for configuring DCC.
 */
class DccSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    /**
     * Constructor.
     *
     * @param[in] parent QObject parent
     */
    DccSettingsPage(QWidget* parent = nullptr);

    /// See base class docs
    bool hasDefaults() const override;

public slots:
    // See base class docs
    void save() final override;
    void load() final override;
    void defaults() final override;

private:
    /**
     * Whether the client's DccConfig is valid
     *
     * @returns true if the client is connected and its DccConfig instance synchronized
     */
    bool isClientConfigValid() const;

    /**
     * Set the client config
     *
     * @param[in] config The client's config. Must be be valid or a nullptr.
     */
    void setClientConfig(DccConfig* config);

    // See base class docs
    QVariant loadAutoWidgetValue(const QString& widgetName) override;
    void saveAutoWidgetValue(const QString& widgetName, const QVariant& value) override;

private slots:
    /**
     * Updates the enabled state according to the current config.
     */
    void updateWidgetStates();

    /**
     * Checks if the current unsaved config differs from the client's and sets state accordingly.
     */
    void widgetHasChanged();

    /**
     * Called if the client's config was changed (e.g. if the connection state changed).
     */
    void onClientConfigChanged();

private:
    Ui::DccSettingsPage ui;             ///< The UI object
    DccConfig* _clientConfig{nullptr};  ///< Pointer to the client's config (nullptr if not synchronized/available)
    DccConfig _localConfig;             ///< Local config reflecting the widget states
};
