// SPDX-License-Identifier: GPL-2.0-or-later

#include "windowssignalwatcher.h"

#include <signal.h>
#include <windows.h>

#include <QDebug>

// This handler is called by Windows in a different thread when a console event happens
// FIXME: When the console window is closed, the application is supposedly terminated as soon as
//        this handler returns. We may want to block and wait for the main thread so set some
//        condition variable once shutdown is complete...
static BOOL WINAPI consoleCtrlHandler(DWORD ctrlType)
{
    switch (ctrlType) {
    case CTRL_C_EVENT:      // Ctrl+C
    case CTRL_CLOSE_EVENT:  // Closing the console window
        WindowsSignalWatcher::signalHandler(SIGTERM);
        return TRUE;
    default:
        return FALSE;
    }
}

WindowsSignalWatcher::WindowsSignalWatcher(QObject* parent)
    : AbstractSignalWatcher{parent}
    , Singleton<WindowsSignalWatcher>{this}
{
    static bool registered = []() {
        qRegisterMetaType<AbstractSignalWatcher::Action>();
        return true;
    }();
    Q_UNUSED(registered)

    // Use POSIX-style API to register standard signals.
    // Not sure if this is safe to use, but it has worked so far...
    signal(SIGTERM, signalHandler);
    signal(SIGINT,  signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGSEGV, signalHandler);

    // React on console window events
    SetConsoleCtrlHandler(consoleCtrlHandler, TRUE);
}

void WindowsSignalWatcher::signalHandler(int signal)
{
    qInfo() << "Caught signal" << signal;

    switch (signal) {
    case SIGINT:
    case SIGTERM:
        emit instance()->handleSignal(Action::Terminate);
        break;
    case SIGABRT:
    case SIGSEGV:
        emit instance()->handleSignal(Action::HandleCrash);
        break;
    default:
        ;
    }
}
