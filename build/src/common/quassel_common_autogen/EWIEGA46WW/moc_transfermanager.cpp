/****************************************************************************
** Meta object code from reading C++ file 'transfermanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/transfermanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transfermanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15TransferManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto TransferManager::qt_create_metaobjectdata<qt_meta_tag_ZN15TransferManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TransferManager",
        "transferAdded",
        "",
        "uuid",
        "transferRemoved",
        "setTransferIds",
        "TransferIdList",
        "transferIds",
        "onCoreTransferAdded",
        "transferId",
        "TransferManager::TransferIdList"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'transferAdded'
        QtMocHelpers::SignalData<void(const QUuid &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QUuid, 3 },
        }}),
        // Signal 'transferRemoved'
        QtMocHelpers::SignalData<void(const QUuid &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QUuid, 3 },
        }}),
        // Slot 'setTransferIds'
        QtMocHelpers::SlotData<void(const TransferIdList &)>(5, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'onCoreTransferAdded'
        QtMocHelpers::SlotData<void(const QUuid &)>(8, 2, QMC::AccessProtected, QMetaType::Void, {{
            { QMetaType::QUuid, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'transferIds'
        QtMocHelpers::PropertyData<TransferManager::TransferIdList>(7, 0x80000000 | 10, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TransferManager, qt_meta_tag_ZN15TransferManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TransferManager::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15TransferManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15TransferManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15TransferManagerE_t>.metaTypes,
    nullptr
} };

void TransferManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TransferManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->transferAdded((*reinterpret_cast< std::add_pointer_t<QUuid>>(_a[1]))); break;
        case 1: _t->transferRemoved((*reinterpret_cast< std::add_pointer_t<QUuid>>(_a[1]))); break;
        case 2: _t->setTransferIds((*reinterpret_cast< std::add_pointer_t<TransferIdList>>(_a[1]))); break;
        case 3: _t->onCoreTransferAdded((*reinterpret_cast< std::add_pointer_t<QUuid>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TransferManager::*)(const QUuid & )>(_a, &TransferManager::transferAdded, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TransferManager::*)(const QUuid & )>(_a, &TransferManager::transferRemoved, 1))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TransferManager::TransferIdList >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<TransferManager::TransferIdList*>(_v) = _t->transferIds(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTransferIds(*reinterpret_cast<TransferManager::TransferIdList*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *TransferManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransferManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15TransferManagerE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int TransferManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TransferManager::transferAdded(const QUuid & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void TransferManager::transferRemoved(const QUuid & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
