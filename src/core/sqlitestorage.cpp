// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "sqlitestorage.h"

#include <QByteArray>
#include <QDataStream>
#include <QLatin1String>
#include <QStringConverter>
#include <QVariant>

#include "network.h"
#include "quassel.h"

int SqliteStorage::_maxRetryCount = 150;

SqliteStorage::SqliteStorage(QObject* parent)
    : AbstractSqlStorage(parent)
{
}

bool SqliteStorage::isAvailable() const
{
    if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
        return false;
    return true;
}

QString SqliteStorage::backendId() const
{
    return QString("SQLite");
}

QString SqliteStorage::displayName() const
{
    // Note: Pre-0.13 clients use the displayName property for backend idenfication
    // We identify the backend to use for the monolithic core by its displayname.
    // so only change this string if you _really_ have to and make sure the core
    // setup for the mono client still works ;)
    return backendId();
}

QString SqliteStorage::description() const
{
    return tr("SQLite is a file-based database engine that does not require any setup. It is suitable for small and medium-sized "
              "databases that do not require access via network. Use SQLite if your Quassel Core should store its data on the same machine "
              "it is running on, and if you only expect a few users to use your core.");
}

int SqliteStorage::installedSchemaVersion()
{
    // Only used during startup (single-threaded), so no locking needed
    QSqlDatabase db = logDb();

    // Check if coreinfo table exists
    QSqlQuery tableCheckQuery(db);
    tableCheckQuery.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name='coreinfo'");
    safeExec(tableCheckQuery);
    if (!tableCheckQuery.first()) {
        // Fresh database, no coreinfo table; return -1 to signal initialization needed
        return -1;
    }

    // Try querying schemaversion
    QSqlQuery query(db);
    query.prepare("SELECT value FROM coreinfo WHERE key = 'schemaversion'");
    safeExec(query);
    if (query.first()) {
        return query.value(0).toInt();
    }
    else {
        watchQuery(query);  // Log errors only if table exists
    }

    // Fallback for older schema (version 0)
    query.prepare("SELECT MAX(version) FROM coreinfo");
    safeExec(query);
    if (query.first()) {
        return query.value(0).toInt();
    }
    else {
        watchQuery(query);  // Log errors only if table exists
    }

    return AbstractSqlStorage::installedSchemaVersion();
}

bool SqliteStorage::updateSchemaVersion(int newVersion, bool clearUpgradeStep)
{
    // only used when there is a singlethread (during startup)
    // so we don't need locking here

    QSqlDatabase db = logDb();

    // Atomically update the schema version and clear the upgrade step, if specified
    // Note: This will need reworked if "updateSchemaVersion" is ever called within a transaction.
    db.transaction();

    QSqlQuery query(db);
    query.prepare("UPDATE coreinfo SET value = :version WHERE key = 'schemaversion'");
    query.bindValue(":version", newVersion);
    safeExec(query);

    if (!watchQuery(query)) {
        qCritical() << "SqliteStorage::updateSchemaVersion(int, bool): Updating schema version failed!";
        db.rollback();
        return false;
    }

    if (clearUpgradeStep) {
        // Try clearing the upgrade step if requested
        if (!setSchemaVersionUpgradeStep("")) {
            db.rollback();
            return false;
        }
    }

    // Successful, commit and return true
    db.commit();
    return true;
}

bool SqliteStorage::setupSchemaVersion(int version)
{
    // only used when there is a singlethread (during startup)
    // so we don't need locking here
    QSqlQuery query(logDb());
    query.prepare("INSERT INTO coreinfo (key, value) VALUES ('schemaversion', :version)");
    query.bindValue(":version", version);
    query.exec();

    bool success = true;
    if (query.lastError().isValid()) {
        qCritical() << "SqliteStorage::setupSchemaVersion(int): Updating schema version failed!";
        success = false;
    }
    return success;
}

QString SqliteStorage::schemaVersionUpgradeStep()
{
    // Only used when there is a singlethread (during startup), so we don't need locking here
    QSqlQuery query(logDb());
    query.prepare("SELECT value FROM coreinfo WHERE key = 'schemaupgradestep'");
    safeExec(query);
    watchQuery(query);
    if (query.first())
        return query.value(0).toString();

    // Fall back to the default value
    return AbstractSqlStorage::schemaVersionUpgradeStep();
}

bool SqliteStorage::setSchemaVersionUpgradeStep(QString upgradeQuery)
{
    // Only used when there is a singlethread (during startup), so we don't need locking here

    // Intentionally do not wrap in a transaction so other functions can include multiple operations
    QSqlQuery query(logDb());
    query.prepare("UPDATE coreinfo SET value = :upgradestep WHERE key = 'schemaupgradestep'");
    query.bindValue(":upgradestep", upgradeQuery);
    safeExec(query);

    // Don't wrap with watchQuery to avoid an alarming message in the log when the key is missing
    // Make sure that the query didn't fail, and that some non-zero number of rows were affected
    bool success = !query.lastError().isValid() && query.numRowsAffected() != 0;

    if (!success) {
        // The key might not exist (Quassel 0.13.0 and older).  Try inserting it...
        query = QSqlQuery(logDb());
        query.prepare("INSERT INTO coreinfo (key, value) VALUES ('schemaupgradestep', :upgradestep)");
        query.bindValue(":upgradestep", upgradeQuery);
        safeExec(query);

        if (!watchQuery(query)) {
            qCritical() << Q_FUNC_INFO << "Setting schema upgrade step failed!";
            success = false;
        }
        else {
            success = true;
        }
    }
    return success;
}

UserId SqliteStorage::addUser(const QString& user, const QString& password, const QString& authenticator)
{
    QSqlDatabase db = logDb();
    UserId uid;

    db.transaction();
    // this scope ensures that the query is freed in sqlite before we call unlock()
    // this ensures that our thread doesn't hold a internal after unlock is called
    // (see sqlites doc on implicit locking for details)
    {
        QSqlQuery query(db);
        query.prepare(queryString("insert_quasseluser"));
        query.bindValue(":username", user);
        query.bindValue(":password", hashPassword(password));
        query.bindValue(":hashversion", Storage::HashVersion::Latest);
        query.bindValue(":authenticator", authenticator);
        lockForWrite();
        safeExec(query);
        if (query.lastError().isValid()
            && query.lastError().nativeErrorCode()
                   == QLatin1String{"19"}) {  // user already exists - sadly 19 seems to be the general constraint violation error...
            db.rollback();
        }
        else {
            uid = query.lastInsertId().toInt();
            db.commit();
        }
    }
    unlock();

    if (uid.isValid())
        emit userAdded(uid, user);
    return uid;
}

