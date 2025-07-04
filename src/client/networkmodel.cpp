// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "networkmodel.h"

#include <algorithm>
#include <utility>

#include <QAbstractItemView>
#include <QMimeData>

#include "buffermodel.h"
#include "buffersettings.h"
#include "buffersyncer.h"
#include "client.h"
#include "clientignorelistmanager.h"
#include "clientsettings.h"
#include "ircchannel.h"
#include "network.h"
#include "signalproxy.h"

/*****************************************
 *  Network Items
 *****************************************/
NetworkItem::NetworkItem(const NetworkId& netid, AbstractTreeItem* parent)
    : PropertyMapItem(parent)
    , _networkId(netid)
    , _statusBufferItem(nullptr)
{
    // DO NOT EMIT dataChanged() DIRECTLY IN NetworkItem
    // use networkDataChanged() instead. Otherwise you will end up in a infinite loop
    // as we "sync" the dataChanged() signals of NetworkItem and StatusBufferItem
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    connect(this, &NetworkItem::networkDataChanged, this, &NetworkItem::dataChanged);
    connect(this, &NetworkItem::beginRemoveChilds, this, &NetworkItem::onBeginRemoveChilds);
}

QStringList NetworkItem::propertyOrder() const
{
    static QStringList order{"networkName", "currentServer", "nickCount"};
    return order;
}

QVariant NetworkItem::data(int column, int role) const
{
    switch (role) {
    case NetworkModel::BufferIdRole:
    case NetworkModel::BufferInfoRole:
    case NetworkModel::BufferTypeRole:
    case NetworkModel::BufferActivityRole:
        if (_statusBufferItem)
            return _statusBufferItem->data(column, role);
        else
            return QVariant();
    case NetworkModel::NetworkIdRole:
        return QVariant::fromValue(_networkId);
    case NetworkModel::ItemTypeRole:
        return NetworkModel::NetworkItemType;
    case NetworkModel::ItemActiveRole:
        return isActive();
    default:
        return PropertyMapItem::data(column, role);
    }
}

QString NetworkItem::escapeHTML(const QString& string, bool useNonbreakingSpaces)
{
    // QString.replace() doesn't guarantee the source string will remain constant.
    // Use a local variable to avoid compiler errors.
    QString formattedString = string.toHtmlEscaped();
    return (useNonbreakingSpaces ? formattedString.replace(" ", "&nbsp;") : formattedString);
}

// FIXME shouldn't we check the bufferItemCache here?
BufferItem* NetworkItem::findBufferItem(BufferId bufferId)
{
    BufferItem* bufferItem = nullptr;

    for (int i = 0; i < childCount(); i++) {
        bufferItem = qobject_cast<BufferItem*>(child(i));
        if (!bufferItem)
            continue;
        if (bufferItem->bufferId() == bufferId)
            return bufferItem;
    }
    return nullptr;
}

BufferItem* NetworkItem::bufferItem(const BufferInfo& bufferInfo)
{
    BufferItem* bufferItem = findBufferItem(bufferInfo);
    if (bufferItem)
        return bufferItem;

    switch (bufferInfo.type()) {
    case BufferInfo::StatusBuffer:
        _statusBufferItem = new StatusBufferItem(bufferInfo, this);
        bufferItem = _statusBufferItem;
        disconnect(this, &NetworkItem::networkDataChanged, this, &NetworkItem::dataChanged);
        connect(this, &NetworkItem::networkDataChanged, bufferItem, &BufferItem::dataChanged);
        connect(bufferItem, &BufferItem::dataChanged, this, &NetworkItem::dataChanged);
        break;
    case BufferInfo::ChannelBuffer:
        bufferItem = new ChannelBufferItem(bufferInfo, this);
        break;
    case BufferInfo::QueryBuffer:
        bufferItem = new QueryBufferItem(bufferInfo, this);
        break;
    default:
        bufferItem = new BufferItem(bufferInfo, this);
    }

    newChild(bufferItem);

    // postprocess... this is necessary because Qt doesn't seem to like adding children which already have children on their own
    switch (bufferInfo.type()) {
    case BufferInfo::ChannelBuffer: {
        auto* channelBufferItem = static_cast<ChannelBufferItem*>(bufferItem);
        if (_network) {
            IrcChannel* ircChannel = _network->ircChannel(bufferInfo.bufferName());
            if (ircChannel)
                channelBufferItem->attachIrcChannel(ircChannel);
        }
    } break;
    default:
        break;
    }

    BufferSyncer* bufferSyncer = Client::bufferSyncer();
    if (bufferSyncer) {
        bufferItem->addActivity(bufferSyncer->activity(bufferItem->bufferId()), bufferSyncer->highlightCount(bufferItem->bufferId()) > 0);
    }

    return bufferItem;
}

void NetworkItem::attachNetwork(Network* network)
{
    if (!network)
        return;

    _network = network;

    connect(network, &Network::networkNameSet, this, &NetworkItem::setNetworkName);
    connect(network, &Network::currentServerSet, this, &NetworkItem::setCurrentServer);
    connect(network, &Network::ircChannelAdded, this, &NetworkItem::attachIrcChannel);
    connect(network, &Network::ircUserAdded, this, &NetworkItem::attachIrcUser);
    connect(network, &Network::connectedSet, this, [this]() { emit networkDataChanged(); });
    connect(network, &QObject::destroyed, this, &NetworkItem::onNetworkDestroyed);

    emit networkDataChanged();
}

void NetworkItem::attachIrcChannel(IrcChannel* ircChannel)
{
    ChannelBufferItem* channelItem;
    for (int i = 0; i < childCount(); i++) {
        channelItem = qobject_cast<ChannelBufferItem*>(child(i));
        if (!channelItem)
            continue;

        if (channelItem->bufferName().toLower() == ircChannel->name().toLower()) {
            channelItem->attachIrcChannel(ircChannel);
            return;
        }
    }
}

void NetworkItem::attachIrcUser(IrcUser* ircUser)
{
    QueryBufferItem* queryItem = nullptr;
    for (int i = 0; i < childCount(); i++) {
        queryItem = qobject_cast<QueryBufferItem*>(child(i));
        if (!queryItem)
            continue;

        if (queryItem->bufferName().toLower() == ircUser->nick().toLower()) {
            queryItem->setIrcUser(ircUser);
            break;
        }
    }
}

void NetworkItem::setNetworkName(const QString& networkName)
{
    Q_UNUSED(networkName);
    emit networkDataChanged(0);
}

void NetworkItem::setCurrentServer(const QString& serverName)
{
    Q_UNUSED(serverName);
    emit networkDataChanged(1);
}

QString NetworkItem::toolTip(int column) const
{
    Q_UNUSED(column);
    QString strTooltip;
    QTextStream tooltip(&strTooltip, QIODevice::WriteOnly);
    tooltip << "<qt><style>.bold { font-weight: bold; } .italic { font-style: italic; }</style>";

    // Function to add a row to the tooltip table
    auto addRow = [&](const QString& key, const QString& value, bool condition) {
        if (condition) {
            tooltip << "<tr><td class='bold' align='right'>" << key << "</td><td>" << value << "</td></tr>";
        }
    };

    tooltip << "<p class='bold' align='center'>" << NetworkItem::escapeHTML(networkName(), true) << "</p>";
    if (isActive()) {
        tooltip << "<table cellspacing='5' cellpadding='0'>";
        addRow(tr("Server"), NetworkItem::escapeHTML(currentServer(), true), !currentServer().isEmpty());
        addRow(tr("Users"), QString::number(nickCount()), true);
        if (_network)
            addRow(tr("Lag"), NetworkItem::escapeHTML(tr("%1 msecs").arg(_network->latency()), true), true);

        tooltip << "</table>";
    }
    else {
        tooltip << "<p class='italic' align='center'>" << tr("Not connected") << "</p>";
    }
    tooltip << "</qt>";
    return strTooltip;
}

