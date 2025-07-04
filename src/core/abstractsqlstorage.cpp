// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "abstractsqlstorage.h"

#include <QDir>
#include <QFileInfo>
#include <QMetaType>
#include <QMutexLocker>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QThread>

#include "quassel.h"

int AbstractSqlStorage::_nextConnectionId = 0;
AbstractSqlStorage::AbstractSqlStorage(QObject* parent)
    : Storage(parent)
{
}

AbstractSqlStorage::~AbstractSqlStorage()
{
    // disconnect the connections, so their deletion is no longer interesting for us
    QHash<QThread*, Connection*>::iterator conIter;
    for (conIter = _connectionPool.begin(); conIter != _connectionPool.end(); ++conIter) {
        QSqlDatabase::removeDatabase(conIter.value()->name());
        disconnect(conIter.value(), nullptr, this, nullptr);
    }
}

QSqlDatabase AbstractSqlStorage::logDb()
{
    if (!_connectionPool.contains(QThread::currentThread()))
        addConnectionToPool();

    QSqlDatabase db = QSqlDatabase::database(_connectionPool[QThread::currentThread()]->name(), false);

    if (!db.isOpen()) {
        qWarning() << "Database connection" << displayName() << "for thread" << QThread::currentThread()
                   << "was lost, attempting to reconnect...";
        dbConnect(db);
    }

    return db;
}

void AbstractSqlStorage::addConnectionToPool()
{
    QMutexLocker locker(&_connectionPoolMutex);
    // we have to recheck if the connection pool already contains a connection for
    // this thread. Since now (after the lock) we can only tell for sure
    if (_connectionPool.contains(QThread::currentThread()))
        return;

    QThread* currentThread = QThread::currentThread();

    int connectionId = _nextConnectionId++;

    Connection* connection = new Connection(QLatin1String(QString("quassel_%1_con_%2").arg(driverName()).arg(connectionId).toLatin1()));
    connection->moveToThread(currentThread);
    connect(this, &QObject::destroyed, connection, &QObject::deleteLater);
    connect(currentThread, &QObject::destroyed, connection, &QObject::deleteLater);
    connect(connection, &QObject::destroyed, this, &AbstractSqlStorage::connectionDestroyed);
    _connectionPool[currentThread] = connection;

    QSqlDatabase db = QSqlDatabase::addDatabase(driverName(), connection->name());
    db.setDatabaseName(databaseName());

    if (!hostName().isEmpty())
        db.setHostName(hostName());

    if (port() != -1)
        db.setPort(port());

    if (!userName().isEmpty()) {
        db.setUserName(userName());
        db.setPassword(password());
    }

    dbConnect(db);
}

void AbstractSqlStorage::dbConnect(QSqlDatabase& db)
{
    if (!db.open()) {
        qWarning() << "Unable to open database" << displayName() << "for thread" << QThread::currentThread();
        qWarning() << "-" << db.lastError().text();
    }
    else {
        if (!initDbSession(db)) {
            qWarning() << "Unable to initialize database" << displayName() << "for thread" << QThread::currentThread();
            db.close();
        }
    }
}

Storage::State AbstractSqlStorage::init(const QVariantMap& settings, const QProcessEnvironment& environment, bool loadFromEnvironment)
{
    setConnectionProperties(settings, environment, loadFromEnvironment);
    _debug = true;
    // _debug = Quassel::isOptionSet("debug");

    QSqlDatabase db = logDb();
    if (!db.isValid() || !db.isOpen())
        return NotAvailable;

    if (installedSchemaVersion() == -1) {
        qCritical() << "Storage Schema is missing!";
        return NeedsSetup;
    }

    if (installedSchemaVersion() > schemaVersion()) {
        qCritical() << "Installed Schema is newer then any known Version.";
        return NotAvailable;
    }

    if (installedSchemaVersion() < schemaVersion()) {
        qInfo() << qPrintable(tr("Installed database schema (version %1) is not up to date. Upgrading to "
                                 "version %2...  This may take a while for major upgrades.")
                                  .arg(installedSchemaVersion())
                                  .arg(schemaVersion()));
        emit dbUpgradeInProgress(true);
        auto upgradeResult = upgradeDb();
        emit dbUpgradeInProgress(false);
        if (!upgradeResult) {
            qWarning() << qPrintable(tr("Upgrade failed..."));
            return NotAvailable;
        }
        // Add a message when migration succeeds to avoid confusing folks by implying the schema upgrade failed if
        // later functionality does not work.
        qInfo() << qPrintable(tr("Installed database schema successfully upgraded to version %1.").arg(schemaVersion()));
    }

    qInfo() << qPrintable(displayName()) << "storage backend is ready. Schema version:" << installedSchemaVersion();
    return IsReady;
}

