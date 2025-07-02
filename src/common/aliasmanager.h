// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <utility>

#include <QVariantMap>

#include "bufferinfo.h"
#include "syncableobject.h"

class Network;

class COMMON_EXPORT AliasManager : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

public:
    inline AliasManager(QObject* parent = nullptr)
        : SyncableObject(parent)
    {
        setAllowClientUpdates(true);
    }

    struct Alias
    {
        QString name;
        QString expansion;
        Alias(QString name_, QString expansion_)
            : name(std::move(name_))
            , expansion(std::move(expansion_))
        {}
    };
    using AliasList = QList<Alias>;

    int indexOf(const QString& name) const;
    inline bool contains(const QString& name) const { return indexOf(name) != -1; }
    inline bool isEmpty() const { return _aliases.isEmpty(); }
    inline int count() const { return _aliases.count(); }
    inline void removeAt(int index) { _aliases.removeAt(index); }
    inline Alias& operator[](int i) { return _aliases[i]; }
    inline const Alias& operator[](int i) const { return _aliases.at(i); }
    inline const AliasList& aliases() const { return _aliases; }

    static AliasList defaults();

    using CommandList = QList<QPair<BufferInfo, QString>>;

    CommandList processInput(const BufferInfo& info, const QString& message);

public slots:
    virtual QVariantMap initAliases() const;
    virtual void initSetAliases(const QVariantMap& aliases);

    virtual void addAlias(const QString& name, const QString& expansion);

protected:
    void setAliases(const QList<Alias>& aliases) { _aliases = aliases; }
    virtual const Network* network(NetworkId) const = 0;  // core and client require different access

private:
    void processInput(const BufferInfo& info, const QString& message, CommandList& previousCommands);
    void expand(const QString& alias, const BufferInfo& bufferInfo, const QString& msg, CommandList& previousCommands);

    AliasList _aliases;
};