void NetworkItem::onBeginRemoveChilds(int start, int end)
{
    for (int i = start; i <= end; i++) {
        auto* statusBufferItem = qobject_cast<StatusBufferItem*>(child(i));
        if (statusBufferItem) {
            _statusBufferItem = nullptr;
            break;
        }
    }
}

void NetworkItem::onNetworkDestroyed()
{
    _network = nullptr;
    emit networkDataChanged();
    removeAllChilds();
}

/*****************************************
 *  Fancy Buffer Items
 *****************************************/
BufferItem::BufferItem(BufferInfo bufferInfo, AbstractTreeItem* parent)
    : PropertyMapItem(parent)
    , _bufferInfo(std::move(bufferInfo))
    , _activity(BufferInfo::NoActivity)
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

QStringList BufferItem::propertyOrder() const
{
    static QStringList order{"bufferName", "topic", "nickCount"};
    return order;
}

void BufferItem::setActivityLevel(BufferInfo::ActivityLevel level)
{
    if (_activity != level) {
        _activity = level;
        emit dataChanged();
    }
}

void BufferItem::clearActivityLevel()
{
    if (Client::isCoreFeatureEnabled(Quassel::Feature::BufferActivitySync)) {
        // If the core handles activity sync, clear only the highlight flag
        _activity &= ~BufferInfo::Highlight;
    }
    else {
        _activity = BufferInfo::NoActivity;
    }
    _firstUnreadMsgId = MsgId();

    // FIXME remove with core proto v11
    if (!Client::isCoreFeatureEnabled(Quassel::Feature::SynchronizedMarkerLine)) {
        _markerLineMsgId = _lastSeenMsgId;
    }

    emit dataChanged();
}

void BufferItem::updateActivityLevel(const Message& msg)
{
    // If the core handles activity, and this message is not a highlight, ignore this
    if (Client::isCoreFeatureEnabled(Quassel::Feature::BufferActivitySync) && !msg.flags().testFlag(Message::Highlight)) {
        return;
    }

    if (isCurrentBuffer()) {
        return;
    }

    if (msg.flags() & Message::Self)  // don't update activity for our own messages
        return;

    if (Client::ignoreListManager() && Client::ignoreListManager()->match(msg, qobject_cast<NetworkItem*>(parent())->networkName()))
        return;

    if (msg.msgId() <= lastSeenMsgId())
        return;

    bool stateChanged = false;
    if (!firstUnreadMsgId().isValid() || msg.msgId() < firstUnreadMsgId()) {
        stateChanged = true;
        _firstUnreadMsgId = msg.msgId();
    }

    Message::Types type;
    // If the core handles activities, ignore types
    if (Client::isCoreFeatureEnabled(Quassel::Feature::BufferActivitySync)) {
        type = Message::Types();
    }
    else {
        type = msg.type();
    }

    if (addActivity(type, msg.flags().testFlag(Message::Highlight)) || stateChanged) {
        emit dataChanged();
    }
}

void BufferItem::setActivity(Message::Types type, bool highlight)
{
    BufferInfo::ActivityLevel oldLevel = activityLevel();

    _activity &= BufferInfo::Highlight;
    addActivity(type, highlight);

    if (_activity != oldLevel) {
        emit dataChanged();
    }
}

bool BufferItem::addActivity(Message::Types type, bool highlight)
{
    auto oldActivity = activityLevel();

    if (type != Message::Types())
        _activity |= BufferInfo::OtherActivity;

    if (type.testFlag(Message::Plain) || type.testFlag(Message::Notice) || type.testFlag(Message::Action))
        _activity |= BufferInfo::NewMessage;

    if (highlight)
        _activity |= BufferInfo::Highlight;

    return oldActivity != _activity;
}

QVariant BufferItem::data(int column, int role) const
{
    switch (role) {
    case NetworkModel::ItemTypeRole:
        return NetworkModel::BufferItemType;
    case NetworkModel::BufferIdRole:
        return QVariant::fromValue(bufferInfo().bufferId());
    case NetworkModel::NetworkIdRole:
        return QVariant::fromValue(bufferInfo().networkId());
    case NetworkModel::BufferInfoRole:
        return QVariant::fromValue(bufferInfo());
    case NetworkModel::BufferTypeRole:
        return int(bufferType());
    case NetworkModel::ItemActiveRole:
        return isActive();
    case NetworkModel::BufferActivityRole:
        return (int)activityLevel();
    case NetworkModel::BufferFirstUnreadMsgIdRole:
        return QVariant::fromValue(firstUnreadMsgId());
    case NetworkModel::MarkerLineMsgIdRole:
        return QVariant::fromValue(markerLineMsgId());
    default:
        return PropertyMapItem::data(column, role);
    }
}

bool BufferItem::setData(int column, const QVariant& value, int role)
{
    switch (role) {
    case NetworkModel::BufferActivityRole:
        setActivityLevel((BufferInfo::ActivityLevel)value.toInt());
        return true;
    default:
        return PropertyMapItem::setData(column, value, role);
    }
}

void BufferItem::setBufferName(const QString& name)
{
    _bufferInfo = BufferInfo(_bufferInfo.bufferId(), _bufferInfo.networkId(), _bufferInfo.type(), _bufferInfo.groupId(), name);
    emit dataChanged(0);
}

void BufferItem::setLastSeenMsgId(MsgId msgId)
{
    _lastSeenMsgId = msgId;

    // FIXME remove with core protocol v11
    if (!Client::isCoreFeatureEnabled(Quassel::Feature::SynchronizedMarkerLine)) {
        if (!isCurrentBuffer())
            _markerLineMsgId = msgId;
    }

    setActivityLevel(BufferInfo::NoActivity);
}

void BufferItem::setMarkerLineMsgId(MsgId msgId)
{
    _markerLineMsgId = msgId;
    emit dataChanged();
}

bool BufferItem::isCurrentBuffer() const
{
    return _bufferInfo.bufferId() == Client::bufferModel()->currentIndex().data(NetworkModel::BufferIdRole).value<BufferId>();
}

QString BufferItem::toolTip(int column) const
{
    Q_UNUSED(column);
    return tr("<p> %1 - %2 </p>").arg(bufferInfo().bufferId().toInt()).arg(bufferName());
}

/*****************************************
 *  StatusBufferItem
 *****************************************/
StatusBufferItem::StatusBufferItem(const BufferInfo& bufferInfo, NetworkItem* parent)
    : BufferItem(bufferInfo, parent)
{
}

QString StatusBufferItem::toolTip(int column) const
{
    auto* networkItem = qobject_cast<NetworkItem*>(parent());
    if (networkItem)
        return networkItem->toolTip(column);
    else
        return QString();
}

