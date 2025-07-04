// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "postgresqlstorage.h"

#include <vector>

#include <QByteArray>
#include <QDataStream>
#include <QMetaType>
#include <QSqlDriver>
#include <QSqlField>
#include <QTimeZone>

#include "network.h"
#include "quassel.h"

PostgreSqlStorage::PostgreSqlStorage(QObject* parent)
    : AbstractSqlStorage(parent)
{
}

std::unique_ptr<AbstractSqlMigrationWriter> PostgreSqlStorage::createMigrationWriter()
{
    auto writer = new PostgreSqlMigrationWriter();
    QVariantMap properties;
    properties["Username"] = _userName;
    properties["Password"] = _password;
    properties["Hostname"] = _hostName;
    properties["Port"] = _port;
    properties["Database"] = _databaseName;
    writer->setConnectionProperties(properties, {}, false);
    return std::unique_ptr<AbstractSqlMigrationWriter>{writer};
}

bool PostgreSqlStorage::isAvailable() const
{
    if (!QSqlDatabase::isDriverAvailable("QPSQL")) {
        qWarning() << qPrintable(tr("PostgreSQL driver plugin not available for Qt. Installed drivers:"))
                   << qPrintable(QSqlDatabase::drivers().join(", "));
        return false;
    }
    return true;
}

QString PostgreSqlStorage::backendId() const
{
    return QString("PostgreSQL");
}

QString PostgreSqlStorage::displayName() const
{
    return backendId();  // Note: Pre-0.13 clients use the displayName property for backend idenfication
}

QString PostgreSqlStorage::description() const
{
    // FIXME: proper description
    return tr("PostgreSQL Turbo Bomber HD!");
}

QVariantList PostgreSqlStorage::setupData() const
{
    QVariantList data;
    data << "Username" << tr("Username") << QString("quassel") << "Password" << tr("Password") << QString() << "Hostname" << tr("Hostname")
         << QString("localhost") << "Port" << tr("Port") << 5432 << "Database" << tr("Database") << QString("quassel");
    return data;
}

bool PostgreSqlStorage::initDbSession(QSqlDatabase& db)
{
    // check whether the Qt driver performs string escaping or not.
    // i.e. test if it doubles slashes.
    QSqlField testField("", QMetaType(QMetaType::QString));
    testField.setValue("\\");
    QString formattedString = db.driver()->formatValue(testField);
    QSqlQuery query1(db);
    QSqlQuery query2(db);
    switch (formattedString.count('\\')) {
    case 2:
        // yes it does... and we cannot do anything to change the behavior of Qt.
        // If this is a legacy DB (Postgres < 8.2), then everything is already ok,
        // as this is the expected behavior.
        // If it is a newer version, switch to legacy mode.

        qWarning() << "Switching Postgres to legacy mode. (set standard conforming strings to off)";
        // If the following calls fail, it is a legacy DB anyways, so it doesn't matter
        // and no need to check the outcome.
        query1.prepare("set standard_conforming_strings = off");
        query1.exec();

        query2.prepare("set escape_string_warning = off");
        query2.exec();
        break;
    case 1:
        // ok, so Qt does not escape...
        // That means we have to ensure that postgres uses standard conforming strings...
        {
            QSqlQuery query(db);
            query.prepare("set standard_conforming_strings = on");
            query.exec();
            if (query.lastError().isValid()) {
                // We cannot enable standard conforming strings...
                // since Quassel does no escaping by itself, this would yield a major vulnerability.
                qCritical() << "Failed to enable standard_conforming_strings for the Postgres db!";
                return false;
            }
        }
        break;
    default:
        // The slash got replaced with 0 or more than 2 slashes! o_O
        qCritical()
            << "Your version of Qt does something _VERY_ strange to slashes in QSqlQueries! You should consult your trusted doctor!";
        return false;
        break;
    }

    // Set the PostgreSQL session timezone to UTC, since we want timestamps stored in UTC
    QSqlQuery tzQuery(db);
    tzQuery.prepare("SET timezone = 'UTC'");
    tzQuery.exec();
    if (tzQuery.lastError().isValid()) {
        qCritical() << "Failed to set timezone to UTC!";
        return false;
    }

    return true;
}

void PostgreSqlStorage::setConnectionProperties(const QVariantMap& properties, const QProcessEnvironment& environment, bool loadFromEnvironment)
{
    if (loadFromEnvironment) {
        _userName = environment.value("DB_PGSQL_USERNAME");
        _password = environment.value("DB_PGSQL_PASSWORD");
        _hostName = environment.value("DB_PGSQL_HOSTNAME");
        _port = environment.value("DB_PGSQL_PORT").toInt();
        _databaseName = environment.value("DB_PGSQL_DATABASE");
    }
    else {
        _userName = properties["Username"].toString();
        _password = properties["Password"].toString();
        _hostName = properties["Hostname"].toString();
        _port = properties["Port"].toInt();
        _databaseName = properties["Database"].toString();
    }
}

int PostgreSqlStorage::installedSchemaVersion()
{
    QSqlQuery query(logDb());
    query.prepare("SELECT value FROM coreinfo WHERE key = 'schemaversion'");
    safeExec(query);
    watchQuery(query);
    if (query.first())
        return query.value(0).toInt();

    // maybe it's really old... (schema version 0)
    query.prepare("SELECT MAX(version) FROM coreinfo");
    safeExec(query);
    watchQuery(query);
    if (query.first())
        return query.value(0).toInt();

    return AbstractSqlStorage::installedSchemaVersion();
}

bool PostgreSqlStorage::updateSchemaVersion(int newVersion, bool clearUpgradeStep)
{
    // Atomically update the schema version and clear the upgrade step, if specified
    // Note: This will need reworked if "updateSchemaVersion" is ever called within a transaction.
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::updateSchemaVersion(int, bool): cannot start transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE coreinfo SET value = :version WHERE key = 'schemaversion'");
    query.bindValue(":version", newVersion);
    safeExec(query);

    if (!watchQuery(query)) {
        qCritical() << "PostgreSqlStorage::updateSchemaVersion(int, bool): Updating schema version failed!";
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

bool PostgreSqlStorage::setupSchemaVersion(int version)
{
    QSqlQuery query(logDb());
    query.prepare("INSERT INTO coreinfo (key, value) VALUES ('schemaversion', :version)");
    query.bindValue(":version", version);
    safeExec(query);

    bool success = true;
    if (!watchQuery(query)) {
        qCritical() << "PostgreSqlStorage::setupSchemaVersion(int): Updating schema version failed!";
        success = false;
    }
    return success;
}

QString PostgreSqlStorage::schemaVersionUpgradeStep()
{
    QSqlQuery query(logDb());
    query.prepare("SELECT value FROM coreinfo WHERE key = 'schemaupgradestep'");
    safeExec(query);
    watchQuery(query);
    if (query.first())
        return query.value(0).toString();

    // Fall back to the default value
    return AbstractSqlStorage::schemaVersionUpgradeStep();
}

bool PostgreSqlStorage::setSchemaVersionUpgradeStep(QString upgradeQuery)
{
    // Intentionally do not wrap in a transaction so other functions can include multiple operations

    QSqlQuery query(logDb());
    query.prepare("UPDATE coreinfo SET value = :upgradestep WHERE key = 'schemaupgradestep'");
    query.bindValue(":upgradestep", upgradeQuery);
    safeExec(query);

    // Make sure that the query didn't fail (shouldn't ever happen), and that some non-zero number
    // of rows were affected
    bool success = watchQuery(query) && query.numRowsAffected() != 0;

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

UserId PostgreSqlStorage::addUser(const QString& user, const QString& password, const QString& authenticator)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("insert_quasseluser"));
    query.bindValue(":username", user);
    query.bindValue(":password", hashPassword(password));
    query.bindValue(":hashversion", Storage::HashVersion::Latest);
    query.bindValue(":authenticator", authenticator);
    safeExec(query);
    if (!watchQuery(query))
        return 0;

    query.first();
    UserId uid = query.value(0).toInt();
    emit userAdded(uid, user);
    return uid;
}

bool PostgreSqlStorage::updateUser(UserId user, const QString& password)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_userpassword"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":password", hashPassword(password));
    query.bindValue(":hashversion", Storage::HashVersion::Latest);
    safeExec(query);
    watchQuery(query);
    return query.numRowsAffected() != 0;
}

void PostgreSqlStorage::renameUser(UserId user, const QString& newName)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_username"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":username", newName);
    safeExec(query);
    watchQuery(query);
    emit userRenamed(user, newName);
}

UserId PostgreSqlStorage::validateUser(const QString& user, const QString& password)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_authuser"));
    query.bindValue(":username", user);
    safeExec(query);
    watchQuery(query);

    if (query.first()
        && checkHashedPassword(query.value(0).toInt(),
                               password,
                               query.value(1).toString(),
                               static_cast<Storage::HashVersion>(query.value(2).toInt()))) {
        return query.value(0).toInt();
    }
    else {
        return 0;
    }
}

