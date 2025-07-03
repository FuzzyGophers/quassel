// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "clientidentity.h"
#include "identityeditwidget.h"
#include "settingspage.h"

#include "ui_createidentitydlg.h"
#include "ui_identitiessettingspage.h"
#include "ui_saveidentitiesdlg.h"

class QAbstractItemModel;

class IdentitiesSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    IdentitiesSettingsPage(QWidget* parent = nullptr);

    inline bool needsCoreConnection() const override { return true; }

    bool aboutToSave() override;

public slots:
    void save() final override;
    void load() final override;

private slots:
    void coreConnectionStateChanged(bool);
    void clientIdentityCreated(IdentityId);
    void clientIdentityUpdated();
    void clientIdentityRemoved(IdentityId);

    void on_identityList_currentIndexChanged(int index);

    void on_addIdentity_clicked();
    void on_deleteIdentity_clicked();
    void on_renameIdentity_clicked();

    void continueUnsecured();
    void widgetHasChanged();
    void setWidgetStates();

private:
    Ui::IdentitiesSettingsPage ui;

    QHash<IdentityId, CertIdentity*> identities;
    IdentityId currentId;

    QList<IdentityId> changedIdentities;  // for setting the widget changed state
    QList<IdentityId> deletedIdentities;

    bool _editSsl{false};

    void insertIdentity(CertIdentity* identity);
    void removeIdentity(Identity* identity);
    void renameIdentity(IdentityId id, const QString& newName);

    QSslKey keyByFilename(const QString& filename);
    void showKeyState(const QSslKey& key);
    QSslCertificate certByFilename(const QString& filename);
    void showCertState(const QSslCertificate& cert);

    bool testHasChanged();
};

// ==============================
//  Various Dialogs
// ==============================
class CreateIdentityDlg : public QDialog
{
    Q_OBJECT

public:
    CreateIdentityDlg(QAbstractItemModel* model, QWidget* parent = nullptr);

    QString identityName() const;
    IdentityId duplicateId() const;

private slots:
    void on_identityName_textChanged(const QString& text);

private:
    Ui::CreateIdentityDlg ui;
};

class SaveIdentitiesDlg : public QDialog
{
    Q_OBJECT

public:
    SaveIdentitiesDlg(const QList<CertIdentity*>& toCreate,
                      const QList<CertIdentity*>& toUpdate,
                      const QList<IdentityId>& toRemove,
                      QWidget* parent = nullptr);

private slots:
    void clientEvent();

private:
    Ui::SaveIdentitiesDlg ui;

    int numevents, rcvevents;
};