/*****************************************
 *  QueryBufferItem
 *****************************************/
QueryBufferItem::QueryBufferItem(const BufferInfo& bufferInfo, NetworkItem* parent)
    : BufferItem(bufferInfo, parent)
    , _ircUser(nullptr)
{
    setFlags(flags() | Qt::ItemIsDropEnabled | Qt::ItemIsEditable);

    const Network* net = Client::network(bufferInfo.networkId());
    if (!net)
        return;

    IrcUser* ircUser = net->ircUser(bufferInfo.bufferName());
    setIrcUser(ircUser);
}

QVariant QueryBufferItem::data(int column, int role) const
{
    switch (role) {
    case Qt::EditRole:
        return BufferItem::data(column, Qt::DisplayRole);
    case NetworkModel::IrcUserRole:
        return QVariant::fromValue(_ircUser);
    case NetworkModel::UserAwayRole:
        return (bool)_ircUser ? _ircUser->isAway() : false;
    default:
        return BufferItem::data(column, role);
    }
}

bool QueryBufferItem::setData(int column, const QVariant& value, int role)
{
    if (column != 0)
        return BufferItem::setData(column, value, role);

    switch (role) {
    case Qt::EditRole: {
        QString newName = value.toString();

        // Sanity check - buffer names must not contain newlines!
        int nlpos = newName.indexOf('\n');
        if (nlpos >= 0)
            newName = newName.left(nlpos);

        if (!newName.isEmpty()) {
            Client::renameBuffer(bufferId(), newName);
            return true;
        }
        else {
            return false;
        }
    } break;
    default:
        return BufferItem::setData(column, value, role);
    }
}

void QueryBufferItem::setBufferName(const QString& name)
{
    BufferItem::setBufferName(name);
    NetworkId netId = data(0, NetworkModel::NetworkIdRole).value<NetworkId>();
    const Network* net = Client::network(netId);
    if (net)
        setIrcUser(net->ircUser(name));
}

QString QueryBufferItem::toolTip(int column) const
{
    // pretty much code duplication of IrcUserItem::toolTip() but inheritance won't solve this...
    Q_UNUSED(column);
    QString strTooltip;
    QTextStream tooltip(&strTooltip, QIODevice::WriteOnly);
    tooltip << "<qt><style>.bold { font-weight: bold; } .italic { font-style: italic; }</style>";

    // Keep track of whether or not information has been added
    bool infoAdded = false;

    // Use bufferName() for QueryBufferItem, nickName() for IrcUserItem
    tooltip << "<p class='bold' align='center'>";
    tooltip << tr("Query with %1").arg(NetworkItem::escapeHTML(bufferName(), true));
    if (!_ircUser) {
        // User seems to be offline, let the no information message be added below
        tooltip << "</p>";
    }
    else {
        // Function to add a row to the tooltip table
        auto addRow = [&](const QString& key, const QString& value, bool condition) {
            if (condition) {
                tooltip << "<tr><td class='bold' align='right'>" << key << "</td><td>" << value << "</td></tr>";
                infoAdded = true;
            }
        };

        // User information is available
        if (_ircUser->userModes() != "") {
            // TODO Translate user Modes and add them to the table below and in IrcUserItem::toolTip
            tooltip << " (" << _ircUser->userModes() << ")";
        }
        tooltip << "</p>";

        tooltip << "<table cellspacing='5' cellpadding='0'>";
        if (_ircUser->isAway()) {
            QString awayMessageHTML = QString("<p class='italic'>%1</p>").arg(tr("Unknown"));

            // If away message is known, replace with the escaped message.
            if (!_ircUser->awayMessage().isEmpty()) {
                awayMessageHTML = NetworkItem::escapeHTML(_ircUser->awayMessage());
            }
            addRow(NetworkItem::escapeHTML(tr("Away message"), true), awayMessageHTML, true);
        }
        addRow(tr("Realname"), NetworkItem::escapeHTML(_ircUser->realName()), !_ircUser->realName().isEmpty());
        // suserHost may return "<nick> is available for help", which should be translated.
        // See https://www.alien.net.au/irc/irc2numerics.html
        if (_ircUser->suserHost().endsWith("available for help")) {
            addRow(NetworkItem::escapeHTML(tr("Help status"), true), NetworkItem::escapeHTML(tr("Available for help")), true);
        }
        else {
            addRow(NetworkItem::escapeHTML(tr("Service status"), true),
                   NetworkItem::escapeHTML(_ircUser->suserHost()),
                   !_ircUser->suserHost().isEmpty());
        }

        // Keep track of whether or not the account information's been added.  Don't show it twice.
        bool accountAdded = false;
        if (!_ircUser->account().isEmpty()) {
            // IRCv3 account-notify is supported by the core and IRC server.
            // Assume logged out (seems to be more common)
            QString accountHTML = QString("<p class='italic'>%1</p>").arg(tr("Not logged in"));

            // If account is logged in, replace with the escaped account name.
            if (_ircUser->account() != "*") {
                accountHTML = NetworkItem::escapeHTML(_ircUser->account());
            }
            addRow(NetworkItem::escapeHTML(tr("Account"), true), accountHTML, true);
            // Mark the row as added
            accountAdded = true;
        }
        // whoisServiceReply may return "<nick> is identified for this nick", which should be translated.
        // See https://www.alien.net.au/irc/irc2numerics.html
        if (_ircUser->whoisServiceReply().endsWith("identified for this nick")) {
            addRow(NetworkItem::escapeHTML(tr("Account"), true), NetworkItem::escapeHTML(tr("Identified for this nick")), !accountAdded);
            // Don't add the account row again if information's already added via account-notify
            // Not used further down...
            // accountAdded = true;
        }
        else {
            addRow(NetworkItem::escapeHTML(tr("Service Reply"), true),
                   NetworkItem::escapeHTML(_ircUser->whoisServiceReply()),
                   !_ircUser->whoisServiceReply().isEmpty());
        }
        addRow(tr("Hostmask"),
               NetworkItem::escapeHTML(_ircUser->hostmask().remove(0, _ircUser->hostmask().indexOf("!") + 1)),
               !(_ircUser->hostmask().remove(0, _ircUser->hostmask().indexOf("!") + 1) == "@"));
        // ircOperator may contain "is an" or "is a", which should be removed.
        addRow(tr("Operator"),
               NetworkItem::escapeHTML(_ircUser->ircOperator().replace("is an ", "").replace("is a ", "")),
               !_ircUser->ircOperator().isEmpty());

        if (_ircUser->idleTime().isValid()) {
            QDateTime now = QDateTime::currentDateTime();
            QDateTime idle = _ircUser->idleTime();
            int idleTime = idle.secsTo(now);
            addRow(NetworkItem::escapeHTML(tr("Idling since"), true), secondsToString(idleTime), true);
        }

        if (_ircUser->loginTime().isValid()) {
            addRow(NetworkItem::escapeHTML(tr("Login time"), true), _ircUser->loginTime().toString(), true);
        }

        addRow(tr("Server"), NetworkItem::escapeHTML(_ircUser->server()), !_ircUser->server().isEmpty());
        tooltip << "</table>";
    }

    // If no further information found, offer an explanatory message
    if (!infoAdded)
        tooltip << "<p class='italic' align='center'>" << tr("No information available") << "</p>";

    tooltip << "</qt>";
    return strTooltip;
}