UserId PostgreSqlStorage::getUserId(const QString& user)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_userid"));
    query.bindValue(":username", user);
    safeExec(query);
    watchQuery(query);

    if (query.first()) {
        return query.value(0).toInt();
    }
    else {
        return 0;
    }
}

QString PostgreSqlStorage::getUserAuthenticator(const UserId userid)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_authenticator"));
    query.bindValue(":userid", userid.toInt());
    safeExec(query);
    watchQuery(query);

    if (query.first()) {
        return query.value(0).toString();
    }
    else {
        return QString("");
    }
}

UserId PostgreSqlStorage::internalUser()
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_internaluser"));
    safeExec(query);
    watchQuery(query);

    if (query.first()) {
        return query.value(0).toInt();
    }
    else {
        return 0;
    }
}

void PostgreSqlStorage::delUser(UserId user)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::delUser(): cannot start transaction!";
        return;
    }

    QSqlQuery query(db);
    query.prepare(queryString("delete_quasseluser"));
    query.bindValue(":userid", user.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return;
    }
    else {
        db.commit();
        emit userRemoved(user);
    }
}

void PostgreSqlStorage::setUserSetting(UserId userId, const QString& settingName, const QVariant& data)
{
    QByteArray rawData;
    QDataStream out(&rawData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << data;

    QSqlDatabase db = logDb();
    QSqlQuery selectQuery(db);
    selectQuery.prepare(queryString("select_user_setting"));
    selectQuery.bindValue(":userid", userId.toInt());
    selectQuery.bindValue(":settingname", settingName);
    safeExec(selectQuery);
    watchQuery(selectQuery);

    QString setQueryString;
    if (!selectQuery.first()) {
        setQueryString = queryString("insert_user_setting");
    }
    else {
        setQueryString = queryString("update_user_setting");
    }

    QSqlQuery setQuery(db);
    setQuery.prepare(setQueryString);
    setQuery.bindValue(":userid", userId.toInt());
    setQuery.bindValue(":settingname", settingName);
    setQuery.bindValue(":settingvalue", rawData);
    safeExec(setQuery);
    watchQuery(setQuery);
}

QVariant PostgreSqlStorage::getUserSetting(UserId userId, const QString& settingName, const QVariant& defaultData)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_user_setting"));
    query.bindValue(":userid", userId.toInt());
    query.bindValue(":settingname", settingName);
    safeExec(query);
    watchQuery(query);

    if (query.first()) {
        QVariant data;
        QByteArray rawData = query.value(0).toByteArray();
        QDataStream in(&rawData, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_4_2);
        in >> data;
        return data;
    }
    else {
        return defaultData;
    }
}

void PostgreSqlStorage::setCoreState(const QVariantList& data)
{
    QByteArray rawData;
    QDataStream out(&rawData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << data;

    QSqlDatabase db = logDb();
    QSqlQuery selectQuery(db);
    selectQuery.prepare(queryString("select_core_state"));
    selectQuery.bindValue(":key", "active_sessions");
    safeExec(selectQuery);
    watchQuery(selectQuery);

    QString setQueryString;
    if (!selectQuery.first()) {
        setQueryString = queryString("insert_core_state");
    }
    else {
        setQueryString = queryString("update_core_state");
    }

    QSqlQuery setQuery(db);
    setQuery.prepare(setQueryString);
    setQuery.bindValue(":key", "active_sessions");
    setQuery.bindValue(":value", rawData);
    safeExec(setQuery);
    watchQuery(setQuery);
}

QVariantList PostgreSqlStorage::getCoreState(const QVariantList& defaultData)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_core_state"));
    query.bindValue(":key", "active_sessions");
    safeExec(query);
    watchQuery(query);

    if (query.first()) {
        QVariantList data;
        QByteArray rawData = query.value(0).toByteArray();
        QDataStream in(&rawData, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_4_2);
        in >> data;
        return data;
    }
    else {
        return defaultData;
    }
}

IdentityId PostgreSqlStorage::createIdentity(UserId user, CoreIdentity& identity)
{
    IdentityId identityId;

    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::createIdentity(): Unable to start Transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return identityId;
    }

    QSqlQuery query(db);
    query.prepare(queryString("insert_identity"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":identityname", identity.identityName());
    query.bindValue(":realname", identity.realName());
    query.bindValue(":awaynick", identity.awayNick());
    query.bindValue(":awaynickenabled", identity.awayNickEnabled());
    query.bindValue(":awayreason", identity.awayReason());
    query.bindValue(":awayreasonenabled", identity.awayReasonEnabled());
    query.bindValue(":autoawayenabled", identity.awayReasonEnabled());
    query.bindValue(":autoawaytime", identity.autoAwayTime());
    query.bindValue(":autoawayreason", identity.autoAwayReason());
    query.bindValue(":autoawayreasonenabled", identity.autoAwayReasonEnabled());
    query.bindValue(":detachawayenabled", identity.detachAwayEnabled());
    query.bindValue(":detachawayreason", identity.detachAwayReason());
    query.bindValue(":detachawayreasonenabled", identity.detachAwayReasonEnabled());
    query.bindValue(":ident", identity.ident());
    query.bindValue(":kickreason", identity.kickReason());
    query.bindValue(":partreason", identity.partReason());
    query.bindValue(":quitreason", identity.quitReason());
    query.bindValue(":sslcert", identity.sslCert().toPem());
    query.bindValue(":sslkey", identity.sslKey().toPem());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return {};
    }

    query.first();
    identityId = query.value(0).toInt();
    identity.setId(identityId);

    if (!identityId.isValid()) {
        db.rollback();
        return {};
    }

    QSqlQuery insertNickQuery(db);
    insertNickQuery.prepare(queryString("insert_nick"));
    foreach (QString nick, identity.nicks()) {
        insertNickQuery.bindValue(":identityid", identityId.toInt());
        insertNickQuery.bindValue(":nick", nick);
        safeExec(insertNickQuery);
        if (!watchQuery(insertNickQuery)) {
            db.rollback();
            return {};
        }
    }

    if (!db.commit()) {
        qWarning() << "PostgreSqlStorage::createIdentity(): committing data failed!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return {};
    }
    return identityId;
}

bool PostgreSqlStorage::updateIdentity(UserId user, const CoreIdentity& identity)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::updateIdentity(): Unable to start Transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }

    QSqlQuery checkQuery(db);
    checkQuery.prepare(queryString("select_checkidentity"));
    checkQuery.bindValue(":identityid", identity.id().toInt());
    checkQuery.bindValue(":userid", user.toInt());
    safeExec(checkQuery);
    watchQuery(checkQuery);

    // there should be exactly one identity for the given id and user
    if (!checkQuery.first() || checkQuery.value(0).toInt() != 1) {
        db.rollback();
        return false;
    }

    QSqlQuery query(db);
    query.prepare(queryString("update_identity"));
    query.bindValue(":identityname", identity.identityName());
    query.bindValue(":realname", identity.realName());
    query.bindValue(":awaynick", identity.awayNick());
    query.bindValue(":awaynickenabled", identity.awayNickEnabled());
    query.bindValue(":awayreason", identity.awayReason());
    query.bindValue(":awayreasonenabled", identity.awayReasonEnabled());
    query.bindValue(":autoawayenabled", identity.awayReasonEnabled());
    query.bindValue(":autoawaytime", identity.autoAwayTime());
    query.bindValue(":autoawayreason", identity.autoAwayReason());
    query.bindValue(":autoawayreasonenabled", identity.autoAwayReasonEnabled());
    query.bindValue(":detachawayenabled", identity.detachAwayEnabled());
    query.bindValue(":detachawayreason", identity.detachAwayReason());
    query.bindValue(":detachawayreasonenabled", identity.detachAwayReasonEnabled());
    query.bindValue(":ident", identity.ident());
    query.bindValue(":kickreason", identity.kickReason());
    query.bindValue(":partreason", identity.partReason());
    query.bindValue(":quitreason", identity.quitReason());
    query.bindValue(":sslcert", identity.sslCert().toPem());
    query.bindValue(":sslkey", identity.sslKey().toPem());
    query.bindValue(":identityid", identity.id().toInt());

    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return false;
    }

    QSqlQuery deleteNickQuery(db);
    deleteNickQuery.prepare(queryString("delete_nicks"));
    deleteNickQuery.bindValue(":identityid", identity.id().toInt());
    safeExec(deleteNickQuery);
    if (!watchQuery(deleteNickQuery)) {
        db.rollback();
        return false;
    }

    QSqlQuery insertNickQuery(db);
    insertNickQuery.prepare(queryString("insert_nick"));
    foreach (QString nick, identity.nicks()) {
        insertNickQuery.bindValue(":identityid", identity.id().toInt());
        insertNickQuery.bindValue(":nick", nick);
        safeExec(insertNickQuery);
        if (!watchQuery(insertNickQuery)) {
            db.rollback();
            return false;
        }
    }

    if (!db.commit()) {
        qWarning() << "PostgreSqlStorage::updateIdentity(): committing data failed!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }
    return true;
}

