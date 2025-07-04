// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SHORTCUTSMODEL_H
#define SHORTCUTSMODEL_H

#include <QAbstractItemModel>
#include <QKeySequence>

class Action;
class ActionCollection;

//! Model that exposes the actions from one or more ActionCollections
/** This model takes one or more ActionCollections and exposes their actions as model items.
 *  Note that the ShortcutsModel will not react to changes in the ActionCollection (e.g. adding,
 *  removing actions), because it is supposed to be used after all actions being defined.
 */
class ShortcutsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Role
    {
        ActionRole = Qt::UserRole,
        DefaultShortcutRole,
        ActiveShortcutRole,
        IsConfigurableRole
    };

    ShortcutsModel(const QHash<QString, ActionCollection*>& actionCollections, QObject* parent = nullptr);
    ~ShortcutsModel() override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = ActiveShortcutRole) override;

public slots:
    //! Load shortcuts from the ActionCollections
    /** Note that this will not rebuild the internal structure of the model, as we assume the
     *  ActionCollections to be static during the lifetime of the settingspage. This will merely
     *  re-read the shortcuts currently set in Quassel.
     */
    void load();

    //! Load default shortcuts from the ActionCollections
    /** Note that this will not rebuild the internal structure of the model, as we assume the
     *  ActionCollections to be static during the lifetime of the settingspage. This will update
     *  the model's state from the ActionCollections' defaults.
     */
    void defaults();

    //! Commit the model changes to the ActionCollections
    void commit();

    inline bool hasChanged() const { return _changedCount; }

signals:
    //! Reflects the difference between model contents and the ActionCollections we loaded this from
    void changed(bool changed);

private:
    struct Item
    {
        inline Item()
        {
            parentItem = nullptr;
            collection = nullptr;
            action = nullptr;
        }
        inline ~Item() { qDeleteAll(actionItems); }
        int row;
        Item* parentItem;
        ActionCollection* collection;
        Action* action;
        QKeySequence shortcut;
        QList<Item*> actionItems;
    };

    QList<Item*> _categoryItems;
    int _changedCount;
};

#endif  // SHORTCUTSMODEL_H