void QueryBufferItem::setIrcUser(IrcUser* ircUser)
{
    if (_ircUser == ircUser)
        return;

    if (_ircUser) {
        disconnect(_ircUser, nullptr, this, nullptr);
    }

    if (ircUser) {
        connect(ircUser, &IrcUser::destroyed, this, &QueryBufferItem::removeIrcUser);
        connect(ircUser, &IrcUser::quited, this, &QueryBufferItem::removeIrcUser);
        connect(ircUser, &IrcUser::awaySet, this, [this]() { emit dataChanged(); });
        connect(ircUser, &IrcUser::encryptedSet, this, &BufferItem::setEncrypted);
    }

    _ircUser = ircUser;
    emit dataChanged();
}

void QueryBufferItem::removeIrcUser()
{
    if (_ircUser) {
        // Disconnect the active IrcUser before removing it, otherwise it will fire removeIrcUser()
        // a second time when the object's destroyed due to QueryBufferItem::setIrcUser() connecting
        // SIGNAL destroyed(QObject*) to SLOT removeIrcUser().
        // This fixes removing an active IrcUser if the user had quit then rejoined in a nonstandard
        // manner (e.g. updateNickFromHost calling newIrcUser, triggered by an away-notify message).
        disconnect(_ircUser, nullptr, this, nullptr);

        // Clear IrcUser (only set to 0 if not already 0)
        _ircUser = nullptr;

        // Only emit dataChanged() if data actually changed.  This might serve as a small
        // optimization, but it can be moved outside the if statement if other behavior depends on
        // it always being called.
        emit dataChanged();
    }
}

/*****************************************
 *  ChannelBufferItem
 *****************************************/
ChannelBufferItem::ChannelBufferItem(const BufferInfo& bufferInfo, AbstractTreeItem* parent)
    : BufferItem(bufferInfo, parent)
    , _ircChannel(nullptr)
{
    setFlags(flags() | Qt::ItemIsDropEnabled);
}

QVariant ChannelBufferItem::data(int column, int role) const
{
    switch (role) {
    case NetworkModel::IrcChannelRole:
        return QVariant::fromValue(_ircChannel);
    default:
        return BufferItem::data(column, role);
    }
}

QString ChannelBufferItem::toolTip(int column) const
{
    Q_UNUSED(column);
    QString strTooltip;
    QTextStream tooltip(&strTooltip, QIODevice::WriteOnly);
    tooltip << "<qt><style>.bold { font-weight: bold; } .italic { font-style: italic; }</style>";

    // Function to add a row to the tooltip table
    auto addRow = [&](const QString& key, const QString& value, bool condition) {
        if (condition) {
            tooltip << "<tr><td class='bold' align='right'>" << key << "</td><td>" << value << "</td></tr>";
        }
    };

    tooltip << "<p class='bold' align='center'>";
    tooltip << NetworkItem::escapeHTML(tr("Channel %1").arg(bufferName()), true) << "</p>";

    if (isActive()) {
        tooltip << "<table cellspacing='5' cellpadding='0'>";
        addRow(tr("Users"), QString::number(nickCount()), true);

        if (_ircChannel) {
            QString channelMode = _ircChannel->channelModeString();  // channelModeString is compiled on the fly -> thus cache the result
            if (!channelMode.isEmpty())
                addRow(tr("Mode"), channelMode, true);
        }

        ItemViewSettings s;
        bool showTopic = s.displayTopicInTooltip();
        if (showTopic) {
            QString _topic = topic();
            if (_topic != "") {
                _topic = stripFormatCodes(_topic);
                _topic = NetworkItem::escapeHTML(_topic);
                addRow(tr("Topic"), _topic, true);
            }
        }

        tooltip << "</table>";
    }
    else {
        tooltip << "<p class='italic' align='center'>" << tr("Not active, double-click to join") << "</p>";
    }

    tooltip << "</qt>";
    return strTooltip;
}

void ChannelBufferItem::attachIrcChannel(IrcChannel* ircChannel)
{
    if (_ircChannel) {
        qWarning() << Q_FUNC_INFO << "IrcChannel already set; cleanup failed!?";
        disconnect(_ircChannel, nullptr, this, nullptr);
    }

    _ircChannel = ircChannel;

    connect(ircChannel, &QObject::destroyed, this, &ChannelBufferItem::ircChannelDestroyed);
    connect(ircChannel, &IrcChannel::topicSet, this, &ChannelBufferItem::setTopic);
    connect(ircChannel, &IrcChannel::encryptedSet, this, &ChannelBufferItem::setEncrypted);
    connect(ircChannel, &IrcChannel::ircUsersJoined, this, &ChannelBufferItem::join);
    connect(ircChannel, &IrcChannel::ircUserParted, this, &ChannelBufferItem::part);
    connect(ircChannel, &IrcChannel::parted, this, &ChannelBufferItem::ircChannelParted);
    connect(ircChannel, &IrcChannel::ircUserModesSet, this, &ChannelBufferItem::userModeChanged);
    connect(ircChannel, &IrcChannel::ircUserModeAdded, this, &ChannelBufferItem::userModeChanged);
    connect(ircChannel, &IrcChannel::ircUserModeRemoved, this, &ChannelBufferItem::userModeChanged);

    if (!ircChannel->ircUsers().isEmpty())
        join(ircChannel->ircUsers());

    emit dataChanged();
}

QString ChannelBufferItem::nickChannelModes(const QString& nick) const
{
    if (!_ircChannel) {
        qDebug() << Q_FUNC_INFO << "IrcChannel not set, can't get user modes";
        return QString();
    }

    return _ircChannel->userModes(nick);
}

void ChannelBufferItem::ircChannelParted()
{
    Q_CHECK_PTR(_ircChannel);
    disconnect(_ircChannel, nullptr, this, nullptr);
    _ircChannel = nullptr;
    emit dataChanged();
    removeAllChilds();
}

void ChannelBufferItem::ircChannelDestroyed()
{
    if (_ircChannel) {
        _ircChannel = nullptr;
        emit dataChanged();
        removeAllChilds();
    }
}

void ChannelBufferItem::join(const QList<IrcUser*>& ircUsers)
{
    addUsersToCategory(ircUsers);
    emit dataChanged(2);
}

UserCategoryItem* ChannelBufferItem::findCategoryItem(int categoryId)
{
    UserCategoryItem* categoryItem = nullptr;

    for (int i = 0; i < childCount(); i++) {
        categoryItem = qobject_cast<UserCategoryItem*>(child(i));
        if (!categoryItem)
            continue;
        if (categoryItem->categoryId() == categoryId)
            return categoryItem;
    }
    return nullptr;
}

void ChannelBufferItem::addUserToCategory(IrcUser* ircUser)
{
    addUsersToCategory(QList<IrcUser*>() << ircUser);
}

