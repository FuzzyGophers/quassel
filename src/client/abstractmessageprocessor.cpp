// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "abstractmessageprocessor.h"

#include "client.h"

AbstractMessageProcessor::AbstractMessageProcessor(QObject* parent)
    : QObject(parent)
{
}
