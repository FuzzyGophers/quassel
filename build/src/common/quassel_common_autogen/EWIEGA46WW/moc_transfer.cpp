/****************************************************************************
** Meta object code from reading C++ file 'transfer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/transfer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transfer.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8TransferE_t {};
} // unnamed namespace

template <> constexpr inline auto Transfer::qt_create_metaobjectdata<qt_meta_tag_ZN8TransferE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Transfer",
        "statusChanged",
        "",
        "Transfer::Status",
        "state",
        "directionChanged",
        "Transfer::Direction",
        "direction",
        "addressChanged",
        "QHostAddress",
        "address",
        "portChanged",
        "port",
        "fileNameChanged",
        "fileName",
        "fileSizeChanged",
        "fileSize",
        "transferredChanged",
        "transferred",
        "nickChanged",
        "nick",
        "error",
        "errorString",
        "accepted",
        "PeerPtr",
        "peer",
        "rejected",
        "accept",
        "savePath",
        "reject",
        "requestAccepted",
        "requestRejected",
        "setStatus",
        "status",
        "setError",
        "dataReceived",
        "data",
        "cleanUp",
        "uuid",
        "Direction",
        "Send",
        "Receive"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'statusChanged'
        QtMocHelpers::SignalData<void(Transfer::Status)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'directionChanged'
        QtMocHelpers::SignalData<void(Transfer::Direction)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Signal 'addressChanged'
        QtMocHelpers::SignalData<void(const QHostAddress &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'portChanged'
        QtMocHelpers::SignalData<void(quint16)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UShort, 12 },
        }}),
        // Signal 'fileNameChanged'
        QtMocHelpers::SignalData<void(const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 },
        }}),
        // Signal 'fileSizeChanged'
        QtMocHelpers::SignalData<void(quint64)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::ULongLong, 16 },
        }}),
        // Signal 'transferredChanged'
        QtMocHelpers::SignalData<void(quint64)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::ULongLong, 18 },
        }}),
        // Signal 'nickChanged'
        QtMocHelpers::SignalData<void(const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 20 },
        }}),
        // Signal 'error'
        QtMocHelpers::SignalData<void(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 22 },
        }}),
        // Signal 'accepted'
        QtMocHelpers::SignalData<void(PeerPtr) const>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Signal 'accepted'
        QtMocHelpers::SignalData<void() const>(23, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Signal 'rejected'
        QtMocHelpers::SignalData<void(PeerPtr) const>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Signal 'rejected'
        QtMocHelpers::SignalData<void() const>(26, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Slot 'accept'
        QtMocHelpers::SlotData<void(const QString &) const>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 28 },
        }}),
        // Slot 'reject'
        QtMocHelpers::SlotData<void() const>(29, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'requestAccepted'
        QtMocHelpers::SlotData<void(PeerPtr)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Slot 'requestRejected'
        QtMocHelpers::SlotData<void(PeerPtr)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Slot 'setStatus'
        QtMocHelpers::SlotData<void(Transfer::Status)>(32, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 3, 33 },
        }}),
        // Slot 'setError'
        QtMocHelpers::SlotData<void(const QString &)>(34, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QString, 22 },
        }}),
        // Slot 'dataReceived'
        QtMocHelpers::SlotData<void(PeerPtr, const QByteArray &)>(35, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 24, 2 }, { QMetaType::QByteArray, 36 },
        }}),
        // Slot 'cleanUp'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessProtected, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'uuid'
        QtMocHelpers::PropertyData<QUuid>(38, QMetaType::QUuid, QMC::DefaultPropertyFlags),
        // property 'status'
        QtMocHelpers::PropertyData<Transfer::Status>(33, 0x80000000 | 3, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 0),
        // property 'direction'
        QtMocHelpers::PropertyData<Transfer::Direction>(7, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 1),
        // property 'address'
        QtMocHelpers::PropertyData<QHostAddress>(10, 0x80000000 | 9, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 2),
        // property 'port'
        QtMocHelpers::PropertyData<quint16>(12, QMetaType::UShort, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'fileName'
        QtMocHelpers::PropertyData<QString>(14, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'fileSize'
        QtMocHelpers::PropertyData<quint64>(16, QMetaType::ULongLong, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'nick'
        QtMocHelpers::PropertyData<QString>(20, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Direction'
        QtMocHelpers::EnumData<Direction>(39, 39, QMC::EnumIsScoped).add({
            {   40, Direction::Send },
            {   41, Direction::Receive },
        }),
    };
    return QtMocHelpers::metaObjectData<Transfer, qt_meta_tag_ZN8TransferE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Transfer::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8TransferE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8TransferE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8TransferE_t>.metaTypes,
    nullptr
} };

void Transfer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Transfer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->statusChanged((*reinterpret_cast< std::add_pointer_t<Transfer::Status>>(_a[1]))); break;
        case 1: _t->directionChanged((*reinterpret_cast< std::add_pointer_t<Transfer::Direction>>(_a[1]))); break;
        case 2: _t->addressChanged((*reinterpret_cast< std::add_pointer_t<QHostAddress>>(_a[1]))); break;
        case 3: _t->portChanged((*reinterpret_cast< std::add_pointer_t<quint16>>(_a[1]))); break;
        case 4: _t->fileNameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->fileSizeChanged((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1]))); break;
        case 6: _t->transferredChanged((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1]))); break;
        case 7: _t->nickChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->error((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->accepted((*reinterpret_cast< std::add_pointer_t<PeerPtr>>(_a[1]))); break;
        case 10: _t->accepted(); break;
        case 11: _t->rejected((*reinterpret_cast< std::add_pointer_t<PeerPtr>>(_a[1]))); break;
        case 12: _t->rejected(); break;
        case 13: _t->accept((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->reject(); break;
        case 15: _t->requestAccepted((*reinterpret_cast< std::add_pointer_t<PeerPtr>>(_a[1]))); break;
        case 16: _t->requestRejected((*reinterpret_cast< std::add_pointer_t<PeerPtr>>(_a[1]))); break;
        case 17: _t->setStatus((*reinterpret_cast< std::add_pointer_t<Transfer::Status>>(_a[1]))); break;
        case 18: _t->setError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->dataReceived((*reinterpret_cast< std::add_pointer_t<PeerPtr>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2]))); break;
        case 20: _t->cleanUp(); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Transfer::Status >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Transfer::Direction >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QHostAddress >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< PeerPtr >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< PeerPtr >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< PeerPtr >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< PeerPtr >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Transfer::Status >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< PeerPtr >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(Transfer::Status )>(_a, &Transfer::statusChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(Transfer::Direction )>(_a, &Transfer::directionChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(const QHostAddress & )>(_a, &Transfer::addressChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(quint16 )>(_a, &Transfer::portChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(const QString & )>(_a, &Transfer::fileNameChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(quint64 )>(_a, &Transfer::fileSizeChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(quint64 )>(_a, &Transfer::transferredChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(const QString & )>(_a, &Transfer::nickChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(const QString & )>(_a, &Transfer::error, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(PeerPtr ) const>(_a, &Transfer::accepted, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (Transfer::*)(PeerPtr ) const>(_a, &Transfer::rejected, 11))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostAddress >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Transfer::Direction >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Transfer::Status >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QUuid*>(_v) = _t->uuid(); break;
        case 1: *reinterpret_cast<Transfer::Status*>(_v) = _t->status(); break;
        case 2: *reinterpret_cast<Transfer::Direction*>(_v) = _t->direction(); break;
        case 3: *reinterpret_cast<QHostAddress*>(_v) = _t->address(); break;
        case 4: *reinterpret_cast<quint16*>(_v) = _t->port(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->fileName(); break;
        case 6: *reinterpret_cast<quint64*>(_v) = _t->fileSize(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->nick(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setStatus(*reinterpret_cast<Transfer::Status*>(_v)); break;
        case 2: _t->setDirection(*reinterpret_cast<Transfer::Direction*>(_v)); break;
        case 3: _t->setAddress(*reinterpret_cast<QHostAddress*>(_v)); break;
        case 4: _t->setPort(*reinterpret_cast<quint16*>(_v)); break;
        case 5: _t->setFileName(*reinterpret_cast<QString*>(_v)); break;
        case 6: _t->setFileSize(*reinterpret_cast<quint64*>(_v)); break;
        case 7: _t->setNick(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Transfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Transfer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8TransferE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int Transfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Transfer::statusChanged(Transfer::Status _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Transfer::directionChanged(Transfer::Direction _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Transfer::addressChanged(const QHostAddress & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Transfer::portChanged(quint16 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Transfer::fileNameChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Transfer::fileSizeChanged(quint64 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void Transfer::transferredChanged(quint64 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void Transfer::nickChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void Transfer::error(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void Transfer::accepted(PeerPtr _t1)const
{
    QMetaObject::activate<void>(const_cast< Transfer *>(this), &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 11
void Transfer::rejected(PeerPtr _t1)const
{
    QMetaObject::activate<void>(const_cast< Transfer *>(this), &staticMetaObject, 11, nullptr, _t1);
}
QT_WARNING_POP