void ChannelBufferItem::addUsersToCategory(const QList<IrcUser*>& ircUsers)
{
    Q_ASSERT(_ircChannel);

    QHash<UserCategoryItem*, QList<IrcUser*>> categories;

    int categoryId = -1;
    UserCategoryItem* categoryItem = nullptr;

    foreach (IrcUser* ircUser, ircUsers) {
        categoryId = UserCategoryItem::categoryFromModes(_ircChannel->userModes(ircUser));
        categoryItem = findCategoryItem(categoryId);
        if (!categoryItem) {
            categoryItem = new UserCategoryItem(categoryId, this);
            categories[categoryItem] = QList<IrcUser*>();
            newChild(categoryItem);
        }
        categories[categoryItem] << ircUser;
    }

    QHash<UserCategoryItem*, QList<IrcUser*>>::const_iterator catIter = categories.constBegin();
    while (catIter != categories.constEnd()) {
        catIter.key()->addUsers(catIter.value());
        ++catIter;
    }
}

void ChannelBufferItem::part(IrcUser* ircUser)
{
    if (!ircUser) {
        qWarning() << bufferName() << "ChannelBufferItem::part(): unknown User" << ircUser;
        return;
    }

    disconnect(ircUser, nullptr, this, nullptr);
    removeUserFromCategory(ircUser);
    emit dataChanged(2);
}

void ChannelBufferItem::removeUserFromCategory(IrcUser* ircUser)
{
    if (!_ircChannel) {
        // If we parted the channel there might still be some ircUsers connected.
        // in that case we just ignore the call
        Q_ASSERT(childCount() == 0);
        return;
    }

    UserCategoryItem* categoryItem = nullptr;
    for (int i = 0; i < childCount(); i++) {
        categoryItem = qobject_cast<UserCategoryItem*>(child(i));
        if (categoryItem->removeUser(ircUser)) {
            if (categoryItem->childCount() == 0)
                removeChild(i);
            break;
        }
    }
}

void ChannelBufferItem::userModeChanged(IrcUser* ircUser)
{
    Q_ASSERT(_ircChannel);

    int categoryId = UserCategoryItem::categoryFromModes(_ircChannel->userModes(ircUser));
    UserCategoryItem* categoryItem = findCategoryItem(categoryId);

    if (categoryItem) {
        if (categoryItem->findIrcUser(ircUser)) {
            return;  // already in the right category;
        }
    }
    else {
        categoryItem = new UserCategoryItem(categoryId, this);
        newChild(categoryItem);
    }

    // find the item that needs reparenting
    IrcUserItem* ircUserItem = nullptr;
    for (int i = 0; i < childCount(); i++) {
        auto* oldCategoryItem = qobject_cast<UserCategoryItem*>(child(i));
        Q_ASSERT(oldCategoryItem);
        IrcUserItem* userItem = oldCategoryItem->findIrcUser(ircUser);
        if (userItem) {
            ircUserItem = userItem;
            break;
        }
    }

    if (!ircUserItem) {
        qWarning() << "ChannelBufferItem::userModeChanged(IrcUser *): unable to determine old category of" << ircUser;
        return;
    }
    ircUserItem->reParent(categoryItem);
}

/*****************************************
 *  User Category Items (like @vh etc.)
 *****************************************/
// we hardcode this even though we have PREFIX in network... but that wouldn't help with mapping modes to
// category strings anyway.
const QList<QChar> UserCategoryItem::categories = QList<QChar>() << 'q' << 'a' << 'o' << 'h' << 'v';

UserCategoryItem::UserCategoryItem(int category, AbstractTreeItem* parent)
    : PropertyMapItem(parent)
    , _category(category)
{
    setFlags(Qt::ItemIsEnabled);
    setTreeItemFlags(AbstractTreeItem::DeleteOnLastChildRemoved);
    setObjectName(parent->data(0, Qt::DisplayRole).toString() + "/" + QString::number(category));
}

QStringList UserCategoryItem::propertyOrder() const
{
    static QStringList order{"categoryName"};
    return order;
}

// caching this makes no sense, since we display the user number dynamically
QString UserCategoryItem::categoryName() const
{
    int n = childCount();
    switch (_category) {
    case 0:
        return tr("%n Owner(s)", "", n);
    case 1:
        return tr("%n Admin(s)", "", n);
    case 2:
        return tr("%n Operator(s)", "", n);
    case 3:
        return tr("%n Half-Op(s)", "", n);
    case 4:
        return tr("%n Voiced", "", n);
    default:
        return tr("%n User(s)", "", n);
    }
}

IrcUserItem* UserCategoryItem::findIrcUser(IrcUser* ircUser)
{
    IrcUserItem* userItem = nullptr;

    for (int i = 0; i < childCount(); i++) {
        userItem = qobject_cast<IrcUserItem*>(child(i));
        if (!userItem)
            continue;
        if (userItem->ircUser() == ircUser)
            return userItem;
    }
    return nullptr;
}

void UserCategoryItem::addUsers(const QList<IrcUser*>& ircUsers)
{
    QList<AbstractTreeItem*> userItems;
    foreach (IrcUser* ircUser, ircUsers)
        userItems << new IrcUserItem(ircUser, this);
    newChilds(userItems);
    emit dataChanged(0);
}

bool UserCategoryItem::removeUser(IrcUser* ircUser)
{
    IrcUserItem* userItem = findIrcUser(ircUser);
    auto success = (bool)userItem;
    if (success) {
        removeChild(userItem);
        emit dataChanged(0);
    }
    return success;
}

int UserCategoryItem::categoryFromModes(const QString& modes)
{
    for (int i = 0; i < categories.count(); i++) {
        if (modes.contains(categories[i]))
            return i;
    }
    return categories.count();
}

QVariant UserCategoryItem::data(int column, int role) const
{
    switch (role) {
    case TreeModel::SortRole:
        return _category;
    case NetworkModel::ItemActiveRole:
        return true;
    case NetworkModel::ItemTypeRole:
        return NetworkModel::UserCategoryItemType;
    case NetworkModel::BufferIdRole:
        return parent()->data(column, role);
    case NetworkModel::NetworkIdRole:
        return parent()->data(column, role);
    case NetworkModel::BufferInfoRole:
        return parent()->data(column, role);
    default:
        return PropertyMapItem::data(column, role);
    }
}

/*****************************************
 *  Irc User Items
 *****************************************/
IrcUserItem::IrcUserItem(IrcUser* ircUser, AbstractTreeItem* parent)
    : PropertyMapItem(parent)
    , _ircUser(ircUser)
{
    setObjectName(ircUser->nick());
    connect(ircUser, &IrcUser::quited, this, &IrcUserItem::ircUserQuited);
    connect(ircUser, &IrcUser::nickSet, this, [this]() { emit dataChanged(); });
    connect(ircUser, &IrcUser::awaySet, this, [this]() { emit dataChanged(); });
}

QStringList IrcUserItem::propertyOrder() const
{
    static QStringList order{"nickName"};
    return order;
}

QVariant IrcUserItem::data(int column, int role) const
{
    switch (role) {
    case NetworkModel::ItemActiveRole:
        return isActive();
    case NetworkModel::ItemTypeRole:
        return NetworkModel::IrcUserItemType;
    case NetworkModel::BufferIdRole:
        return parent()->data(column, role);
    case NetworkModel::NetworkIdRole:
        return parent()->data(column, role);
    case NetworkModel::BufferInfoRole:
        return parent()->data(column, role);
    case NetworkModel::IrcChannelRole:
        return parent()->data(column, role);
    case NetworkModel::IrcUserRole:
        return QVariant::fromValue(_ircUser.data());
    case NetworkModel::UserAwayRole:
        return (bool)_ircUser ? _ircUser->isAway() : false;
    default:
        return PropertyMapItem::data(column, role);
    }
}

