// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QMap>
#include <QPointer>
#include <QString>

#include "types.h"

class MultiLineEdit;
class IrcUser;
class Network;

class UISUPPORT_EXPORT TabCompleter : public QObject
{
    Q_OBJECT

public:
    enum Type
    {
        UserTab = 0x01,
        ChannelTab = 0x02
    };

    explicit TabCompleter(MultiLineEdit* inputLine_);

    void reset();
    void complete();

    bool eventFilter(QObject* obj, QEvent* event) override;

public slots:
    void onTabCompletionKey();

private:
    struct CompletionKey
    {
        inline CompletionKey(const QString& n) { contents = n; }
        bool operator<(const CompletionKey& other) const;
        QString contents;
    };

    QPointer<MultiLineEdit> _lineEdit;
    bool _enabled;
    QString _nickSuffix;

    static const Network* _currentNetwork;
    static BufferId _currentBufferId;
    static QString _currentBufferName;
    static Type _completionType;

    QMap<CompletionKey, QString> _completionMap;
    // QStringList completionTemplates;

    QMap<CompletionKey, QString>::Iterator _nextCompletion;
    int _lastCompletionLength;

    void buildCompletionList();
};
