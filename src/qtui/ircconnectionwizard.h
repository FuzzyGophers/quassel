// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef IRCCONNECTIONWIZARD_H
#define IRCCONNECTIONWIZARD_H

#include <QWizard>

#include "types.h"

class IrcConnectionWizard : public QWizard
{
    Q_OBJECT

public:
    IrcConnectionWizard(QWidget* parent = nullptr, Qt::WindowFlags flags = {});

    static QWizardPage* createIntroductionPage(QWidget* parent = nullptr);

private slots:
    void finishClicked();
    void identityReady(IdentityId id);
    void networkReady(NetworkId id);

private:
    QWizardPage* _introductionPage{nullptr};
    QWizardPage* _identityPage{nullptr};
    QWizardPage* _networkPage{nullptr};
};

// ==============================
//  Wizard Pages
// ==============================

// Identity Page
#include "clientidentity.h"

class IdentityEditWidget;

class IdentityPage : public QWizardPage
{
    Q_OBJECT

public:
    IdentityPage(QWidget* parent = nullptr);

    CertIdentity* identity();

private:
    IdentityEditWidget* _identityEditWidget;
    CertIdentity* _identity{nullptr};
};

// Network Page
#include "network.h"

class SimpleNetworkEditor;

class NetworkPage : public QWizardPage
{
    Q_OBJECT

public:
    NetworkPage(QWidget* parent = nullptr);

    NetworkInfo networkInfo();
    QStringList channelList();

private:
    SimpleNetworkEditor* _networkEditor;
    NetworkInfo _networkInfo;
    QStringList _channelList;
};

#endif  // IRCCONNECTIONWIZARD_H