QString IrcUserItem::toolTip(int column) const
{
    Q_UNUSED(column);
    QString strTooltip;
    QTextStream tooltip(&strTooltip, QIODevice::WriteOnly);
    tooltip << "<qt><style>.bold { font-weight: bold; } .italic { font-style: italic; }</style>";

    // Keep track of whether or not information has been added
    bool infoAdded = false;

    // Use bufferName() for QueryBufferItem, nickName() for IrcUserItem
    tooltip << "<p class='bold' align='center'>" << NetworkItem::escapeHTML(nickName(), true);
    if (_ircUser->userModes() != "") {
        // TODO: Translate user Modes and add them to the table below and in QueryBufferItem::toolTip
        tooltip << " (" << _ircUser->userModes() << ")";
    }
    tooltip << "</p>";

    auto addRow = [&](const QString& key, const QString& value, bool condition) {
        if (condition) {
            tooltip << "<tr><td class='bold' align='right'>" << key << "</td><td>" << value << "</td></tr>";
            infoAdded = true;
        }
    };

    tooltip << "<table cellspacing='5' cellpadding='0'>";
    addRow(tr("Modes"), NetworkItem::escapeHTML(channelModes()), !channelModes().isEmpty());
    if (_ircUser->isAway()) {
        QString awayMessageHTML = QString("<p class='italic'>%1</p>").arg(tr("Unknown"));

        // If away message is known, replace with the escaped message.
        if (!_ircUser->awayMessage().isEmpty()) {
            awayMessageHTML = NetworkItem::escapeHTML(_ircUser->awayMessage());
        }
        addRow(NetworkItem::escapeHTML(tr("Away message"), true), awayMessageHTML, true);
    }
    addRow(tr("Realname"), NetworkItem::escapeHTML(_ircUser->realName()), !_ircUser->realName().isEmpty());

    // suserHost may return "<nick> is available for help", which should be translated.
    // See https://www.alien.net.au/irc/irc2numerics.html
    if (_ircUser->suserHost().endsWith("available for help")) {
        addRow(NetworkItem::escapeHTML(tr("Help status"), true), NetworkItem::escapeHTML(tr("Available for help")), true);
    }
    else {
        addRow(NetworkItem::escapeHTML(tr("Service status"), true),
               NetworkItem::escapeHTML(_ircUser->suserHost()),
               !_ircUser->suserHost().isEmpty());
    }

    // Keep track of whether or not the account information's been added.  Don't show it twice.
    bool accountAdded = false;
    if (!_ircUser->account().isEmpty()) {
        // IRCv3 account-notify is supported by the core and IRC server.
        // Assume logged out (seems to be more common)
        QString accountHTML = QString("<p class='italic'>%1</p>").arg(tr("Not logged in"));

        // If account is logged in, replace with the escaped account name.
        if (_ircUser->account() != "*") {
            accountHTML = NetworkItem::escapeHTML(_ircUser->account());
        }
        addRow(NetworkItem::escapeHTML(tr("Account"), true), accountHTML, true);
        // Mark the row as added
        accountAdded = true;
    }
    // whoisServiceReply may return "<nick> is identified for this nick", which should be translated.
    // See https://www.alien.net.au/irc/irc2numerics.html
    if (_ircUser->whoisServiceReply().endsWith("identified for this nick")) {
        addRow(NetworkItem::escapeHTML(tr("Account"), true), NetworkItem::escapeHTML(tr("Identified for this nick")), !accountAdded);
        // Don't add the account row again if information's already added via account-notify
        // Not used further down...
        // accountAdded = true;
    }
    else {
        addRow(NetworkItem::escapeHTML(tr("Service Reply"), true),
               NetworkItem::escapeHTML(_ircUser->whoisServiceReply()),
               !_ircUser->whoisServiceReply().isEmpty());
    }
    addRow(tr("Hostmask"),
           NetworkItem::escapeHTML(_ircUser->hostmask().remove(0, _ircUser->hostmask().indexOf("!") + 1)),
           !(_ircUser->hostmask().remove(0, _ircUser->hostmask().indexOf("!") + 1) == "@"));
    // ircOperator may contain "is an" or "is a", which should be removed.
    addRow(tr("Operator"),
           NetworkItem::escapeHTML(_ircUser->ircOperator().replace("is an ", "").replace("is a ", "")),
           !_ircUser->ircOperator().isEmpty());

    if (_ircUser->idleTime().isValid()) {
        QDateTime now = QDateTime::currentDateTime();
        QDateTime idle = _ircUser->idleTime();
        int idleTime = idle.secsTo(now);
        addRow(NetworkItem::escapeHTML(tr("Idling since"), true), secondsToString(idleTime), true);
    }

    if (_ircUser->loginTime().isValid()) {
        addRow(NetworkItem::escapeHTML(tr("Login time"), true), _ircUser->loginTime().toString(), true);
    }

    addRow(tr("Server"), NetworkItem::escapeHTML(_ircUser->server()), !_ircUser->server().isEmpty());
    tooltip << "</table>";

    // If no further information found, offer an explanatory message
    if (!infoAdded)
        tooltip << "<p class='italic' align='center'>" << tr("No information available") << "</p>";

    tooltip << "</qt>";
    return strTooltip;
}

QString IrcUserItem::channelModes() const
{
    // IrcUserItems are parented to UserCategoryItem, which are parented to ChannelBufferItem.
    // We want the channel buffer item in order to get the channel-specific user modes.
    auto* category = qobject_cast<UserCategoryItem*>(parent());
    if (!category)
        return QString();

    auto* channel = qobject_cast<ChannelBufferItem*>(category->parent());
    if (!channel)
        return QString();

    return channel->nickChannelModes(nickName());
}

/*****************************************
 * NetworkModel
 *****************************************/
NetworkModel::NetworkModel(QObject* parent)
    : TreeModel(NetworkModel::defaultHeader(), parent)
{
    connect(this, &NetworkModel::rowsInserted, this, &NetworkModel::checkForNewBuffers);
    connect(this, &NetworkModel::rowsAboutToBeRemoved, this, &NetworkModel::checkForRemovedBuffers);

    BufferSettings defaultSettings;
    defaultSettings.notify("UserNoticesTarget", this, &NetworkModel::messageRedirectionSettingsChanged);
    defaultSettings.notify("ServerNoticesTarget", this, &NetworkModel::messageRedirectionSettingsChanged);
    defaultSettings.notify("ErrorMsgsTarget", this, &NetworkModel::messageRedirectionSettingsChanged);
    messageRedirectionSettingsChanged();
}

QList<QVariant> NetworkModel::defaultHeader()
{
    QList<QVariant> data;
    data << tr("Chat") << tr("Topic") << tr("Nick Count");
    return data;
}

bool NetworkModel::isBufferIndex(const QModelIndex& index) const
{
    return index.data(NetworkModel::ItemTypeRole) == NetworkModel::BufferItemType;
}