void PostgreSqlStorage::removeIdentity(UserId user, IdentityId identityId)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::removeIdentity(): Unable to start Transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare(queryString("delete_identity"));
    query.bindValue(":identityid", identityId.toInt());
    query.bindValue(":userid", user.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
    }
    else {
        db.commit();
    }
}

std::vector<CoreIdentity> PostgreSqlStorage::identities(UserId user)
{
    std::vector<CoreIdentity> identities;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::identites(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return identities;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_identities"));
    query.bindValue(":userid", user.toInt());

    QSqlQuery nickQuery(db);
    nickQuery.prepare(queryString("select_nicks"));

    safeExec(query);
    watchQuery(query);

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
        identity.setNicks(nicks);
        identities.push_back(std::move(identity));
    }
    db.commit();
    return identities;
}

NetworkId PostgreSqlStorage::createNetwork(UserId user, const NetworkInfo& info)
{
    NetworkId networkId;

    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::createNetwork(): failed to begin transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }

    QSqlQuery query(db);
    query.prepare(queryString("insert_network"));
    query.bindValue(":userid", user.toInt());
    bindNetworkInfo(query, info);
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return {};
    }

    query.first();
    networkId = query.value(0).toInt();

    if (!networkId.isValid()) {
        db.rollback();
        return {};
    }

    QSqlQuery insertServersQuery(db);
    insertServersQuery.prepare(queryString("insert_server"));
    foreach (Network::Server server, info.serverList) {
        insertServersQuery.bindValue(":userid", user.toInt());
        insertServersQuery.bindValue(":networkid", networkId.toInt());
        bindServerInfo(insertServersQuery, server);
        safeExec(insertServersQuery);
        if (!watchQuery(insertServersQuery)) {
            db.rollback();
            return {};
        }
    }

    if (!db.commit()) {
        qWarning() << "PostgreSqlStorage::createNetwork(): committing data failed!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return {};
    }
    return networkId;
}

void PostgreSqlStorage::bindNetworkInfo(QSqlQuery& query, const NetworkInfo& info)
{
    query.bindValue(":networkname", info.networkName);
    query.bindValue(":identityid", info.identity.isValid() ? info.identity.toInt() : QVariant());
    query.bindValue(":encodingcodec", QString(info.codecForEncoding));
    query.bindValue(":decodingcodec", QString(info.codecForDecoding));
    query.bindValue(":servercodec", QString(info.codecForServer));
    query.bindValue(":userandomserver", info.useRandomServer);
    query.bindValue(":perform", info.perform.join("\n"));
    query.bindValue(":useautoidentify", info.useAutoIdentify);
    query.bindValue(":autoidentifyservice", info.autoIdentifyService);
    query.bindValue(":autoidentifypassword", info.autoIdentifyPassword);
    query.bindValue(":usesasl", info.useSasl);
    query.bindValue(":saslaccount", info.saslAccount);
    query.bindValue(":saslpassword", info.saslPassword);
    query.bindValue(":useautoreconnect", info.useAutoReconnect);
    query.bindValue(":autoreconnectinterval", info.autoReconnectInterval);
    query.bindValue(":autoreconnectretries", info.autoReconnectRetries);
    query.bindValue(":unlimitedconnectretries", info.unlimitedReconnectRetries);
    query.bindValue(":rejoinchannels", info.rejoinChannels);
    // Custom rate limiting
    query.bindValue(":usecustomessagerate", info.useCustomMessageRate);
    query.bindValue(":messagerateburstsize", info.messageRateBurstSize);
    query.bindValue(":messageratedelay", info.messageRateDelay);
    query.bindValue(":unlimitedmessagerate", info.unlimitedMessageRate);
    query.bindValue(":skipcaps", info.skipCapsToString());

    if (info.networkId.isValid())
        query.bindValue(":networkid", info.networkId.toInt());
}

void PostgreSqlStorage::bindServerInfo(QSqlQuery& query, const Network::Server& server)
{
    query.bindValue(":hostname", server.host);
    query.bindValue(":port", server.port);
    query.bindValue(":password", server.password);
    query.bindValue(":ssl", server.useSsl);
    query.bindValue(":sslversion", server.sslVersion);
    query.bindValue(":useproxy", server.useProxy);
    query.bindValue(":proxytype", server.proxyType);
    query.bindValue(":proxyhost", server.proxyHost);
    query.bindValue(":proxyport", server.proxyPort);
    query.bindValue(":proxyuser", server.proxyUser);
    query.bindValue(":proxypass", server.proxyPass);
    query.bindValue(":sslverify", server.sslVerify);
}

bool PostgreSqlStorage::updateNetwork(UserId user, const NetworkInfo& info)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::updateNetwork(): failed to begin transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }

    QSqlQuery updateQuery(db);
    updateQuery.prepare(queryString("update_network"));
    updateQuery.bindValue(":userid", user.toInt());
    bindNetworkInfo(updateQuery, info);
    safeExec(updateQuery);
    if (!watchQuery(updateQuery)) {
        db.rollback();
        return false;
    }
    if (updateQuery.numRowsAffected() != 1) {
        // seems this is not our network...
        db.rollback();
        return false;
    }

    QSqlQuery dropServersQuery(db);
    dropServersQuery.prepare("DELETE FROM ircserver WHERE networkid = :networkid");
    dropServersQuery.bindValue(":networkid", info.networkId.toInt());
    safeExec(dropServersQuery);
    if (!watchQuery(dropServersQuery)) {
        db.rollback();
        return false;
    }

    QSqlQuery insertServersQuery(db);
    insertServersQuery.prepare(queryString("insert_server"));
    foreach (Network::Server server, info.serverList) {
        insertServersQuery.bindValue(":userid", user.toInt());
        insertServersQuery.bindValue(":networkid", info.networkId.toInt());
        bindServerInfo(insertServersQuery, server);
        safeExec(insertServersQuery);
        if (!watchQuery(insertServersQuery)) {
            db.rollback();
            return false;
        }
    }

    if (!db.commit()) {
        qWarning() << "PostgreSqlStorage::updateNetwork(): committing data failed!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }
    return true;
}

bool PostgreSqlStorage::removeNetwork(UserId user, const NetworkId& networkId)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::removeNetwork(): cannot start transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }

    QSqlQuery query(db);
    query.prepare(queryString("delete_network"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return false;
    }

    db.commit();
    return true;
}

std::vector<NetworkInfo> PostgreSqlStorage::networks(UserId user)
{
    std::vector<NetworkInfo> nets;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::networks(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return nets;
    }

    QSqlQuery networksQuery(db);
    networksQuery.prepare(queryString("select_networks_for_user"));
    networksQuery.bindValue(":userid", user.toInt());

    QSqlQuery serversQuery(db);
    serversQuery.prepare(queryString("select_servers_for_network"));

    safeExec(networksQuery);
    if (!watchQuery(networksQuery)) {
        db.rollback();
        return nets;
    }

    while (networksQuery.next()) {
        NetworkInfo net;
        net.networkId = networksQuery.value(0).toInt();
        net.networkName = networksQuery.value(1).toString();
        net.identity = networksQuery.value(2).toInt();
        net.codecForServer = networksQuery.value(3).toString().toLatin1();
        net.codecForEncoding = networksQuery.value(4).toString().toLatin1();
        net.codecForDecoding = networksQuery.value(5).toString().toLatin1();
        net.useRandomServer = networksQuery.value(6).toBool();
        net.perform = networksQuery.value(7).toString().split("\n");
        net.useAutoIdentify = networksQuery.value(8).toBool();
        net.autoIdentifyService = networksQuery.value(9).toString();
        net.autoIdentifyPassword = networksQuery.value(10).toString();
        net.useAutoReconnect = networksQuery.value(11).toBool();
        net.autoReconnectInterval = networksQuery.value(12).toUInt();
        net.autoReconnectRetries = networksQuery.value(13).toInt();
        net.unlimitedReconnectRetries = networksQuery.value(14).toBool();
        net.rejoinChannels = networksQuery.value(15).toBool();
        net.useSasl = networksQuery.value(16).toBool();
        net.saslAccount = networksQuery.value(17).toString();
        net.saslPassword = networksQuery.value(18).toString();
        // Custom rate limiting
        net.useCustomMessageRate = networksQuery.value(19).toBool();
        net.messageRateBurstSize = networksQuery.value(20).toUInt();
        net.messageRateDelay = networksQuery.value(21).toUInt();
        net.unlimitedMessageRate = networksQuery.value(22).toBool();
        net.skipCapsFromString(networksQuery.value(23).toString());

        serversQuery.bindValue(":networkid", net.networkId.toInt());
        safeExec(serversQuery);
        if (!watchQuery(serversQuery)) {
            db.rollback();
            return nets;
        }

        Network::ServerList servers;
        while (serversQuery.next()) {
            Network::Server server;
            server.host = serversQuery.value(0).toString();
            server.port = serversQuery.value(1).toUInt();
            server.password = serversQuery.value(2).toString();
            server.useSsl = serversQuery.value(3).toBool();
            server.sslVersion = serversQuery.value(4).toInt();
            server.useProxy = serversQuery.value(5).toBool();
            server.proxyType = serversQuery.value(6).toInt();
            server.proxyHost = serversQuery.value(7).toString();
            server.proxyPort = serversQuery.value(8).toUInt();
            server.proxyUser = serversQuery.value(9).toString();
            server.proxyPass = serversQuery.value(10).toString();
            server.sslVerify = serversQuery.value(11).toBool();
            servers << server;
        }
        net.serverList = servers;
        nets.push_back(std::move(net));
    }
    db.commit();
    return nets;
}

