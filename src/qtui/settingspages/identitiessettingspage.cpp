// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "identitiessettingspage.h"

#include <utility>

#include <QInputDialog>
#include <QMessageBox>

#include "client.h"
#include "icon.h"
#include "signalproxy.h"

IdentitiesSettingsPage::IdentitiesSettingsPage(QWidget* parent)
    : SettingsPage(tr("IRC"), tr("Identities"), parent)
{
    ui.setupUi(this);
    ui.renameIdentity->setIcon(icon::get("edit-rename"));
    ui.addIdentity->setIcon(icon::get("list-add-user"));
    ui.deleteIdentity->setIcon(icon::get("list-remove-user"));

    coreConnectionStateChanged(Client::isConnected());  // need a core connection!
    connect(Client::instance(), &Client::coreConnectionStateChanged, this, &IdentitiesSettingsPage::coreConnectionStateChanged);

    connect(Client::instance(), &Client::identityCreated, this, &IdentitiesSettingsPage::clientIdentityCreated);
    connect(Client::instance(), &Client::identityRemoved, this, &IdentitiesSettingsPage::clientIdentityRemoved);

    connect(ui.identityEditor, &IdentityEditWidget::widgetHasChanged, this, &IdentitiesSettingsPage::widgetHasChanged);
    connect(ui.identityEditor, &IdentityEditWidget::requestEditSsl, this, &IdentitiesSettingsPage::continueUnsecured);

    currentId = 0;
}

void IdentitiesSettingsPage::coreConnectionStateChanged(bool connected)
{
    setEnabled(connected);
    if (connected) {
        if (Client::signalProxy()->isSecure()) {
            ui.identityEditor->setSslState(IdentityEditWidget::AllowSsl);
            _editSsl = true;
        }
        else {
            ui.identityEditor->setSslState(IdentityEditWidget::UnsecureSsl);
            _editSsl = false;
        }
        load();
    }
    else {
        // reset
        currentId = 0;
    }
}

void IdentitiesSettingsPage::continueUnsecured()
{
    _editSsl = true;

    QHash<IdentityId, CertIdentity*>::iterator idIter;
    for (idIter = identities.begin(); idIter != identities.end(); ++idIter) {
        idIter.value()->enableEditSsl();
    }

    ui.identityEditor->setSslState(IdentityEditWidget::AllowSsl);
}

void IdentitiesSettingsPage::save()
{
    setEnabled(false);
    QList<CertIdentity*> toCreate, toUpdate;
    // we need to remove our temporarily created identities.
    // these are going to be re-added after the core has propagated them back...
    QHash<IdentityId, CertIdentity*>::iterator i = identities.begin();
    while (i != identities.end()) {
        if ((*i)->id() < 0) {
            CertIdentity* temp = *i;
            i = identities.erase(i);
            toCreate.append(temp);
            ui.identityList->removeItem(ui.identityList->findData(temp->id().toInt()));
        }
        else {
            if (**i != *Client::identity((*i)->id()) || (*i)->isDirty()) {
                toUpdate.append(*i);
            }
            ++i;
        }
    }
    SaveIdentitiesDlg dlg(toCreate, toUpdate, deletedIdentities, this);
    int ret = dlg.exec();
    if (ret == QDialog::Rejected) {
        // canceled -> reload everything to be safe
        load();
    }
    foreach (Identity* id, toCreate) {
        id->deleteLater();
    }
    changedIdentities.clear();
    deletedIdentities.clear();
    setChangedState(false);
    setEnabled(true);
}

void IdentitiesSettingsPage::load()
{
    currentId = 0;
    foreach (Identity* identity, identities.values()) {
        identity->deleteLater();
    }
    identities.clear();
    deletedIdentities.clear();
    changedIdentities.clear();
    ui.identityList->clear();
    setWidgetStates();
    foreach (IdentityId id, Client::identityIds()) {
        clientIdentityCreated(id);
    }
    setChangedState(false);
}

void IdentitiesSettingsPage::widgetHasChanged()
{
    bool changed = testHasChanged();
    if (changed != hasChanged())
        setChangedState(changed);
}

void IdentitiesSettingsPage::setWidgetStates()
{
    bool enabled = (ui.identityList->count() > 0);
    ui.identityEditor->setEnabled(enabled);
    ui.renameIdentity->setEnabled(enabled);
    ui.deleteIdentity->setEnabled(ui.identityList->count() > 1);
}

bool IdentitiesSettingsPage::testHasChanged()
{
    if (deletedIdentities.count())
        return true;
    if (currentId < 0) {
        return true;  // new identity
    }
    else {
        if (currentId != 0) {
            changedIdentities.removeAll(currentId);
            CertIdentity temp(currentId, this);
            // we need to set the cert and key manually, as they aren't synced
            CertIdentity* old = identities[currentId];
            temp.setSslKey(old->sslKey());
            temp.setSslCert(old->sslCert());
            ui.identityEditor->saveToIdentity(&temp);
            temp.setIdentityName(identities[currentId]->identityName());
            if (temp != *Client::identity(currentId) || temp.isDirty())
                changedIdentities.append(currentId);
        }
        return changedIdentities.count();
    }
}