bool SqliteStorage::updateUser(UserId user, const QString& password)
{
    QSqlDatabase db = logDb();
    bool success = false;

    db.transaction();
    {
        QSqlQuery query(db);
        query.prepare(queryString("update_userpassword"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":password", hashPassword(password));
        query.bindValue(":hashversion", Storage::HashVersion::Latest);
        lockForWrite();
        safeExec(query);
        success = query.numRowsAffected() != 0;
        db.commit();
    }
    unlock();
    return success;
}

void SqliteStorage::renameUser(UserId user, const QString& newName)
{
    QSqlDatabase db = logDb();
    db.transaction();
    {
        QSqlQuery query(db);
        query.prepare(queryString("update_username"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":username", newName);
        lockForWrite();
        safeExec(query);
        db.commit();
    }
    unlock();
    emit userRenamed(user, newName);
}

UserId SqliteStorage::validateUser(const QString& user, const QString& password)
{
    UserId userId;
    QString hashedPassword;
    Storage::HashVersion hashVersion = Storage::HashVersion::Latest;

    {
        QSqlQuery query(logDb());
        query.prepare(queryString("select_authuser"));
        query.bindValue(":username", user);

        lockForRead();
        safeExec(query);

        if (query.first()) {
            userId = query.value(0).toInt();
            hashedPassword = query.value(1).toString();
            hashVersion = static_cast<Storage::HashVersion>(query.value(2).toInt());
        }
    }
    unlock();

    UserId returnUserId;
    if (userId != 0 && checkHashedPassword(userId, password, hashedPassword, hashVersion)) {
        returnUserId = userId;
    }
    return returnUserId;
}

UserId SqliteStorage::getUserId(const QString& username)
{
    UserId userId;

    {
        QSqlQuery query(logDb());
        query.prepare(queryString("select_userid"));
        query.bindValue(":username", username);

        lockForRead();
        safeExec(query);

        if (query.first()) {
            userId = query.value(0).toInt();
        }
    }
    unlock();

    return userId;
}

QString SqliteStorage::getUserAuthenticator(const UserId userid)
{
    QString authenticator = QString("");

    {
        QSqlQuery query(logDb());
        query.prepare(queryString("select_authenticator"));
        query.bindValue(":userid", userid.toInt());

        lockForRead();
        safeExec(query);

        if (query.first()) {
            authenticator = query.value(0).toString();
        }
    }
    unlock();

    return authenticator;
}

UserId SqliteStorage::internalUser()
{
    UserId userId;

    {
        QSqlQuery query(logDb());
        query.prepare(queryString("select_internaluser"));
        lockForRead();
        safeExec(query);

        if (query.first()) {
            userId = query.value(0).toInt();
        }
    }
    unlock();

    return userId;
}

void SqliteStorage::delUser(UserId user)
{
    QSqlDatabase db = logDb();
    db.transaction();

    lockForWrite();
    {
        QSqlQuery query(db);
        query.prepare(queryString("delete_backlog_by_uid"));
        query.bindValue(":userid", user.toInt());
        safeExec(query);

        query.prepare(queryString("delete_buffers_by_uid"));
        query.bindValue(":userid", user.toInt());
        safeExec(query);

        query.prepare(queryString("delete_networks_by_uid"));
        query.bindValue(":userid", user.toInt());
        safeExec(query);

        query.prepare(queryString("delete_quasseluser"));
        query.bindValue(":userid", user.toInt());
        safeExec(query);
        // I hate the lack of foreign keys and on delete cascade... :(
        db.commit();
    }
    unlock();

    emit userRemoved(user);
}

void SqliteStorage::setUserSetting(UserId userId, const QString& settingName, const QVariant& data)
{
    QByteArray rawData;
    QDataStream out(&rawData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << data;

    QSqlDatabase db = logDb();
    db.transaction();
    {
        QSqlQuery query(db);
        query.prepare(queryString("insert_user_setting"));
        query.bindValue(":userid", userId.toInt());
        query.bindValue(":settingname", settingName);
        query.bindValue(":settingvalue", rawData);
        lockForWrite();
        safeExec(query);

        if (query.lastError().isValid()) {
            QSqlQuery updateQuery(db);
            updateQuery.prepare(queryString("update_user_setting"));
            updateQuery.bindValue(":userid", userId.toInt());
            updateQuery.bindValue(":settingname", settingName);
            updateQuery.bindValue(":settingvalue", rawData);
            safeExec(updateQuery);
        }
        db.commit();
    }
    unlock();
}

QVariant SqliteStorage::getUserSetting(UserId userId, const QString& settingName, const QVariant& defaultData)
{
    QVariant data = defaultData;
    {
        QSqlQuery query(logDb());
        query.prepare(queryString("select_user_setting"));
        query.bindValue(":userid", userId.toInt());
        query.bindValue(":settingname", settingName);
        lockForRead();
        safeExec(query);

        if (query.first()) {
            QByteArray rawData = query.value(0).toByteArray();
            QDataStream in(&rawData, QIODevice::ReadOnly);
            in.setVersion(QDataStream::Qt_4_2);
            in >> data;
        }
    }
    unlock();
    return data;
}

void SqliteStorage::setCoreState(const QVariantList& data)
{
    QByteArray rawData;
    QDataStream out(&rawData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << data;

    QSqlDatabase db = logDb();
    db.transaction();
    {
        QSqlQuery query(db);
        query.prepare(queryString("insert_core_state"));
        query.bindValue(":key", "active_sessions");
        query.bindValue(":value", rawData);
        lockForWrite();
        safeExec(query);

        if (query.lastError().isValid()) {
            QSqlQuery updateQuery(db);
            updateQuery.prepare(queryString("update_core_state"));
            updateQuery.bindValue(":key", "active_sessions");
            updateQuery.bindValue(":value", rawData);
            safeExec(updateQuery);
        }
        db.commit();
    }
    unlock();
}

QVariantList SqliteStorage::getCoreState(const QVariantList& defaultData)
{
    QVariantList data;
    {
        QSqlQuery query(logDb());
        query.prepare(queryString("select_core_state"));
        query.bindValue(":key", "active_sessions");
        lockForRead();
        safeExec(query);

        if (query.first()) {
            QByteArray rawData = query.value(0).toByteArray();
            QDataStream in(&rawData, QIODevice::ReadOnly);
            in.setVersion(QDataStream::Qt_4_2);
            in >> data;
        }
        else {
            data = defaultData;
        }
    }
    unlock();
    return data;
}

IdentityId SqliteStorage::createIdentity(UserId user, CoreIdentity& identity)
{
    IdentityId identityId;

    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("insert_identity"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":identityname", identity.identityName());
        query.bindValue(":realname", identity.realName());
        query.bindValue(":awaynick", identity.awayNick());
        query.bindValue(":awaynickenabled", identity.awayNickEnabled() ? 1 : 0);
        query.bindValue(":awayreason", identity.awayReason());
        query.bindValue(":awayreasonenabled", identity.awayReasonEnabled() ? 1 : 0);
        query.bindValue(":autoawayenabled", identity.awayReasonEnabled() ? 1 : 0);
        query.bindValue(":autoawaytime", identity.autoAwayTime());
        query.bindValue(":autoawayreason", identity.autoAwayReason());
        query.bindValue(":autoawayreasonenabled", identity.autoAwayReasonEnabled() ? 1 : 0);
        query.bindValue(":detachawayenabled", identity.detachAwayEnabled() ? 1 : 0);
        query.bindValue(":detachawayreason", identity.detachAwayReason());
        query.bindValue(":detachawayreasonenabled", identity.detachAwayReasonEnabled() ? 1 : 0);
        query.bindValue(":ident", identity.ident());
        query.bindValue(":kickreason", identity.kickReason());
        query.bindValue(":partreason", identity.partReason());
        query.bindValue(":quitreason", identity.quitReason());
        query.bindValue(":sslcert", identity.sslCert().toPem());
        query.bindValue(":sslkey", identity.sslKey().toPem());

        lockForWrite();
        safeExec(query);

        identityId = query.lastInsertId().toInt();
        if (!identityId.isValid()) {
            watchQuery(query);
        }
        else {
            QSqlQuery deleteNickQuery(db);
            deleteNickQuery.prepare(queryString("delete_nicks"));
            deleteNickQuery.bindValue(":identityid", identityId.toInt());
            safeExec(deleteNickQuery);

            QSqlQuery insertNickQuery(db);
            insertNickQuery.prepare(queryString("insert_nick"));
            foreach (QString nick, identity.nicks()) {
                insertNickQuery.bindValue(":identityid", identityId.toInt());
                insertNickQuery.bindValue(":nick", nick);
                safeExec(insertNickQuery);
            }
        }
        db.commit();
    }
    unlock();
    identity.setId(identityId);
    return identityId;
}

bool SqliteStorage::updateIdentity(UserId user, const CoreIdentity& identity)
{
    QSqlDatabase db = logDb();
    bool error = false;
    db.transaction();

    {
        QSqlQuery checkQuery(db);
        checkQuery.prepare(queryString("select_checkidentity"));
        checkQuery.bindValue(":identityid", identity.id().toInt());
        checkQuery.bindValue(":userid", user.toInt());
        lockForRead();
        safeExec(checkQuery);

        // there should be exactly one identity for the given id and user
        error = (!checkQuery.first() || checkQuery.value(0).toInt() != 1);
    }
    if (error) {
        unlock();
        return false;
    }

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_identity"));
        query.bindValue(":identityname", identity.identityName());
        query.bindValue(":realname", identity.realName());
        query.bindValue(":awaynick", identity.awayNick());
        query.bindValue(":awaynickenabled", identity.awayNickEnabled() ? 1 : 0);
        query.bindValue(":awayreason", identity.awayReason());
        query.bindValue(":awayreasonenabled", identity.awayReasonEnabled() ? 1 : 0);
        query.bindValue(":autoawayenabled", identity.awayReasonEnabled() ? 1 : 0);
        query.bindValue(":autoawaytime", identity.autoAwayTime());
        query.bindValue(":autoawayreason", identity.autoAwayReason());
        query.bindValue(":autoawayreasonenabled", identity.autoAwayReasonEnabled() ? 1 : 0);
        query.bindValue(":detachawayenabled", identity.detachAwayEnabled() ? 1 : 0);
        query.bindValue(":detachawayreason", identity.detachAwayReason());
        query.bindValue(":detachawayreasonenabled", identity.detachAwayReasonEnabled() ? 1 : 0);
        query.bindValue(":ident", identity.ident());
        query.bindValue(":kickreason", identity.kickReason());
        query.bindValue(":partreason", identity.partReason());
        query.bindValue(":quitreason", identity.quitReason());
        query.bindValue(":sslcert", identity.sslCert().toPem());
        query.bindValue(":sslkey", identity.sslKey().toPem());
        query.bindValue(":identityid", identity.id().toInt());
        safeExec(query);
        watchQuery(query);

        QSqlQuery deleteNickQuery(db);
        deleteNickQuery.prepare(queryString("delete_nicks"));
        deleteNickQuery.bindValue(":identityid", identity.id().toInt());
        safeExec(deleteNickQuery);
        watchQuery(deleteNickQuery);

        QSqlQuery insertNickQuery(db);
        insertNickQuery.prepare(queryString("insert_nick"));
        foreach (QString nick, identity.nicks()) {
            insertNickQuery.bindValue(":identityid", identity.id().toInt());
            insertNickQuery.bindValue(":nick", nick);
            safeExec(insertNickQuery);
            watchQuery(insertNickQuery);
        }
        db.commit();
    }
    unlock();
    return true;
}

void SqliteStorage::removeIdentity(UserId user, IdentityId identityId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery checkQuery(db);
        checkQuery.prepare(queryString("select_checkidentity"));
        checkQuery.bindValue(":identityid", identityId.toInt());
        checkQuery.bindValue(":userid", user.toInt());
        lockForRead();
        safeExec(checkQuery);

        // there should be exactly one identity for the given id and user
        error = (!checkQuery.first() || checkQuery.value(0).toInt() != 1);
    }
    if (error) {
        unlock();
        return;
    }

    {
        QSqlQuery deleteNickQuery(db);
        deleteNickQuery.prepare(queryString("delete_nicks"));
        deleteNickQuery.bindValue(":identityid", identityId.toInt());
        safeExec(deleteNickQuery);

        QSqlQuery deleteIdentityQuery(db);
        deleteIdentityQuery.prepare(queryString("delete_identity"));
        deleteIdentityQuery.bindValue(":identityid", identityId.toInt());
        deleteIdentityQuery.bindValue(":userid", user.toInt());
        safeExec(deleteIdentityQuery);
        db.commit();
    }
    unlock();
}

std::vector<CoreIdentity> SqliteStorage::identities(UserId user)
{
    std::vector<CoreIdentity> identities;
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("select_identities"));
        query.bindValue(":userid", user.toInt());

        QSqlQuery nickQuery(db);
        nickQuery.prepare(queryString("select_nicks"));

        lockForRead();
        safeExec(query);

        while (query.next()) {
            CoreIdentity identity(IdentityId(query.value(0).toInt()));

            identity.setIdentityName(query.value(1).toString());
            identity.setRealName(query.value(2).toString());
            identity.setAwayNick(query.value(3).toString());
            identity.setAwayNickEnabled(!!query.value(4).toInt());
            identity.setAwayReason(query.value(5).toString());
            identity.setAwayReasonEnabled(!!query.value(6).toInt());
            identity.setAutoAwayEnabled(!!query.value(7).toInt());
            identity.setAutoAwayTime(query.value(8).toInt());
            identity.setAutoAwayReason(query.value(9).toString());
            identity.setAutoAwayReasonEnabled(!!query.value(10).toInt());
            identity.setDetachAwayEnabled(!!query.value(11).toInt());
            identity.setDetachAwayReason(query.value(12).toString());
            identity.setDetachAwayReasonEnabled(!!query.value(13).toInt());
            identity.setIdent(query.value(14).toString());
            identity.setKickReason(query.value(15).toString());
            identity.setPartReason(query.value(16).toString());
            identity.setQuitReason(query.value(17).toString());
            identity.setSslCert(query.value(18).toByteArray());
            identity.setSslKey(query.value(19).toByteArray());

            nickQuery.bindValue(":identityid", identity.id().toInt());
            QList<QString> nicks;
            safeExec(nickQuery);
            watchQuery(nickQuery);
            while (nickQuery.next()) {
                nicks << nickQuery.value(0).toString();
            }
            identity.setNicks(std::move(nicks));
            identities.push_back(std::move(identity));
        }
        db.commit();
    }
    unlock();
    return identities;
}