std::vector<NetworkId> PostgreSqlStorage::connectedNetworks(UserId user)
{
    std::vector<NetworkId> connectedNets;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::connectedNetworks(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return connectedNets;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_connected_networks"));
    query.bindValue(":userid", user.toInt());
    safeExec(query);
    watchQuery(query);

    while (query.next()) {
        connectedNets.emplace_back(query.value(0).toInt());
    }

    db.commit();
    return connectedNets;
}

void PostgreSqlStorage::setNetworkConnected(UserId user, const NetworkId& networkId, bool isConnected)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_network_connected"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    query.bindValue(":connected", isConnected);
    safeExec(query);
    watchQuery(query);
}

QHash<QString, QString> PostgreSqlStorage::persistentChannels(UserId user, const NetworkId& networkId)
{
    QHash<QString, QString> persistentChans;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::persistentChannels(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return persistentChans;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_persistent_channels"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    safeExec(query);
    watchQuery(query);

    while (query.next()) {
        persistentChans[query.value(0).toString()] = query.value(1).toString();
    }

    db.commit();
    return persistentChans;
}

void PostgreSqlStorage::setChannelPersistent(UserId user, const NetworkId& networkId, const QString& channel, bool isJoined)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_buffer_persistent_channel"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    query.bindValue(":buffercname", channel.toLower());
    query.bindValue(":joined", isJoined);
    safeExec(query);
    watchQuery(query);
}

void PostgreSqlStorage::setPersistentChannelKey(UserId user, const NetworkId& networkId, const QString& channel, const QString& key)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_buffer_set_channel_key"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    query.bindValue(":buffercname", channel.toLower());
    query.bindValue(":key", key);
    safeExec(query);
    watchQuery(query);
}

QString PostgreSqlStorage::awayMessage(UserId user, NetworkId networkId)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_network_awaymsg"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    safeExec(query);
    watchQuery(query);
    QString awayMsg;
    if (query.first())
        awayMsg = query.value(0).toString();
    return awayMsg;
}

void PostgreSqlStorage::setAwayMessage(UserId user, NetworkId networkId, const QString& awayMsg)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_network_set_awaymsg"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    query.bindValue(":awaymsg", awayMsg);
    safeExec(query);
    watchQuery(query);
}

QString PostgreSqlStorage::userModes(UserId user, NetworkId networkId)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_network_usermode"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    safeExec(query);
    watchQuery(query);
    QString modes;
    if (query.first())
        modes = query.value(0).toString();
    return modes;
}

void PostgreSqlStorage::setUserModes(UserId user, NetworkId networkId, const QString& userModes)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_network_set_usermode"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    query.bindValue(":usermode", userModes);
    safeExec(query);
    watchQuery(query);
}

BufferInfo PostgreSqlStorage::bufferInfo(UserId user, const NetworkId& networkId, BufferInfo::Type type, const QString& buffer, bool create)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::bufferInfo(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return {};
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_bufferByName"));
    query.bindValue(":networkid", networkId.toInt());
    query.bindValue(":userid", user.toInt());
    query.bindValue(":buffercname", buffer.toLower());
    safeExec(query);
    watchQuery(query);

    if (query.first()) {
        BufferInfo bufferInfo = BufferInfo(query.value(0).toInt(), networkId, (BufferInfo::Type)query.value(1).toInt(), 0, buffer);
        if (query.next()) {
            qCritical() << "PostgreSqlStorage::bufferInfo(): received more then one Buffer!";
            qCritical() << "         Query:" << query.lastQuery();
            qCritical() << "  bound Values:";
            QVariantList boundValues = query.boundValues();
            for (int i = 0; i < boundValues.size(); ++i)
                qCritical() << i << ":" << boundValues[i].toString().toLatin1().data();
            Q_ASSERT(false);
        }
        db.commit();
        return bufferInfo;
    }

    if (!create) {
        db.rollback();
        return {};
    }

    QSqlQuery createQuery(db);
    createQuery.prepare(queryString("insert_buffer"));
    createQuery.bindValue(":userid", user.toInt());
    createQuery.bindValue(":networkid", networkId.toInt());
    createQuery.bindValue(":buffertype", (int)type);
    createQuery.bindValue(":buffername", buffer);
    createQuery.bindValue(":buffercname", buffer.toLower());
    createQuery.bindValue(":joined", type & BufferInfo::ChannelBuffer ? true : false);

    safeExec(createQuery);

    if (!watchQuery(createQuery)) {
        qWarning() << "PostgreSqlStorage::bufferInfo(): unable to create buffer";
        db.rollback();
        return BufferInfo();
    }

    createQuery.first();

    BufferInfo bufferInfo = BufferInfo(createQuery.value(0).toInt(), networkId, type, 0, buffer);
    db.commit();
    return bufferInfo;
}

BufferInfo PostgreSqlStorage::getBufferInfo(UserId user, const BufferId& bufferId)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_buffer_by_id"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":bufferid", bufferId.toInt());
    safeExec(query);
    if (!watchQuery(query))
        return {};

    if (!query.first())
        return {};

    BufferInfo bufferInfo(query.value(0).toInt(),
                          query.value(1).toInt(),
                          (BufferInfo::Type)query.value(2).toInt(),
                          0,
                          query.value(4).toString());
    Q_ASSERT(!query.next());

    return bufferInfo;
}

std::vector<BufferInfo> PostgreSqlStorage::requestBuffers(UserId user)
{
    std::vector<BufferInfo> bufferlist;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::requestBuffers(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return bufferlist;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_buffers"));
    query.bindValue(":userid", user.toInt());

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
    return bufferlist;
}

std::vector<BufferId> PostgreSqlStorage::requestBufferIdsForNetwork(UserId user, NetworkId networkId)
{
    std::vector<BufferId> bufferList;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::requestBufferIdsForNetwork(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return bufferList;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_buffers_for_network"));
    query.bindValue(":networkid", networkId.toInt());
    query.bindValue(":userid", user.toInt());

    safeExec(query);
    watchQuery(query);
    while (query.next()) {
        bufferList.emplace_back(query.value(0).toInt());
    }
    db.commit();
    return bufferList;
}

bool PostgreSqlStorage::removeBuffer(const UserId& user, const BufferId& bufferId)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::removeBuffer(): cannot start transaction!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare(queryString("delete_buffer_for_bufferid"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":bufferid", bufferId.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return false;
    }

    int numRows = query.numRowsAffected();
    switch (numRows) {
    case 0:
        db.commit();
        return false;
    case 1:
        db.commit();
        return true;
    default:
        // there was more then one buffer deleted...
        qWarning() << "PostgreSqlStorage::removeBuffer(): Userid" << user << "BufferId"
                   << "caused deletion of" << numRows << "Buffers! Rolling back transaction...";
        db.rollback();
        return false;
    }
}

bool PostgreSqlStorage::renameBuffer(const UserId& user, const BufferId& bufferId, const QString& newName)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::renameBuffer(): cannot start transaction!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare(queryString("update_buffer_name"));
    query.bindValue(":buffername", newName);
    query.bindValue(":buffercname", newName.toLower());
    query.bindValue(":userid", user.toInt());
    query.bindValue(":bufferid", bufferId.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return false;
    }

    int numRows = query.numRowsAffected();
    switch (numRows) {
    case 0:
        db.commit();
        return false;
    case 1:
        db.commit();
        return true;
    default:
        // there was more then one buffer deleted...
        qWarning() << "PostgreSqlStorage::renameBuffer(): Userid" << user << "BufferId"
                   << "affected" << numRows << "Buffers! Rolling back transaction...";
        db.rollback();
        return false;
    }
}

bool PostgreSqlStorage::mergeBuffersPermanently(const UserId& user, const BufferId& bufferId1, const BufferId& bufferId2)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::mergeBuffersPermanently(): cannot start transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }

    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT count(*) FROM buffer "
                       "WHERE userid = :userid AND bufferid IN (:buffer1, :buffer2)");
    checkQuery.bindValue(":userid", user.toInt());
    checkQuery.bindValue(":buffer1", bufferId1.toInt());
    checkQuery.bindValue(":buffer2", bufferId2.toInt());
    safeExec(checkQuery);
    if (!watchQuery(checkQuery)) {
        db.rollback();
        return false;
    }
    checkQuery.first();
    if (checkQuery.value(0).toInt() != 2) {
        db.rollback();
        return false;
    }

    QSqlQuery query(db);
    query.prepare(queryString("update_backlog_bufferid"));
    query.bindValue(":oldbufferid", bufferId2.toInt());
    query.bindValue(":newbufferid", bufferId1.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return false;
    }

    QSqlQuery delBufferQuery(logDb());
    delBufferQuery.prepare(queryString("delete_buffer_for_bufferid"));
    delBufferQuery.bindValue(":userid", user.toInt());
    delBufferQuery.bindValue(":bufferid", bufferId2.toInt());
    safeExec(delBufferQuery);
    if (!watchQuery(delBufferQuery)) {
        db.rollback();
        return false;
    }

    db.commit();
    return true;
}

