// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CHANNELLISTDLG_H
#define CHANNELLISTDLG_H

#include <QSortFilterProxyModel>

#include "irclisthelper.h"
#include "irclistmodel.h"
#include "types.h"

#include "ui_channellistdlg.h"

class QSpacerItem;

class ChannelListDlg : public QDialog
{
    Q_OBJECT

public:
    ChannelListDlg(QWidget* parent = nullptr);

    void setNetwork(NetworkId netId);

    /**
     * Set the channel search string, enabling advanced mode if needed
     *
     * Sets the channel name search text to the specified string, enabling advanced mode.  If search
     * string is empty, advanced mode will be automatically hidden.
     *
     * @param channelFilters Partial channel name to search for, or empty to not filter by name
     */
    void setChannelFilters(const QString& channelFilters);

public slots:
    /**
     * Request a channel listing using any parameters set in the UI
     */
    void requestSearch();

protected slots:
    void receiveChannelList(const NetworkId& netId,
                            const QStringList& channelFilters,
                            const QList<IrcListHelper::ChannelDescription>& channelList);
    void reportFinishedList();
    void joinChannel(const QModelIndex&);

private slots:
    inline void toggleMode() { setAdvancedMode(!_advancedMode); }
    void showError(const QString& error);

private:
    void showFilterLine(bool show);
    void showErrors(bool show);
    void enableQuery(bool enable);
    void setAdvancedMode(bool advanced);

    /**
     * Update the focus of input widgets according to dialog state
     */
    void updateInputFocus();

    Ui::ChannelListDlg ui;

    bool _listFinished{true};
    NetworkId _netId;
    IrcListModel _ircListModel;
    QSortFilterProxyModel _sortFilter;
    QSpacerItem* _simpleModeSpacer{nullptr};
    bool _advancedMode{false};
};

#endif  // CHANNELLIST_H
