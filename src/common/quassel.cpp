// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quassel.h"

#include <algorithm>
#include <iostream>

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QHostAddress>
#include <QLibraryInfo>
#include <QMetaEnum>
#include <QRandomGenerator>
#include <QSettings>
#include <QTime>
#include <QTranslator>
#include <QUuid>

#include "bufferinfo.h"
#include "identity.h"
#include "logger.h"
#include "message.h"
#include "network.h"
#include "peer.h"
#include "protocol.h"
#include "syncableobject.h"
#include "types.h"
#include "version.h"

#ifndef Q_OS_WIN
#    include "posixsignalwatcher.h"
#else
#    include "windowssignalwatcher.h"
#endif

Quassel::Quassel()
    : Singleton<Quassel>{this}
    , _logger{new Logger{this}}
{
#ifdef EMBED_DATA
    Q_INIT_RESOURCE(i18n);
#endif
}

void Quassel::init(RunMode runMode)
{
    _runMode = runMode;

    // Initialize and seed the Quassel random generator
    if (!_randomGenerator) {
        _randomGenerator = new QRandomGenerator();
        QTime currentTime = QTime::currentTime();
        if (currentTime.isValid()) {
            _randomGenerator->seed(static_cast<quint32>(currentTime.msecsSinceStartOfDay()));
        }
        else {
            qWarning() << "Invalid system time, using default seed.";
            _randomGenerator->seed(0);
        }
    }

    setupSignalHandling();
    setupEnvironment();
    registerMetaTypes();

    // Initial translation (may be overridden in UI settings)
    loadTranslation(QLocale::system());

    setupCliParser();

    // Don't keep a debug log on the core
    logger()->setup(runMode != RunMode::CoreOnly);

    Network::setDefaultCodecForServer("UTF-8");
    Network::setDefaultCodecForEncoding("UTF-8");
    Network::setDefaultCodecForDecoding("ISO-8859-15");
}

QRandomGenerator* Quassel::_randomGenerator = nullptr;

QRandomGenerator* Quassel::randomGenerator()
{
    return _randomGenerator;
}

Logger* Quassel::logger() const
{
    return _logger;
}

void Quassel::registerQuitHandler(QuitHandler handler)
{
    instance()->_quitHandlers.emplace_back(std::move(handler));
}

void Quassel::quit()
{
    // Protect against multiple invocations (e.g. triggered by MainWin::closeEvent())
    if (!_quitting) {
        _quitting = true;
        qInfo() << "Quitting...";
        delete _randomGenerator;
        _randomGenerator = nullptr;
        if (_quitHandlers.empty()) {
            QCoreApplication::quit();
        }
        else {
            // Note: We expect one of the registered handlers to call QCoreApplication::quit()
            for (auto&& handler : _quitHandlers) {
                handler();
            }
        }
    }
}

void Quassel::registerReloadHandler(ReloadHandler handler)
{
    instance()->_reloadHandlers.emplace_back(std::move(handler));
}

bool Quassel::reloadConfig()
{
    bool result{true};
    for (auto&& handler : _reloadHandlers) {
        result = result && handler();
    }
    return result;
}

void Quassel::registerMetaTypes()
{
    // Complex types
    qRegisterMetaType<Message>("Message");
    qRegisterMetaType<BufferInfo>("BufferInfo");
    qRegisterMetaType<NetworkInfo>("NetworkInfo");
    qRegisterMetaType<Network::Server>("Network::Server");
    qRegisterMetaType<Identity>("Identity");

    qRegisterMetaType<IdentityId>("IdentityId");
    qRegisterMetaType<BufferId>("BufferId");
    qRegisterMetaType<NetworkId>("NetworkId");
    qRegisterMetaType<UserId>("UserId");
    qRegisterMetaType<AccountId>("AccountId");
    qRegisterMetaType<MsgId>("MsgId");

    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<QUuid>("QUuid");

    qRegisterMetaType<QuasselProtocol::SessionState>("QuasselProtocol::SessionState");
    qRegisterMetaType<PeerPtr>("PeerPtr");

    // Versions of Qt prior to 4.7 didn't define QVariant as a meta type
    if (!QMetaType::fromName("QVariant").isValid()) {
        qRegisterMetaType<QVariant>("QVariant");
    }
}