bool IdentitiesSettingsPage::aboutToSave()
{
    ui.identityEditor->saveToIdentity(identities[currentId]);
    QList<int> errors;
    foreach (Identity* id, identities.values()) {
        if (id->identityName().isEmpty())
            errors.append(1);
        if (!id->nicks().count())
            errors.append(2);
        if (id->realName().isEmpty())
            errors.append(3);
        if (id->ident().isEmpty())
            errors.append(4);
    }
    if (!errors.count())
        return true;
    QString error(tr("<b>The following problems need to be corrected before your changes can be applied:</b><ul>"));
    if (errors.contains(1))
        error += tr("<li>All identities need an identity name set</li>");
    if (errors.contains(2))
        error += tr("<li>Every identity needs at least one nickname defined</li>");
    if (errors.contains(3))
        error += tr("<li>You need to specify a real name for every identity</li>");
    if (errors.contains(4))
        error += tr("<li>You need to specify an ident for every identity</li>");
    error += tr("</ul>");
    QMessageBox::warning(this, tr("One or more identities are invalid"), error);
    return false;
}

void IdentitiesSettingsPage::clientIdentityCreated(IdentityId id)
{
    auto* identity = new CertIdentity(*Client::identity(id), this);
    identity->enableEditSsl(_editSsl);
    insertIdentity(identity);
    connect(identity, &CertIdentity::sslSettingsUpdated, this, &IdentitiesSettingsPage::clientIdentityUpdated);
    connect(Client::identity(id), &SyncableObject::updatedRemotely, this, &IdentitiesSettingsPage::clientIdentityUpdated);
}

void IdentitiesSettingsPage::clientIdentityUpdated()
{
    const Identity* clientIdentity = qobject_cast<Identity*>(sender());
    if (!clientIdentity) {
        qWarning() << "Invalid identity to update!";
        return;
    }
    if (!identities.contains(clientIdentity->id())) {
        qWarning() << "Unknown identity to update:" << clientIdentity->identityName();
        return;
    }

    CertIdentity* identity = identities[clientIdentity->id()];

    if (identity->identityName() != clientIdentity->identityName())
        renameIdentity(identity->id(), clientIdentity->identityName());

    identity->copyFrom(*clientIdentity);

    if (identity->id() == currentId)
        ui.identityEditor->displayIdentity(identity);
}

void IdentitiesSettingsPage::clientIdentityRemoved(IdentityId id)
{
    if (identities.contains(id)) {
        removeIdentity(identities[id]);
        changedIdentities.removeAll(id);
        deletedIdentities.removeAll(id);
    }
}

void IdentitiesSettingsPage::insertIdentity(CertIdentity* identity)
{
    IdentityId id = identity->id();
    identities[id] = identity;

    QString name = identity->identityName();
    for (int j = 0; j < ui.identityList->count(); j++) {
        if ((j > 0 || ui.identityList->itemData(0).toInt() != 1) && name.localeAwareCompare(ui.identityList->itemText(j)) < 0) {
            ui.identityList->insertItem(j, name, id.toInt());
            widgetHasChanged();
            return;
        }
    }
    // append
    ui.identityList->insertItem(ui.identityList->count(), name, id.toInt());
    setWidgetStates();
    widgetHasChanged();
}

void IdentitiesSettingsPage::renameIdentity(IdentityId id, const QString& newName)
{
    Identity* identity = identities[id];
    ui.identityList->setItemText(ui.identityList->findData(identity->id().toInt()), newName);
    identity->setIdentityName(newName);
}

void IdentitiesSettingsPage::removeIdentity(Identity* id)
{
    identities.remove(id->id());
    ui.identityList->removeItem(ui.identityList->findData(id->id().toInt()));
    changedIdentities.removeAll(id->id());
    if (currentId == id->id())
        currentId = 0;
    id->deleteLater();
    setWidgetStates();
    widgetHasChanged();
}

void IdentitiesSettingsPage::on_identityList_currentIndexChanged(int index)
{
    CertIdentity* previousIdentity = nullptr;
    if (currentId != 0 && identities.contains(currentId))
        previousIdentity = identities[currentId];

    if (index < 0) {
        // ui.identityList->setEditable(false);
        ui.identityEditor->displayIdentity(nullptr, previousIdentity);
        currentId = 0;
    }
    else {
        IdentityId id = ui.identityList->itemData(index).toInt();
        if (identities.contains(id)) {
            ui.identityEditor->displayIdentity(identities[id], previousIdentity);
            currentId = id;
        }
    }
}