int NetworkModel::networkRow(NetworkId networkId) const
{
    NetworkItem* netItem = nullptr;
    for (int i = 0; i < rootItem->childCount(); i++) {
        netItem = qobject_cast<NetworkItem*>(rootItem->child(i));
        if (!netItem)
            continue;
        if (netItem->networkId() == networkId)
            return i;
    }
    return -1;
}

QModelIndex NetworkModel::networkIndex(NetworkId networkId)
{
    int netRow = networkRow(networkId);
    if (netRow == -1)
        return {};
    else
        return indexByItem(qobject_cast<NetworkItem*>(rootItem->child(netRow)));
}

NetworkItem* NetworkModel::findNetworkItem(NetworkId networkId) const
{
    int netRow = networkRow(networkId);
    if (netRow == -1)
        return nullptr;
    else
        return qobject_cast<NetworkItem*>(rootItem->child(netRow));
}

NetworkItem* NetworkModel::networkItem(NetworkId networkId)
{
    NetworkItem* netItem = findNetworkItem(networkId);

    if (netItem == nullptr) {
        netItem = new NetworkItem(networkId, rootItem);
        rootItem->newChild(netItem);
    }
    return netItem;
}

void NetworkModel::networkRemoved(const NetworkId& networkId)
{
    int netRow = networkRow(networkId);
    if (netRow != -1) {
        rootItem->removeChild(netRow);
    }
}

QModelIndex NetworkModel::bufferIndex(BufferId bufferId)
{
    if (!_bufferItemCache.contains(bufferId))
        return {};

    return indexByItem(_bufferItemCache[bufferId]);
}

BufferItem* NetworkModel::findBufferItem(BufferId bufferId) const
{
    if (_bufferItemCache.contains(bufferId))
        return _bufferItemCache[bufferId];
    else
        return nullptr;
}

BufferItem* NetworkModel::bufferItem(const BufferInfo& bufferInfo)
{
    if (_bufferItemCache.contains(bufferInfo.bufferId()))
        return _bufferItemCache[bufferInfo.bufferId()];

    NetworkItem* netItem = networkItem(bufferInfo.networkId());
    return netItem->bufferItem(bufferInfo);
}

QStringList NetworkModel::mimeTypes() const
{
    // mimetypes we accept for drops
    QStringList types;
    // comma separated list of colon separated pairs of networkid and bufferid
    // example: 0:1,0:2,1:4
    types << "application/Quassel/BufferItemList";
    return types;
}

bool NetworkModel::mimeContainsBufferList(const QMimeData* mimeData)
{
    return mimeData->hasFormat("application/Quassel/BufferItemList");
}

QList<QPair<NetworkId, BufferId>> NetworkModel::mimeDataToBufferList(const QMimeData* mimeData)
{
    QList<QPair<NetworkId, BufferId>> bufferList;

    if (!mimeContainsBufferList(mimeData))
        return bufferList;

    QStringList rawBufferList = QString::fromLatin1(mimeData->data("application/Quassel/BufferItemList")).split(",");
    NetworkId networkId;
    BufferId bufferUid;
    foreach (QString rawBuffer, rawBufferList) {
        if (!rawBuffer.contains(":"))
            continue;
        networkId = rawBuffer.section(":", 0, 0).toInt();
        bufferUid = rawBuffer.section(":", 1, 1).toInt();
        bufferList.append(qMakePair(networkId, bufferUid));
    }
    return bufferList;
}

QMimeData* NetworkModel::mimeData(const QModelIndexList& indexes) const
{
    auto* mimeData = new QMimeData();

    QStringList bufferlist;
    QString netid, uid, bufferid;
    foreach (QModelIndex index, indexes) {
        netid = QString::number(index.data(NetworkIdRole).value<NetworkId>().toInt());
        uid = QString::number(index.data(BufferIdRole).value<BufferId>().toInt());
        bufferid = QString("%1:%2").arg(netid).arg(uid);
        if (!bufferlist.contains(bufferid))
            bufferlist << bufferid;
    }

    mimeData->setData("application/Quassel/BufferItemList", bufferlist.join(",").toLatin1());

    return mimeData;
}

void NetworkModel::attachNetwork(Network* net)
{
    NetworkItem* netItem = networkItem(net->networkId());
    netItem->attachNetwork(net);
}

void NetworkModel::bufferUpdated(BufferInfo bufferInfo)
{
    BufferItem* bufItem = bufferItem(bufferInfo);
    QModelIndex itemindex = indexByItem(bufItem);
    emit dataChanged(itemindex, itemindex);
}

void NetworkModel::removeBuffer(BufferId bufferId)
{
    BufferItem* buffItem = findBufferItem(bufferId);
    if (!buffItem)
        return;

    buffItem->parent()->removeChild(buffItem);
}

MsgId NetworkModel::lastSeenMsgId(BufferId bufferId) const
{
    if (!_bufferItemCache.contains(bufferId))
        return {};

    return _bufferItemCache[bufferId]->lastSeenMsgId();
}

MsgId NetworkModel::markerLineMsgId(BufferId bufferId) const
{
    if (!_bufferItemCache.contains(bufferId))
        return {};

    return _bufferItemCache[bufferId]->markerLineMsgId();
}

// FIXME we always seem to use this (expensive) non-const version
MsgId NetworkModel::lastSeenMsgId(const BufferId& bufferId)
{
    BufferItem* bufferItem = findBufferItem(bufferId);
    if (!bufferItem) {
        qDebug() << "NetworkModel::lastSeenMsgId(): buffer is unknown:" << bufferId;
        Client::purgeKnownBufferIds();
        return {};
    }
    return bufferItem->lastSeenMsgId();
}

void NetworkModel::setLastSeenMsgId(const BufferId& bufferId, const MsgId& msgId)
{
    BufferItem* bufferItem = findBufferItem(bufferId);
    if (!bufferItem) {
        qDebug() << "NetworkModel::setLastSeenMsgId(): buffer is unknown:" << bufferId;
        Client::purgeKnownBufferIds();
        return;
    }
    bufferItem->setLastSeenMsgId(msgId);
    emit lastSeenMsgSet(bufferId, msgId);
}

void NetworkModel::setMarkerLineMsgId(const BufferId& bufferId, const MsgId& msgId)
{
    BufferItem* bufferItem = findBufferItem(bufferId);
    if (!bufferItem) {
        qDebug() << "NetworkModel::setMarkerLineMsgId(): buffer is unknown:" << bufferId;
        Client::purgeKnownBufferIds();
        return;
    }
    bufferItem->setMarkerLineMsgId(msgId);
    emit markerLineSet(bufferId, msgId);
}