void Quassel::setupEnvironment()
{
    // On modern Linux systems, XDG_DATA_DIRS contains a list of directories containing application data. This
    // is, for example, used by Qt for finding icons and other things. In case Quassel is installed in a non-standard
    // prefix (or run from the build directory), it makes sense to add this to XDG_DATA_DIRS so we don't have to
    // hack extra search paths into various places.
#ifdef Q_OS_UNIX
    QString xdgDataVar = QFile::decodeName(qgetenv("XDG_DATA_DIRS"));
    if (xdgDataVar.isEmpty())
        xdgDataVar = QLatin1String("/usr/local/share:/usr/share");  // sane defaults

    QStringList xdgDirs = xdgDataVar.split(QLatin1Char(':'), Qt::SkipEmptyParts);

    // Add our install prefix (if we're not in a bindir, this just adds the current workdir)
    QString appDir = QCoreApplication::applicationDirPath();
    int binpos = appDir.lastIndexOf("/bin");
    if (binpos >= 0) {
        appDir.replace(binpos, 4, "/share");
        xdgDirs.append(appDir);
        // Also append apps/quassel, this is only for QIconLoader to find icons there
        xdgDirs.append(appDir + "/apps/quassel");
    }
    else
        xdgDirs.append(appDir);  // build directory is always the last fallback

    xdgDirs.removeDuplicates();

    qputenv("XDG_DATA_DIRS", QFile::encodeName(xdgDirs.join(":")));
#endif
}

void Quassel::setupBuildInfo()
{
    BuildInfo buildInfo;
    buildInfo.applicationName = "quassel";
    buildInfo.coreApplicationName = "quasselcore";
    buildInfo.clientApplicationName = "quasselclient";
    buildInfo.organizationName = "Quassel Project";
    buildInfo.organizationDomain = "quassel-irc.org";

    buildInfo.protocolVersion = 10;  // FIXME: deprecated, will be removed

    buildInfo.baseVersion = QUASSEL_VERSION_STRING;
    buildInfo.generatedVersion = GIT_DESCRIBE;

    // Check if we got a commit hash
    if (!QString(GIT_HEAD).isEmpty()) {
        buildInfo.commitHash = GIT_HEAD;
        // Set to Unix epoch, wrapped as a string for backwards-compatibility
        buildInfo.commitDate = QString::number(GIT_COMMIT_DATE);
    }
    else if (!QString(DIST_HASH).contains("Format")) {
        buildInfo.commitHash = DIST_HASH;
        // Leave as Unix epoch if set as Unix epoch, but don't force this for
        // backwards-compatibility with existing packaging/release tools that might set strings.
        buildInfo.commitDate = QString(DIST_DATE);
    }

    // create a nice version string
    if (buildInfo.generatedVersion.isEmpty()) {
        if (!buildInfo.commitHash.isEmpty()) {
            // dist version
            buildInfo.plainVersionString = QString{"v%1 (dist-%2)"}.arg(buildInfo.baseVersion).arg(buildInfo.commitHash.left(7));
            buildInfo.fancyVersionString = QString{"v%1 (dist-<a href=\"https://github.com/quassel/quassel/commit/%3\">%2</a>)"}
                                               .arg(buildInfo.baseVersion)
                                               .arg(buildInfo.commitHash.left(7))
                                               .arg(buildInfo.commitHash);
        }
        else {
            // we only have a base version :(
            buildInfo.plainVersionString = QString{"v%1 (unknown revision)"}.arg(buildInfo.baseVersion);
        }
    }
    else {
        // analyze what we got from git-describe
        static const QRegularExpression rx{R"((.*)-(\d+)-g([0-9a-f]+)(-dirty)?$)"};
        QRegularExpressionMatch match = rx.match(buildInfo.generatedVersion);
        if (match.hasMatch()) {
            QString distance = match.captured(2) == "0" ? QString{} : QString{"%1+%2 "}.arg(match.captured(1), match.captured(2));
            buildInfo.plainVersionString = QString{"v%1 (%2git-%3%4)"}.arg(buildInfo.baseVersion,
                                                                           distance,
                                                                           match.captured(3),
                                                                           match.captured(4));
            if (!buildInfo.commitHash.isEmpty()) {
                buildInfo.fancyVersionString = QString{"v%1 (%2git-<a href=\"https://github.com/quassel/quassel/commit/%5\">%3</a>%4)"}
                                                   .arg(buildInfo.baseVersion,
                                                        distance,
                                                        match.captured(3),
                                                        match.captured(4),
                                                        buildInfo.commitHash);
            }
        }
        else {
            buildInfo.plainVersionString = QString{"v%1 (invalid revision)"}.arg(buildInfo.baseVersion);
        }
    }
    if (buildInfo.fancyVersionString.isEmpty()) {
        buildInfo.fancyVersionString = buildInfo.plainVersionString;
    }

    instance()->_buildInfo = std::move(buildInfo);
}

