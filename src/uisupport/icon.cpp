// SPDX-License-Identifier: GPL-2.0-or-later

#include "icon.h"

#include <set>

#include <QDebug>

namespace icon {

namespace {

void printWarning(const QString& iconName, const QString& extra = {})
{
    static std::set<QString> warnedAbout;
    if (warnedAbout.insert(iconName).second) {
        qWarning() << "Missing icon:" << iconName << qPrintable(extra);
    }
}

}  // namespace

QIcon get(const QString& iconName, const QString& fallbackPath)
{
    return get(std::vector<QString>{iconName}, fallbackPath);
}

QIcon get(const std::vector<QString>& iconNames, const QString& fallbackPath)
{
    for (auto&& iconName : iconNames) {
        // Exact match
        if (QIcon::hasThemeIcon(iconName)) {
            return QIcon::fromTheme(iconName);
        }
    }

    for (auto&& iconName : iconNames) {
        // Try to get something from the theme anyway (i.e. a more generic fallback)
        QIcon fallback = QIcon::fromTheme(iconName);
        if (!fallback.availableSizes().isEmpty()) {
            printWarning(iconName, QString{"(using fallback: \"%1\")"}.arg(fallback.name()));
            return fallback;
        }
    }

    // Build error string
    QStringList requested;
    for (auto&& iconName : iconNames) {
        requested << iconName;
    }
    QString missing = "{" + requested.join(", ") + "}";

    // Nothing from the theme, so try to load from path if given
    if (!fallbackPath.isEmpty()) {
        QIcon fallback{fallbackPath};
        if (!fallback.availableSizes().isEmpty()) {
            printWarning(missing, QString{"(using fallback: \"%1\")"}.arg(fallbackPath));
            return fallback;
        }
    }

    // Meh.
    printWarning(missing);
    return {};
}

}  // namespace icon
