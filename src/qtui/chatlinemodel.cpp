// SPDX-License-Identifier: GPL-2.0-or-later

#include "chatlinemodel.h"

#include "qtui.h"
#include "qtuistyle.h"

ChatLineModel::ChatLineModel(QObject* parent)
    : MessageModel(parent)
{
    qRegisterMetaType<WrapList>("ChatLineModel::WrapList");

    connect(QtUi::style(), &UiStyle::changed, this, &ChatLineModel::styleChanged);
}

// MessageModelItem *ChatLineModel::createMessageModelItem(const Message &msg) {
//   return new ChatLineModelItem(msg);
// }

void ChatLineModel::insertMessages__(int pos, const QList<Message>& messages)
{
    for (int i = 0; i < messages.count(); i++) {
        _messageList.insert(pos, ChatLineModelItem(messages[i]));
        pos++;
    }
}

Message ChatLineModel::takeMessageAt(int i)
{
    Message msg = _messageList[i].message();
    _messageList.removeAt(i);
    return msg;
}

void ChatLineModel::styleChanged()
{
    foreach (ChatLineModelItem item, _messageList) {
        item.invalidateWrapList();
    }
    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

QDataStream& operator<<(QDataStream& out, const ChatLineModel::WrapList wplist)
{
    out << wplist.count();
    ChatLineModel::WrapList::const_iterator it = wplist.begin();
    while (it != wplist.end()) {
        out << (*it).start << (*it).width << (*it).trailing;
        ++it;
    }
    return out;
}

QDataStream& operator>>(QDataStream& in, ChatLineModel::WrapList& wplist)
{
    quint16 cnt;
    in >> cnt;
    wplist.resize(cnt);
    for (quint16 i = 0; i < cnt; i++) {
        in >> wplist[i].start >> wplist[i].width >> wplist[i].trailing;
    }
    return in;
}
