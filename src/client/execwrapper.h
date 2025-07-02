// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef EXECWRAPPER_H_
#define EXECWRAPPER_H_

#include <QProcess>

#include "bufferinfo.h"

class ExecWrapper : public QObject
{
    Q_OBJECT

public:
    ExecWrapper(QObject* parent = nullptr);

public slots:
    void start(const BufferInfo& info, const QString& command);

signals:
    void error(const QString& errorMsg);
    void output(const QString& out);

private slots:
    void processReadStdout();
    void processReadStderr();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError);

    void postStdout(const QString&);
    void postStderr(const QString&);

private:
    QProcess _process;
    BufferInfo _bufferInfo;
    QString _scriptName;
    QString _stdoutBuffer;
    QString _stderrBuffer;
};

#endif
