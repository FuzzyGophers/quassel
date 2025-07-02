/****************************************************************************
** Meta object code from reading C++ file 'buffersyncer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/buffersyncer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buffersyncer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12BufferSyncerE_t {};
} // unnamed namespace

template <> constexpr inline auto BufferSyncer::qt_create_metaobjectdata<qt_meta_tag_ZN12BufferSyncerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BufferSyncer",
        "lastMsgSet",
        "",
        "BufferId",
        "buffer",
        "MsgId",
        "msgId",
        "lastSeenMsgSet",
        "markerLineSet",
        "bufferRemoved",
        "bufferRenamed",
        "newName",
        "buffersPermanentlyMerged",
        "buffer1",
        "buffer2",
        "bufferMarkedAsRead",
        "bufferActivityChanged",
        "Message::Types",
        "highlightCountChanged",
        "initLastMsg",
        "QVariantList",
        "initSetLastMsg",
        "initLastSeenMsg",
        "initSetLastSeenMsg",
        "initMarkerLines",
        "initSetMarkerLines",
        "initActivities",
        "initSetActivities",
        "initHighlightCounts",
        "initSetHighlightCounts",
        "setLastMsg",
        "requestSetLastSeenMsg",
        "requestSetMarkerLine",
        "setBufferActivity",
        "activity",
        "setHighlightCount",
        "count",
        "requestRemoveBuffer",
        "removeBuffer",
        "requestRenameBuffer",
        "renameBuffer",
        "requestMergeBuffersPermanently",
        "mergeBuffersPermanently",
        "requestPurgeBufferIds",
        "requestMarkBufferAsRead",
        "markBufferAsRead",
        "setLastSeenMsg",
        "setMarkerLine"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'lastMsgSet'
        QtMocHelpers::SignalData<void(BufferId, const MsgId &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'lastSeenMsgSet'
        QtMocHelpers::SignalData<void(BufferId, const MsgId &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'markerLineSet'
        QtMocHelpers::SignalData<void(BufferId, const MsgId &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'bufferRemoved'
        QtMocHelpers::SignalData<void(BufferId)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'bufferRenamed'
        QtMocHelpers::SignalData<void(BufferId, QString)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QString, 11 },
        }}),
        // Signal 'buffersPermanentlyMerged'
        QtMocHelpers::SignalData<void(BufferId, BufferId)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 13 }, { 0x80000000 | 3, 14 },
        }}),
        // Signal 'bufferMarkedAsRead'
        QtMocHelpers::SignalData<void(BufferId)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'bufferActivityChanged'
        QtMocHelpers::SignalData<void(BufferId, Message::Types)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 17, 2 },
        }}),
        // Signal 'highlightCountChanged'
        QtMocHelpers::SignalData<void(BufferId, int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { QMetaType::Int, 2 },
        }}),
        // Slot 'initLastMsg'
        QtMocHelpers::SlotData<QVariantList() const>(19, 2, QMC::AccessPublic, 0x80000000 | 20),
        // Slot 'initSetLastMsg'
        QtMocHelpers::SlotData<void(const QVariantList &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 2 },
        }}),
        // Slot 'initLastSeenMsg'
        QtMocHelpers::SlotData<QVariantList() const>(22, 2, QMC::AccessPublic, 0x80000000 | 20),
        // Slot 'initSetLastSeenMsg'
        QtMocHelpers::SlotData<void(const QVariantList &)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 2 },
        }}),
        // Slot 'initMarkerLines'
        QtMocHelpers::SlotData<QVariantList() const>(24, 2, QMC::AccessPublic, 0x80000000 | 20),
        // Slot 'initSetMarkerLines'
        QtMocHelpers::SlotData<void(const QVariantList &)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 2 },
        }}),
        // Slot 'initActivities'
        QtMocHelpers::SlotData<QVariantList() const>(26, 2, QMC::AccessPublic, 0x80000000 | 20),
        // Slot 'initSetActivities'
        QtMocHelpers::SlotData<void(const QVariantList &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 2 },
        }}),
        // Slot 'initHighlightCounts'
        QtMocHelpers::SlotData<QVariantList() const>(28, 2, QMC::AccessPublic, 0x80000000 | 20),
        // Slot 'initSetHighlightCounts'
        QtMocHelpers::SlotData<void(const QVariantList &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 2 },
        }}),
        // Slot 'setLastMsg'
        QtMocHelpers::SlotData<void(BufferId, const MsgId &)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Slot 'requestSetLastSeenMsg'
        QtMocHelpers::SlotData<void(BufferId, const MsgId &)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Slot 'requestSetMarkerLine'
        QtMocHelpers::SlotData<void(BufferId, const MsgId &)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Slot 'setBufferActivity'
        QtMocHelpers::SlotData<void(BufferId, int)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Int, 34 },
        }}),
        // Slot 'setHighlightCount'
        QtMocHelpers::SlotData<void(BufferId, int)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Int, 36 },
        }}),
        // Slot 'requestRemoveBuffer'
        QtMocHelpers::SlotData<void(BufferId)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'removeBuffer'
        QtMocHelpers::SlotData<void(BufferId)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'requestRenameBuffer'
        QtMocHelpers::SlotData<void(BufferId, QString)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QString, 11 },
        }}),
        // Slot 'renameBuffer'
        QtMocHelpers::SlotData<void(BufferId, QString)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QString, 11 },
        }}),
        // Slot 'requestMergeBuffersPermanently'
        QtMocHelpers::SlotData<void(BufferId, BufferId)>(41, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 13 }, { 0x80000000 | 3, 14 },
        }}),
        // Slot 'mergeBuffersPermanently'
        QtMocHelpers::SlotData<void(BufferId, BufferId)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 13 }, { 0x80000000 | 3, 14 },
        }}),
        // Slot 'requestPurgeBufferIds'
        QtMocHelpers::SlotData<void()>(43, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'requestMarkBufferAsRead'
        QtMocHelpers::SlotData<void(BufferId)>(44, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'markBufferAsRead'
        QtMocHelpers::SlotData<void(BufferId)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'setLastSeenMsg'
        QtMocHelpers::SlotData<bool(BufferId, const MsgId &)>(46, 2, QMC::AccessProtected, QMetaType::Bool, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Slot 'setMarkerLine'
        QtMocHelpers::SlotData<bool(BufferId, const MsgId &)>(47, 2, QMC::AccessProtected, QMetaType::Bool, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BufferSyncer, qt_meta_tag_ZN12BufferSyncerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BufferSyncer::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12BufferSyncerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12BufferSyncerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12BufferSyncerE_t>.metaTypes,
    nullptr
} };

void BufferSyncer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BufferSyncer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->lastMsgSet((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2]))); break;
        case 1: _t->lastSeenMsgSet((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2]))); break;
        case 2: _t->markerLineSet((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2]))); break;
        case 3: _t->bufferRemoved((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 4: _t->bufferRenamed((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->buffersPermanentlyMerged((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[2]))); break;
        case 6: _t->bufferMarkedAsRead((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 7: _t->bufferActivityChanged((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Message::Types>>(_a[2]))); break;
        case 8: _t->highlightCountChanged((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 9: { QVariantList _r = _t->initLastMsg();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->initSetLastMsg((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 11: { QVariantList _r = _t->initLastSeenMsg();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->initSetLastSeenMsg((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 13: { QVariantList _r = _t->initMarkerLines();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->initSetMarkerLines((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 15: { QVariantList _r = _t->initActivities();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->initSetActivities((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 17: { QVariantList _r = _t->initHighlightCounts();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->initSetHighlightCounts((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 19: _t->setLastMsg((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2]))); break;
        case 20: _t->requestSetLastSeenMsg((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2]))); break;
        case 21: _t->requestSetMarkerLine((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2]))); break;
        case 22: _t->setBufferActivity((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 23: _t->setHighlightCount((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 24: _t->requestRemoveBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 25: _t->removeBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 26: _t->requestRenameBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 27: _t->renameBuffer((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 28: _t->requestMergeBuffersPermanently((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[2]))); break;
        case 29: _t->mergeBuffersPermanently((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[2]))); break;
        case 30: _t->requestPurgeBufferIds(); break;
        case 31: _t->requestMarkBufferAsRead((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 32: _t->markBufferAsRead((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1]))); break;
        case 33: { bool _r = _t->setLastSeenMsg((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { bool _r = _t->setMarkerLine((*reinterpret_cast< std::add_pointer_t<BufferId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MsgId>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 26:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 27:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 28:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 29:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 31:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            }
            break;
        case 33:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        case 34:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BufferId >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MsgId >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId , const MsgId & )>(_a, &BufferSyncer::lastMsgSet, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId , const MsgId & )>(_a, &BufferSyncer::lastSeenMsgSet, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId , const MsgId & )>(_a, &BufferSyncer::markerLineSet, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId )>(_a, &BufferSyncer::bufferRemoved, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId , QString )>(_a, &BufferSyncer::bufferRenamed, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId , BufferId )>(_a, &BufferSyncer::buffersPermanentlyMerged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId )>(_a, &BufferSyncer::bufferMarkedAsRead, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId , Message::Types )>(_a, &BufferSyncer::bufferActivityChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferSyncer::*)(BufferId , int )>(_a, &BufferSyncer::highlightCountChanged, 8))
            return;
    }
}

const QMetaObject *BufferSyncer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BufferSyncer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12BufferSyncerE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int BufferSyncer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    return _id;
}

// SIGNAL 0
void BufferSyncer::lastMsgSet(BufferId _t1, const MsgId & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void BufferSyncer::lastSeenMsgSet(BufferId _t1, const MsgId & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void BufferSyncer::markerLineSet(BufferId _t1, const MsgId & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void BufferSyncer::bufferRemoved(BufferId _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void BufferSyncer::bufferRenamed(BufferId _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void BufferSyncer::buffersPermanentlyMerged(BufferId _t1, BufferId _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void BufferSyncer::bufferMarkedAsRead(BufferId _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void BufferSyncer::bufferActivityChanged(BufferId _t1, Message::Types _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}

// SIGNAL 8
void BufferSyncer::highlightCountChanged(BufferId _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}
QT_WARNING_POP
