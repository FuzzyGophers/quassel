/****************************************************************************
** Meta object code from reading C++ file 'ircchannel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/ircchannel.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ircchannel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10IrcChannelE_t {};
} // unnamed namespace

template <> constexpr inline auto IrcChannel::qt_create_metaobjectdata<qt_meta_tag_ZN10IrcChannelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "IrcChannel",
        "topicSet",
        "",
        "topic",
        "encryptedSet",
        "encrypted",
        "ircUsersJoined",
        "QList<IrcUser*>",
        "ircusers",
        "ircUserParted",
        "IrcUser*",
        "ircuser",
        "ircUserNickSet",
        "nick",
        "ircUserModeAdded",
        "mode",
        "ircUserModeRemoved",
        "ircUserModesSet",
        "modes",
        "parted",
        "setTopic",
        "setPassword",
        "password",
        "setEncrypted",
        "joinIrcUsers",
        "users",
        "nicks",
        "joinIrcUser",
        "part",
        "setUserModes",
        "addUserMode",
        "removeUserMode",
        "addChannelMode",
        "value",
        "removeChannelMode",
        "initUserModes",
        "QVariantMap",
        "initChanModes",
        "initSetUserModes",
        "usermodes",
        "initSetChanModes",
        "chanModes",
        "ircUserDestroyed",
        "name"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'topicSet'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'encryptedSet'
        QtMocHelpers::SignalData<void(bool)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Signal 'ircUsersJoined'
        QtMocHelpers::SignalData<void(const QList<IrcUser*> &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Signal 'ircUserParted'
        QtMocHelpers::SignalData<void(IrcUser *)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Signal 'ircUserNickSet'
        QtMocHelpers::SignalData<void(IrcUser *, QString)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 13 },
        }}),
        // Signal 'ircUserModeAdded'
        QtMocHelpers::SignalData<void(IrcUser *, QString)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 15 },
        }}),
        // Signal 'ircUserModeRemoved'
        QtMocHelpers::SignalData<void(IrcUser *, QString)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 15 },
        }}),
        // Signal 'ircUserModesSet'
        QtMocHelpers::SignalData<void(IrcUser *, QString)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 18 },
        }}),
        // Signal 'parted'
        QtMocHelpers::SignalData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setTopic'
        QtMocHelpers::SlotData<void(const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'setPassword'
        QtMocHelpers::SlotData<void(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 22 },
        }}),
        // Slot 'setEncrypted'
        QtMocHelpers::SlotData<void(bool)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Slot 'joinIrcUsers'
        QtMocHelpers::SlotData<void(const QList<IrcUser*> &, const QStringList &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 25 }, { QMetaType::QStringList, 18 },
        }}),
        // Slot 'joinIrcUsers'
        QtMocHelpers::SlotData<void(const QStringList &, const QStringList &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 26 }, { QMetaType::QStringList, 18 },
        }}),
        // Slot 'joinIrcUser'
        QtMocHelpers::SlotData<void(IrcUser *)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'part'
        QtMocHelpers::SlotData<void(IrcUser *)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'part'
        QtMocHelpers::SlotData<void(const QString &)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Slot 'setUserModes'
        QtMocHelpers::SlotData<void(IrcUser *, const QString &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 18 },
        }}),
        // Slot 'setUserModes'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 18 },
        }}),
        // Slot 'addUserMode'
        QtMocHelpers::SlotData<void(IrcUser *, const QString &)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 15 },
        }}),
        // Slot 'addUserMode'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 15 },
        }}),
        // Slot 'removeUserMode'
        QtMocHelpers::SlotData<void(IrcUser *, const QString &)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::QString, 15 },
        }}),
        // Slot 'removeUserMode'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 15 },
        }}),
        // Slot 'addChannelMode'
        QtMocHelpers::SlotData<void(const QChar &, const QString &)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QChar, 15 }, { QMetaType::QString, 33 },
        }}),
        // Slot 'removeChannelMode'
        QtMocHelpers::SlotData<void(const QChar &, const QString &)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QChar, 15 }, { QMetaType::QString, 33 },
        }}),
        // Slot 'initUserModes'
        QtMocHelpers::SlotData<QVariantMap() const>(35, 2, QMC::AccessPublic, 0x80000000 | 36),
        // Slot 'initChanModes'
        QtMocHelpers::SlotData<QVariantMap() const>(37, 2, QMC::AccessPublic, 0x80000000 | 36),
        // Slot 'initSetUserModes'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 36, 39 },
        }}),
        // Slot 'initSetChanModes'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 36, 41 },
        }}),
        // Slot 'ircUserDestroyed'
        QtMocHelpers::SlotData<void()>(42, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'ircUserNickSet'
        QtMocHelpers::SlotData<void(QString)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'name'
        QtMocHelpers::PropertyData<QString>(43, QMetaType::QString, QMC::DefaultPropertyFlags),
        // property 'topic'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'password'
        QtMocHelpers::PropertyData<QString>(22, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'encrypted'
        QtMocHelpers::PropertyData<bool>(5, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<IrcChannel, qt_meta_tag_ZN10IrcChannelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject IrcChannel::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10IrcChannelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10IrcChannelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10IrcChannelE_t>.metaTypes,
    nullptr
} };

void IrcChannel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<IrcChannel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->topicSet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->encryptedSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->ircUsersJoined((*reinterpret_cast< std::add_pointer_t<QList<IrcUser*>>>(_a[1]))); break;
        case 3: _t->ircUserParted((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1]))); break;
        case 4: _t->ircUserNickSet((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->ircUserModeAdded((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->ircUserModeRemoved((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->ircUserModesSet((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->parted(); break;
        case 9: _t->setTopic((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->setPassword((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->setEncrypted((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->joinIrcUsers((*reinterpret_cast< std::add_pointer_t<QList<IrcUser*>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 13: _t->joinIrcUsers((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 14: _t->joinIrcUser((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1]))); break;
        case 15: _t->part((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1]))); break;
        case 16: _t->part((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->setUserModes((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 18: _t->setUserModes((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 19: _t->addUserMode((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 20: _t->addUserMode((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 21: _t->removeUserMode((*reinterpret_cast< std::add_pointer_t<IrcUser*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 22: _t->removeUserMode((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 23: _t->addChannelMode((*reinterpret_cast< std::add_pointer_t<QChar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 24: _t->removeChannelMode((*reinterpret_cast< std::add_pointer_t<QChar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 25: { QVariantMap _r = _t->initUserModes();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 26: { QVariantMap _r = _t->initChanModes();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->initSetUserModes((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 28: _t->initSetChanModes((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 29: _t->ircUserDestroyed(); break;
        case 30: _t->ircUserNickSet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)(const QString & )>(_a, &IrcChannel::topicSet, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)(bool )>(_a, &IrcChannel::encryptedSet, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)(const QList<IrcUser*> & )>(_a, &IrcChannel::ircUsersJoined, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)(IrcUser * )>(_a, &IrcChannel::ircUserParted, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)(IrcUser * , QString )>(_a, &IrcChannel::ircUserNickSet, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)(IrcUser * , QString )>(_a, &IrcChannel::ircUserModeAdded, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)(IrcUser * , QString )>(_a, &IrcChannel::ircUserModeRemoved, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)(IrcUser * , QString )>(_a, &IrcChannel::ircUserModesSet, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (IrcChannel::*)()>(_a, &IrcChannel::parted, 8))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->name(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->topic(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->password(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->encrypted(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setTopic(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setPassword(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setEncrypted(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *IrcChannel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IrcChannel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10IrcChannelE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int IrcChannel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 31;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void IrcChannel::topicSet(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void IrcChannel::encryptedSet(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void IrcChannel::ircUsersJoined(const QList<IrcUser*> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void IrcChannel::ircUserParted(IrcUser * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void IrcChannel::ircUserNickSet(IrcUser * _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void IrcChannel::ircUserModeAdded(IrcUser * _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void IrcChannel::ircUserModeRemoved(IrcUser * _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void IrcChannel::ircUserModesSet(IrcUser * _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}

// SIGNAL 8
void IrcChannel::parted()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