NetworkId SqliteStorage::createNetwork(UserId user, const NetworkInfo& info)
{
    NetworkId networkId;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery query(db);
        query.prepare(queryString("insert_network"));
        query.bindValue(":userid", user.toInt());
        bindNetworkInfo(query, info);
        lockForWrite();
        safeExec(query);
        if (!watchQuery(query)) {
            db.rollback();
            error = true;
        }
        else {
            networkId = query.lastInsertId().toInt();
        }
    }
    if (error) {
        unlock();
        return {};
    }

    {
        QSqlQuery insertServersQuery(db);
        insertServersQuery.prepare(queryString("insert_server"));
        foreach (Network::Server server, info.serverList) {
            insertServersQuery.bindValue(":userid", user.toInt());
            insertServersQuery.bindValue(":networkid", networkId.toInt());
            bindServerInfo(insertServersQuery, server);
            safeExec(insertServersQuery);
            if (!watchQuery(insertServersQuery)) {
                db.rollback();
                error = true;
                break;
            }
        }
        if (!error)
            db.commit();
    }
    unlock();
    if (error)
        return {};
    else
        return networkId;
}

void SqliteStorage::bindNetworkInfo(QSqlQuery& query, const NetworkInfo& info)
{
    query.bindValue(":networkname", info.networkName);
    query.bindValue(":identityid", info.identity.toInt());
    query.bindValue(":encodingcodec", info.codecForEncoding.isEmpty() ? "ISO-8859-15" : QString(info.codecForEncoding));
    query.bindValue(":decodingcodec", info.codecForDecoding.isEmpty() ? "ISO-8859-15" : QString(info.codecForDecoding));
    query.bindValue(":servercodec", info.codecForServer.isEmpty() ? "ISO-8859-15" : QString(info.codecForServer));
    query.bindValue(":userandomserver", info.useRandomServer ? 1 : 0);
    query.bindValue(":perform", info.perform.join("\n"));
    query.bindValue(":useautoidentify", info.useAutoIdentify ? 1 : 0);
    query.bindValue(":autoidentifyservice", info.autoIdentifyService);
    query.bindValue(":autoidentifypassword", info.autoIdentifyPassword);
    query.bindValue(":usesasl", info.useSasl ? 1 : 0);
    query.bindValue(":saslaccount", info.saslAccount);
    query.bindValue(":saslpassword", info.saslPassword);
    query.bindValue(":useautoreconnect", info.useAutoReconnect ? 1 : 0);
    query.bindValue(":autoreconnectinterval", info.autoReconnectInterval);
    query.bindValue(":autoreconnectretries", info.autoReconnectRetries);
    query.bindValue(":unlimitedconnectretries", info.unlimitedReconnectRetries ? 1 : 0);
    query.bindValue(":rejoinchannels", info.rejoinChannels ? 1 : 0);
    query.bindValue(":usecustomessagerate", info.useCustomMessageRate ? 1 : 0);
    query.bindValue(":messagerateburstsize", info.messageRateBurstSize);
    query.bindValue(":messageratedelay", info.messageRateDelay);
    query.bindValue(":unlimitedmessagerate", info.unlimitedMessageRate ? 1 : 0);
    query.bindValue(":skipcaps", info.skipCapsToString());
    if (info.networkId.isValid())
        query.bindValue(":networkid", info.networkId.toInt());
}

void SqliteStorage::bindServerInfo(QSqlQuery& query, const Network::Server& server)
{
    query.bindValue(":hostname", server.host);
    query.bindValue(":port", server.port);
    query.bindValue(":password", server.password);
    query.bindValue(":ssl", server.useSsl ? 1 : 0);
    query.bindValue(":sslversion", server.sslVersion);
    query.bindValue(":useproxy", server.useProxy ? 1 : 0);
    query.bindValue(":proxytype", server.proxyType);
    query.bindValue(":proxyhost", server.proxyHost);
    query.bindValue(":proxyport", server.proxyPort);
    query.bindValue(":proxyuser", server.proxyUser);
    query.bindValue(":proxypass", server.proxyPass);
    query.bindValue(":sslverify", server.sslVerify ? 1 : 0);
}

bool SqliteStorage::updateNetwork(UserId user, const NetworkInfo& info)
{
    QSqlDatabase db = logDb();
    bool error = false;
    db.transaction();

    {
        QSqlQuery updateQuery(db);
        updateQuery.prepare(queryString("update_network"));
        updateQuery.bindValue(":userid", user.toInt());
        bindNetworkInfo(updateQuery, info);

        lockForWrite();
        safeExec(updateQuery);
        if (!watchQuery(updateQuery) || updateQuery.numRowsAffected() != 1) {
            error = true;
            db.rollback();
        }
    }
    if (error) {
        unlock();
        return false;
    }

    {
        QSqlQuery dropServersQuery(db);
        dropServersQuery.prepare("DELETE FROM ircserver WHERE networkid = :networkid");
        dropServersQuery.bindValue(":networkid", info.networkId.toInt());
        safeExec(dropServersQuery);
        if (!watchQuery(dropServersQuery)) {
            error = true;
            db.rollback();
        }
    }
    if (error) {
        unlock();
        return false;
    }

    {
        QSqlQuery insertServersQuery(db);
        insertServersQuery.prepare(queryString("insert_server"));
        foreach (Network::Server server, info.serverList) {
            insertServersQuery.bindValue(":userid", user.toInt());
            insertServersQuery.bindValue(":networkid", info.networkId.toInt());
            bindServerInfo(insertServersQuery, server);
            safeExec(insertServersQuery);
            if (!watchQuery(insertServersQuery)) {
                error = true;
                db.rollback();
                break;
            }
        }
    }

    db.commit();
    unlock();
    return !error;
}

bool SqliteStorage::removeNetwork(UserId user, const NetworkId& networkId)
{
    QSqlDatabase db = logDb();
    bool error = false;
    db.transaction();

    {
        QSqlQuery deleteNetworkQuery(db);
        deleteNetworkQuery.prepare(queryString("delete_network"));
        deleteNetworkQuery.bindValue(":networkid", networkId.toInt());
        deleteNetworkQuery.bindValue(":userid", user.toInt());
        lockForWrite();
        safeExec(deleteNetworkQuery);
        if (!watchQuery(deleteNetworkQuery) || deleteNetworkQuery.numRowsAffected() != 1) {
            error = true;
            db.rollback();
        }
    }
    if (error) {
        unlock();
        return false;
    }

    {
        QSqlQuery deleteBacklogQuery(db);
        deleteBacklogQuery.prepare(queryString("delete_backlog_for_network"));
        deleteBacklogQuery.bindValue(":networkid", networkId.toInt());
        safeExec(deleteBacklogQuery);
        if (!watchQuery(deleteBacklogQuery)) {
            db.rollback();
            error = true;
        }
    }
    if (error) {
        unlock();
        return false;
    }

    {
        QSqlQuery deleteBuffersQuery(db);
        deleteBuffersQuery.prepare(queryString("delete_buffers_for_network"));
        deleteBuffersQuery.bindValue(":networkid", networkId.toInt());
        safeExec(deleteBuffersQuery);
        if (!watchQuery(deleteBuffersQuery)) {
            db.rollback();
            error = true;
        }
    }
    if (error) {
        unlock();
        return false;
    }

    {
        QSqlQuery deleteServersQuery(db);
        deleteServersQuery.prepare(queryString("delete_ircservers_for_network"));
        deleteServersQuery.bindValue(":networkid", networkId.toInt());
        safeExec(deleteServersQuery);
        if (!watchQuery(deleteServersQuery)) {
            db.rollback();
            error = true;
        }
    }
    if (error) {
        unlock();
        return false;
    }

    db.commit();
    unlock();
    return true;
}

