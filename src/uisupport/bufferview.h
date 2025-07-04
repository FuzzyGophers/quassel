// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QAction>
#include <QDockWidget>
#include <QMenu>
#include <QModelIndex>
#include <QPointer>
#include <QStyledItemDelegate>

#include "actioncollection.h"
#include "bufferviewconfig.h"
#include "networkmodel.h"
#include "treeviewtouch.h"
#include "types.h"

/*****************************************
 * The TreeView showing the Buffers
 *****************************************/
class UISUPPORT_EXPORT BufferView : public TreeViewTouch
{
    Q_OBJECT

public:
    enum Direction
    {
        Forward = 1,
        Backward = -1
    };

    BufferView(QWidget* parent = nullptr);
    void init();

    void setModel(QAbstractItemModel* model) override;
    void setFilteredModel(QAbstractItemModel* model, BufferViewConfig* config);

    void setConfig(BufferViewConfig* config);
    inline BufferViewConfig* config() { return _config; }

    void addActionsToMenu(QMenu* menu, const QModelIndex& index);
    void addFilterActions(QMenu* contextMenu, const QModelIndex& index);

    void selectFirstBuffer();

public slots:
    void setRootIndexForNetworkId(const NetworkId& networkId);
    void removeSelectedBuffers(bool permanently = false);
    void menuActionTriggered(QAction*);
    void nextBuffer();
    void previousBuffer();
    void hideCurrentBuffer();
    void filterTextChanged(const QString& filterString);
    void changeHighlight(Direction direction);
    void selectHighlighted();
    void clearHighlight();

signals:
    void removeBuffer(const QModelIndex&);
    void removeBufferPermanently(const QModelIndex&);

protected:
    void dropEvent(QDropEvent* event) override;
    void rowsInserted(const QModelIndex& parent, int start, int end) override;
    void wheelEvent(QWheelEvent*) override;
    void focusInEvent(QFocusEvent* event) override { QAbstractScrollArea::focusInEvent(event); }
    void contextMenuEvent(QContextMenuEvent* event) override;

    void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles) override;

private slots:
    void joinChannel(const QModelIndex& index);
    void toggleHeader(bool checked);

    /**
     * Expand all active networks and collapse inactive ones unless manually changed
     *
     * Applies to all networks.  Shouldn't need called except during initialization.
     */
    void setExpandedState();

    /**
     * Save the current display state of the given network
     *
     * Tracks expanded or collapsed and active or inactive.
     *
     * @see setExpandedState()
     * @param[in] networkIdx QModelIndex of the root network to store
     */
    void storeExpandedState(const QModelIndex& networkIdx);

    /**
     * Set the display state of the given network according to network status and manual changes
     *
     * Expands if active or previously expanded, collapses if inactive or previously collapsed.
     *
     * @see storeExpandedState()
     * @param[in] networkIdx QModelIndex of the root network to update
     */
    void setExpandedState(const QModelIndex& networkIdx);

    void on_configChanged();
    void on_layoutChanged();

    void changeBuffer(Direction direction);

private:
    QPointer<BufferViewConfig> _config;

    enum ExpandedState
    {
        WasExpanded = 0x01,
        WasActive = 0x02
    };
    QHash<NetworkId, short> _expandedState;
    QModelIndex _currentHighlight;
};

// ******************************
//  BufferViewDelegate
// ******************************

class BufferViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    BufferViewDelegate(QObject* parent = nullptr);
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

public:
    QModelIndex currentHighlight;

protected:
    void customEvent(QEvent* event) override;
};

// ==============================
//  BufferView Dock
// ==============================
class UISUPPORT_EXPORT BufferViewDock : public QDockWidget
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive WRITE setActive STORED true)

public:
    BufferViewDock(BufferViewConfig* config, QWidget* parent);

    int bufferViewId() const;
    BufferViewConfig* config() const;
    inline BufferView* bufferView() const { return qobject_cast<BufferView*>(widget()); }
    inline bool isActive() const { return _active; }
    void setWidget(QWidget* newWidget);
    void setLocked(bool locked);
    QWidget* widget() const { return _childWidget; }

    void activateFilter();

public slots:
    void setActive(bool active = true);

protected slots:
    bool eventFilter(QObject* object, QEvent* event) override;
    void focusInEvent(QFocusEvent* event) override { qDebug() << event; }

private slots:
    void bufferViewRenamed(const QString& newName);
    void updateTitle();
    void configChanged();
    void onFilterReturnPressed();

private:
    QWidget* _childWidget;
    QWidget* _widget;
    QPointer<QWidget> _oldFocusItem;  // QPointer in case the old item gets deleted
    QLineEdit* _filterEdit;
    bool _active;
    QString _title;
};
