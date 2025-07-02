/****************************************************************************
** Meta object code from reading C++ file 'identity.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/identity.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'identity.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8IdentityE_t {};
} // unnamed namespace

template <> constexpr inline auto Identity::qt_create_metaobjectdata<qt_meta_tag_ZN8IdentityE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Identity",
        "idSet",
        "",
        "IdentityId",
        "id",
        "nicksSet",
        "nicks",
        "setId",
        "setIdentityName",
        "name",
        "setRealName",
        "realName",
        "setNicks",
        "setAwayNick",
        "awayNick",
        "setAwayNickEnabled",
        "enabled",
        "setAwayReason",
        "awayReason",
        "setAwayReasonEnabled",
        "setAutoAwayEnabled",
        "setAutoAwayTime",
        "time",
        "setAutoAwayReason",
        "reason",
        "setAutoAwayReasonEnabled",
        "setDetachAwayEnabled",
        "setDetachAwayReason",
        "setDetachAwayReasonEnabled",
        "setIdent",
        "ident",
        "setKickReason",
        "setPartReason",
        "setQuitReason",
        "copyFrom",
        "other",
        "identityId",
        "identityName",
        "awayNickEnabled",
        "awayReasonEnabled",
        "autoAwayEnabled",
        "autoAwayTime",
        "autoAwayReason",
        "autoAwayReasonEnabled",
        "detachAwayEnabled",
        "detachAwayReason",
        "detachAwayReasonEnabled",
        "kickReason",
        "partReason",
        "quitReason"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'idSet'
        QtMocHelpers::SignalData<void(IdentityId)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'nicksSet'
        QtMocHelpers::SignalData<void(const QStringList &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 6 },
        }}),
        // Slot 'setId'
        QtMocHelpers::SlotData<void(IdentityId)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'setIdentityName'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'setRealName'
        QtMocHelpers::SlotData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Slot 'setNicks'
        QtMocHelpers::SlotData<void(const QStringList &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 6 },
        }}),
        // Slot 'setAwayNick'
        QtMocHelpers::SlotData<void(const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 },
        }}),
        // Slot 'setAwayNickEnabled'
        QtMocHelpers::SlotData<void(bool)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 16 },
        }}),
        // Slot 'setAwayReason'
        QtMocHelpers::SlotData<void(const QString &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Slot 'setAwayReasonEnabled'
        QtMocHelpers::SlotData<void(bool)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 16 },
        }}),
        // Slot 'setAutoAwayEnabled'
        QtMocHelpers::SlotData<void(bool)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 16 },
        }}),
        // Slot 'setAutoAwayTime'
        QtMocHelpers::SlotData<void(int)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 22 },
        }}),
        // Slot 'setAutoAwayReason'
        QtMocHelpers::SlotData<void(const QString &)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'setAutoAwayReasonEnabled'
        QtMocHelpers::SlotData<void(bool)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 16 },
        }}),
        // Slot 'setDetachAwayEnabled'
        QtMocHelpers::SlotData<void(bool)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 16 },
        }}),
        // Slot 'setDetachAwayReason'
        QtMocHelpers::SlotData<void(const QString &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'setDetachAwayReasonEnabled'
        QtMocHelpers::SlotData<void(bool)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 16 },
        }}),
        // Slot 'setIdent'
        QtMocHelpers::SlotData<void(const QString &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 30 },
        }}),
        // Slot 'setKickReason'
        QtMocHelpers::SlotData<void(const QString &)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'setPartReason'
        QtMocHelpers::SlotData<void(const QString &)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'setQuitReason'
        QtMocHelpers::SlotData<void(const QString &)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'copyFrom'
        QtMocHelpers::SlotData<void(const Identity &)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 0, 35 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'identityId'
        QtMocHelpers::PropertyData<IdentityId>(36, 0x80000000 | 3, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag),
        // property 'identityName'
        QtMocHelpers::PropertyData<QString>(37, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'realName'
        QtMocHelpers::PropertyData<QString>(11, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'nicks'
        QtMocHelpers::PropertyData<QStringList>(6, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'awayNick'
        QtMocHelpers::PropertyData<QString>(14, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'awayNickEnabled'
        QtMocHelpers::PropertyData<bool>(38, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'awayReason'
        QtMocHelpers::PropertyData<QString>(18, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'awayReasonEnabled'
        QtMocHelpers::PropertyData<bool>(39, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoAwayEnabled'
        QtMocHelpers::PropertyData<bool>(40, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoAwayTime'
        QtMocHelpers::PropertyData<int>(41, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoAwayReason'
        QtMocHelpers::PropertyData<QString>(42, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'autoAwayReasonEnabled'
        QtMocHelpers::PropertyData<bool>(43, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'detachAwayEnabled'
        QtMocHelpers::PropertyData<bool>(44, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'detachAwayReason'
        QtMocHelpers::PropertyData<QString>(45, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'detachAwayReasonEnabled'
        QtMocHelpers::PropertyData<bool>(46, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'ident'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'kickReason'
        QtMocHelpers::PropertyData<QString>(47, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'partReason'
        QtMocHelpers::PropertyData<QString>(48, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'quitReason'
        QtMocHelpers::PropertyData<QString>(49, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Identity, qt_meta_tag_ZN8IdentityE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Identity::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8IdentityE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8IdentityE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8IdentityE_t>.metaTypes,
    nullptr
} };

void Identity::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Identity *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->idSet((*reinterpret_cast< std::add_pointer_t<IdentityId>>(_a[1]))); break;
        case 1: _t->nicksSet((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 2: _t->setId((*reinterpret_cast< std::add_pointer_t<IdentityId>>(_a[1]))); break;
        case 3: _t->setIdentityName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->setRealName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->setNicks((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 6: _t->setAwayNick((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->setAwayNickEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->setAwayReason((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->setAwayReasonEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->setAutoAwayEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->setAutoAwayTime((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->setAutoAwayReason((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->setAutoAwayReasonEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->setDetachAwayEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->setDetachAwayReason((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->setDetachAwayReasonEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->setIdent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->setKickReason((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->setPartReason((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->setQuitReason((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->copyFrom((*reinterpret_cast< std::add_pointer_t<Identity>>(_a[1]))); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< IdentityId >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< IdentityId >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Identity >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Identity::*)(IdentityId )>(_a, &Identity::idSet, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Identity::*)(const QStringList & )>(_a, &Identity::nicksSet, 1))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IdentityId >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<IdentityId*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->identityName(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->realName(); break;
        case 3: *reinterpret_cast<QStringList*>(_v) = _t->nicks(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->awayNick(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->awayNickEnabled(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->awayReason(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->awayReasonEnabled(); break;
        case 8: *reinterpret_cast<bool*>(_v) = _t->autoAwayEnabled(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->autoAwayTime(); break;
        case 10: *reinterpret_cast<QString*>(_v) = _t->autoAwayReason(); break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->autoAwayReasonEnabled(); break;
        case 12: *reinterpret_cast<bool*>(_v) = _t->detachAwayEnabled(); break;
        case 13: *reinterpret_cast<QString*>(_v) = _t->detachAwayReason(); break;
        case 14: *reinterpret_cast<bool*>(_v) = _t->detachAwayReasonEnabled(); break;
        case 15: *reinterpret_cast<QString*>(_v) = _t->ident(); break;
        case 16: *reinterpret_cast<QString*>(_v) = _t->kickReason(); break;
        case 17: *reinterpret_cast<QString*>(_v) = _t->partReason(); break;
        case 18: *reinterpret_cast<QString*>(_v) = _t->quitReason(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId(*reinterpret_cast<IdentityId*>(_v)); break;
        case 1: _t->setIdentityName(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setRealName(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setNicks(*reinterpret_cast<QStringList*>(_v)); break;
        case 4: _t->setAwayNick(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setAwayNickEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 6: _t->setAwayReason(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setAwayReasonEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 8: _t->setAutoAwayEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 9: _t->setAutoAwayTime(*reinterpret_cast<int*>(_v)); break;
        case 10: _t->setAutoAwayReason(*reinterpret_cast<QString*>(_v)); break;
        case 11: _t->setAutoAwayReasonEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 12: _t->setDetachAwayEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 13: _t->setDetachAwayReason(*reinterpret_cast<QString*>(_v)); break;
        case 14: _t->setDetachAwayReasonEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 15: _t->setIdent(*reinterpret_cast<QString*>(_v)); break;
        case 16: _t->setKickReason(*reinterpret_cast<QString*>(_v)); break;
        case 17: _t->setPartReason(*reinterpret_cast<QString*>(_v)); break;
        case 18: _t->setQuitReason(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Identity::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Identity::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8IdentityE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int Identity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Identity::idSet(IdentityId _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Identity::nicksSet(const QStringList & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN11CertManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto CertManager::qt_create_metaobjectdata<qt_meta_tag_ZN11CertManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CertManager",
        "setSslKey",
        "",
        "encoded",
        "setSslCert",
        "sslKey",
        "sslCert"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'setSslKey'
        QtMocHelpers::SlotData<void(const QByteArray &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 3 },
        }}),
        // Slot 'setSslCert'
        QtMocHelpers::SlotData<void(const QByteArray &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 3 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'sslKey'
        QtMocHelpers::PropertyData<QByteArray>(5, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'sslCert'
        QtMocHelpers::PropertyData<QByteArray>(6, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CertManager, qt_meta_tag_ZN11CertManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CertManager::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11CertManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11CertManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11CertManagerE_t>.metaTypes,
    nullptr
} };

void CertManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CertManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->setSslKey((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 1: _t->setSslCert((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QByteArray*>(_v) = _t->sslKeyPem(); break;
        case 1: *reinterpret_cast<QByteArray*>(_v) = _t->sslCertPem(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSslKey(*reinterpret_cast<QByteArray*>(_v)); break;
        case 1: _t->setSslCert(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *CertManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CertManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11CertManagerE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int CertManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