const Quassel::BuildInfo& Quassel::buildInfo()
{
    return instance()->_buildInfo;
}

void Quassel::setupSignalHandling()
{
#ifndef Q_OS_WIN
    _signalWatcher = new PosixSignalWatcher(this);
#else
    _signalWatcher = new WindowsSignalWatcher(this);
#endif
    connect(_signalWatcher, &AbstractSignalWatcher::handleSignal, this, &Quassel::handleSignal);
}

void Quassel::handleSignal(AbstractSignalWatcher::Action action)
{
    switch (action) {
    case AbstractSignalWatcher::Action::Reload:
        // Most applications use this as the 'configuration reload' command, e.g. nginx uses it for graceful reloading of processes.
        if (!_reloadHandlers.empty()) {
            qInfo() << "Reloading configuration";
            if (reloadConfig()) {
                qInfo() << "Successfully reloaded configuration";
            }
        }
        break;
    case AbstractSignalWatcher::Action::Terminate:
        if (!_quitting) {
            quit();
        }
        else {
            qInfo() << "Already shutting down, ignoring signal";
        }
        break;
    case AbstractSignalWatcher::Action::HandleCrash:
        logBacktrace(instance()->coreDumpFileName());
        exit(EXIT_FAILURE);
    }
}

Quassel::RunMode Quassel::runMode()
{
    return instance()->_runMode;
}

void Quassel::setupCliParser()
{
    QList<QCommandLineOption> options;

    // General options
    /// @todo Bring back --datadir to specify the database location independent of config
    if (runMode() == RunMode::ClientOnly) {
        options += {{"c", "configdir"}, tr("Specify the directory holding the client configuration."), tr("path")};
    }
    else {
        options += {{"c", "configdir"},
                    tr("Specify the directory holding configuration files, the SQlite database and the SSL certificate."),
                    tr("path")};
    }

    // Client options
    if (runMode() != RunMode::CoreOnly) {
        options += {
            {"icontheme", tr("Override the system icon theme ('breeze' is recommended)."), tr("theme")},
            {"qss", tr("Load a custom application stylesheet."), tr("file.qss")},
            {"hidewindow", tr("Start the client minimized to the system tray.")},
            {"account", tr("Account id to connect to on startup."), tr("account"), "0"},
        };
    }

    // Core options
    if (runMode() != RunMode::ClientOnly) {
        options += {{"listen", tr("The address(es) quasselcore will listen on."), tr("<address>[,<address>[,...]]"), "::,0.0.0.0"},
                    {{"p", "port"}, tr("The port quasselcore will listen at."), tr("port"), "4242"},
                    {{"n", "norestore"}, tr("Don't restore last core's state.")},
                    {"config-from-environment", tr("Load configuration from environment variables.")},
                    {"select-backend", tr("Switch storage backend (migrating data if possible)."), tr("backendidentifier")},
                    {"select-authenticator", tr("Select authentication backend."), tr("authidentifier")},
                    {"add-user", tr("Starts an interactive session to add a new core user.")},
                    {"change-userpass",
                     tr("Starts an interactive session to change the password of the user identified by <username>."),
                     tr("username")},
                    {"strict-ident", tr("Use users' quasselcore username as ident reply. Ignores each user's configured ident setting.")},
                    {"ident-daemon", tr("Enable internal ident daemon.")},
                    {"ident-port",
                     tr("The port quasselcore will listen at for ident requests. Only meaningful with --ident-daemon."),
                     tr("port"),
                     "10113"},
                    {"ident-listen",
                     tr("The address(es) quasselcore will listen on for ident requests. Same format as --listen."),
                     tr("<address>[,...]"),
                     "::1,127.0.0.1"},
                    {"oidentd", tr("Enable oidentd integration. In most cases you should also enable --strict-ident.")},
                    {"oidentd-conffile", tr("Set path to oidentd configuration file."), tr("file")},
                    {"proxy-cidr", tr("Set IP range from which proxy protocol definitions are allowed"), tr("<address>[,...]"), "::1,127.0.0.1"},
                    {"require-ssl", tr("Require SSL for remote (non-loopback) client connections.")},
                    {"ssl-cert", tr("Specify the path to the SSL certificate."), tr("path"), "configdir/quasselCert.pem"},
                    {"ssl-key", tr("Specify the path to the SSL key."), tr("path"), "ssl-cert-path"},
                    {"metrics-daemon", tr("Enable metrics API.")},
                    {"metrics-port",
                     tr("The port quasselcore will listen at for metrics requests. Only meaningful with --metrics-daemon."),
                     tr("port"),
                     "9558"},
                    {"metrics-listen",
                     tr("The address(es) quasselcore will listen on for metrics requests. Same format as --listen."),
                     tr("<address>[,...]"),
                     "::1,127.0.0.1"}};
    }

    // Logging options
    options += {
        {{"L", "loglevel"}, tr("Supports one of Debug|Info|Warning|Error; default is Info."), tr("level"), "Info"},
        {{"l", "logfile"}, tr("Log to a file."), "path"},
#ifdef HAVE_SYSLOG
        {"syslog", tr("Log to syslog.")},
#endif
    };

    // Debug options
    options += {{"d", "debug"}, tr("Enable debug output.")};
    if (runMode() != RunMode::CoreOnly) {
        options += {
            {"debugbufferswitches", tr("Enables debugging for bufferswitches.")},
            {"debugmodel", tr("Enables debugging for models.")},
        };
    }
    if (runMode() != RunMode::ClientOnly) {
        options += {
            {"debug-irc", tr("Enable logging of all raw IRC messages to debug log, including passwords!  In most cases you should also set --loglevel Debug")},
            {"debug-irc-id", tr("Limit raw IRC logging to this network ID.  Implies --debug-irc"), tr("database network ID"), "-1"},
            {"debug-irc-parsed",
             tr("Enable logging of all parsed IRC messages to debug log, including passwords!  In most cases you should also set "
                "--loglevel Debug")},
            {"debug-irc-parsed-id",
             tr("Limit parsed IRC logging to this network ID.  Implies --debug-irc-parsed"),
             tr("database network ID"),
             "-1"},
        };
    }

    _cliParser.addOptions(options);
    _cliParser.addHelpOption();
    _cliParser.addVersionOption();
    _cliParser.setApplicationDescription(tr("Quassel IRC is a modern, distributed IRC client."));

    // This will call ::exit() for --help, --version and in case of errors
    _cliParser.process(*QCoreApplication::instance());
}

