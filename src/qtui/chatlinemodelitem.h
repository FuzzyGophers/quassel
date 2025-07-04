// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "messagemodel.h"
#include "uistyle.h"

class ChatLineModelItem : public MessageModelItem
{
public:
    ChatLineModelItem(const Message&);

    QVariant data(int column, int role) const override;
    bool setData(int column, const QVariant& value, int role) override;

    inline const Message& message() const override { return _styledMsg; }
    inline const QDateTime& timestamp() const override { return _styledMsg.timestamp(); }
    inline const MsgId& msgId() const override { return _styledMsg.msgId(); }
    inline const BufferId& bufferId() const override { return _styledMsg.bufferId(); }
    inline void setBufferId(BufferId bufferId) override { _styledMsg.setBufferId(bufferId); }
    inline Message::Type msgType() const override { return _styledMsg.type(); }
    inline Message::Flags msgFlags() const override { return _styledMsg.flags(); }

    virtual inline void invalidateWrapList() { _wrapList.clear(); }

    /// Used to store information about words to be used for wrapping
    struct Word
    {
        quint16 start;
        qreal endX;
        qreal width;
        qreal trailing;
    };
    using WrapList = QVector<Word>;

private:
    QVariant timestampData(int role) const;
    QVariant senderData(int role) const;
    QVariant contentsData(int role) const;

    QVariant backgroundBrush(UiStyle::FormatType subelement, bool selected = false) const;
    UiStyle::MessageLabel messageLabel() const;

    void computeWrapList() const;

    mutable WrapList _wrapList;
    UiStyle::StyledMessage _styledMsg;

    static unsigned char* TextBoundaryFinderBuffer;
    static int TextBoundaryFinderBufferSize;
};
