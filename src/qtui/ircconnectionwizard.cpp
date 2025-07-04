// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ircconnectionwizard.h"

#include <QVBoxLayout>

#include "client.h"
#include "identityeditwidget.h"
#include "presetnetworks.h"
#include "simplenetworkeditor.h"

IrcConnectionWizard::IrcConnectionWizard(QWidget* parent, Qt::WindowFlags flags)
    : QWizard(parent, flags)
{
    _introductionPage = createIntroductionPage(this);
    _identityPage = new IdentityPage(this);
    _networkPage = new NetworkPage(this);

    addPage(_introductionPage);
    addPage(_identityPage);
    addPage(_networkPage);

    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    setOptions(options() | (QWizard::WizardOptions)(QWizard::NoDefaultButton | QWizard::CancelButtonOnLeft));
    setOption(QWizard::NoCancelButton, false);

    connect(button(QWizard::FinishButton), &QAbstractButton::clicked, this, &IrcConnectionWizard::finishClicked);
    setButtonText(QWizard::FinishButton, tr("Save && Connect"));
}

QWizardPage* IrcConnectionWizard::createIntroductionPage(QWidget* parent)
{
    auto* page = new QWizardPage(parent);
    page->setTitle(QObject::tr("Welcome to Quassel IRC"));

    QLabel* label = new QLabel(
        QObject::tr(
            "This wizard will help you to set up your default identity and your IRC network connection.<br>"
            "This only covers basic settings. You can cancel this wizard any time and use the settings dialog for more detailed changes."),
        page);
    label->setWordWrap(true);

    auto* layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

void IrcConnectionWizard::finishClicked()
{
    CertIdentity* identity = static_cast<IdentityPage*>(_identityPage)->identity();
    if (identity->id().isValid()) {
        Client::updateIdentity(identity->id(), identity->toVariantMap());
        identityReady(identity->id());
    }
    else {
        connect(Client::instance(), &Client::identityCreated, this, &IrcConnectionWizard::identityReady);
        Client::createIdentity(*identity);
    }
}

void IrcConnectionWizard::identityReady(IdentityId id)
{
    disconnect(Client::instance(), &Client::identityCreated, this, &IrcConnectionWizard::identityReady);
    auto* networkPage = static_cast<NetworkPage*>(_networkPage);
    NetworkInfo networkInfo = networkPage->networkInfo();
    QStringList channels = networkPage->channelList();
    networkInfo.identity = id;
    connect(Client::instance(), &Client::networkCreated, this, &IrcConnectionWizard::networkReady);
    Client::createNetwork(networkInfo, channels);
}

void IrcConnectionWizard::networkReady(NetworkId id)
{
    disconnect(Client::instance(), &Client::networkCreated, this, &IrcConnectionWizard::networkReady);
    const Network* net = Client::network(id);
    Q_ASSERT(net);
    net->requestConnect();
    deleteLater();
}

// ==============================
//  Wizard Pages
// ==============================

// Identity Page
IdentityPage::IdentityPage(QWidget* parent)
    : QWizardPage(parent)
    , _identityEditWidget(new IdentityEditWidget(this))
{
    setTitle(tr("Setup Identity"));

    if (Client::identityIds().isEmpty()) {
        _identity = new CertIdentity(-1, this);
        _identity->setToDefaults();
        _identity->setIdentityName(tr("Default Identity"));
    }
    else {
        _identity = new CertIdentity(*Client::identity(Client::identityIds().first()), this);
    }

    _identityEditWidget->displayIdentity(_identity);
    _identityEditWidget->showAdvanced(false);
    auto* layout = new QVBoxLayout;
    layout->addWidget(_identityEditWidget);
    setLayout(layout);
}

CertIdentity* IdentityPage::identity()
{
    _identityEditWidget->saveToIdentity(_identity);
    return _identity;
}

// Network Page
NetworkPage::NetworkPage(QWidget* parent)
    : QWizardPage(parent)
    , _networkEditor(new SimpleNetworkEditor(this))
{
    QStringList defaultNets = PresetNetworks::names(true);
    if (!defaultNets.isEmpty()) {
        NetworkInfo info = PresetNetworks::networkInfo(defaultNets[0]);
        if (!info.networkName.isEmpty()) {
            _networkInfo = info;
            _channelList = PresetNetworks::defaultChannels(defaultNets[0]);
        }
    }

    _networkEditor->displayNetworkInfo(_networkInfo);
    _networkEditor->setDefaultChannels(_channelList);

    setTitle(tr("Setup Network Connection"));

    auto* layout = new QVBoxLayout;
    layout->addWidget(_networkEditor);
    setLayout(layout);
}

NetworkInfo NetworkPage::networkInfo()
{
    _networkEditor->saveToNetworkInfo(_networkInfo);
    return _networkInfo;
}

QStringList NetworkPage::channelList()
{
    _channelList = _networkEditor->defaultChannels();
    return _channelList;
}
