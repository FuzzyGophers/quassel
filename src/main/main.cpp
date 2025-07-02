// SPDX-License-Identifier: GPL-2.0-or-later

#include <cstdlib>
#include <memory>

#ifdef HAVE_UMASK
#    include <sys/stat.h>
#    include <sys/types.h>
#endif /* HAVE_UMASK */

#include <QCoreApplication>

#ifdef BUILD_CORE
#    include "coreapplication.h"
#elif defined BUILD_QTUI
#    include "aboutdata.h"
#    include "qtuiapplication.h"
#elif defined BUILD_MONO
#    include "aboutdata.h"
#    include "monoapplication.h"

#else
#    error "Something is wrong - you need to #define a build mode!"
#endif

// We don't want quasselcore to depend on KDE
#if defined HAVE_KF6 && defined BUILD_CORE
#    undef HAVE_KF6
#endif

#if defined HAVE_KF6
#    include <KCoreAddons/KAboutData>
#    include <KCoreAddons/Kdelibs4ConfigMigrator>
#endif

#include "quassel.h"
#include "types.h"

int main(int argc, char** argv)
{
    // Set umask so files are created with restricted permissions
#ifdef HAVE_UMASK
    umask(S_IRWXG | S_IRWXO);
#endif

    // Instantiate early, so log messages are handled
    Quassel quassel;

    Quassel::setupBuildInfo();
    QCoreApplication::setApplicationName(Quassel::buildInfo().applicationName);
    QCoreApplication::setApplicationVersion(Quassel::buildInfo().plainVersionString);
    QCoreApplication::setOrganizationName(Quassel::buildInfo().organizationName);
    QCoreApplication::setOrganizationDomain(Quassel::buildInfo().organizationDomain);

    // Migrate settings from KDE to KF if appropriate
#ifdef HAVE_KF6
    Kdelibs4ConfigMigrator migrator(QCoreApplication::applicationName());
    migrator.setConfigFiles(QStringList() << "quasselrc"
                                          << "quassel.notifyrc");
    migrator.migrate();
#endif

    // Setup the High-DPI settings
#if QT_VERSION >= 0x050600 && defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);  // Added in Qt 5.6
#endif
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Instantiate application
#if defined BUILD_CORE
    CoreApplication app(argc, argv);
    const auto runMode = Quassel::RunMode::CoreOnly;
#elif defined BUILD_QTUI
    QtUiApplication app(argc, argv);
    const auto runMode = Quassel::RunMode::ClientOnly;
#elif defined BUILD_MONO
    MonolithicApplication app(argc, argv);
    const auto runMode = Quassel::RunMode::Monolithic;
#endif

    try {
        Quassel::instance()->init(runMode);

#ifdef HAVE_KF6
        AboutData aboutData;
        AboutData::setQuasselPersons(&aboutData);
        KAboutData::setApplicationData(aboutData.kAboutData());
#endif

        // Initialize the application
        app.init();
    }
    catch (ExitException e) {
        if (!e.errorString.isEmpty()) {
            qCritical() << qPrintable(e.errorString);
        }
        return e.exitCode;
    }

    return app.exec();
}
