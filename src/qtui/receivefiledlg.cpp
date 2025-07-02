// SPDX-License-Identifier: GPL-2.0-or-later

#include "receivefiledlg.h"

#include <QDir>
#include <QFileDialog>

#include "transfer.h"

ReceiveFileDlg::ReceiveFileDlg(const Transfer* transfer, QWidget* parent)
    : QDialog(parent)
    , _transfer(transfer)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui.setupUi(this);

    QString label
        = tr("<b>%1</b> wants to send you a file:<br>%2 (%3 bytes)").arg(transfer->nick(), transfer->fileName()).arg(transfer->fileSize());
    ui.infoText->setText(label);
}

void ReceiveFileDlg::on_buttonBox_clicked(QAbstractButton* button)
{
    if (ui.buttonBox->standardButton(button) == QDialogButtonBox::Save) {
        QString name = QFileDialog::getSaveFileName(this, QString(), QDir::currentPath() + "/" + _transfer->fileName());
        _transfer->accept(name);
    }
}
