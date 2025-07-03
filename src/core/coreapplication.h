// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "core-export.h"

#include <memory>

#include <QCoreApplication>

#include "core.h"
#include "quassel.h"

class Core;

class CORE_EXPORT CoreApplication : public QCoreApplication
{
    Q_OBJECT

public:
    CoreApplication(int& argc, char** argv);

    void init();

private slots:
    void onShutdownComplete();

private:
    std::unique_ptr<Core> _core;
};