std::vector<NetworkInfo> SqliteStorage::networks(UserId user)
{
    std::vector<NetworkInfo> nets;

    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery networksQuery(db);
        networksQuery.prepare(queryString("select_networks_for_user"));
        networksQuery.bindValue(":userid", user.toInt());

        QSqlQuery serversQuery(db);
        serversQuery.prepare(queryString("select_servers_for_network"));

        lockForRead();
        safeExec(networksQuery);
        if (watchQuery(networksQuery)) {
            while (networksQuery.next()) {
                NetworkInfo net;
                net.networkId = networksQuery.value(0).toInt();
                net.networkName = networksQuery.value(1).toString();
                net.identity = networksQuery.value(2).toInt();
                net.codecForServer = networksQuery.value(3).toString().toLatin1();
                net.codecForEncoding = networksQuery.value(4).toString().toLatin1();
                net.codecForDecoding = networksQuery.value(5).toString().toLatin1();
                net.useRandomServer = networksQuery.value(6).toInt() == 1 ? true : false;
                net.perform = networksQuery.value(7).toString().split("\n");
                net.useAutoIdentify = networksQuery.value(8).toInt() == 1 ? true : false;
                net.autoIdentifyService = networksQuery.value(9).toString();
                net.autoIdentifyPassword = networksQuery.value(10).toString();
                net.useAutoReconnect = networksQuery.value(11).toInt() == 1 ? true : false;
                net.autoReconnectInterval = networksQuery.value(12).toUInt();
                net.autoReconnectRetries = networksQuery.value(13).toInt();
                net.unlimitedReconnectRetries = networksQuery.value(14).toInt() == 1 ? true : false;
                net.rejoinChannels = networksQuery.value(15).toInt() == 1 ? true : false;
                net.useSasl = networksQuery.value(16).toInt() == 1 ? true : false;
                net.saslAccount = networksQuery.value(17).toString();
                net.saslPassword = networksQuery.value(18).toString();
                // Custom rate limiting
                net.useCustomMessageRate = networksQuery.value(19).toInt() == 1 ? true : false;
                net.messageRateBurstSize = networksQuery.value(20).toUInt();
                net.messageRateDelay = networksQuery.value(21).toUInt();
                net.unlimitedMessageRate = networksQuery.value(22).toInt() == 1 ? true : false;
                net.skipCapsFromString(networksQuery.value(23).toString());

                serversQuery.bindValue(":networkid", net.networkId.toInt());
                safeExec(serversQuery);
                if (!watchQuery(serversQuery)) {
                    nets.clear();
                    break;
                }
                else {
                    Network::ServerList servers;
                    while (serversQuery.next()) {
                        Network::Server server;
                        server.host = serversQuery.value(0).toString();
                        server.port = serversQuery.value(1).toUInt();
                        server.password = serversQuery.value(2).toString();
                        server.useSsl = serversQuery.value(3).toInt() == 1 ? true : false;
                        server.sslVersion = serversQuery.value(4).toInt();
                        server.useProxy = serversQuery.value(5).toInt() == 1 ? true : false;
                        server.proxyType = serversQuery.value(6).toInt();
                        server.proxyHost = serversQuery.value(7).toString();
                        server.proxyPort = serversQuery.value(8).toUInt();
                        server.proxyUser = serversQuery.value(9).toString();
                        server.proxyPass = serversQuery.value(10).toString();
                        server.sslVerify = serversQuery.value(11).toInt() == 1 ? true : false;
                        servers << server;
                    }
                    net.serverList = servers;
                    nets.push_back(std::move(net));
                }
            }
        }
    }
    db.commit();
    unlock();
    return nets;
}

std::vector<NetworkId> SqliteStorage::connectedNetworks(UserId user)
{
    std::vector<NetworkId> connectedNets;

    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("select_connected_networks"));
        query.bindValue(":userid", user.toInt());
        lockForRead();
        safeExec(query);
        watchQuery(query);

        while (query.next()) {
            connectedNets.emplace_back(query.value(0).toInt());
        }
        db.commit();
    }
    unlock();
    return connectedNets;
}

void SqliteStorage::setNetworkConnected(UserId user, const NetworkId& networkId, bool isConnected)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_network_connected"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());
        query.bindValue(":connected", isConnected ? 1 : 0);

        lockForWrite();
        safeExec(query);
        watchQuery(query);
        db.commit();
    }
    unlock();
}

QHash<QString, QString> SqliteStorage::persistentChannels(UserId user, const NetworkId& networkId)
{
    QHash<QString, QString> persistentChans;

    QSqlDatabase db = logDb();
    db.transaction();
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_persistent_channels"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());

        lockForRead();
        safeExec(query);
        watchQuery(query);
        while (query.next()) {
            persistentChans[query.value(0).toString()] = query.value(1).toString();
        }
    }
    unlock();
    return persistentChans;
}

void SqliteStorage::setChannelPersistent(UserId user, const NetworkId& networkId, const QString& channel, bool isJoined)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_buffer_persistent_channel"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());
        query.bindValue(":buffercname", channel.toLower());
        query.bindValue(":joined", isJoined ? 1 : 0);

        lockForWrite();
        safeExec(query);
        watchQuery(query);
        db.commit();
    }
    unlock();
}

void SqliteStorage::setPersistentChannelKey(UserId user, const NetworkId& networkId, const QString& channel, const QString& key)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_buffer_set_channel_key"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());
        query.bindValue(":buffercname", channel.toLower());
        query.bindValue(":key", key);

        lockForWrite();
        safeExec(query);
        watchQuery(query);
        db.commit();
    }
    unlock();
}

QString SqliteStorage::awayMessage(UserId user, NetworkId networkId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    QString awayMsg;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_network_awaymsg"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());

        lockForRead();
        safeExec(query);
        watchQuery(query);
        if (query.first())
            awayMsg = query.value(0).toString();
        db.commit();
    }
    unlock();

    return awayMsg;
}

void SqliteStorage::setAwayMessage(UserId user, NetworkId networkId, const QString& awayMsg)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_network_set_awaymsg"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());
        query.bindValue(":awaymsg", awayMsg);

        lockForWrite();
        safeExec(query);
        watchQuery(query);
        db.commit();
    }
    unlock();
}

QString SqliteStorage::userModes(UserId user, NetworkId networkId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    QString modes;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_network_usermode"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());

        lockForRead();
        safeExec(query);
        watchQuery(query);
        if (query.first())
            modes = query.value(0).toString();
        db.commit();
    }
    unlock();

    return modes;
}

void SqliteStorage::setUserModes(UserId user, NetworkId networkId, const QString& userModes)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_network_set_usermode"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());
        query.bindValue(":usermode", userModes);

        lockForWrite();
        safeExec(query);
        watchQuery(query);
        db.commit();
    }
    unlock();
}

BufferInfo SqliteStorage::bufferInfo(UserId user, const NetworkId& networkId, BufferInfo::Type type, const QString& buffer, bool create)
{
    QSqlDatabase db = logDb();
    db.transaction();

    BufferInfo bufferInfo;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_bufferByName"));
        query.bindValue(":networkid", networkId.toInt());
        query.bindValue(":userid", user.toInt());
        query.bindValue(":buffercname", buffer.toLower());

        lockForRead();
        safeExec(query);

        if (query.first()) {
            bufferInfo = BufferInfo(query.value(0).toInt(), networkId, (BufferInfo::Type)query.value(1).toInt(), 0, buffer);
            if (query.next()) {
                qCritical() << "SqliteStorage::getBufferInfo(): received more then one Buffer!";
                qCritical() << "         Query:" << query.lastQuery();
                qCritical() << "  bound Values:";
                QVariantList boundValues = query.boundValues();
                for (int i = 0; i < boundValues.size(); ++i)
                    qCritical() << i << ":" << boundValues[i].toString().toLatin1().data();
                Q_ASSERT(false);
            }
        }
        else if (create) {
            // let's create the buffer
            QSqlQuery createQuery(db);
            createQuery.prepare(queryString("insert_buffer"));
            createQuery.bindValue(":userid", user.toInt());
            createQuery.bindValue(":networkid", networkId.toInt());
            createQuery.bindValue(":buffertype", (int)type);
            createQuery.bindValue(":buffername", buffer);
            createQuery.bindValue(":buffercname", buffer.toLower());
            createQuery.bindValue(":joined", type & BufferInfo::ChannelBuffer ? 1 : 0);

            unlock();
            lockForWrite();
            safeExec(createQuery);
            watchQuery(createQuery);
            bufferInfo = BufferInfo(createQuery.lastInsertId().toInt(), networkId, type, 0, buffer);
        }
    }
    db.commit();
    unlock();
    return bufferInfo;
}

BufferInfo SqliteStorage::getBufferInfo(UserId user, const BufferId& bufferId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    BufferInfo bufferInfo;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_by_id"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":bufferid", bufferId.toInt());

        lockForRead();
        safeExec(query);

        if (watchQuery(query) && query.first()) {
            bufferInfo = BufferInfo(query.value(0).toInt(),
                                    query.value(1).toInt(),
                                    (BufferInfo::Type)query.value(2).toInt(),
                                    0,
                                    query.value(4).toString());
            Q_ASSERT(!query.next());
        }
        db.commit();
    }
    unlock();
    return bufferInfo;
}

std::vector<BufferInfo> SqliteStorage::requestBuffers(UserId user)
{
    std::vector<BufferInfo> bufferlist;

    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffers"));
        query.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(query);
        watchQuery(query);
        while (query.next()) {
            bufferlist.emplace_back(query.value(0).toInt(),
                                    query.value(1).toInt(),
                                    (BufferInfo::Type)query.value(2).toInt(),
                                    query.value(3).toInt(),
                                    query.value(4).toString());
        }
        db.commit();
    }
    unlock();

    return bufferlist;
}

