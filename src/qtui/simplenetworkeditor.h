// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SIMPLENETWORKEDITOR_H
#define SIMPLENETWORKEDITOR_H

#include "network.h"

#include "ui_simplenetworkeditor.h"

class SimpleNetworkEditor : public QWidget
{
    Q_OBJECT

public:
    SimpleNetworkEditor(QWidget* parent = nullptr);

    void displayNetworkInfo(const NetworkInfo& networkInfo);
    void saveToNetworkInfo(NetworkInfo& networkInfo);

    QStringList defaultChannels() const;
    void setDefaultChannels(const QStringList& channels);

signals:
    void widgetHasChanged();

private slots:
    // code duplication from settingspages/networkssettingspage.{h|cpp}
    void on_serverList_itemSelectionChanged();
    void on_addServer_clicked();
    void on_deleteServer_clicked();
    void on_editServer_clicked();
    void on_upServer_clicked();
    void on_downServer_clicked();

    void setWidgetStates();

private:
    Ui::SimpleNetworkEditor ui;

    NetworkInfo _networkInfo;
};

#endif  // SIMPLENETWORKEDITOR_H
