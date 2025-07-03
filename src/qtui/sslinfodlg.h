// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SSLINFODLG_H
#define SSLINFODLG_H

#include <QDialog>
#include <QSslCertificate>

#include "ui_sslinfodlg.h"

class QSslSocket;

// ========================================
//  SslInfoDialog
// ========================================

class SslInfoDlg : public QDialog
{
    Q_OBJECT

public:
    SslInfoDlg(const QSslSocket* socket, QWidget* parent = nullptr);
    inline const QSslSocket* socket() const { return _socket; }

private slots:
    void setCurrentCert(int index);

private:
    // simplify handling the API changes between Qt4 and Qt5 (QString -> QStringList)
    QString subjectInfo(const QSslCertificate& cert, QSslCertificate::SubjectInfo subjectInfo) const;
    QString issuerInfo(const QSslCertificate& cert, QSslCertificate::SubjectInfo subjectInfo) const;

private:
    Ui::SslInfoDlg ui;
    const QSslSocket* _socket;
};

#endif
