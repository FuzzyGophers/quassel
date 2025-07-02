// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include "networkmodelcontroller.h"

class QToolBar;

class UISUPPORT_EXPORT ToolBarActionProvider : public NetworkModelController
{
    Q_OBJECT

public:
    ToolBarActionProvider(QObject* parent = nullptr);

    enum ToolBarType
    {
        MainToolBar,
        ChatViewToolBar,
        NickToolBar
    };

    void addActions(QToolBar*, ToolBarType type);

public slots:
    void disconnectedFromCore() override;
    void onCurrentBufferChanged(const QModelIndex&);
    void onNickSelectionChanged(const QModelIndexList&);

protected:
    void handleNetworkAction(ActionType, QAction*) override;
    void handleBufferAction(ActionType, QAction*) override;
    void handleNickAction(ActionType, QAction*) override;
    void handleGeneralAction(ActionType, QAction*) override;

private slots:
    void networkCreated(NetworkId id);
    void networkRemoved(NetworkId id);
    void networkUpdated(const Network* net = nullptr);
    void connectOrDisconnectNet();

    void updateStates();

private:
    QMenu *_networksConnectMenu, *_networksDisconnectMenu;
    QHash<NetworkId, Action*> _networkActions;
    QModelIndex _currentBuffer;
    QModelIndexList _selectedNicks;
};