void NetworkModel::updateBufferActivity(Message& msg)
{
    int redirectionTarget = 0;
    switch (msg.type()) {
    case Message::Notice:
        if (bufferType(msg.bufferId()) != BufferInfo::ChannelBuffer) {
            msg.setFlags(msg.flags() | Message::Redirected);
            if (msg.flags() & Message::ServerMsg) {
                // server notice
                redirectionTarget = _serverNoticesTarget;
            }
            else {
                redirectionTarget = _userNoticesTarget;
            }
        }
        break;
    case Message::Error:
        msg.setFlags(msg.flags() | Message::Redirected);
        redirectionTarget = _errorMsgsTarget;
        break;
    // Update IrcUser's last activity
    case Message::Plain:
    case Message::Action:
        if (bufferType(msg.bufferId()) == BufferInfo::ChannelBuffer) {
            const Network* net = Client::network(msg.bufferInfo().networkId());
            IrcUser* user = net ? net->ircUser(nickFromMask(msg.sender())) : nullptr;
            if (user)
                user->setLastChannelActivity(msg.bufferId(), msg.timestamp());
        }
        break;
    default:
        break;
    }

    if (msg.flags() & Message::Redirected) {
        if (redirectionTarget & BufferSettings::DefaultBuffer)
            updateBufferActivity(bufferItem(msg.bufferInfo()), msg);

        if (redirectionTarget & BufferSettings::StatusBuffer) {
            const NetworkItem* netItem = findNetworkItem(msg.bufferInfo().networkId());
            if (netItem) {
                updateBufferActivity(netItem->statusBufferItem(), msg);
            }
        }
    }
    else {
        if ((BufferSettings(msg.bufferId()).messageFilter() & msg.type()) != msg.type())
            updateBufferActivity(bufferItem(msg.bufferInfo()), msg);
    }
}

void NetworkModel::updateBufferActivity(BufferItem* bufferItem, const Message& msg)
{
    if (!bufferItem)
        return;

    bufferItem->updateActivityLevel(msg);
    if (bufferItem->isCurrentBuffer())
        emit requestSetLastSeenMsg(bufferItem->bufferId(), msg.msgId());
}

void NetworkModel::setBufferActivity(const BufferId& bufferId, BufferInfo::ActivityLevel level)
{
    BufferItem* bufferItem = findBufferItem(bufferId);
    if (!bufferItem) {
        qDebug() << "NetworkModel::setBufferActivity(): buffer is unknown:" << bufferId;
        return;
    }
    bufferItem->setActivityLevel(level);
}

void NetworkModel::clearBufferActivity(const BufferId& bufferId)
{
    BufferItem* bufferItem = findBufferItem(bufferId);
    if (!bufferItem) {
        qDebug() << "NetworkModel::clearBufferActivity(): buffer is unknown:" << bufferId;
        return;
    }
    bufferItem->clearActivityLevel();
}

const Network* NetworkModel::networkByIndex(const QModelIndex& index) const
{
    QVariant netVariant = index.data(NetworkIdRole);
    if (!netVariant.isValid())
        return nullptr;

    NetworkId networkId = netVariant.value<NetworkId>();
    return Client::network(networkId);
}

void NetworkModel::checkForRemovedBuffers(const QModelIndex& parent, int start, int end)
{
    if (parent.data(ItemTypeRole) != NetworkItemType)
        return;

    for (int row = start; row <= end; row++) {
        _bufferItemCache.remove(index(row, 0, parent).data(BufferIdRole).value<BufferId>());
    }
}

void NetworkModel::checkForNewBuffers(const QModelIndex& parent, int start, int end)
{
    if (parent.data(ItemTypeRole) != NetworkItemType)
        return;

    for (int row = start; row <= end; row++) {
        QModelIndex child = parent.model()->index(row, 0, parent);
        _bufferItemCache[child.data(BufferIdRole).value<BufferId>()] = static_cast<BufferItem*>(child.internalPointer());
    }
}

QString NetworkModel::bufferName(BufferId bufferId) const
{
    if (!_bufferItemCache.contains(bufferId))
        return QString();

    return _bufferItemCache[bufferId]->bufferName();
}

BufferInfo::Type NetworkModel::bufferType(BufferId bufferId) const
{
    if (!_bufferItemCache.contains(bufferId))
        return BufferInfo::InvalidBuffer;

    return _bufferItemCache[bufferId]->bufferType();
}

BufferInfo NetworkModel::bufferInfo(BufferId bufferId) const
{
    if (!_bufferItemCache.contains(bufferId))
        return BufferInfo();

    return _bufferItemCache[bufferId]->bufferInfo();
}

NetworkId NetworkModel::networkId(BufferId bufferId) const
{
    if (!_bufferItemCache.contains(bufferId))
        return {};

    auto* netItem = qobject_cast<NetworkItem*>(_bufferItemCache[bufferId]->parent());
    if (netItem)
        return netItem->networkId();
    else
        return {};
}

QString NetworkModel::networkName(BufferId bufferId) const
{
    if (!_bufferItemCache.contains(bufferId))
        return QString();

    auto* netItem = qobject_cast<NetworkItem*>(_bufferItemCache[bufferId]->parent());
    if (netItem)
        return netItem->networkName();
    else
        return QString();
}

BufferId NetworkModel::bufferId(NetworkId networkId, const QString& bufferName, Qt::CaseSensitivity cs) const
{
    const NetworkItem* netItem = findNetworkItem(networkId);
    if (!netItem)
        return {};

    for (int i = 0; i < netItem->childCount(); i++) {
        auto* bufferItem = qobject_cast<BufferItem*>(netItem->child(i));
        if (bufferItem && !bufferItem->bufferName().compare(bufferName, cs))
            return bufferItem->bufferId();
    }
    return {};
}

void NetworkModel::sortBufferIds(QList<BufferId>& bufferIds) const
{
    QList<BufferItem*> bufferItems;
    foreach (BufferId bufferId, bufferIds) {
        if (_bufferItemCache.contains(bufferId))
            bufferItems << _bufferItemCache[bufferId];
    }

    std::sort(bufferItems.begin(), bufferItems.end(), bufferItemLessThan);

    bufferIds.clear();
    foreach (BufferItem* bufferItem, bufferItems) {
        bufferIds << bufferItem->bufferId();
    }
}

QList<BufferId> NetworkModel::allBufferIdsSorted() const
{
    QList<BufferId> bufferIds = allBufferIds();
    sortBufferIds(bufferIds);
    return bufferIds;
}

bool NetworkModel::bufferItemLessThan(const BufferItem* left, const BufferItem* right)
{
    int leftType = left->bufferType();
    int rightType = right->bufferType();

    if (leftType != rightType)
        return leftType < rightType;
    else
        return QString::compare(left->bufferName(), right->bufferName(), Qt::CaseInsensitive) < 0;
}

void NetworkModel::messageRedirectionSettingsChanged()
{
    BufferSettings bufferSettings;

    _userNoticesTarget = bufferSettings.userNoticesTarget();
    _serverNoticesTarget = bufferSettings.serverNoticesTarget();
    _errorMsgsTarget = bufferSettings.errorMsgsTarget();
}

void NetworkModel::bufferActivityChanged(BufferId bufferId, const Message::Types activity)
{
    auto _bufferItem = findBufferItem(bufferId);
    if (!_bufferItem) {
        qDebug() << "NetworkModel::bufferActivityChanged(): buffer is unknown:" << bufferId;
        return;
    }
    auto hiddenTypes = BufferSettings(bufferId).messageFilter();
    auto visibleTypes = ~hiddenTypes;
    auto activityVisibleTypesIntersection = activity & visibleTypes;
    _bufferItem->setActivity(activityVisibleTypesIntersection, false);
}

void NetworkModel::highlightCountChanged(BufferId bufferId, int count)
{
    auto _bufferItem = findBufferItem(bufferId);
    if (!_bufferItem) {
        qDebug() << "NetworkModel::highlightCountChanged(): buffer is unknown:" << bufferId;
        return;
    }
    _bufferItem->addActivity(Message::Types{}, count > 0);
}
