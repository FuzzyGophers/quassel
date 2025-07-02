/****************************************************************************
** Meta object code from reading C++ file 'highlightrulemanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/highlightrulemanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'highlightrulemanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20HighlightRuleManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto HighlightRuleManager::qt_create_metaobjectdata<qt_meta_tag_ZN20HighlightRuleManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "HighlightRuleManager",
        "ruleAdded",
        "",
        "name",
        "isRegEx",
        "isCaseSensitive",
        "isEnabled",
        "isInverse",
        "sender",
        "chanName",
        "initHighlightRuleList",
        "QVariantMap",
        "initSetHighlightRuleList",
        "HighlightRuleList",
        "requestRemoveHighlightRule",
        "highlightRule",
        "removeHighlightRule",
        "requestToggleHighlightRule",
        "toggleHighlightRule",
        "requestAddHighlightRule",
        "id",
        "addHighlightRule",
        "requestSetHighlightNick",
        "highlightNick",
        "setHighlightNick",
        "requestSetNicksCaseSensitive",
        "nicksCaseSensitive",
        "setNicksCaseSensitive",
        "networkRemoved",
        "NetworkId"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'ruleAdded'
        QtMocHelpers::SignalData<void(QString, bool, bool, bool, bool, QString, QString)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::Bool, 4 }, { QMetaType::Bool, 5 }, { QMetaType::Bool, 6 },
            { QMetaType::Bool, 7 }, { QMetaType::QString, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'initHighlightRuleList'
        QtMocHelpers::SlotData<QVariantMap() const>(10, 2, QMC::AccessPublic, 0x80000000 | 11),
        // Slot 'initSetHighlightRuleList'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 13 },
        }}),
        // Slot 'requestRemoveHighlightRule'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'removeHighlightRule'
        QtMocHelpers::SlotData<void(int)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'requestToggleHighlightRule'
        QtMocHelpers::SlotData<void(int)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'toggleHighlightRule'
        QtMocHelpers::SlotData<void(int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'requestAddHighlightRule'
        QtMocHelpers::SlotData<void(int, const QString &, bool, bool, bool, bool, const QString &, const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 20 }, { QMetaType::QString, 3 }, { QMetaType::Bool, 4 }, { QMetaType::Bool, 5 },
            { QMetaType::Bool, 6 }, { QMetaType::Bool, 7 }, { QMetaType::QString, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'addHighlightRule'
        QtMocHelpers::SlotData<void(int, const QString &, bool, bool, bool, bool, const QString &, const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 20 }, { QMetaType::QString, 3 }, { QMetaType::Bool, 4 }, { QMetaType::Bool, 5 },
            { QMetaType::Bool, 6 }, { QMetaType::Bool, 7 }, { QMetaType::QString, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'requestSetHighlightNick'
        QtMocHelpers::SlotData<void(int)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'setHighlightNick'
        QtMocHelpers::SlotData<void(int)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'requestSetNicksCaseSensitive'
        QtMocHelpers::SlotData<void(bool)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 26 },
        }}),
        // Slot 'setNicksCaseSensitive'
        QtMocHelpers::SlotData<void(bool)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 26 },
        }}),
        // Slot 'networkRemoved'
        QtMocHelpers::SlotData<void(NetworkId)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 29, 20 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'highlightNick'
        QtMocHelpers::PropertyData<int>(23, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'nicksCaseSensitive'
        QtMocHelpers::PropertyData<bool>(26, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<HighlightRuleManager, qt_meta_tag_ZN20HighlightRuleManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject HighlightRuleManager::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20HighlightRuleManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20HighlightRuleManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20HighlightRuleManagerE_t>.metaTypes,
    nullptr
} };

void HighlightRuleManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<HighlightRuleManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->ruleAdded((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7]))); break;
        case 1: { QVariantMap _r = _t->initHighlightRuleList();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->initSetHighlightRuleList((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 3: _t->requestRemoveHighlightRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->removeHighlightRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->requestToggleHighlightRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->toggleHighlightRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->requestAddHighlightRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8]))); break;
        case 8: _t->addHighlightRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8]))); break;
        case 9: _t->requestSetHighlightNick((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->setHighlightNick((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->requestSetNicksCaseSensitive((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->setNicksCaseSensitive((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->networkRemoved((*reinterpret_cast< std::add_pointer_t<NetworkId>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< NetworkId >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (HighlightRuleManager::*)(QString , bool , bool , bool , bool , QString , QString )>(_a, &HighlightRuleManager::ruleAdded, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->highlightNick(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->nicksCaseSensitive(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setHighlightNick(*reinterpret_cast<int*>(_v)); break;
        case 1: _t->setNicksCaseSensitive(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *HighlightRuleManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HighlightRuleManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20HighlightRuleManagerE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int HighlightRuleManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void HighlightRuleManager::ruleAdded(QString _t1, bool _t2, bool _t3, bool _t4, bool _t5, QString _t6, QString _t7)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3, _t4, _t5, _t6, _t7);
}
QT_WARNING_POP