std::vector<BufferId> SqliteStorage::requestBufferIdsForNetwork(UserId user, NetworkId networkId)
{
    std::vector<BufferId> bufferList;

    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffers_for_network"));
        query.bindValue(":networkid", networkId.toInt());
        query.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(query);
        watchQuery(query);
        while (query.next()) {
            bufferList.emplace_back(query.value(0).toInt());
        }
        db.commit();
    }
    unlock();

    return bufferList;
}

bool SqliteStorage::removeBuffer(const UserId& user, const BufferId& bufferId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery delBufferQuery(db);
        delBufferQuery.prepare(queryString("delete_buffer_for_bufferid"));
        delBufferQuery.bindValue(":bufferid", bufferId.toInt());
        delBufferQuery.bindValue(":userid", user.toInt());

        lockForWrite();
        safeExec(delBufferQuery);

        error = (!watchQuery(delBufferQuery) || delBufferQuery.numRowsAffected() != 1);
    }

    if (error) {
        db.rollback();
        unlock();
        return false;
    }

    {
        QSqlQuery delBacklogQuery(db);
        delBacklogQuery.prepare(queryString("delete_backlog_for_buffer"));
        delBacklogQuery.bindValue(":bufferid", bufferId.toInt());

        safeExec(delBacklogQuery);
        error = !watchQuery(delBacklogQuery);
    }

    if (error) {
        db.rollback();
    }
    else {
        db.commit();
    }
    unlock();
    return !error;
}

bool SqliteStorage::renameBuffer(const UserId& user, const BufferId& bufferId, const QString& newName)
{
    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery query(db);
        query.prepare(queryString("update_buffer_name"));
        query.bindValue(":buffername", newName);
        query.bindValue(":buffercname", newName.toLower());
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":userid", user.toInt());

        lockForWrite();
        safeExec(query);

        error = query.lastError().isValid();
        // unexpected error occurred (19 == constraint violation)
        if (error && query.lastError().nativeErrorCode() != QLatin1String{"19"}) {
            watchQuery(query);
        }
        else {
            error |= (query.numRowsAffected() != 1);
        }
    }
    if (error) {
        db.rollback();
    }
    else {
        db.commit();
    }
    unlock();
    return !error;
}

bool SqliteStorage::mergeBuffersPermanently(const UserId& user, const BufferId& bufferId1, const BufferId& bufferId2)
{
    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery checkQuery(db);
        checkQuery.prepare(queryString("select_buffers_for_merge"));
        checkQuery.bindValue(":oldbufferid", bufferId2.toInt());
        checkQuery.bindValue(":newbufferid", bufferId1.toInt());
        checkQuery.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(checkQuery);
        error = (!checkQuery.first() || checkQuery.value(0).toInt() != 2);
    }
    if (error) {
        db.rollback();
        unlock();
        return false;
    }

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_backlog_bufferid"));
        query.bindValue(":oldbufferid", bufferId2.toInt());
        query.bindValue(":newbufferid", bufferId1.toInt());
        safeExec(query);
        error = !watchQuery(query);
    }
    if (error) {
        db.rollback();
        unlock();
        return false;
    }

    {
        QSqlQuery delBufferQuery(db);
        delBufferQuery.prepare(queryString("delete_buffer_for_bufferid"));
        delBufferQuery.bindValue(":bufferid", bufferId2.toInt());
        delBufferQuery.bindValue(":userid", user.toInt());
        safeExec(delBufferQuery);
        error = !watchQuery(delBufferQuery);
    }

    if (error) {
        db.rollback();
    }
    else {
        db.commit();
    }
    unlock();
    return !error;
}

QHash<BufferId, MsgId> SqliteStorage::bufferLastMsgIds(UserId user)
{
    QHash<BufferId, MsgId> lastMsgHash;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_last_messages"));
        query.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(query);
        error = !watchQuery(query);
        if (!error) {
            while (query.next()) {
                lastMsgHash[query.value(0).toInt()] = query.value(1).toLongLong();
            }
        }
    }

    db.commit();
    unlock();
    return lastMsgHash;
}

void SqliteStorage::setBufferLastSeenMsg(UserId user, const BufferId& bufferId, const MsgId& msgId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_buffer_lastseen"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":lastseenmsgid", msgId.toQint64());

        lockForWrite();
        safeExec(query);
        watchQuery(query);
    }
    db.commit();
    unlock();
}

QHash<BufferId, MsgId> SqliteStorage::bufferLastSeenMsgIds(UserId user)
{
    QHash<BufferId, MsgId> lastSeenHash;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_lastseen_messages"));
        query.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(query);
        error = !watchQuery(query);
        if (!error) {
            while (query.next()) {
                lastSeenHash[query.value(0).toInt()] = query.value(1).toLongLong();
            }
        }
    }

    db.commit();
    unlock();
    return lastSeenHash;
}

void SqliteStorage::setBufferMarkerLineMsg(UserId user, const BufferId& bufferId, const MsgId& msgId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_buffer_markerlinemsgid"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":markerlinemsgid", msgId.toQint64());

        lockForWrite();
        safeExec(query);
        watchQuery(query);
    }
    db.commit();
    unlock();
}

QHash<BufferId, MsgId> SqliteStorage::bufferMarkerLineMsgIds(UserId user)
{
    QHash<BufferId, MsgId> markerLineHash;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_markerlinemsgids"));
        query.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(query);
        error = !watchQuery(query);
        if (!error) {
            while (query.next()) {
                markerLineHash[query.value(0).toInt()] = query.value(1).toLongLong();
            }
        }
    }

    db.commit();
    unlock();
    return markerLineHash;
}

void SqliteStorage::setBufferActivity(UserId user, BufferId bufferId, Message::Types bufferActivity)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_buffer_bufferactivity"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":bufferactivity", (int)bufferActivity);

        lockForWrite();
        safeExec(query);
        watchQuery(query);
    }
    db.commit();
    unlock();
}

QHash<BufferId, Message::Types> SqliteStorage::bufferActivities(UserId user)
{
    QHash<BufferId, Message::Types> bufferActivityHash;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_bufferactivities"));
        query.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(query);
        error = !watchQuery(query);
        if (!error) {
            while (query.next()) {
                bufferActivityHash[query.value(0).toInt()] = Message::Types(query.value(1).toInt());
            }
        }
    }

    db.commit();
    unlock();
    return bufferActivityHash;
}

Message::Types SqliteStorage::bufferActivity(BufferId bufferId, MsgId lastSeenMsgId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    Message::Types result{};
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_bufferactivity"));
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":lastseenmsgid", lastSeenMsgId.toQint64());

        lockForRead();
        safeExec(query);
        if (query.first())
            result = Message::Types(query.value(0).toInt());
    }

    db.commit();
    unlock();
    return result;
}

QHash<QString, QByteArray> SqliteStorage::bufferCiphers(UserId user, const NetworkId& networkId)
{
    QHash<QString, QByteArray> bufferCiphers;

    QSqlDatabase db = logDb();
    db.transaction();
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_ciphers"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());

        lockForRead();
        safeExec(query);
        watchQuery(query);
        while (query.next()) {
            bufferCiphers[query.value(0).toString()] = QByteArray::fromHex(query.value(1).toString().toUtf8());
        }
    }
    unlock();
    return bufferCiphers;
}

void SqliteStorage::setBufferCipher(UserId user, const NetworkId& networkId, const QString& bufferName, const QByteArray& cipher)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_buffer_cipher"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":networkid", networkId.toInt());
        query.bindValue(":buffercname", bufferName.toLower());
        query.bindValue(":cipher", QString(cipher.toHex()));

        lockForWrite();
        safeExec(query);
        watchQuery(query);
        db.commit();
    }
    unlock();
}

void SqliteStorage::setHighlightCount(UserId user, BufferId bufferId, int count)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSqlQuery query(db);
        query.prepare(queryString("update_buffer_highlightcount"));
        query.bindValue(":userid", user.toInt());
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":highlightcount", count);

        lockForWrite();
        safeExec(query);
        watchQuery(query);
    }
    db.commit();
    unlock();
}

QHash<BufferId, int> SqliteStorage::highlightCounts(UserId user)
{
    QHash<BufferId, int> highlightCountHash;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_highlightcounts"));
        query.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(query);
        error = !watchQuery(query);
        if (!error) {
            while (query.next()) {
                highlightCountHash[query.value(0).toInt()] = query.value(1).toInt();
            }
        }
    }

    db.commit();
    unlock();
    return highlightCountHash;
}

int SqliteStorage::highlightCount(BufferId bufferId, MsgId lastSeenMsgId)
{
    QSqlDatabase db = logDb();
    db.transaction();

    int result = 0;
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_buffer_highlightcount"));
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":lastseenmsgid", lastSeenMsgId.toQint64());

        lockForRead();
        safeExec(query);
        if (query.first())
            result = query.value(0).toInt();
    }

    db.commit();
    unlock();
    return result;
}

#include <QStringConverter>  // For QStringEncoder and QStringDecoder

