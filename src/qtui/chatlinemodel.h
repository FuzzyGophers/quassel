// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CHATLINEMODEL_H_
#define CHATLINEMODEL_H_

#include <QList>
#include <QMetaType>

#include "chatlinemodelitem.h"
#include "messagemodel.h"

class ChatLineModel : public MessageModel
{
    Q_OBJECT

public:
    enum ChatLineRole
    {
        WrapListRole = MessageModel::UserRole,
        MsgLabelRole,
        SelectedBackgroundRole
    };

    ChatLineModel(QObject* parent = nullptr);

    using Word = ChatLineModelItem::Word;
    using WrapList = ChatLineModelItem::WrapList;
    inline const MessageModelItem* messageItemAt(int i) const override { return &_messageList[i]; }

protected:
    // virtual MessageModelItem *createMessageModelItem(const Message &);

    inline int messageCount() const override { return _messageList.count(); }
    inline bool messagesIsEmpty() const override { return _messageList.isEmpty(); }
    inline MessageModelItem* messageItemAt(int i) override { return &_messageList[i]; }
    inline const MessageModelItem* firstMessageItem() const override { return &_messageList.first(); }
    inline MessageModelItem* firstMessageItem() override { return &_messageList.first(); }
    inline const MessageModelItem* lastMessageItem() const override { return &_messageList.last(); }
    inline MessageModelItem* lastMessageItem() override { return &_messageList.last(); }
    inline void insertMessage__(int pos, const Message& msg) override { _messageList.insert(pos, ChatLineModelItem(msg)); }
    void insertMessages__(int pos, const QList<Message>&) override;
    inline void removeMessageAt(int i) override { _messageList.removeAt(i); }
    inline void removeAllMessages() override { _messageList.clear(); }
    Message takeMessageAt(int i) override;

protected slots:
    virtual void styleChanged();

private:
    QList<ChatLineModelItem> _messageList;
};

QDataStream& operator<<(QDataStream& out, const ChatLineModel::WrapList);
QDataStream& operator>>(QDataStream& in, ChatLineModel::WrapList&);

Q_DECLARE_METATYPE(ChatLineModel::WrapList)

#endif