QString Quassel::optionValue(const QString& key)
{
    return instance()->_cliParser.value(key);
}

bool Quassel::isOptionSet(const QString& key)
{
    return instance()->_cliParser.isSet(key);
}

const QString& Quassel::coreDumpFileName()
{
    if (_coreDumpFileName.isEmpty()) {
        QDir configDir(configDirPath());
        _coreDumpFileName = configDir.absoluteFilePath(
            QString("Quassel-Crash-%1.log").arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmm")));
        QFile dumpFile(_coreDumpFileName);
        dumpFile.open(QIODevice::Append);
        QTextStream dumpStream(&dumpFile);
        dumpStream << "Quassel IRC: " << _buildInfo.baseVersion << ' ' << _buildInfo.commitHash << '\n';
        qDebug() << "Quassel IRC: " << _buildInfo.baseVersion << ' ' << _buildInfo.commitHash;
        dumpStream.flush();
        dumpFile.close();
    }
    return _coreDumpFileName;
}

QString Quassel::configDirPath()
{
    if (!instance()->_configDirPath.isEmpty())
        return instance()->_configDirPath;

    QString path;
    if (isOptionSet("configdir")) {
        path = Quassel::optionValue("configdir");
    }
    else {
#ifdef Q_OS_MAC
        // On Mac, the path is always the same
        path = QDir::homePath() + "/Library/Application Support/Quassel/";
#else
        // We abuse QSettings to find us a sensible path on the other platforms
#    ifdef Q_OS_WIN
        // don't use the registry
        QSettings::Format format = QSettings::IniFormat;
#    else
        QSettings::Format format = QSettings::NativeFormat;
#    endif
        QSettings s(format, QSettings::UserScope, QCoreApplication::organizationDomain(), buildInfo().applicationName);
        QFileInfo fileInfo(s.fileName());
        path = fileInfo.dir().absolutePath();
#endif /* Q_OS_MAC */
    }

    path = QFileInfo{path}.absoluteFilePath();

    if (!path.endsWith(QDir::separator()) && !path.endsWith('/'))
        path += QDir::separator();

    QDir qDir{path};
    if (!qDir.exists(path)) {
        if (!qDir.mkpath(path)) {
            qCritical() << "Unable to create Quassel config directory:" << qPrintable(qDir.absolutePath());
            return {};
        }
    }

    instance()->_configDirPath = path;
    return path;
}

QStringList Quassel::dataDirPaths()
{
    if (!instance()->_dataDirPaths.isEmpty())
        return instance()->_dataDirPaths;

    // TODO: Migrate to QStandardPaths (will require moving of the sqlite database,
    //       or a fallback for it being in the config dir)

    QStringList dataDirNames;
#ifdef Q_OS_WIN
    dataDirNames << QCoreApplication::applicationDirPath() + "/data/quassel/" << qgetenv("APPDATA") + QCoreApplication::organizationDomain()
                 << QCoreApplication::applicationDirPath();
#else
#    if defined Q_OS_MAC
    dataDirNames << QDir::homePath() + "/Library/Application Support/Quassel/" << QCoreApplication::applicationDirPath();
#    endif
    // Linux et al

    // XDG_DATA_HOME is the location for users to override system-installed files, usually in .local/share
    // This should thus come first.
    QString xdgDataHome = QFile::decodeName(qgetenv("XDG_DATA_HOME"));
    if (xdgDataHome.isEmpty())
        xdgDataHome = QDir::homePath() + QLatin1String("/.local/share");
    dataDirNames << xdgDataHome;

    // Now whatever is configured through XDG_DATA_DIRS
    QString xdgDataDirs = QFile::decodeName(qgetenv("XDG_DATA_DIRS"));
    if (xdgDataDirs.isEmpty())
        dataDirNames << "/usr/local/share"
                     << "/usr/share";
    else
        dataDirNames << xdgDataDirs.split(':', Qt::SkipEmptyParts);

    // Just in case, also check our install prefix
    dataDirNames << QCoreApplication::applicationDirPath() + "/../share";

    // Normalize and append our application name
    for (int i = 0; i < dataDirNames.count(); i++)
        dataDirNames[i] = QDir::cleanPath(dataDirNames.at(i)) + "/quassel/";

#endif

    // Add resource path and workdir just in case.
    // Workdir should have precedence
    dataDirNames.prepend(QCoreApplication::applicationDirPath() + "/data/");
    dataDirNames.append(":/data/");

    // Append trailing '/' and check for existence
    auto iter = dataDirNames.begin();
    while (iter != dataDirNames.end()) {
        if (!iter->endsWith(QDir::separator()) && !iter->endsWith('/'))
            iter->append(QDir::separator());
        if (!QFile::exists(*iter))
            iter = dataDirNames.erase(iter);
        else
            ++iter;
    }

    dataDirNames.removeDuplicates();

    instance()->_dataDirPaths = dataDirNames;
    return dataDirNames;
}

QString Quassel::findDataFilePath(const QString& fileName)
{
    QStringList dataDirs = dataDirPaths();
    for (const QString& dataDir : dataDirs) {
        QString path = dataDir + fileName;
        if (QFile::exists(path))
            return path;
    }
    return QString();
}

QStringList Quassel::scriptDirPaths()
{
    QStringList res(configDirPath() + "scripts/");
    for (const QString& path : dataDirPaths())
        res << path + "scripts/";
    return res;
}

QString Quassel::translationDirPath()
{
    if (instance()->_translationDirPath.isEmpty()) {
        // We support only one translation dir; fallback mechanisms wouldn't work else.
        // This means that if we have a $data/translations dir, the internal :/i18n resource won't be considered.
        for (const QString& dir : dataDirPaths()) {
            if (QFile::exists(dir + "translations/")) {
                instance()->_translationDirPath = dir + "translations/";
                break;
            }
        }
        if (instance()->_translationDirPath.isEmpty())
            instance()->_translationDirPath = ":/i18n/";
    }
    return instance()->_translationDirPath;
}

void Quassel::loadTranslation(const QLocale& locale)
{
    auto* qtTranslator = QCoreApplication::instance()->findChild<QTranslator*>("QtTr");
    auto* quasselTranslator = QCoreApplication::instance()->findChild<QTranslator*>("QuasselTr");

    if (qtTranslator)
        qApp->removeTranslator(qtTranslator);
    if (quasselTranslator)
        qApp->removeTranslator(quasselTranslator);

    // We use QLocale::C to indicate that we don't want a translation
    if (locale.language() == QLocale::C)
        return;

    qtTranslator = new QTranslator(qApp);
    qtTranslator->setObjectName("QtTr");

    quasselTranslator = new QTranslator(qApp);
    quasselTranslator->setObjectName("QuasselTr");

#ifndef Q_OS_MAC
    bool success = qtTranslator->load(locale, QString("qt_"), QLibraryInfo::path(QLibraryInfo::TranslationsPath));
    if (!success)
        success = qtTranslator->load(locale, QString("qt_"), QLibraryInfo::path(QLibraryInfo::TranslationsPath));
    if (!success)
        qWarning() << "Failed to load Qt translations for locale" << locale.name();
    success = quasselTranslator->load(locale, QString(""), translationDirPath());
    if (!success)
        qWarning() << "Failed to load Quassel translations for locale" << locale.name();
#else
    bool success = qtTranslator->load(QString("qt_%1").arg(locale.name()), translationDirPath());
    if (!success)
        success = qtTranslator->load(QString("qt_%1").arg(locale.name()), QLibraryInfo::path(QLibraryInfo::TranslationsPath));
    if (!success)
        qWarning() << "Failed to load Qt translations for locale" << locale.name();
    success = quasselTranslator->load(QString("%1").arg(locale.name()), translationDirPath());
    if (!success)
        qWarning() << "Failed to load Quassel translations for locale" << locale.name();
#endif

    qApp->installTranslator(quasselTranslator);
    qApp->installTranslator(qtTranslator);
}

// ---- Quassel::Features ---------------------------------------------------------------------------------------------

Quassel::Features::Features()
{
    QStringList features;

    auto featureEnum = QMetaEnum::fromType<Quassel::Feature>();
    _features.resize(featureEnum.keyCount(), true);  // enable all known features to true
}

Quassel::Features::Features(const QStringList& features, Quassel::LegacyFeatures legacyFeatures)
{
    auto featureEnum = QMetaEnum::fromType<Quassel::Feature>();
    _features.resize(featureEnum.keyCount(), false);

    for (const auto& feature : features) {
        int i = featureEnum.keyToValue(qPrintable(feature));
        if (i >= 0) {
            _features[i] = true;
        }
        else {
            _unknownFeatures << feature;
        }
    }

    if (legacyFeatures) {
        auto legacyFeatureEnum = QMetaEnum::fromType<Quassel::LegacyFeature>();
        for (quint32 mask = 0x0001; mask <= 0x8000; mask <<= 1) {
            if (static_cast<quint32>(legacyFeatures) & mask) {
                int i = featureEnum.keyToValue(legacyFeatureEnum.valueToKey(mask));
                if (i >= 0) {
                    _features[i] = true;
                }
            }
        }
    }
}

bool Quassel::Features::isEnabled(Feature feature) const
{
    auto i = static_cast<size_t>(feature);
    return i < _features.size() ? _features[i] : false;
}

QStringList Quassel::Features::toStringList(bool enabled) const
{
    // Check if any feature is enabled
    if (!enabled && std::all_of(_features.cbegin(), _features.cend(), [](bool feature) { return !feature; })) {
        return QStringList{} << "NoFeatures";
    }

    QStringList result;

    auto featureEnum = QMetaEnum::fromType<Quassel::Feature>();
    for (quint32 i = 0; i < _features.size(); ++i) {
        if (_features[i] == enabled) {
            result << featureEnum.key(i);
        }
    }
    return result;
}

Quassel::LegacyFeatures Quassel::Features::toLegacyFeatures() const
{
    quint32 result{0};
    auto featureEnum = QMetaEnum::fromType<Quassel::Feature>();
    auto legacyFeatureEnum = QMetaEnum::fromType<Quassel::LegacyFeature>();

    for (quint32 i = 0; i < _features.size(); ++i) {
        if (_features[i]) {
            int v = legacyFeatureEnum.keyToValue(featureEnum.key(i));
            if (v >= 0) {
                result |= v;
            }
        }
    }
    return static_cast<Quassel::LegacyFeatures>(result);
}

QStringList Quassel::Features::unknownFeatures() const
{
    return _unknownFeatures;
}