bool SqliteStorage::logMessage(Message& msg)
{
    QSqlDatabase db = logDb();
    db.transaction();
    bool error = false;

    // Sanitize strings for UTF-8 compatibility
    auto sanitizeString = [](const QString& input) -> QString {
        if (input.isEmpty()) {
            return input;
        }
        // Try to validate as UTF-8
        QStringConverter::Encoding encoding = QStringConverter::Utf8;
        QStringEncoder encoder(encoding);
        QStringDecoder decoder(encoding);
        QByteArray utf8Data = encoder(input);
        QString result = decoder(utf8Data);
        if (result == input && !utf8Data.isEmpty()) {
            return input;  // Valid UTF-8
        }
        // Fallback to Latin1
        qWarning() << "UTF-8 decoding failed for input:" << qPrintable(input);
        return QString::fromLatin1(input.toLatin1());
    };

    // Handle empty sender
    QString sender = msg.sender().isEmpty() ? QStringLiteral("Server") : sanitizeString(msg.sender());
    QString realName = sanitizeString(msg.realName());
    QString avatarUrl = sanitizeString(msg.avatarUrl());
    QString senderPrefixes = sanitizeString(msg.senderPrefixes());
    QString message = sanitizeString(msg.contents());

    // Log warning for empty sender
    if (msg.sender().isEmpty()) {
        qWarning() << "Empty sender for message, using default 'Server'. Message details:"
                   << "type=" << msg.type() << "buffer=" << msg.bufferInfo().bufferName() << "content=" << msg.contents();
    }

    // Step 1: Ensure the sender exists
    {
        QSqlQuery addSenderQuery(db);
        addSenderQuery.prepare(queryString("insert_sender"));
        addSenderQuery.bindValue(":sender", QVariant(sender));
        addSenderQuery.bindValue(":realname", QVariant(realName));
        addSenderQuery.bindValue(":avatarurl", QVariant(avatarUrl));
        lockForWrite();
        safeExec(addSenderQuery);
        if (addSenderQuery.lastError().isValid() && addSenderQuery.lastError().nativeErrorCode() != QLatin1String{"19"}) {
            qCritical() << "Failed to insert sender:" << qPrintable(sender) << "Error:" << qPrintable(addSenderQuery.lastError().text());
            error = true;
        }
    }

    // Step 2: Insert the message (senderid is handled by the query's subquery)
    if (!error) {
        QSqlQuery logMessageQuery(db);
        logMessageQuery.prepare(queryString("insert_message"));
        logMessageQuery.bindValue(":time", msg.timestamp().toMSecsSinceEpoch());
        logMessageQuery.bindValue(":bufferid", static_cast<int>(msg.bufferInfo().bufferId().toInt()));
        logMessageQuery.bindValue(":type", static_cast<int>(msg.type()));
        logMessageQuery.bindValue(":flags", static_cast<int>(msg.flags()));
        logMessageQuery.bindValue(":sender", QVariant(sender));
        logMessageQuery.bindValue(":realname", QVariant(realName));
        logMessageQuery.bindValue(":avatarurl", QVariant(avatarUrl));
        logMessageQuery.bindValue(":senderprefixes", QVariant(senderPrefixes));
        logMessageQuery.bindValue(":message", QVariant(message));
        safeExec(logMessageQuery);
        if (logMessageQuery.lastError().isValid()) {
            qCritical() << "Failed to insert backlog message. Bound values:" << logMessageQuery.boundValues()
                        << "Error:" << qPrintable(logMessageQuery.lastError().text());
            error = true;
        }
        else {
            MsgId msgId = logMessageQuery.lastInsertId().toLongLong();
            if (msgId.isValid()) {
                msg.setMsgId(msgId);
            }
            else {
                qCritical() << "Invalid message ID after backlog insert";
                error = true;
            }
        }
    }

    if (error) {
        db.rollback();
    }
    else {
        db.commit();
    }
    unlock();
    return !error;
}

bool SqliteStorage::logMessages(MessageList& msgs)
{
    QSqlDatabase db = logDb();
    db.transaction();

    {
        QSet<SenderData> senders;
        QSqlQuery addSenderQuery(db);
        addSenderQuery.prepare(queryString("insert_sender"));
        lockForWrite();
        for (int i = 0; i < msgs.count(); i++) {
            auto& msg = msgs.at(i);
            SenderData sender = {msg.sender(), msg.realName(), msg.avatarUrl()};
            if (senders.contains(sender))
                continue;
            senders << sender;

            addSenderQuery.bindValue(":sender", sender.sender);
            addSenderQuery.bindValue(":realname", sender.realname);
            addSenderQuery.bindValue(":avatarurl", sender.avatarurl);
            safeExec(addSenderQuery);
        }
    }

    bool error = false;
    {
        QSqlQuery logMessageQuery(db);
        logMessageQuery.prepare(queryString("insert_message"));
        for (int i = 0; i < msgs.count(); i++) {
            Message& msg = msgs[i];
            // As of SQLite schema version 31, timestamps are stored in milliseconds instead of
            // seconds.  This nets us more precision as well as simplifying 64-bit time.
            logMessageQuery.bindValue(":time", msg.timestamp().toMSecsSinceEpoch());
            logMessageQuery.bindValue(":bufferid", msg.bufferInfo().bufferId().toInt());
            logMessageQuery.bindValue(":type", msg.type());
            logMessageQuery.bindValue(":flags", (int)msg.flags());
            logMessageQuery.bindValue(":sender", msg.sender());
            logMessageQuery.bindValue(":realname", msg.realName());
            logMessageQuery.bindValue(":avatarurl", msg.avatarUrl());
            logMessageQuery.bindValue(":senderprefixes", msg.senderPrefixes());
            logMessageQuery.bindValue(":message", msg.contents());

            safeExec(logMessageQuery);
            if (!watchQuery(logMessageQuery)) {
                error = true;
                break;
            }
            else {
                msg.setMsgId(logMessageQuery.lastInsertId().toLongLong());
            }
        }
    }

    if (error) {
        db.rollback();
        unlock();
        // we had a rollback in the db so we need to reset all msgIds
        for (int i = 0; i < msgs.count(); i++) {
            msgs[i].setMsgId(MsgId());
        }
    }
    else {
        db.commit();
        unlock();
    }
    return !error;
}

std::vector<Message> SqliteStorage::requestMsgs(UserId user, BufferId bufferId, MsgId first, MsgId last, int limit)
{
    std::vector<Message> messagelist;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    BufferInfo bufferInfo;
    {
        // code duplication from getBufferInfo:
        // this is due to the impossibility of nesting transactions and recursive locking
        QSqlQuery bufferInfoQuery(db);
        bufferInfoQuery.prepare(queryString("select_buffer_by_id"));
        bufferInfoQuery.bindValue(":userid", user.toInt());
        bufferInfoQuery.bindValue(":bufferid", bufferId.toInt());

        lockForRead();
        safeExec(bufferInfoQuery);
        error = !watchQuery(bufferInfoQuery) || !bufferInfoQuery.first();
        if (!error) {
            bufferInfo = BufferInfo(bufferInfoQuery.value(0).toInt(),
                                    bufferInfoQuery.value(1).toInt(),
                                    (BufferInfo::Type)bufferInfoQuery.value(2).toInt(),
                                    0,
                                    bufferInfoQuery.value(4).toString());
            error = !bufferInfo.isValid();
        }
    }
    if (error) {
        db.rollback();
        unlock();
        return messagelist;
    }

    {
        QSqlQuery query(db);
        if (last == -1 && first == -1) {
            query.prepare(queryString("select_messagesNewestK"));
        }
        else if (last == -1) {
            query.prepare(queryString("select_messagesNewerThan"));
            query.bindValue(":firstmsg", first.toQint64());
        }
        else {
            query.prepare(queryString("select_messagesRange"));
            query.bindValue(":lastmsg", last.toQint64());
            query.bindValue(":firstmsg", first.toQint64());
        }
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":limit", limit);

        safeExec(query);
        watchQuery(query);

        while (query.next()) {
            Message msg(
                // As of SQLite schema version 31, timestamps are stored in milliseconds instead of
                // seconds.  This nets us more precision as well as simplifying 64-bit time.
                QDateTime::fromMSecsSinceEpoch(query.value(1).toLongLong()),
                bufferInfo,
                (Message::Type)query.value(2).toInt(),
                query.value(8).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toString(),
                query.value(7).toString(),
                (Message::Flags)query.value(3).toInt());
            msg.setMsgId(query.value(0).toLongLong());
            messagelist.push_back(std::move(msg));
        }
    }
    db.commit();
    unlock();

    return messagelist;
}

std::vector<Message> SqliteStorage::requestMsgsFiltered(
    UserId user, BufferId bufferId, MsgId first, MsgId last, int limit, Message::Types type, Message::Flags flags)
{
    std::vector<Message> messagelist;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    BufferInfo bufferInfo;
    {
        // code dupication from getBufferInfo:
        // this is due to the impossibility of nesting transactions and recursive locking
        QSqlQuery bufferInfoQuery(db);
        bufferInfoQuery.prepare(queryString("select_buffer_by_id"));
        bufferInfoQuery.bindValue(":userid", user.toInt());
        bufferInfoQuery.bindValue(":bufferid", bufferId.toInt());

        lockForRead();
        safeExec(bufferInfoQuery);
        error = !watchQuery(bufferInfoQuery) || !bufferInfoQuery.first();
        if (!error) {
            bufferInfo = BufferInfo(bufferInfoQuery.value(0).toInt(),
                                    bufferInfoQuery.value(1).toInt(),
                                    (BufferInfo::Type)bufferInfoQuery.value(2).toInt(),
                                    0,
                                    bufferInfoQuery.value(4).toString());
            error = !bufferInfo.isValid();
        }
    }
    if (error) {
        db.rollback();
        unlock();
        return messagelist;
    }

    {
        QSqlQuery query(db);
        if (last == -1 && first == -1) {
            query.prepare(queryString("select_messagesNewestK_filtered"));
        }
        else if (last == -1) {
            query.prepare(queryString("select_messagesNewerThan_filtered"));
            query.bindValue(":firstmsg", first.toQint64());
        }
        else {
            query.prepare(queryString("select_messagesRange_filtered"));
            query.bindValue(":lastmsg", last.toQint64());
            query.bindValue(":firstmsg", first.toQint64());
        }
        query.bindValue(":bufferid", bufferId.toInt());
        query.bindValue(":limit", limit);
        int typeRaw = type;
        query.bindValue(":type", typeRaw);
        int flagsRaw = flags;
        query.bindValue(":flags", flagsRaw);

        safeExec(query);
        watchQuery(query);

        while (query.next()) {
            Message msg(
                // As of SQLite schema version 31, timestamps are stored in milliseconds
                // instead of seconds.  This nets us more precision as well as simplifying
                // 64-bit time.
                QDateTime::fromMSecsSinceEpoch(query.value(1).toLongLong()),
                bufferInfo,
                (Message::Type)query.value(2).toInt(),
                query.value(8).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toString(),
                query.value(7).toString(),
                Message::Flags{query.value(3).toInt()});
            msg.setMsgId(query.value(0).toLongLong());
            messagelist.push_back(std::move(msg));
        }
    }
    db.commit();
    unlock();

    return messagelist;
}