void IdentitiesSettingsPage::on_addIdentity_clicked()
{
    CreateIdentityDlg dlg(ui.identityList->model(), this);
    if (dlg.exec() == QDialog::Accepted) {
        // find a free (negative) ID
        IdentityId id;
        for (id = 1; id <= identities.count(); id++) {
            if (!identities.keys().contains(-id.toInt()))
                break;
        }
        id = -id.toInt();
        auto* newId = new CertIdentity(id, this);
        newId->enableEditSsl(_editSsl);
        if (dlg.duplicateId() != 0) {
            // duplicate
            newId->copyFrom(*identities[dlg.duplicateId()]);
            newId->setId(id);
        }
        newId->setIdentityName(dlg.identityName());
        identities[id] = newId;
        insertIdentity(newId);
        ui.identityList->setCurrentIndex(ui.identityList->findData(id.toInt()));
        widgetHasChanged();
    }
}

void IdentitiesSettingsPage::on_deleteIdentity_clicked()
{
    Identity* id = identities[currentId];
    int ret = QMessageBox::question(this,
                                    tr("Delete Identity?"),
                                    tr("Do you really want to delete identity \"%1\"?").arg(id->identityName()),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::No);
    if (ret != QMessageBox::Yes)
        return;
    if (id->id() > 0)
        deletedIdentities.append(id->id());
    currentId = 0;
    removeIdentity(id);
}

void IdentitiesSettingsPage::on_renameIdentity_clicked()
{
    QString oldName = identities[currentId]->identityName();
    bool ok = false;
    QString name = QInputDialog::getText(this,
                                         tr("Rename Identity"),
                                         tr("Please enter a new name for the identity \"%1\"!").arg(oldName),
                                         QLineEdit::Normal,
                                         oldName,
                                         &ok);
    if (ok && !name.isEmpty()) {
        renameIdentity(currentId, name);
        widgetHasChanged();
    }
}

/*****************************************************************************************/

CreateIdentityDlg::CreateIdentityDlg(QAbstractItemModel* model, QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    ui.identityList->setModel(model);  // now we use the identity list of the main page... Trolltech <3
    on_identityName_textChanged("");   // disable ok button :)
}

QString CreateIdentityDlg::identityName() const
{
    return ui.identityName->text();
}

IdentityId CreateIdentityDlg::duplicateId() const
{
    if (!ui.duplicateIdentity->isChecked())
        return 0;
    if (ui.identityList->currentIndex() >= 0) {
        return ui.identityList->itemData(ui.identityList->currentIndex()).toInt();
    }
    return 0;
}

void CreateIdentityDlg::on_identityName_textChanged(const QString& text)
{
    ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(text.length());
}

/*********************************************************************************************/

SaveIdentitiesDlg::SaveIdentitiesDlg(const QList<CertIdentity*>& toCreate,
                                     const QList<CertIdentity*>& toUpdate,
                                     const QList<IdentityId>& toRemove,
                                     QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    ui.abort->setIcon(icon::get("dialog-cancel"));

    numevents = toCreate.count() + toUpdate.count() + toRemove.count();
    rcvevents = 0;
    if (numevents) {
        ui.progressBar->setMaximum(numevents);
        ui.progressBar->setValue(0);

        connect(Client::instance(), &Client::identityCreated, this, &SaveIdentitiesDlg::clientEvent);
        connect(Client::instance(), &Client::identityRemoved, this, &SaveIdentitiesDlg::clientEvent);

        foreach (CertIdentity* id, toCreate) {
            Client::createIdentity(*id);
        }
        foreach (CertIdentity* id, toUpdate) {
            const Identity* cid = Client::identity(id->id());
            if (!cid) {
                qWarning() << "Invalid client identity!";
                numevents--;
                continue;
            }
            connect(cid, &SyncableObject::updatedRemotely, this, &SaveIdentitiesDlg::clientEvent);
            Client::updateIdentity(id->id(), id->toVariantMap());
            id->requestUpdateSslSettings();
        }
        foreach (IdentityId id, toRemove) {
            Client::removeIdentity(id);
        }
    }
    else {
        qWarning() << "Sync dialog called without stuff to change!";
        accept();
    }
}

void SaveIdentitiesDlg::clientEvent()
{
    ui.progressBar->setValue(++rcvevents);
    if (rcvevents >= numevents)
        accept();
}

/*************************************************************************************************/

NickEditDlg::NickEditDlg(const QString& old, QStringList exist, QWidget* parent)
    : QDialog(parent)
    , oldNick(old)
    , existing(std::move(exist))
{
    ui.setupUi(this);

    // define a regexp for valid nicknames
    // TODO: add max nicklength according to ISUPPORT
    QString letter = "A-Za-z";
    QString special = R"([-`{-})";
    QRegularExpression rx(QString("[%1%2][%1%2\\d-]*").arg(letter, special));
    ui.nickEdit->setValidator(new QRegularExpressionValidator(rx, ui.nickEdit));
    if (old.isEmpty()) {
        // new nick
        setWindowTitle(tr("Add Nickname"));
        on_nickEdit_textChanged("");  // disable ok button
    }
    else
        ui.nickEdit->setText(old);
}

QString NickEditDlg::nick() const
{
    return ui.nickEdit->text();
}

void NickEditDlg::on_nickEdit_textChanged(const QString& text)
{
    ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(text.isEmpty() || existing.contains(text));
}
