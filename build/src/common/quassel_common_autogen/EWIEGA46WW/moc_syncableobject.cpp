/****************************************************************************
** Meta object code from reading C++ file 'syncableobject.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/syncableobject.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'syncableobject.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14SyncableObjectE_t {};
} // unnamed namespace

template <> constexpr inline auto SyncableObject::qt_create_metaobjectdata<qt_meta_tag_ZN14SyncableObjectE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SyncableObject",
        "initDone",
        "",
        "updatedRemotely",
        "updated",
        "setInitialized",
        "requestUpdate",
        "QVariantMap",
        "properties",
        "update"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'initDone'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'updatedRemotely'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'updated'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setInitialized'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'requestUpdate'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Slot 'update'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SyncableObject, qt_meta_tag_ZN14SyncableObjectE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SyncableObject::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14SyncableObjectE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14SyncableObjectE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14SyncableObjectE_t>.metaTypes,
    nullptr
} };

void SyncableObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SyncableObject *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->initDone(); break;
        case 1: _t->updatedRemotely(); break;
        case 2: _t->updated(); break;
        case 3: _t->setInitialized(); break;
        case 4: _t->requestUpdate((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 5: _t->update((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SyncableObject::*)()>(_a, &SyncableObject::initDone, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SyncableObject::*)()>(_a, &SyncableObject::updatedRemotely, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SyncableObject::*)()>(_a, &SyncableObject::updated, 2))
            return;
    }
}

const QMetaObject *SyncableObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SyncableObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14SyncableObjectE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SyncableObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SyncableObject::initDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SyncableObject::updatedRemotely()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SyncableObject::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
