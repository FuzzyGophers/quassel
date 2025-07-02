// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QSslCertificate>
#include <QSslKey>

#include "clientidentity.h"

#include "ui_identityeditwidget.h"
#include "ui_nickeditdlg.h"

class IdentityEditWidget : public QWidget
{
    Q_OBJECT

public:
    IdentityEditWidget(QWidget* parent = nullptr);

    enum SslState
    {
        NoSsl,
        UnsecureSsl,
        AllowSsl
    };

    void displayIdentity(CertIdentity* id, CertIdentity* saveId = nullptr);
    void saveToIdentity(CertIdentity* id);

public slots:
    void setSslState(SslState state);
    void showAdvanced(bool advanced);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

signals:
    void requestEditSsl();
    void widgetHasChanged();

private slots:
    void on_addNick_clicked();
    void on_deleteNick_clicked();
    void on_renameNick_clicked();
    void on_nickUp_clicked();
    void on_nickDown_clicked();

    void on_clearOrLoadKeyButton_clicked();
    void on_clearOrLoadCertButton_clicked();
    void setWidgetStates();

    void sslDragEnterEvent(QDragEnterEvent* event);
    void sslDropEvent(QDropEvent* event, bool isCert);

private:
    Ui::IdentityEditWidget ui;
    bool _editSsl;

    QSslKey keyByFilename(const QString& filename);
    void showKeyState(const QSslKey& key);
    QSslCertificate certByFilename(const QString& filename);
    void showCertState(const QSslCertificate& cert);

    bool testHasChanged();
};

class NickEditDlg : public QDialog
{
    Q_OBJECT

public:
    NickEditDlg(const QString& oldnick, QStringList existing = QStringList(), QWidget* parent = nullptr);

    QString nick() const;

private slots:
    void on_nickEdit_textChanged(const QString&);

private:
    Ui::NickEditDlg ui;

    QString oldNick;
    QStringList existing;
};
