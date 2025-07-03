// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>
#include <QString>
#include <QTimer>

class Action;
class QMenu;

class SystemTray : public QObject
{
    Q_OBJECT
    Q_ENUMS(State Mode MessageIcon ActivationReason)

public:
    enum State
    {
        Passive,
        Active,
        NeedsAttention
    };

    enum Mode
    {
        Invalid,
        Legacy,
        StatusNotifier
    };

    // same as in QSystemTrayIcon
    enum MessageIcon
    {
        NoIcon,
        Information,
        Warning,
        Critical
    };

    // same as in QSystemTrayIcon
    enum ActivationReason
    {
        Unknown,
        Context,
        DoubleClick,
        Trigger,
        MiddleClick
    };

    enum class AttentionBehavior
    {
        DoNothing,
        ChangeColor,
        Blink
    };

    explicit SystemTray(QWidget* parent);
    ~SystemTray() override;

    Mode mode() const;
    State state() const;
    bool isVisible() const;
    bool isAlerted() const;

    virtual bool isSystemTrayAvailable() const;

    QWidget* associatedWidget() const;

public slots:
    void setVisible(bool visible = true);
    void setState(State);
    void setAlert(bool alerted);

    void setToolTip(const QString& title, const QString& subtitle);
    virtual void showMessage(
        const QString& title, const QString& message, MessageIcon icon = Information, int msTimeout = 10000, uint notificationId = 0);
    virtual void closeMessage(uint notificationId);

signals:
    void modeChanged(Mode mode);
    void stateChanged(State state);
    void visibilityChanged(bool isVisible);
    void iconsChanged();
    void currentIconNameChanged();
    void toolTipChanged(const QString& title, const QString& subtitle);

    void activated(SystemTray::ActivationReason);
    void messageClicked(uint notificationId);
    void messageClosed(uint notificationId);

protected slots:
    virtual void activate(SystemTray::ActivationReason = Trigger);

protected:
    void setMode(Mode mode);

    QString toolTipTitle() const;
    QString toolTipSubTitle() const;
    QMenu* trayMenu() const;

    QString iconName(State state) const;
    QString currentIconName() const;
    QString currentAttentionIconName() const;

private slots:
    void minimizeRestore();
    void trayMenuAboutToShow();
    void invertTrayIconChanged(const QVariant&);
    void enableChangeColorChanged(const QVariant&);
    void enableBlinkChanged(const QVariant&);

    void onBlinkTimeout();

private:
    bool _isVisible{false};
    Mode _mode{Mode::Invalid};
    State _state{State::Passive};
    bool _trayIconInverted{false};
    AttentionBehavior _attentionBehavior{AttentionBehavior::ChangeColor};

    QTimer _blinkTimer;
    bool _blinkState{false};

    QString _toolTipTitle;
    QString _toolTipSubTitle;

    QMenu* _trayMenu{nullptr};
    QWidget* _associatedWidget{nullptr};
    Action* _minimizeRestoreAction{nullptr};
};
