// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "sslinfodlg.h"

#include <QDateTime>
#include <QHostAddress>
#include <QSslCipher>
#include <QSslSocket>

#include "util.h"

// ========================================
//  SslInfoDlg
// ========================================

SslInfoDlg::SslInfoDlg(const QSslSocket* socket, QWidget* parent)
    : QDialog(parent)
    , _socket(socket)
{
    ui.setupUi(this);

    QSslCipher cipher = socket->sessionCipher();

    ui.hostname->setText(socket->peerName());
    ui.address->setText(socket->peerAddress().toString());
    ui.encryption->setText(cipher.name());
    ui.protocol->setText(cipher.protocolString());

    connect(ui.certificateChain, selectOverload<int>(&QComboBox::currentIndexChanged), this, &SslInfoDlg::setCurrentCert);
    foreach (const QSslCertificate& cert, socket->peerCertificateChain()) {
        ui.certificateChain->addItem(subjectInfo(cert, QSslCertificate::CommonName));
    }
}

void SslInfoDlg::setCurrentCert(int index)
{
    QSslCertificate cert = socket()->peerCertificateChain().at(index);
    ui.subjectCommonName->setText(subjectInfo(cert, QSslCertificate::CommonName));
    ui.subjectOrganization->setText(subjectInfo(cert, QSslCertificate::Organization));
    ui.subjectOrganizationalUnit->setText(subjectInfo(cert, QSslCertificate::OrganizationalUnitName));
    ui.subjectCountry->setText(subjectInfo(cert, QSslCertificate::CountryName));
    ui.subjectState->setText(subjectInfo(cert, QSslCertificate::StateOrProvinceName));
    ui.subjectCity->setText(subjectInfo(cert, QSslCertificate::LocalityName));

    ui.issuerCommonName->setText(issuerInfo(cert, QSslCertificate::CommonName));
    ui.issuerOrganization->setText(issuerInfo(cert, QSslCertificate::Organization));
    ui.issuerOrganizationalUnit->setText(issuerInfo(cert, QSslCertificate::OrganizationalUnitName));
    ui.issuerCountry->setText(issuerInfo(cert, QSslCertificate::CountryName));
    ui.issuerState->setText(issuerInfo(cert, QSslCertificate::StateOrProvinceName));
    ui.issuerCity->setText(issuerInfo(cert, QSslCertificate::LocalityName));

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    const auto& sslErrors = socket()->sslErrors();
#else
    const auto& sslErrors = socket()->sslHandshakeErrors();
#endif
    if (sslErrors.isEmpty()) {
        ui.trusted->setText(tr("Yes"));
    }
    else {
        QString errorString = tr("No, for the following reasons:<ul>");
        for (const auto& error : sslErrors) {
            errorString += "<li>" + error.errorString() + "</li>";
        }
        errorString += "</ul>";
        ui.trusted->setText(errorString);
    }

    ui.validity->setText(
        tr("%1 to %2").arg(cert.effectiveDate().date().toString(Qt::ISODate), cert.expiryDate().date().toString(Qt::ISODate)));
    ui.md5Digest->setText(prettyDigest(cert.digest(QCryptographicHash::Md5)));
    ui.sha1Digest->setText(prettyDigest(cert.digest(QCryptographicHash::Sha1)));
    ui.sha256Digest->setText(prettyDigest(cert.digest(QCryptographicHash::Sha256)));
}

// in Qt5, subjectInfo returns a QStringList(); turn this into a comma-separated string instead
QString SslInfoDlg::subjectInfo(const QSslCertificate& cert, QSslCertificate::SubjectInfo subjectInfo) const
{
    return cert.subjectInfo(subjectInfo).join(", ");
}

// same here
QString SslInfoDlg::issuerInfo(const QSslCertificate& cert, QSslCertificate::SubjectInfo subjectInfo) const
{
    return cert.issuerInfo(subjectInfo).join(", ");
}
