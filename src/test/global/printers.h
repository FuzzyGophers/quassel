// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "test-global-export.h"

#include <iostream>

#include <QByteArray>
#include <QDateTime>
#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>

#include "testglobal.h"

// GTest printers for commonly used Qt types

TEST_GLOBAL_EXPORT void PrintTo(const QByteArray&, std::ostream*);
TEST_GLOBAL_EXPORT void PrintTo(const QDateTime&, std::ostream*);
TEST_GLOBAL_EXPORT void PrintTo(const QString&, std::ostream*);
TEST_GLOBAL_EXPORT void PrintTo(const QVariant&, std::ostream*);
TEST_GLOBAL_EXPORT void PrintTo(const QVariantList&, std::ostream*);
TEST_GLOBAL_EXPORT void PrintTo(const QVariantMap&, std::ostream*);