QHash<BufferId, MsgId> PostgreSqlStorage::bufferLastMsgIds(UserId user)
{
    QHash<BufferId, MsgId> lastMsgHash;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::bufferLastMsgIds(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return lastMsgHash;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_buffer_last_messages"));
    query.bindValue(":userid", user.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return lastMsgHash;
    }

    while (query.next()) {
        lastMsgHash[query.value(0).toInt()] = query.value(1).toLongLong();
    }

    db.commit();
    return lastMsgHash;
}

void PostgreSqlStorage::setBufferLastSeenMsg(UserId user, const BufferId& bufferId, const MsgId& msgId)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_buffer_lastseen"));

    query.bindValue(":userid", user.toInt());
    query.bindValue(":bufferid", bufferId.toInt());
    query.bindValue(":lastseenmsgid", msgId.toQint64());
    safeExec(query);
    watchQuery(query);
}

QHash<BufferId, MsgId> PostgreSqlStorage::bufferLastSeenMsgIds(UserId user)
{
    QHash<BufferId, MsgId> lastSeenHash;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::bufferLastSeenMsgIds(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return lastSeenHash;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_buffer_lastseen_messages"));
    query.bindValue(":userid", user.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return lastSeenHash;
    }

    while (query.next()) {
        lastSeenHash[query.value(0).toInt()] = query.value(1).toLongLong();
    }

    db.commit();
    return lastSeenHash;
}

void PostgreSqlStorage::setBufferMarkerLineMsg(UserId user, const BufferId& bufferId, const MsgId& msgId)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_buffer_markerlinemsgid"));

    query.bindValue(":userid", user.toInt());
    query.bindValue(":bufferid", bufferId.toInt());
    query.bindValue(":markerlinemsgid", msgId.toQint64());
    safeExec(query);
    watchQuery(query);
}

QHash<BufferId, MsgId> PostgreSqlStorage::bufferMarkerLineMsgIds(UserId user)
{
    QHash<BufferId, MsgId> markerLineHash;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::bufferMarkerLineMsgIds(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return markerLineHash;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_buffer_markerlinemsgids"));
    query.bindValue(":userid", user.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return markerLineHash;
    }

    while (query.next()) {
        markerLineHash[query.value(0).toInt()] = query.value(1).toLongLong();
    }

    db.commit();
    return markerLineHash;
}

void PostgreSqlStorage::setBufferActivity(UserId user, BufferId bufferId, Message::Types bufferActivity)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_buffer_bufferactivity"));

    query.bindValue(":userid", user.toInt());
    query.bindValue(":bufferid", bufferId.toInt());
    query.bindValue(":bufferactivity", (int)bufferActivity);
    safeExec(query);
    watchQuery(query);
}

QHash<BufferId, Message::Types> PostgreSqlStorage::bufferActivities(UserId user)
{
    QHash<BufferId, Message::Types> bufferActivityHash;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::bufferActivities(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return bufferActivityHash;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_buffer_bufferactivities"));
    query.bindValue(":userid", user.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return bufferActivityHash;
    }

    while (query.next()) {
        bufferActivityHash[query.value(0).toInt()] = Message::Types(query.value(1).toInt());
    }

    db.commit();
    return bufferActivityHash;
}

Message::Types PostgreSqlStorage::bufferActivity(BufferId bufferId, MsgId lastSeenMsgId)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_buffer_bufferactivity"));
    query.bindValue(":bufferid", bufferId.toInt());
    query.bindValue(":lastseenmsgid", lastSeenMsgId.toQint64());
    safeExec(query);
    watchQuery(query);
    Message::Types result{};
    if (query.first())
        result = Message::Types(query.value(0).toInt());
    return result;
}

QHash<QString, QByteArray> PostgreSqlStorage::bufferCiphers(UserId user, const NetworkId& networkId)
{
    QHash<QString, QByteArray> bufferCiphers;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::persistentChannels(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return bufferCiphers;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_buffer_ciphers"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    safeExec(query);
    watchQuery(query);

    while (query.next()) {
        bufferCiphers[query.value(0).toString()] = QByteArray::fromHex(query.value(1).toString().toUtf8());
    }

    db.commit();
    return bufferCiphers;
}

void PostgreSqlStorage::setBufferCipher(UserId user, const NetworkId& networkId, const QString& bufferName, const QByteArray& cipher)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_buffer_cipher"));
    query.bindValue(":userid", user.toInt());
    query.bindValue(":networkid", networkId.toInt());
    query.bindValue(":buffercname", bufferName.toLower());
    query.bindValue(":cipher", QString(cipher.toHex()));
    safeExec(query);
    watchQuery(query);
}

void PostgreSqlStorage::setHighlightCount(UserId user, BufferId bufferId, int highlightcount)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("update_buffer_highlightcount"));

    query.bindValue(":userid", user.toInt());
    query.bindValue(":bufferid", bufferId.toInt());
    query.bindValue(":highlightcount", highlightcount);
    safeExec(query);
    watchQuery(query);
}

QHash<BufferId, int> PostgreSqlStorage::highlightCounts(UserId user)
{
    QHash<BufferId, int> highlightCountHash;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::highlightCounts(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return highlightCountHash;
    }

    QSqlQuery query(db);
    query.prepare(queryString("select_buffer_highlightcounts"));
    query.bindValue(":userid", user.toInt());
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return highlightCountHash;
    }

    while (query.next()) {
        highlightCountHash[query.value(0).toInt()] = query.value(1).toInt();
    }

    db.commit();
    return highlightCountHash;
}

int PostgreSqlStorage::highlightCount(BufferId bufferId, MsgId lastSeenMsgId)
{
    QSqlQuery query(logDb());
    query.prepare(queryString("select_buffer_highlightcount"));
    query.bindValue(":bufferid", bufferId.toInt());
    query.bindValue(":lastseenmsgid", lastSeenMsgId.toQint64());
    safeExec(query);
    watchQuery(query);
    auto result = int(0);
    if (query.first())
        result = query.value(0).toInt();
    return result;
}

bool PostgreSqlStorage::logMessage(Message& msg)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::logMessage(): cannot start transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }

    QVariantList senderParams;
    senderParams << msg.sender() << msg.realName() << msg.avatarUrl();
    QSqlQuery getSenderIdQuery = executePreparedQuery("select_senderid", senderParams, db);
    qint64 senderId;
    if (getSenderIdQuery.first()) {
        senderId = getSenderIdQuery.value(0).toLongLong();
    }
    else {
        // it's possible that the sender was already added by another thread
        // since the insert might fail we're setting a savepoint
        savePoint("sender_sp1", db);
        QSqlQuery addSenderQuery = executePreparedQuery("insert_sender", senderParams, db);

        if (addSenderQuery.lastError().isValid()) {
            rollbackSavePoint("sender_sp1", db);
            getSenderIdQuery = executePreparedQuery("select_senderid", senderParams, db);
            watchQuery(getSenderIdQuery);
            getSenderIdQuery.first();
            senderId = getSenderIdQuery.value(0).toLongLong();
        }
        else {
            releaseSavePoint("sender_sp1", db);
            addSenderQuery.first();
            senderId = addSenderQuery.value(0).toLongLong();
        }
    }

    QVariantList params;
    // PostgreSQL handles QDateTime()'s serialized format by default, and QDateTime() serializes
    // to a 64-bit time compatible format by default.
    params << msg.timestamp() << msg.bufferInfo().bufferId().toInt() << msg.type() << (int)msg.flags() << senderId << msg.senderPrefixes()
           << msg.contents();
    QSqlQuery logMessageQuery = executePreparedQuery("insert_message", params, db);

    if (!watchQuery(logMessageQuery)) {
        db.rollback();
        return false;
    }

    logMessageQuery.first();
    MsgId msgId = logMessageQuery.value(0).toLongLong();
    db.commit();
    if (msgId.isValid()) {
        msg.setMsgId(msgId);
        return true;
    }
    else {
        return false;
    }
}