std::vector<Message> SqliteStorage::requestMsgsForward(
    UserId user, BufferId bufferId, MsgId first, MsgId last, int limit, Message::Types type, Message::Flags flags)
{
    std::vector<Message> messagelist;

    QSqlDatabase db = logDb();
    db.transaction();

    bool error = false;
    BufferInfo bufferInfo;
    {
        // code dupication from getBufferInfo:
        // this is due to the impossibility of nesting transactions and recursive locking
        QSqlQuery bufferInfoQuery(db);
        bufferInfoQuery.prepare(queryString("select_buffer_by_id"));
        bufferInfoQuery.bindValue(":userid", user.toInt());
        bufferInfoQuery.bindValue(":bufferid", bufferId.toInt());

        lockForRead();
        safeExec(bufferInfoQuery);
        error = !watchQuery(bufferInfoQuery) || !bufferInfoQuery.first();
        if (!error) {
            bufferInfo = BufferInfo(bufferInfoQuery.value(0).toInt(),
                                    bufferInfoQuery.value(1).toInt(),
                                    (BufferInfo::Type)bufferInfoQuery.value(2).toInt(),
                                    0,
                                    bufferInfoQuery.value(4).toString());
            error = !bufferInfo.isValid();
        }
    }
    if (error) {
        db.rollback();
        unlock();
        return messagelist;
    }

    {
        QSqlQuery query(db);
        query.prepare(queryString("select_messagesForward"));

        if (first == -1) {
            query.bindValue(":firstmsg", std::numeric_limits<qint64>::min());
        }
        else {
            query.bindValue(":firstmsg", first.toQint64());
        }

        if (last == -1) {
            query.bindValue(":lastmsg", std::numeric_limits<qint64>::max());
        }
        else {
            query.bindValue(":lastmsg", last.toQint64());
        }

        query.bindValue(":bufferid", bufferId.toInt());

        int typeRaw = type;
        int flagsRaw = flags;
        query.bindValue(":type", typeRaw);
        query.bindValue(":flags", flagsRaw);

        query.bindValue(":limit", limit);

        safeExec(query);
        watchQuery(query);

        while (query.next()) {
            Message msg(
                // As of SQLite schema version 31, timestamps are stored in milliseconds
                // instead of seconds.  This nets us more precision as well as simplifying
                // 64-bit time.
                QDateTime::fromMSecsSinceEpoch(query.value(1).toLongLong()),
                bufferInfo,
                (Message::Type)query.value(2).toInt(),
                query.value(8).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toString(),
                query.value(7).toString(),
                Message::Flags{query.value(3).toInt()});
            msg.setMsgId(query.value(0).toLongLong());
            messagelist.push_back(std::move(msg));
        }
    }
    db.commit();
    unlock();

    return messagelist;
}

std::vector<Message> SqliteStorage::requestAllMsgs(UserId user, MsgId first, MsgId last, int limit)
{
    std::vector<Message> messagelist;

    QSqlDatabase db = logDb();
    db.transaction();

    QHash<BufferId, BufferInfo> bufferInfoHash;
    {
        QSqlQuery bufferInfoQuery(db);
        bufferInfoQuery.prepare(queryString("select_buffers"));
        bufferInfoQuery.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(bufferInfoQuery);
        watchQuery(bufferInfoQuery);
        while (bufferInfoQuery.next()) {
            BufferInfo bufferInfo = BufferInfo(bufferInfoQuery.value(0).toInt(),
                                               bufferInfoQuery.value(1).toInt(),
                                               (BufferInfo::Type)bufferInfoQuery.value(2).toInt(),
                                               bufferInfoQuery.value(3).toInt(),
                                               bufferInfoQuery.value(4).toString());
            bufferInfoHash[bufferInfo.bufferId()] = bufferInfo;
        }

        QSqlQuery query(db);
        if (last == -1) {
            query.prepare(queryString("select_messagesAllNew"));
        }
        else {
            query.prepare(queryString("select_messagesAll"));
            query.bindValue(":lastmsg", last.toQint64());
        }
        query.bindValue(":userid", user.toInt());
        query.bindValue(":firstmsg", first.toQint64());
        query.bindValue(":limit", limit);
        safeExec(query);

        watchQuery(query);

        while (query.next()) {
            Message msg(
                // As of SQLite schema version 31, timestamps are stored in milliseconds instead of
                // seconds.  This nets us more precision as well as simplifying 64-bit time.
                QDateTime::fromMSecsSinceEpoch(query.value(2).toLongLong()),
                bufferInfoHash[query.value(1).toInt()],
                (Message::Type)query.value(3).toInt(),
                query.value(9).toString(),
                query.value(5).toString(),
                query.value(6).toString(),
                query.value(7).toString(),
                query.value(8).toString(),
                (Message::Flags)query.value(4).toInt());
            msg.setMsgId(query.value(0).toLongLong());
            messagelist.push_back(std::move(msg));
        }
    }
    db.commit();
    unlock();
    return messagelist;
}

std::vector<Message> SqliteStorage::requestAllMsgsFiltered(
    UserId user, MsgId first, MsgId last, int limit, Message::Types type, Message::Flags flags)
{
    std::vector<Message> messagelist;

    QSqlDatabase db = logDb();
    db.transaction();

    QHash<BufferId, BufferInfo> bufferInfoHash;
    {
        QSqlQuery bufferInfoQuery(db);
        bufferInfoQuery.prepare(queryString("select_buffers"));
        bufferInfoQuery.bindValue(":userid", user.toInt());

        lockForRead();
        safeExec(bufferInfoQuery);
        watchQuery(bufferInfoQuery);
        while (bufferInfoQuery.next()) {
            BufferInfo bufferInfo = BufferInfo(bufferInfoQuery.value(0).toInt(),
                                               bufferInfoQuery.value(1).toInt(),
                                               (BufferInfo::Type)bufferInfoQuery.value(2).toInt(),
                                               bufferInfoQuery.value(3).toInt(),
                                               bufferInfoQuery.value(4).toString());
            bufferInfoHash[bufferInfo.bufferId()] = bufferInfo;
        }

        QSqlQuery query(db);
        if (last == -1) {
            query.prepare(queryString("select_messagesAllNew_filtered"));
        }
        else {
            query.prepare(queryString("select_messagesAll_filtered"));
            query.bindValue(":lastmsg", last.toQint64());
        }
        query.bindValue(":userid", user.toInt());
        query.bindValue(":firstmsg", first.toQint64());
        query.bindValue(":limit", limit);
        int typeRaw = type;
        query.bindValue(":type", typeRaw);
        int flagsRaw = flags;
        query.bindValue(":flags", flagsRaw);
        safeExec(query);

        watchQuery(query);

        while (query.next()) {
            Message msg(
                // As of SQLite schema version 31, timestamps are stored in milliseconds
                // instead of seconds.  This nets us more precision as well as simplifying
                // 64-bit time.
                QDateTime::fromMSecsSinceEpoch(query.value(2).toLongLong()),
                bufferInfoHash[query.value(1).toInt()],
                (Message::Type)query.value(3).toInt(),
                query.value(9).toString(),
                query.value(5).toString(),
                query.value(6).toString(),
                query.value(7).toString(),
                query.value(8).toString(),
                Message::Flags{query.value(4).toInt()});
            msg.setMsgId(query.value(0).toLongLong());
            messagelist.push_back(std::move(msg));
        }
    }
    db.commit();
    unlock();
    return messagelist;
}

QMap<UserId, QString> SqliteStorage::getAllAuthUserNames()
{
    QMap<UserId, QString> authusernames;

    QSqlDatabase db = logDb();
    db.transaction();
    {
        QSqlQuery query(db);
        query.prepare(queryString("select_all_authusernames"));

        lockForRead();
        safeExec(query);
        watchQuery(query);
        while (query.next()) {
            authusernames[query.value(0).toInt()] = query.value(1).toString();
        }
    }
    db.commit();
    unlock();
    return authusernames;
}

QString SqliteStorage::backlogFile()
{
    return Quassel::configDirPath() + "quassel-storage.sqlite";
}

bool SqliteStorage::safeExec(QSqlQuery& query, int retryCount)
{
    query.exec();

    if (!query.lastError().isValid())
        return true;

    QString nativeErrorCode = query.lastError().nativeErrorCode();

    // SQLITE_BUSY         5   /* The database file is locked */
    // SQLITE_LOCKED       6   /* A table in the database is locked */
    if (nativeErrorCode == QLatin1String{"5"} || nativeErrorCode == QLatin1String{"6"}) {
        if (retryCount < _maxRetryCount)
            return safeExec(query, retryCount + 1);
    }
    return false;
}

