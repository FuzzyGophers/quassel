// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "buffersyncer.h"

#include <utility>

BufferSyncer::BufferSyncer(QObject* parent)
    : SyncableObject(parent)
{
}

BufferSyncer::BufferSyncer(QHash<BufferId, MsgId> lastMsg,
                           QHash<BufferId, MsgId> lastSeenMsg,
                           QHash<BufferId, MsgId> markerLines,
                           QHash<BufferId, Message::Types> activities,
                           QHash<BufferId, int> highlightCounts,
                           QObject* parent)
    : SyncableObject(parent)
    , _lastMsg(std::move(lastMsg))
    , _lastSeenMsg(std::move(lastSeenMsg))
    , _markerLines(std::move(markerLines))
    , _bufferActivities(std::move(activities))
    , _highlightCounts(std::move(highlightCounts))
{
}

MsgId BufferSyncer::lastMsg(BufferId buffer) const
{
    return _lastMsg.value(buffer, MsgId());
}

MsgId BufferSyncer::lastSeenMsg(BufferId buffer) const
{
    return _lastSeenMsg.value(buffer, MsgId());
}

bool BufferSyncer::setLastSeenMsg(BufferId buffer, const MsgId& msgId)
{
    if (!msgId.isValid())
        return false;

    const MsgId oldLastSeenMsg = lastSeenMsg(buffer);
    if (!oldLastSeenMsg.isValid() || oldLastSeenMsg < msgId) {
        _lastSeenMsg[buffer] = msgId;
        SYNC(ARG(buffer), ARG(msgId))
        emit lastSeenMsgSet(buffer, msgId);
        return true;
    }
    return false;
}

MsgId BufferSyncer::markerLine(BufferId buffer) const
{
    return _markerLines.value(buffer, MsgId());
}

bool BufferSyncer::setMarkerLine(BufferId buffer, const MsgId& msgId)
{
    if (!msgId.isValid())
        return false;

    if (_markerLines.value(buffer) == msgId)
        return false;

    _markerLines[buffer] = msgId;
    SYNC(ARG(buffer), ARG(msgId))
    emit markerLineSet(buffer, msgId);
    return true;
}

QVariantList BufferSyncer::initLastMsg() const
{
    QVariantList list;
    QHash<BufferId, MsgId>::const_iterator iter = _lastMsg.constBegin();
    while (iter != _lastMsg.constEnd()) {
        list << QVariant::fromValue<BufferId>(iter.key()) << QVariant::fromValue<MsgId>(iter.value());
        ++iter;
    }
    return list;
}

void BufferSyncer::initSetLastMsg(const QVariantList& list)
{
    _lastMsg.clear();
    Q_ASSERT(list.count() % 2 == 0);
    for (int i = 0; i < list.count(); i += 2) {
        setLastMsg(list.at(i).value<BufferId>(), list.at(i + 1).value<MsgId>());
    }
}

QVariantList BufferSyncer::initLastSeenMsg() const
{
    QVariantList list;
    QHash<BufferId, MsgId>::const_iterator iter = _lastSeenMsg.constBegin();
    while (iter != _lastSeenMsg.constEnd()) {
        list << QVariant::fromValue(iter.key()) << QVariant::fromValue(iter.value());
        ++iter;
    }
    return list;
}

void BufferSyncer::initSetLastSeenMsg(const QVariantList& list)
{
    _lastSeenMsg.clear();
    Q_ASSERT(list.count() % 2 == 0);
    for (int i = 0; i < list.count(); i += 2) {
        setLastSeenMsg(list.at(i).value<BufferId>(), list.at(i + 1).value<MsgId>());
    }
}

QVariantList BufferSyncer::initMarkerLines() const
{
    QVariantList list;
    QHash<BufferId, MsgId>::const_iterator iter = _markerLines.constBegin();
    while (iter != _markerLines.constEnd()) {
        list << QVariant::fromValue(iter.key()) << QVariant::fromValue(iter.value());
        ++iter;
    }
    return list;
}

void BufferSyncer::initSetMarkerLines(const QVariantList& list)
{
    _markerLines.clear();
    Q_ASSERT(list.count() % 2 == 0);
    for (int i = 0; i < list.count(); i += 2) {
        setMarkerLine(list.at(i).value<BufferId>(), list.at(i + 1).value<MsgId>());
    }
}

QVariantList BufferSyncer::initActivities() const
{
    QVariantList list;
    auto iter = _bufferActivities.constBegin();
    while (iter != _bufferActivities.constEnd()) {
        list << QVariant::fromValue(iter.key()) << QVariant::fromValue((int)iter.value());
        ++iter;
    }
    return list;
}

void BufferSyncer::initSetActivities(const QVariantList& list)
{
    _bufferActivities.clear();
    Q_ASSERT(list.count() % 2 == 0);
    for (int i = 0; i < list.count(); i += 2) {
        setBufferActivity(list.at(i).value<BufferId>(), list.at(i + 1).value<int>());
    }
}

Message::Types BufferSyncer::activity(BufferId buffer) const
{
    return _bufferActivities.value(buffer, Message::Types());
}

void BufferSyncer::removeBuffer(BufferId buffer)
{
    if (_lastMsg.contains(buffer))
        _lastMsg.remove(buffer);
    if (_lastSeenMsg.contains(buffer))
        _lastSeenMsg.remove(buffer);
    if (_markerLines.contains(buffer))
        _markerLines.remove(buffer);
    if (_bufferActivities.contains(buffer))
        _bufferActivities.remove(buffer);
    if (_highlightCounts.contains(buffer))
        _highlightCounts.remove(buffer);
    SYNC(ARG(buffer))
    emit bufferRemoved(buffer);
}

void BufferSyncer::mergeBuffersPermanently(BufferId buffer1, BufferId buffer2)
{
    setLastMsg(buffer1, std::max(_lastMsg[buffer1], _lastMsg[buffer2]));
    setBufferActivity(buffer1, _bufferActivities[buffer1] | _bufferActivities[buffer2]);
    setHighlightCount(buffer1, _highlightCounts[buffer1] + _highlightCounts[buffer2]);

    if (_lastMsg.contains(buffer2))
        _lastMsg.remove(buffer2);
    if (_lastSeenMsg.contains(buffer2))
        _lastSeenMsg.remove(buffer2);
    if (_markerLines.contains(buffer2))
        _markerLines.remove(buffer2);
    if (_bufferActivities.contains(buffer2))
        _bufferActivities.remove(buffer2);
    if (_highlightCounts.contains(buffer2))
        _highlightCounts.remove(buffer2);
    SYNC(ARG(buffer1), ARG(buffer2))
    emit buffersPermanentlyMerged(buffer1, buffer2);
}

int BufferSyncer::highlightCount(BufferId buffer) const
{
    return _highlightCounts.value(buffer, 0);
}

QVariantList BufferSyncer::initHighlightCounts() const
{
    QVariantList list;
    auto iter = _highlightCounts.constBegin();
    while (iter != _highlightCounts.constEnd()) {
        list << QVariant::fromValue(iter.key()) << QVariant::fromValue((int)iter.value());
        ++iter;
    }
    return list;
}

void BufferSyncer::initSetHighlightCounts(const QVariantList& list)
{
    _highlightCounts.clear();
    Q_ASSERT(list.count() % 2 == 0);
    for (int i = 0; i < list.count(); i += 2) {
        setHighlightCount(list.at(i).value<BufferId>(), list.at(i + 1).value<int>());
    }
}