bool PostgreSqlStorage::logMessages(MessageList& msgs)
{
    QSqlDatabase db = logDb();
    if (!beginTransaction(db)) {
        qWarning() << "PostgreSqlStorage::logMessage(): cannot start transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return false;
    }

    QList<int> senderIdList;
    QHash<SenderData, qint64> senderIds;
    QSqlQuery addSenderQuery;
    QSqlQuery selectSenderQuery;
    ;
    for (int i = 0; i < msgs.count(); i++) {
        auto& msg = msgs.at(i);
        SenderData sender = {msg.sender(), msg.realName(), msg.avatarUrl()};
        if (senderIds.contains(sender)) {
            senderIdList << senderIds[sender];
            continue;
        }

        QVariantList senderParams;
        senderParams << sender.sender << sender.realname << sender.avatarurl;

        selectSenderQuery = executePreparedQuery("select_senderid", senderParams, db);
        if (selectSenderQuery.first()) {
            senderIdList << selectSenderQuery.value(0).toLongLong();
            senderIds[sender] = selectSenderQuery.value(0).toLongLong();
        }
        else {
            savePoint("sender_sp", db);
            addSenderQuery = executePreparedQuery("insert_sender", senderParams, db);
            if (addSenderQuery.lastError().isValid()) {
                // seems it was inserted meanwhile... by a different thread
                rollbackSavePoint("sender_sp", db);
                selectSenderQuery = executePreparedQuery("select_senderid", senderParams, db);
                watchQuery(selectSenderQuery);
                selectSenderQuery.first();
                senderIdList << selectSenderQuery.value(0).toLongLong();
                senderIds[sender] = selectSenderQuery.value(0).toLongLong();
            }
            else {
                releaseSavePoint("sender_sp", db);
                addSenderQuery.first();
                senderIdList << addSenderQuery.value(0).toLongLong();
                senderIds[sender] = addSenderQuery.value(0).toLongLong();
            }
        }
    }

    // yes we loop twice over the same list. This avoids alternating queries.
    bool error = false;
    for (int i = 0; i < msgs.count(); i++) {
        Message& msg = msgs[i];
        QVariantList params;
        // PostgreSQL handles QDateTime()'s serialized format by default, and QDateTime() serializes
        // to a 64-bit time compatible format by default.
        params << msg.timestamp() << msg.bufferInfo().bufferId().toInt() << msg.type() << (int)msg.flags() << senderIdList.at(i)
               << msg.senderPrefixes() << msg.contents();
        QSqlQuery logMessageQuery = executePreparedQuery("insert_message", params, db);
        if (!watchQuery(logMessageQuery)) {
            db.rollback();
            error = true;
            break;
        }
        else {
            logMessageQuery.first();
            msg.setMsgId(logMessageQuery.value(0).toLongLong());
        }
    }

    if (error) {
        // we had a rollback in the db so we need to reset all msgIds
        for (int i = 0; i < msgs.count(); i++) {
            msgs[i].setMsgId(MsgId());
        }
        return false;
    }

    db.commit();
    return true;
}