// ========================================
//  SqliteMigration
// ========================================
SqliteMigrationReader::SqliteMigrationReader()
    : SqliteStorage()
{
}

void SqliteMigrationReader::setMaxId(MigrationObject mo)
{
    QString queryString;
    switch (mo) {
    case Sender:
        queryString = "SELECT max(senderid) FROM sender";
        break;
    case Backlog:
        queryString = "SELECT max(messageid) FROM backlog";
        break;
    default:
        _maxId = 0;
        return;
    }
    QSqlQuery query(logDb());
    query.prepare(queryString);
    query.exec();
    query.first();
    _maxId = query.value(0).toLongLong();
}

bool SqliteMigrationReader::prepareQuery(MigrationObject mo)
{
    setMaxId(mo);

    switch (mo) {
    case QuasselUser:
        newQuery(queryString("migrate_read_quasseluser"), logDb());
        break;
    case Identity:
        newQuery(queryString("migrate_read_identity"), logDb());
        break;
    case IdentityNick:
        newQuery(queryString("migrate_read_identity_nick"), logDb());
        break;
    case Network:
        newQuery(queryString("migrate_read_network"), logDb());
        break;
    case Buffer:
        newQuery(queryString("migrate_read_buffer"), logDb());
        break;
    case Sender:
        newQuery(queryString("migrate_read_sender"), logDb());
        bindValue(0, 0);
        bindValue(1, stepSize());
        break;
    case Backlog:
        newQuery(queryString("migrate_read_backlog"), logDb());
        bindValue(0, 0);
        bindValue(1, stepSize());
        break;
    case IrcServer:
        newQuery(queryString("migrate_read_ircserver"), logDb());
        break;
    case UserSetting:
        newQuery(queryString("migrate_read_usersetting"), logDb());
        break;
    case CoreState:
        newQuery(queryString("migrate_read_corestate"), logDb());
        break;
    }
    return exec();
}

bool SqliteMigrationReader::readMo(QuasselUserMO& user)
{
    if (!next())
        return false;

    user.id = value(0).toInt();
    user.username = value(1).toString();
    user.password = value(2).toString();
    user.hashversion = value(3).toInt();
    user.authenticator = value(4).toString();
    return true;
}

bool SqliteMigrationReader::readMo(IdentityMO& identity)
{
    if (!next())
        return false;

    identity.id = value(0).toInt();
    identity.userid = value(1).toInt();
    identity.identityname = value(2).toString();
    identity.realname = value(3).toString();
    identity.awayNick = value(4).toString();
    identity.awayNickEnabled = value(5).toInt() == 1 ? true : false;
    identity.awayReason = value(6).toString();
    identity.awayReasonEnabled = value(7).toInt() == 1 ? true : false;
    identity.autoAwayEnabled = value(8).toInt() == 1 ? true : false;
    identity.autoAwayTime = value(9).toInt();
    identity.autoAwayReason = value(10).toString();
    identity.autoAwayReasonEnabled = value(11).toInt() == 1 ? true : false;
    identity.detachAwayEnabled = value(12).toInt() == 1 ? true : false;
    identity.detachAwayReason = value(13).toString();
    identity.detachAwayReasonEnabled = value(14).toInt() == 1 ? true : false;
    identity.ident = value(15).toString();
    identity.kickReason = value(16).toString();
    identity.partReason = value(17).toString();
    identity.quitReason = value(18).toString();
    identity.sslCert = value(19).toByteArray();
    identity.sslKey = value(20).toByteArray();
    return true;
}

bool SqliteMigrationReader::readMo(IdentityNickMO& identityNick)
{
    if (!next())
        return false;

    identityNick.nickid = value(0).toInt();
    identityNick.identityId = value(1).toInt();
    identityNick.nick = value(2).toString();
    return true;
}

bool SqliteMigrationReader::readMo(NetworkMO& network)
{
    if (!next())
        return false;

    network.networkid = value(0).toInt();
    network.userid = value(1).toInt();
    network.networkname = value(2).toString();
    network.identityid = value(3).toInt();
    network.encodingcodec = value(4).toString();
    network.decodingcodec = value(5).toString();
    network.servercodec = value(6).toString();
    network.userandomserver = value(7).toInt() == 1 ? true : false;
    network.perform = value(8).toString();
    network.useautoidentify = value(9).toInt() == 1 ? true : false;
    network.autoidentifyservice = value(10).toString();
    network.autoidentifypassword = value(11).toString();
    network.useautoreconnect = value(12).toInt() == 1 ? true : false;
    network.autoreconnectinterval = value(13).toInt();
    network.autoreconnectretries = value(14).toInt();
    network.unlimitedconnectretries = value(15).toInt() == 1 ? true : false;
    network.rejoinchannels = value(16).toInt() == 1 ? true : false;
    network.connected = value(17).toInt() == 1 ? true : false;
    network.usermode = value(18).toString();
    network.awaymessage = value(19).toString();
    network.attachperform = value(20).toString();
    network.detachperform = value(21).toString();
    network.usesasl = value(22).toInt() == 1 ? true : false;
    network.saslaccount = value(23).toString();
    network.saslpassword = value(24).toString();
    // Custom rate limiting
    network.usecustommessagerate = value(25).toInt() == 1 ? true : false;
    network.messagerateburstsize = value(26).toInt();
    network.messageratedelay = value(27).toUInt();
    network.unlimitedmessagerate = value(28).toInt() == 1 ? true : false;
    // Skipped IRCv3 caps
    network.skipcaps = value(29).toString();
    return true;
}

bool SqliteMigrationReader::readMo(BufferMO& buffer)
{
    if (!next())
        return false;

    buffer.bufferid = value(0).toInt();
    buffer.userid = value(1).toInt();
    buffer.groupid = value(2).toInt();
    buffer.networkid = value(3).toInt();
    buffer.buffername = value(4).toString();
    buffer.buffercname = value(5).toString();
    buffer.buffertype = value(6).toInt();
    buffer.lastmsgid = value(7).toLongLong();
    buffer.lastseenmsgid = value(8).toLongLong();
    buffer.markerlinemsgid = value(9).toLongLong();
    buffer.bufferactivity = value(10).toInt();
    buffer.highlightcount = value(11).toInt();
    buffer.key = value(12).toString();
    buffer.joined = value(13).toInt() == 1 ? true : false;
    buffer.cipher = value(14).toString();
    return true;
}

bool SqliteMigrationReader::readMo(SenderMO& sender)
{
    int skipSteps = 0;
    while (!next()) {
        if (sender.senderId < _maxId) {
            bindValue(0, sender.senderId + (skipSteps * stepSize()));
            bindValue(1, sender.senderId + ((skipSteps + 1) * stepSize()));
            skipSteps++;
            if (!exec())
                return false;
        }
        else {
            return false;
        }
    }

    sender.senderId = value(0).toLongLong();
    sender.sender = value(1).toString();
    sender.realname = value(2).toString();
    sender.avatarurl = value(3).toString();
    return true;
}

bool SqliteMigrationReader::readMo(BacklogMO& backlog)
{
    qint64 skipSteps = 0;
    while (!next()) {
        if (backlog.messageid < _maxId) {
            bindValue(0, backlog.messageid.toQint64() + (skipSteps * stepSize()));
            bindValue(1, backlog.messageid.toQint64() + ((skipSteps + 1) * stepSize()));
            skipSteps++;
            if (!exec())
                return false;
        }
        else {
            return false;
        }
    }

    backlog.messageid = value(0).toLongLong();
    // As of SQLite schema version 31, timestamps are stored in milliseconds instead of
    // seconds.  This nets us more precision as well as simplifying 64-bit time.
    backlog.time = QDateTime::fromMSecsSinceEpoch(value(1).toLongLong()).toUTC();
    backlog.bufferid = value(2).toInt();
    backlog.type = value(3).toInt();
    backlog.flags = value(4).toInt();
    backlog.senderid = value(5).toLongLong();
    backlog.senderprefixes = value(6).toString();
    backlog.message = value(7).toString();
    return true;
}

bool SqliteMigrationReader::readMo(IrcServerMO& ircserver)
{
    if (!next())
        return false;

    ircserver.serverid = value(0).toInt();
    ircserver.userid = value(1).toInt();
    ircserver.networkid = value(2).toInt();
    ircserver.hostname = value(3).toString();
    ircserver.port = value(4).toInt();
    ircserver.password = value(5).toString();
    ircserver.ssl = value(6).toInt() == 1 ? true : false;
    ircserver.sslversion = value(7).toInt();
    ircserver.useproxy = value(8).toInt() == 1 ? true : false;
    ircserver.proxytype = value(9).toInt();
    ircserver.proxyhost = value(10).toString();
    ircserver.proxyport = value(11).toInt();
    ircserver.proxyuser = value(12).toString();
    ircserver.proxypass = value(13).toString();
    ircserver.sslverify = value(14).toInt() == 1 ? true : false;
    return true;
}

bool SqliteMigrationReader::readMo(UserSettingMO& userSetting)
{
    if (!next())
        return false;

    userSetting.userid = value(0).toInt();
    userSetting.settingname = value(1).toString();
    userSetting.settingvalue = value(2).toByteArray();

    return true;
}

bool SqliteMigrationReader::readMo(CoreStateMO& coreState)
{
    if (!next())
        return false;

    coreState.key = value(0).toString();
    coreState.value = value(1).toByteArray();

    return true;
}
