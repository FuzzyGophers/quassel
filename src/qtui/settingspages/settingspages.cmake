# SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

# Putting $FOO in SETTINGSPAGES automatically includes
# $FOOsettingspage.cpp, $FOOsettingspage.h and $FOOsettingspage.ui

set(SETTINGSPAGES
    aliases
    appearance
    backlog
    bufferview
    chatmonitor
    chatview
    chatviewcolor
    connection
    coreconnection
    coreaccount
    corehighlight
    dcc
    highlight
    identities
    ignorelist
    inputwidget
    itemview
    networks
    topicwidget
)

# Specify additional files (e.g. for subdialogs) here!
set(SP_SOURCES
    aliasesmodel.cpp
    identityeditwidget.cpp
    ignorelistmodel.cpp
    notificationssettingspage.cpp

    # needed for automoc
    previewbufferview.h
)

set(SP_FORMS
    buffervieweditdlg.ui
    capseditdlg.ui
    coreaccounteditdlg.ui
    createidentitydlg.ui
    identityeditwidget.ui
    ignorelisteditdlg.ui
    networkadddlg.ui
    networkeditdlg.ui
    nickeditdlg.ui
    saveidentitiesdlg.ui
    servereditdlg.ui
)

if (NOT WITH_KDE)
    list(APPEND SETTINGSPAGES shortcuts)
    list(APPEND SP_SOURCES keysequencewidget.cpp shortcutsmodel.cpp)
endif()