std::vector<Message> PostgreSqlStorage::requestMsgs(UserId user, BufferId bufferId, MsgId first, MsgId last, int limit)
{
    std::vector<Message> messagelist;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::requestMsgs(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return messagelist;
    }

    BufferInfo bufferInfo = getBufferInfo(user, bufferId);
    if (!bufferInfo.isValid()) {
        db.rollback();
        return messagelist;
    }

    QString queryName;
    QVariantList params;
    if (last == -1 && first == -1) {
        queryName = "select_messagesNewestK";
    }
    else if (last == -1) {
        queryName = "select_messagesNewerThan";
        params << first.toQint64();
    }
    else {
        queryName = "select_messagesRange";
        params << first.toQint64();
        params << last.toQint64();
    }
    params << bufferId.toInt();
    if (limit != -1)
        params << limit;
    else
        params << QVariant(QMetaType(QMetaType::Int));  // Replaced QVariant(QVariant::Int)

    QSqlQuery query = executePreparedQuery(queryName, params, db);

    if (!watchQuery(query)) {
        qDebug() << "select_messages failed";
        db.rollback();
        return messagelist;
    }

    QDateTime timestamp;
    while (query.next()) {
        // PostgreSQL returns date/time in ISO 8601 format, no 64-bit handling needed
        // See https://www.postgresql.org/docs/current/static/datatype-datetime.html#DATATYPE-DATETIME-OUTPUT
        timestamp = query.value(1).toDateTime();
        timestamp.setTimeZone(QTimeZone::UTC);
        Message msg(timestamp,
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

    db.commit();
    return messagelist;
}

std::vector<Message> PostgreSqlStorage::requestMsgsFiltered(
    UserId user, BufferId bufferId, MsgId first, MsgId last, int limit, Message::Types type, Message::Flags flags)
{
    std::vector<Message> messagelist;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::requestMsgs(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return messagelist;
    }

    BufferInfo bufferInfo = getBufferInfo(user, bufferId);
    if (!bufferInfo.isValid()) {
        db.rollback();
        return messagelist;
    }

    QSqlQuery query(db);
    if (last == -1 && first == -1) {
        query.prepare(queryString("select_messagesNewestK_filtered"));
    }
    else if (last == -1) {
        query.prepare(queryString("select_messagesNewerThan_filtered"));
        query.bindValue(":first", first.toQint64());
    }
    else {
        query.prepare(queryString("select_messagesRange_filtered"));
        query.bindValue(":last", last.toQint64());
        query.bindValue(":first", first.toQint64());
    }
    query.bindValue(":buffer", bufferId.toInt());
    query.bindValue(":limit", limit);
    int typeRaw = type;
    query.bindValue(":type", typeRaw);
    int flagsRaw = flags;
    query.bindValue(":flags", flagsRaw);

    safeExec(query);
    if (!watchQuery(query)) {
        qDebug() << "select_messages failed";
        db.rollback();
        return messagelist;
    }

    QDateTime timestamp;
    while (query.next()) {
        // PostgreSQL returns date/time in ISO 8601 format, no 64-bit handling needed
        // See https://www.postgresql.org/docs/current/static/datatype-datetime.html#DATATYPE-DATETIME-OUTPUT
        timestamp = query.value(1).toDateTime();
        timestamp.setTimeZone(QTimeZone::UTC);
        Message msg(timestamp,
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

    db.commit();
    return messagelist;
}

std::vector<Message> PostgreSqlStorage::requestMsgsForward(
    UserId user, BufferId bufferId, MsgId first, MsgId last, int limit, Message::Types type, Message::Flags flags)
{
    std::vector<Message> messagelist;

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::requestMsgsForward(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return messagelist;
    }

    BufferInfo bufferInfo = getBufferInfo(user, bufferId);
    if (!bufferInfo.isValid()) {
        db.rollback();
        return messagelist;
    }

    QString queryName;
    QVariantList params;

    if (first == -1) {
        params << std::numeric_limits<qint64>::min();
    }
    else {
        params << first.toQint64();
    }

    if (last == -1) {
        params << std::numeric_limits<qint64>::max();
    }
    else {
        params << last.toQint64();
    }

    params << bufferId.toInt();

    int typeRaw = type;
    params << typeRaw;
    int flagsRaw = flags;
    params << flagsRaw;

    if (limit != -1)
        params << limit;
    else
        params << QVariant(QMetaType(QMetaType::Int));  // Replaced QVariant(QVariant::Int)

    QSqlQuery query = executePreparedQuery("select_messagesForward", params, db);

    if (!watchQuery(query)) {
        qDebug() << "select_messages failed";
        db.rollback();
        return messagelist;
    }

    QDateTime timestamp;
    while (query.next()) {
        // PostgreSQL returns date/time in ISO 8601 format, no 64-bit handling needed
        // See https://www.postgresql.org/docs/current/static/datatype-datetime.html#DATATYPE-DATETIME-OUTPUT
        timestamp = query.value(1).toDateTime();
        timestamp.setTimeZone(QTimeZone::UTC);
        Message msg(timestamp,
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

    db.commit();
    return messagelist;
}

std::vector<Message> PostgreSqlStorage::requestAllMsgs(UserId user, MsgId first, MsgId last, int limit)
{
    std::vector<Message> messagelist;

    // requestBuffers uses it's own transaction.
    QHash<BufferId, BufferInfo> bufferInfoHash;
    for (const BufferInfo& bufferInfo : requestBuffers(user)) {
        bufferInfoHash[bufferInfo.bufferId()] = bufferInfo;
    }

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::requestAllMsgs(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return messagelist;
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
    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return messagelist;
    }

    QDateTime timestamp;
    for (int i = 0; i < limit && query.next(); i++) {
        // PostgreSQL returns date/time in ISO 8601 format, no 64-bit handling needed
        // See https://www.postgresql.org/docs/current/static/datatype-datetime.html#DATATYPE-DATETIME-OUTPUT
        timestamp = query.value(2).toDateTime();
        timestamp.setTimeZone(QTimeZone::UTC);
        Message msg(timestamp,
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

    db.commit();
    return messagelist;
}

std::vector<Message> PostgreSqlStorage::requestAllMsgsFiltered(
    UserId user, MsgId first, MsgId last, int limit, Message::Types type, Message::Flags flags)
{
    std::vector<Message> messagelist;

    // requestBuffers uses it's own transaction.
    QHash<BufferId, BufferInfo> bufferInfoHash;
    for (const BufferInfo& bufferInfo : requestBuffers(user)) {
        bufferInfoHash[bufferInfo.bufferId()] = bufferInfo;
    }

    QSqlDatabase db = logDb();
    if (!beginReadOnlyTransaction(db)) {
        qWarning() << "PostgreSqlStorage::requestAllMsgs(): cannot start read only transaction!";
        qWarning() << " -" << qPrintable(db.lastError().text());
        return messagelist;
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

    int typeRaw = type;
    query.bindValue(":type", typeRaw);

    int flagsRaw = flags;
    query.bindValue(":flags", flagsRaw);

    safeExec(query);
    if (!watchQuery(query)) {
        db.rollback();
        return messagelist;
    }

    QDateTime timestamp;
    for (int i = 0; i < limit && query.next(); i++) {
        // PostgreSQL returns date/time in ISO 8601 format, no 64-bit handling needed
        // See https://www.postgresql.org/docs/current/static/datatype-datetime.html#DATATYPE-DATETIME-OUTPUT
        timestamp = query.value(2).toDateTime();
        timestamp.setTimeZone(QTimeZone::UTC);
        Message msg(timestamp,
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

    db.commit();
    return messagelist;
}

QMap<UserId, QString> PostgreSqlStorage::getAllAuthUserNames()
{
    QMap<UserId, QString> authusernames;
    QSqlQuery query(logDb());
    query.prepare(queryString("select_all_authusernames"));
    safeExec(query);
    watchQuery(query);

    while (query.next()) {
        authusernames[query.value(0).toInt()] = query.value(1).toString();
    }
    return authusernames;
}

// void PostgreSqlStorage::safeExec(QSqlQuery &query) {
//   qDebug() << "PostgreSqlStorage::safeExec";
//   qDebug() << "   executing:\n" << query.executedQuery();
//   qDebug() << "   bound Values:";
//   QList<QVariant> list = query.boundValues().values();
//   for (int i = 0; i < list.size(); ++i)
//     qCritical() << i << ": " << list.at(i).toString().toLatin1().data();

//   query.exec();

//   qDebug() << "Success:" << !query.lastError().isValid();
//   qDebug();

//   if(!query.lastError().isValid())
//     return;

//   qDebug() << "==================== ERROR ====================";
//   watchQuery(query);
//   qDebug() << "===============================================";
//   qDebug();
//   return;
// }

bool PostgreSqlStorage::beginTransaction(QSqlDatabase& db)
{
    bool result = db.transaction();
    if (!db.isOpen()) {
        db = logDb();
        result = db.transaction();
    }
    return result;
}

bool PostgreSqlStorage::beginReadOnlyTransaction(QSqlDatabase& db)
{
    QSqlQuery query(db);
    query.prepare("BEGIN TRANSACTION READ ONLY");
    query.exec();
    if (!db.isOpen()) {
        db = logDb();
        query.prepare("BEGIN TRANSACTION READ ONLY");
        query.exec();
    }
    return !query.lastError().isValid();
}

QSqlQuery PostgreSqlStorage::prepareAndExecuteQuery(const QString& queryname, const QString& paramstring, QSqlDatabase& db)
{
    // Query preparing is done lazily. That means that instead of always checking if the query is already prepared
    // we just EXECUTE and catch the error
    QSqlQuery query;

    QSqlQuery saveQuery(db);
    saveQuery.prepare("SAVEPOINT quassel_prepare_query");
    saveQuery.exec();
    if (paramstring.isNull()) {
        query.prepare(QString("EXECUTE quassel_%1").arg(queryname));
        query.exec();
    }
    else {
        query.prepare(QString("EXECUTE quassel_%1 (%2)").arg(queryname).arg(paramstring));
        query.exec();
    }

    if (!db.isOpen() || db.lastError().isValid()) {
        // If the query failed because the DB connection was down, reopen the connection and start a new transaction.
        if (!db.isOpen()) {
            db = logDb();
            if (!beginTransaction(db)) {
                qWarning()
                    << "PostgreSqlStorage::prepareAndExecuteQuery(): cannot start transaction while recovering from connection loss!";
                qWarning() << " -" << qPrintable(db.lastError().text());
                return query;
            }
            QSqlQuery saveQuery2(db);
            saveQuery2.prepare("SAVEPOINT quassel_prepare_query");
            saveQuery2.exec();
        }
        else {
            QSqlQuery rollbackQuery(db);
            rollbackQuery.prepare("ROLLBACK TO SAVEPOINT quassel_prepare_query");
            rollbackQuery.exec();
        }

        // and once again: Qt leaves us without error codes so we either parse (language dependent(!)) strings
        // or we just guess the error. As we're only interested in unprepared queries, this will be our guess. :)
        QSqlQuery checkQuery(db);
        checkQuery.prepare(
            QString("SELECT count(name) FROM pg_prepared_statements WHERE name = 'quassel_%1' AND from_sql = TRUE").arg(queryname.toLower()));
        checkQuery.exec();
        checkQuery.first();
        if (checkQuery.value(0).toInt() == 0) {
            QSqlQuery prepareQuery(db);
            prepareQuery.prepare(QString("PREPARE quassel_%1 AS %2").arg(queryname).arg(queryString(queryname)));
            prepareQuery.exec();
            if (db.lastError().isValid()) {
                qWarning() << "PostgreSqlStorage::prepareQuery(): unable to prepare query:" << queryname << "AS" << queryString(queryname);
                qWarning() << "  Error:" << db.lastError().text();
                return QSqlQuery(db);
            }
        }
        // we always execute the query again, even if the query was already prepared.
        // this ensures, that the error is properly propagated to the calling function
        // (otherwise the last call would be the testing select to pg_prepared_statements
        // which always gives a proper result and the error would be lost)
        if (paramstring.isNull()) {
            query.prepare(QString("EXECUTE quassel_%1").arg(queryname));
            query.exec();
        }
        else {
            query.prepare(QString("EXECUTE quassel_%1 (%2)").arg(queryname).arg(paramstring));
            query.exec();
        }
    }
    else {
        // only release the SAVEPOINT
        QSqlQuery releaseQuery(db);
        releaseQuery.prepare("RELEASE SAVEPOINT quassel_prepare_query");
        releaseQuery.exec();
    }
    return query;
}

QSqlQuery PostgreSqlStorage::executePreparedQuery(const QString& queryname, const QVariantList& params, QSqlDatabase& db)
{
    QSqlDriver* driver = db.driver();

    QStringList paramStrings;
    QSqlField field;
    for (int i = 0; i < params.count(); i++) {
        const QVariant& value = params.at(i);
        field.setMetaType(value.metaType());
        if (value.isNull())
            field.clear();
        else
            field.setValue(value);

        paramStrings << driver->formatValue(field);
    }

    if (params.isEmpty()) {
        return prepareAndExecuteQuery(queryname, db);
    }
    else {
        return prepareAndExecuteQuery(queryname, paramStrings.join(", "), db);
    }
}

QSqlQuery PostgreSqlStorage::executePreparedQuery(const QString& queryname, const QVariant& param, QSqlDatabase& db)
{
    QSqlField field;
    field.setMetaType(param.metaType());
    if (param.isNull())
        field.clear();
    else
        field.setValue(param);

    QString paramString = db.driver()->formatValue(field);
    return prepareAndExecuteQuery(queryname, paramString, db);
}

void PostgreSqlStorage::deallocateQuery(const QString& queryname, const QSqlDatabase& db)
{
    QSqlQuery query(db);
    query.prepare(QString("DEALLOCATE quassel_%1").arg(queryname));
    query.exec();
}

void PostgreSqlStorage::safeExec(QSqlQuery& query)
{
    // If the query fails due to the connection being gone, it seems to cause
    // exec() to return false but no lastError to be set
    if (!query.exec() && !query.lastError().isValid()) {
        QSqlDatabase db = logDb();
        QSqlQuery retryQuery(db);
        retryQuery.prepare(query.lastQuery());
        QVariantList boundValues = query.boundValues();
        for (int i = 0; i < boundValues.size(); ++i) {
            QVariant value = boundValues[i];
            retryQuery.bindValue(i, boundValues[i]);
        }
        query = std::move(retryQuery);
        query.exec();
    }
}

// ========================================
//  PostgreSqlMigrationWriter
// ========================================
PostgreSqlMigrationWriter::PostgreSqlMigrationWriter()
    : PostgreSqlStorage()
{
}

bool PostgreSqlMigrationWriter::prepareQuery(MigrationObject mo)
{
    QString query;
    switch (mo) {
    case QuasselUser:
        query = queryString("migrate_write_quasseluser");
        break;
    case Sender:
        query = queryString("migrate_write_sender");
        break;
    case Identity:
        _validIdentities.clear();
        query = queryString("migrate_write_identity");
        break;
    case IdentityNick:
        query = queryString("migrate_write_identity_nick");
        break;
    case Network:
        query = queryString("migrate_write_network");
        break;
    case Buffer:
        query = queryString("migrate_write_buffer");
        break;
    case Backlog:
        query = queryString("migrate_write_backlog");
        break;
    case IrcServer:
        query = queryString("migrate_write_ircserver");
        break;
    case UserSetting:
        query = queryString("migrate_write_usersetting");
        break;
    case CoreState:
        query = queryString("migrate_write_corestate");
        break;
    }
    newQuery(query, logDb());
    return true;
}

// bool PostgreSqlMigrationWriter::writeUser(const QuasselUserMO &user) {
bool PostgreSqlMigrationWriter::writeMo(const QuasselUserMO& user)
{
    bindValue(0, user.id.toInt());
    bindValue(1, user.username);
    bindValue(2, user.password);
    bindValue(3, user.hashversion);
    bindValue(4, user.authenticator);
    return exec();
}

// bool PostgreSqlMigrationWriter::writeSender(const SenderMO &sender) {
bool PostgreSqlMigrationWriter::writeMo(const SenderMO& sender)
{
    bindValue(0, sender.senderId);
    bindValue(1, sender.sender);
    bindValue(2, sender.realname);
    bindValue(3, sender.avatarurl);
    return exec();
}

// bool PostgreSqlMigrationWriter::writeIdentity(const IdentityMO &identity) {
bool PostgreSqlMigrationWriter::writeMo(const IdentityMO& identity)
{
    _validIdentities << identity.id.toInt();
    bindValue(0, identity.id.toInt());
    bindValue(1, identity.userid.toInt());
    bindValue(2, identity.identityname);
    bindValue(3, identity.realname);
    bindValue(4, identity.awayNick);
    bindValue(5, identity.awayNickEnabled);
    bindValue(6, identity.awayReason);
    bindValue(7, identity.awayReasonEnabled);
    bindValue(8, identity.autoAwayEnabled);
    bindValue(9, identity.autoAwayTime);
    bindValue(10, identity.autoAwayReason);
    bindValue(11, identity.autoAwayReasonEnabled);
    bindValue(12, identity.detachAwayEnabled);
    bindValue(13, identity.detachAwayReason);
    bindValue(14, identity.detachAwayReasonEnabled);
    bindValue(15, identity.ident);
    bindValue(16, identity.kickReason);
    bindValue(17, identity.partReason);
    bindValue(18, identity.quitReason);
    bindValue(19, identity.sslCert);
    bindValue(20, identity.sslKey);
    return exec();
}

// bool PostgreSqlMigrationWriter::writeIdentityNick(const IdentityNickMO &identityNick) {
bool PostgreSqlMigrationWriter::writeMo(const IdentityNickMO& identityNick)
{
    bindValue(0, identityNick.nickid);
    bindValue(1, identityNick.identityId.toInt());
    bindValue(2, identityNick.nick);
    return exec();
}

// bool PostgreSqlMigrationWriter::writeNetwork(const NetworkMO &network) {
bool PostgreSqlMigrationWriter::writeMo(const NetworkMO& network)
{
    bindValue(0, network.networkid.toInt());
    bindValue(1, network.userid.toInt());
    bindValue(2, network.networkname);
    if (_validIdentities.contains(network.identityid.toInt()))
        bindValue(3, network.identityid.toInt());
    else
        bindValue(3, QVariant());
    bindValue(4, network.encodingcodec);
    bindValue(5, network.decodingcodec);
    bindValue(6, network.servercodec);
    bindValue(7, network.userandomserver);
    bindValue(8, network.perform);
    bindValue(9, network.useautoidentify);
    bindValue(10, network.autoidentifyservice);
    bindValue(11, network.autoidentifypassword);
    bindValue(12, network.useautoreconnect);
    bindValue(13, network.autoreconnectinterval);
    bindValue(14, network.autoreconnectretries);
    bindValue(15, network.unlimitedconnectretries);
    bindValue(16, network.rejoinchannels);
    bindValue(17, network.connected);
    bindValue(18, network.usermode);
    bindValue(19, network.awaymessage);
    bindValue(20, network.attachperform);
    bindValue(21, network.detachperform);
    bindValue(22, network.usesasl);
    bindValue(23, network.saslaccount);
    bindValue(24, network.saslpassword);
    // Custom rate limiting
    bindValue(25, network.usecustommessagerate);
    bindValue(26, network.messagerateburstsize);
    bindValue(27, network.messageratedelay);
    bindValue(28, network.unlimitedmessagerate);
    // Skipped IRCv3 caps
    bindValue(29, network.skipcaps);
    return exec();
}

// bool PostgreSqlMigrationWriter::writeBuffer(const BufferMO &buffer) {
bool PostgreSqlMigrationWriter::writeMo(const BufferMO& buffer)
{
    bindValue(0, buffer.bufferid.toInt());
    bindValue(1, buffer.userid.toInt());
    bindValue(2, buffer.groupid);
    bindValue(3, buffer.networkid.toInt());
    bindValue(4, buffer.buffername);
    bindValue(5, buffer.buffercname);
    bindValue(6, (int)buffer.buffertype);
    bindValue(7, buffer.lastmsgid);
    bindValue(8, buffer.lastseenmsgid);
    bindValue(9, buffer.markerlinemsgid);
    bindValue(10, buffer.bufferactivity);
    bindValue(11, buffer.highlightcount);
    bindValue(12, buffer.key);
    bindValue(13, buffer.joined);
    bindValue(14, buffer.cipher);
    return exec();
}

// bool PostgreSqlMigrationWriter::writeBacklog(const BacklogMO &backlog) {
bool PostgreSqlMigrationWriter::writeMo(const BacklogMO& backlog)
{
    bindValue(0, backlog.messageid.toQint64());
    bindValue(1, backlog.time);
    bindValue(2, backlog.bufferid.toInt());
    bindValue(3, backlog.type);
    bindValue(4, (int)backlog.flags);
    bindValue(5, backlog.senderid);
    bindValue(6, backlog.senderprefixes);
    bindValue(7, backlog.message);
    return exec();
}

// bool PostgreSqlMigrationWriter::writeIrcServer(const IrcServerMO &ircserver) {
bool PostgreSqlMigrationWriter::writeMo(const IrcServerMO& ircserver)
{
    bindValue(0, ircserver.serverid);
    bindValue(1, ircserver.userid.toInt());
    bindValue(2, ircserver.networkid.toInt());
    bindValue(3, ircserver.hostname);
    bindValue(4, ircserver.port);
    bindValue(5, ircserver.password);
    bindValue(6, ircserver.ssl);
    bindValue(7, ircserver.sslversion);
    bindValue(8, ircserver.useproxy);
    bindValue(9, ircserver.proxytype);
    bindValue(10, ircserver.proxyhost);
    bindValue(11, ircserver.proxyport);
    bindValue(12, ircserver.proxyuser);
    bindValue(13, ircserver.proxypass);
    bindValue(14, ircserver.sslverify);
    return exec();
}

// bool PostgreSqlMigrationWriter::writeUserSetting(const UserSettingMO &userSetting) {
bool PostgreSqlMigrationWriter::writeMo(const UserSettingMO& userSetting)
{
    bindValue(0, userSetting.userid.toInt());
    bindValue(1, userSetting.settingname);
    bindValue(2, userSetting.settingvalue);
    return exec();
}

bool PostgreSqlMigrationWriter::writeMo(const CoreStateMO& coreState)
{
    bindValue(0, coreState.key);
    bindValue(1, coreState.value);
    return exec();
}

bool PostgreSqlMigrationWriter::postProcess()
{
    QSqlDatabase db = logDb();
    QList<Sequence> sequences;
    sequences << Sequence("backlog", "messageid") << Sequence("buffer", "bufferid") << Sequence("identity", "identityid")
              << Sequence("identity_nick", "nickid") << Sequence("ircserver", "serverid") << Sequence("network", "networkid")
              << Sequence("quasseluser", "userid") << Sequence("sender", "senderid");
    QList<Sequence>::const_iterator iter;
    for (iter = sequences.constBegin(); iter != sequences.constEnd(); ++iter) {
        resetQuery();
        newQuery(QString("SELECT setval('%1_%2_seq', max(%2)) FROM %1").arg(iter->table, iter->field), db);
        if (!exec())
            return false;
    }

    // Update the lastmsgid for all existing buffers.
    resetQuery();
    newQuery(QString("SELECT populate_lastmsgid()"), db);
    if (!exec())
        return false;
    return true;
}