QString AbstractSqlStorage::queryString(const QString& queryName, int version)
{
    QFileInfo queryInfo;

    // The current schema is stored in the root folder, while upgrade queries are stored in the
    // 'versions/##' subfolders.
    if (version == 0) {
        // Use the current SQL schema, not a versioned request
        queryInfo = QFileInfo(QString(":/SQL/%1/%2.sql").arg(displayName()).arg(queryName));
        // If version is needed later, get it via version = schemaVersion();
    }
    else {
        // Use the specified schema version, not the general folder
        queryInfo = QFileInfo(QString(":/SQL/%1/version/%2/%3.sql").arg(displayName()).arg(version).arg(queryName));
    }

    if (!queryInfo.exists() || !queryInfo.isFile() || !queryInfo.isReadable()) {
        qCritical() << "Unable to read SQL-Query" << queryName << "for engine" << displayName();
        return QString();
    }

    QFile queryFile(queryInfo.filePath());
    if (!queryFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();
    QString query = QTextStream(&queryFile).readAll();
    queryFile.close();

    return query.trimmed();
}

std::vector<AbstractSqlStorage::SqlQueryResource> AbstractSqlStorage::setupQueries()
{
    std::vector<SqlQueryResource> queries;
    // The current schema is stored in the root folder, including setup scripts.
    QDir dir = QDir(QString(":/SQL/%1/").arg(displayName()));
    foreach (QFileInfo fileInfo, dir.entryInfoList(QStringList() << "setup*", QDir::NoFilter, QDir::Name)) {
        queries.emplace_back(queryString(fileInfo.baseName()), fileInfo.baseName());
    }
    return queries;
}

bool AbstractSqlStorage::setup(const QVariantMap& settings, const QProcessEnvironment& environment, bool loadFromEnvironment)
{
    setConnectionProperties(settings, environment, loadFromEnvironment);
    QSqlDatabase db = logDb();
    if (!db.isOpen()) {
        qCritical() << "Unable to setup Logging Backend!";
        return false;
    }

    db.transaction();
    for (const auto& queryResource : setupQueries()) {
        QSqlQuery query(db);
        query.exec(queryResource.queryString);
        if (!watchQuery(query)) {
            qCritical() << qPrintable(
                QString("Unable to setup Logging Backend!  Setup query failed (step: %1).").arg(queryResource.queryFilename));
            db.rollback();
            return false;
        }
    }
    bool success = setupSchemaVersion(schemaVersion());
    if (success)
        db.commit();
    else
        db.rollback();
    return success;
}

std::vector<AbstractSqlStorage::SqlQueryResource> AbstractSqlStorage::upgradeQueries(int version)
{
    std::vector<SqlQueryResource> queries;
    // Upgrade queries are stored in the 'version/##' subfolders.
    QDir dir = QDir(QString(":/SQL/%1/version/%2/").arg(displayName()).arg(version));
    foreach (QFileInfo fileInfo, dir.entryInfoList(QStringList() << "upgrade*", QDir::NoFilter, QDir::Name)) {
        queries.emplace_back(queryString(fileInfo.baseName(), version), fileInfo.baseName());
    }
    return queries;
}

bool AbstractSqlStorage::upgradeDb()
{
    if (schemaVersion() <= installedSchemaVersion())
        return true;

    QSqlDatabase db = logDb();

    // TODO: For databases that support it (e.g. almost only PostgreSQL), wrap upgrades in a
    // transaction.  This will need careful testing of potential additional space requirements and
    // any database modifications that might not be allowed in a transaction.

    // Check if we're resuming an interrupted multi-step upgrade: is an upgrade step stored?
    const QString previousLaunchUpgradeStep = schemaVersionUpgradeStep();
    bool resumingUpgrade = !previousLaunchUpgradeStep.isEmpty();

    for (int ver = installedSchemaVersion() + 1; ver <= schemaVersion(); ver++) {
        for (const auto& queryResource : upgradeQueries(ver)) {
            if (resumingUpgrade) {
                // An upgrade was interrupted.  Check if this matches the the last successful query.
                if (previousLaunchUpgradeStep == queryResource.queryFilename) {
                    // Found the matching query!
                    qInfo() << qPrintable(QString("Resuming interrupted upgrade for schema version %1 (last step: %2)")
                                              .arg(QString::number(ver), previousLaunchUpgradeStep));

                    // Stop searching for queries
                    resumingUpgrade = false;
                    // Continue past the previous query with the next not-yet-tried query
                    continue;
                }
                else {
                    // Not yet matched, keep looking
                    continue;
                }
            }

            // Run the upgrade query
            QSqlQuery query(db);
            query.exec(queryResource.queryString);
            if (!watchQuery(query)) {
                // Individual upgrade query failed, bail out
                qCritical() << qPrintable(
                    QString("Unable to upgrade Logging Backend!  Upgrade query in schema version %1 failed (step: %2).")
                        .arg(ver)
                        .arg(queryResource.queryFilename));
                return false;
            }
            else {
                // Mark as successful
                setSchemaVersionUpgradeStep(queryResource.queryFilename);
            }
        }

        if (resumingUpgrade) {
            // Something went wrong and the last successful SQL query to resume from couldn't be
            // found.
            // 1.  The storage of successful query glitched, or the database was manually changed
            // 2.  Quassel changed the filenames of upgrade queries, and the local Quassel core
            //     version was replaced during an interrupted schema upgrade
            //
            // Both are unlikely, but it's a good idea to handle it anyways.

            qCritical() << qPrintable(QString("Unable to resume interrupted upgrade in Logging "
                                              "Backend!  Missing upgrade step in schema version %1 "
                                              "(expected step: %2)")
                                          .arg(QString::number(ver), previousLaunchUpgradeStep));
            return false;
        }

        // Update the schema version for each intermediate step and mark the step as done.  This
        // ensures that any interrupted upgrades have a greater chance of resuming correctly after
        // core restart.
        //
        // Almost all databases make single queries atomic (fully works or fully fails, no partial),
        // and with many of the longest migrations being a single query, this makes upgrade
        // interruptions much more likely to leave the database in a valid intermediate schema
        // version.
        if (!updateSchemaVersion(ver, true)) {
            // Updating the schema version failed, bail out
            qCritical() << "Unable to upgrade Logging Backend!  Setting schema version" << ver << "failed.";
            return false;
        }
    }

    // If we made it here, everything seems to have worked!
    return true;
}

int AbstractSqlStorage::schemaVersion()
{
    // returns the newest Schema Version!
    // not the currently used one! (though it can be the same)
    if (_schemaVersion > 0)
        return _schemaVersion;

    int version;
    bool ok;
    // Schema versions are stored in the 'version/##' subfolders.
    QDir dir = QDir(QString(":/SQL/%1/version/").arg(displayName()));
    foreach (QFileInfo fileInfo, dir.entryInfoList()) {
        if (!fileInfo.isDir())
            continue;

        version = fileInfo.fileName().toInt(&ok);
        if (!ok)
            continue;

        if (version > _schemaVersion)
            _schemaVersion = version;
    }
    return _schemaVersion;
}

QString AbstractSqlStorage::schemaVersionUpgradeStep()
{
    // By default, assume there's no pending upgrade
    return {};
}

bool AbstractSqlStorage::watchQuery(QSqlQuery& query)
{
    bool queryError = query.lastError().isValid();
    if (queryError) {
        qCritical() << "unhandled Error in QSqlQuery!";
        qCritical() << "                  last Query:\n" << qPrintable(query.lastQuery());
        qCritical() << "              executed Query:\n" << qPrintable(query.executedQuery());
        QVariantList boundValues = query.boundValues();
        QStringList valueStrings;
        for (int i = 0; i < boundValues.size(); ++i) {
            QString value;
            QSqlField field;
            if (query.driver()) {
                field.setMetaType(boundValues[i].metaType());
                if (boundValues[i].isNull())
                    field.clear();
                else
                    field.setValue(boundValues[i]);
                value = query.driver()->formatValue(field);
            }
            else {
                switch (boundValues[i].metaType().id()) {
                case QMetaType::UnknownType:
                    value = "NULL";
                    break;
                case QMetaType::Int:
                    value = boundValues[i].toString();
                    break;
                default:
                    value = QString("'%1'").arg(boundValues[i].toString());
                }
            }
            valueStrings << QString("%1=%2").arg(QString::number(i), value);
        }
        qCritical() << "                bound Values:" << qPrintable(valueStrings.join(", "));
        qCritical() << "                  Error Code:" << qPrintable(query.lastError().nativeErrorCode());
        qCritical() << "               Error Message:" << qPrintable(query.lastError().text());
        qCritical() << "              Driver Message:" << qPrintable(query.lastError().driverText());
        qCritical() << "                  DB Message:" << qPrintable(query.lastError().databaseText());
        return false;
    }
    else if (_debug) {
        qDebug() << "Debug Query:\n" << qPrintable(query.lastQuery());
        qDebug() << "Executed Query:\n" << qPrintable(query.executedQuery());
        QVariantList boundValues = query.boundValues();
        QStringList valueStrings;
        for (int i = 0; i < boundValues.size(); ++i) {
            QString value;
            QSqlField field;
            if (query.driver()) {
                field.setMetaType(boundValues[i].metaType());
                if (boundValues[i].isNull())
                    field.clear();
                else
                    field.setValue(boundValues[i]);
                value = query.driver()->formatValue(field);
            }
            else {
                switch (boundValues[i].metaType().id()) {
                case QMetaType::UnknownType:
                    value = "NULL";
                    break;
                case QMetaType::Int:
                    value = boundValues[i].toString();
                    break;
                default:
                    value = QString("'%1'").arg(boundValues[i].toString());
                }
            }
            valueStrings << QString("%1=%2").arg(QString::number(i), value);
        }
        qDebug() << "Bound Values:" << qPrintable(valueStrings.join(", "));
    }
    return true;
}

void AbstractSqlStorage::connectionDestroyed()
{
    QMutexLocker locker(&_connectionPoolMutex);
    _connectionPool.remove(sender()->thread());
}

// ========================================
//  AbstractSqlStorage::Connection
// ========================================
AbstractSqlStorage::Connection::Connection(const QString& name, QObject* parent)
    : QObject(parent)
    , _name(name.toLatin1())
{
}

AbstractSqlStorage::Connection::~Connection()
{
    {
        QSqlDatabase db = QSqlDatabase::database(name(), false);
        if (db.isOpen()) {
            db.commit();
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(name());
}

// ========================================
//  AbstractSqlMigrator
// ========================================

void AbstractSqlMigrator::newQuery(const QString& query, QSqlDatabase db)
{
    Q_ASSERT(!_query);
    _query = new QSqlQuery(db);
    _query->prepare(query);
}

void AbstractSqlMigrator::resetQuery()
{
    delete _query;
    _query = nullptr;
}

bool AbstractSqlMigrator::exec()
{
    Q_ASSERT(_query);
    _query->exec();
    return !_query->lastError().isValid();
}

QString AbstractSqlMigrator::migrationObject(MigrationObject moType)
{
    switch (moType) {
    case QuasselUser:
        return "QuasselUser";
    case Sender:
        return "Sender";
    case Identity:
        return "Identity";
    case IdentityNick:
        return "IdentityNick";
    case Network:
        return "Network";
    case Buffer:
        return "Buffer";
    case Backlog:
        return "Backlog";
    case IrcServer:
        return "IrcServer";
    case UserSetting:
        return "UserSetting";
    case CoreState:
        return "CoreState";
    };
    return QString();
}

QVariantList AbstractSqlMigrator::boundValues()
{
    QVariantList values;
    if (!_query)
        return values;

    int numValues = _query->boundValues().count();
    for (int i = 0; i < numValues; i++) {
        values << _query->boundValue(i);
    }
    return values;
}

void AbstractSqlMigrator::dumpStatus()
{
    qWarning() << "  executed Query:";
    qWarning() << qPrintable(executedQuery());
    qWarning() << "  bound Values:";
    QList<QVariant> list = boundValues();
    for (int i = 0; i < list.size(); ++i)
        qWarning() << i << ": " << list.at(i).toString().toLatin1().data();
    qWarning() << "  Error Code:" << qPrintable(lastError().nativeErrorCode());
    qWarning() << "  Error Message:" << lastError().text();
}

// ========================================
//  AbstractSqlMigrationReader
// ========================================
AbstractSqlMigrationReader::AbstractSqlMigrationReader()
    : AbstractSqlMigrator()
{
}

bool AbstractSqlMigrationReader::migrateTo(AbstractSqlMigrationWriter* writer)
{
    if (!transaction()) {
        qWarning() << "AbstractSqlMigrationReader::migrateTo(): unable to start reader's transaction!";
        return false;
    }
    if (!writer->transaction()) {
        qWarning() << "AbstractSqlMigrationReader::migrateTo(): unable to start writer's transaction!";
        rollback();  // close the reader transaction;
        return false;
    }

    _writer = writer;

    // due to the incompatibility across Migration objects we can't run this in a loop... :/
    QuasselUserMO quasselUserMo;
    if (!transferMo(QuasselUser, quasselUserMo))
        return false;

    IdentityMO identityMo;
    if (!transferMo(Identity, identityMo))
        return false;

    IdentityNickMO identityNickMo;
    if (!transferMo(IdentityNick, identityNickMo))
        return false;

    NetworkMO networkMo;
    if (!transferMo(Network, networkMo))
        return false;

    BufferMO bufferMo;
    if (!transferMo(Buffer, bufferMo))
        return false;

    SenderMO senderMo;
    if (!transferMo(Sender, senderMo))
        return false;

    BacklogMO backlogMo;
    if (!transferMo(Backlog, backlogMo))
        return false;

    IrcServerMO ircServerMo;
    if (!transferMo(IrcServer, ircServerMo))
        return false;

    UserSettingMO userSettingMo;
    if (!transferMo(UserSetting, userSettingMo))
        return false;

    CoreStateMO coreStateMO;
    if (!transferMo(CoreState, coreStateMO))
        return false;

    if (!_writer->postProcess())
        abortMigration();
    return finalizeMigration();
}

void AbstractSqlMigrationReader::abortMigration(const QString& errorMsg)
{
    qWarning() << "Migration Failed!";
    if (!errorMsg.isNull()) {
        qWarning() << qPrintable(errorMsg);
    }
    if (lastError().isValid()) {
        qWarning() << "ReaderError:";
        dumpStatus();
    }

    if (_writer->lastError().isValid()) {
        qWarning() << "WriterError:";
        _writer->dumpStatus();
    }

    rollback();
    _writer->rollback();
    _writer = nullptr;
}

bool AbstractSqlMigrationReader::finalizeMigration()
{
    resetQuery();
    _writer->resetQuery();

    commit();
    if (!_writer->commit()) {
        _writer = nullptr;
        return false;
    }
    _writer = nullptr;
    return true;
}

template<typename T>
bool AbstractSqlMigrationReader::transferMo(MigrationObject moType, T& mo)
{
    resetQuery();
    _writer->resetQuery();

    if (!prepareQuery(moType)) {
        abortMigration(QString("AbstractSqlMigrationReader::migrateTo(): unable to prepare reader query of type %1!")
                           .arg(AbstractSqlMigrator::migrationObject(moType)));
        return false;
    }
    if (!_writer->prepareQuery(moType)) {
        abortMigration(QString("AbstractSqlMigrationReader::migrateTo(): unable to prepare writer query of type %1!")
                           .arg(AbstractSqlMigrator::migrationObject(moType)));
        return false;
    }

    qDebug() << qPrintable(QString("Transferring %1...").arg(AbstractSqlMigrator::migrationObject(moType)));
    int i = 0;
    QFile file;
    file.open(stdout, QIODevice::WriteOnly);

    while (readMo(mo)) {
        if (!_writer->writeMo(mo)) {
            abortMigration(QString("AbstractSqlMigrationReader::transferMo(): unable to transfer Migratable Object of type %1!")
                               .arg(AbstractSqlMigrator::migrationObject(moType)));
            return false;
        }
        i++;
        if (i % 1000 == 0) {
            file.write("*");
            file.flush();
        }
    }
    if (i > 1000) {
        file.write("\n");
        file.flush();
    }

    qDebug() << "Done.";
    return true;
}

uint qHash(const SenderData& key)
{
    return qHash(QString(key.sender + "\n" + key.realname + "\n" + key.avatarurl));
}

bool operator==(const SenderData& a, const SenderData& b)
{
    return a.sender == b.sender && a.realname == b.realname && a.avatarurl == b.avatarurl;
}
