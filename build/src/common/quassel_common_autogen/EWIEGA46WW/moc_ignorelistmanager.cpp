/****************************************************************************
** Meta object code from reading C++ file 'ignorelistmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/ignorelistmanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ignorelistmanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17IgnoreListManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto IgnoreListManager::qt_create_metaobjectdata<qt_meta_tag_ZN17IgnoreListManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "IgnoreListManager",
        "ignoreAdded",
        "",
        "IgnoreType",
        "type",
        "ignoreRule",
        "isRegex",
        "StrictnessType",
        "strictness",
        "ScopeType",
        "scope",
        "QVariant",
        "scopeRule",
        "isActive",
        "initIgnoreList",
        "QVariantMap",
        "initSetIgnoreList",
        "ignoreList",
        "requestRemoveIgnoreListItem",
        "removeIgnoreListItem",
        "requestToggleIgnoreRule",
        "toggleIgnoreRule",
        "requestAddIgnoreListItem",
        "isRegEx",
        "addIgnoreListItem"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'ignoreAdded'
        QtMocHelpers::SignalData<void(IgnoreType, const QString &, bool, StrictnessType, ScopeType, const QVariant &, bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QString, 5 }, { QMetaType::Bool, 6 }, { 0x80000000 | 7, 8 },
            { 0x80000000 | 9, 10 }, { 0x80000000 | 11, 12 }, { QMetaType::Bool, 13 },
        }}),
        // Slot 'initIgnoreList'
        QtMocHelpers::SlotData<QVariantMap() const>(14, 2, QMC::AccessPublic, 0x80000000 | 15),
        // Slot 'initSetIgnoreList'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 15, 17 },
        }}),
        // Slot 'requestRemoveIgnoreListItem'
        QtMocHelpers::SlotData<void(const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'removeIgnoreListItem'
        QtMocHelpers::SlotData<void(const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'requestToggleIgnoreRule'
        QtMocHelpers::SlotData<void(const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'toggleIgnoreRule'
        QtMocHelpers::SlotData<void(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'requestAddIgnoreListItem'
        QtMocHelpers::SlotData<void(int, const QString &, bool, int, int, const QString &, bool)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 4 }, { QMetaType::QString, 5 }, { QMetaType::Bool, 23 }, { QMetaType::Int, 8 },
            { QMetaType::Int, 10 }, { QMetaType::QString, 12 }, { QMetaType::Bool, 13 },
        }}),
        // Slot 'addIgnoreListItem'
        QtMocHelpers::SlotData<void(int, const QString &, bool, int, int, const QString &, bool)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 4 }, { QMetaType::QString, 5 }, { QMetaType::Bool, 23 }, { QMetaType::Int, 8 },
            { QMetaType::Int, 10 }, { QMetaType::QString, 12 }, { QMetaType::Bool, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<IgnoreListManager, qt_meta_tag_ZN17IgnoreListManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject IgnoreListManager::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17IgnoreListManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17IgnoreListManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17IgnoreListManagerE_t>.metaTypes,
    nullptr
} };

void IgnoreListManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<IgnoreListManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->ignoreAdded((*reinterpret_cast< std::add_pointer_t<IgnoreType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<StrictnessType>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<ScopeType>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[7]))); break;
        case 1: { QVariantMap _r = _t->initIgnoreList();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->initSetIgnoreList((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 3: _t->requestRemoveIgnoreListItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->removeIgnoreListItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->requestToggleIgnoreRule((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->toggleIgnoreRule((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->requestAddIgnoreListItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[7]))); break;
        case 8: _t->addIgnoreListItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[7]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (IgnoreListManager::*)(IgnoreType , const QString & , bool , StrictnessType , ScopeType , const QVariant & , bool )>(_a, &IgnoreListManager::ignoreAdded, 0))
            return;
    }
}

const QMetaObject *IgnoreListManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IgnoreListManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17IgnoreListManagerE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int IgnoreListManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void IgnoreListManager::ignoreAdded(IgnoreType _t1, const QString & _t2, bool _t3, StrictnessType _t4, ScopeType _t5, const QVariant & _t6, bool _t7)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3, _t4, _t5, _t6, _t7);
}
QT_WARNING_POP
