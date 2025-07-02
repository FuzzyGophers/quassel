// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include "abstractitemview.h"
#include "buffermodel.h"

class AbstractChatView;
class AbstractUiMsg;
class Buffer;

class UISUPPORT_EXPORT AbstractBufferContainer : public AbstractItemView
{
    Q_OBJECT

public:
    AbstractBufferContainer(QWidget* parent);

    inline BufferId currentBuffer() const { return _currentBuffer; }

signals:
    void currentChanged(BufferId);
    void currentChanged(const QModelIndex&);

protected:
    //! Create an AbstractChatView for the given BufferId and add it to the UI if necessary
    virtual AbstractChatView* createChatView(BufferId) = 0;

    //! Remove a chat view from the UI and delete it
    /** This method shall remove the view from the UI (for example, from a QStackedWidget) if appropriate.
     *  It also shall delete the object afterwards.
     * \param view The chat view to be removed and deleted
     */
    virtual void removeChatView(BufferId) = 0;

    //! If true, the marker line will be set automatically on buffer switch
    /** \return Whether the marker line should be set on buffer switch
     */
    virtual inline bool autoMarkerLine() const { return true; }

protected slots:
    void currentChanged(const QModelIndex& current, const QModelIndex& previous) override;
    void rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end) override;

    //! Show the given chat view
    /** This method is called when the given chat view should be displayed. Use this e.g. for
     *  selecting the appropriate page in a QStackedWidget.
     * \param view The chat view to be displayed. May be 0 if no chat view is selected.
     */
    virtual void showChatView(BufferId) = 0;

private slots:
    void removeBuffer(BufferId bufferId);
    void setCurrentBuffer(BufferId bufferId);

private:
    BufferId _currentBuffer;
    QHash<BufferId, AbstractChatView*> _chatViews;
};

class AbstractChatView
{
public:
    virtual ~AbstractChatView() = default;
    virtual MsgId lastMsgId() const = 0;
};
