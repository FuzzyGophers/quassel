// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quassel.h"

#if defined(HAVE_BACKTRACE) && !defined(Q_OS_MAC)
#    define BUILD_CRASHHANDLER
#    include <QDebug>
#    include <QFile>
#    include <QTextStream>

#    include <cxxabi.h>
#    include <dlfcn.h>

#    include "backtrace_config.h"
#endif

void Quassel::logBacktrace(const QString& filename)
{
#ifndef BUILD_CRASHHANDLER
    Q_UNUSED(filename)
#else
    void* callstack[128];
    int i, frames = backtrace(callstack, 128);

    QFile dumpFile(filename);
    dumpFile.open(QIODevice::Append);
    QTextStream dumpStream(&dumpFile);

    for (i = 0; i < frames; ++i) {
        Dl_info info;
        dladdr(callstack[i], &info);
        // as a reference:
        //     typedef struct
        //     {
        //       __const char *dli_fname;   /* File name of defining object.  */
        //       void *dli_fbase;           /* Load address of that object.  */
        //       __const char *dli_sname;   /* Name of nearest symbol.  */
        //       void *dli_saddr;           /* Exact value of nearest symbol.  */
        //     } Dl_info;

#    ifdef __LP64__
        int addrSize = 16;
#    else
        int addrSize = 8;
#    endif

        QString funcName;
        if (info.dli_sname) {
            char* func = abi::__cxa_demangle(info.dli_sname, nullptr, nullptr, nullptr);
            if (func) {
                funcName = QString(func);
                free(func);
            }
            else {
                funcName = QString(info.dli_sname);
            }
        }
        else {
            funcName = QString("0x%1").arg((ulong)(info.dli_saddr), addrSize, 16, QLatin1Char('0'));
        }

        // prettificating the filename
        QString fileName("???");
        if (info.dli_fname) {
            fileName = QString(info.dli_fname);
            int slashPos = fileName.lastIndexOf('/');
            if (slashPos != -1)
                fileName = fileName.mid(slashPos + 1);
        }

        QString debugLine = QString("#%1 %2 0x%3 %4")
                                .arg(i, 3, 10)
                                .arg(fileName, -20)
                                .arg((ulong)(callstack[i]), addrSize, 16, QLatin1Char('0'))
                                .arg(funcName);

        dumpStream << debugLine << "\n";
        qDebug() << qPrintable(debugLine);
    }
    dumpFile.close();
#endif /* BUILD_CRASHHANDLER */
}
