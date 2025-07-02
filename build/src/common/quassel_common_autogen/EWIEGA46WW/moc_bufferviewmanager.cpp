/****************************************************************************
** Meta object code from reading C++ file 'bufferviewmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/bufferviewmanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bufferviewmanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17BufferViewManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto BufferViewManager::qt_create_metaobjectdata<qt_meta_tag_ZN17BufferViewManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BufferViewManager",
        "bufferViewConfigAdded",
        "",
        "bufferViewConfigId",
        "bufferViewConfigDeleted",
        "initBufferViewIds",
        "QVariantList",
        "initSetBufferViewIds",
        "bufferViewIds",
        "addBufferViewConfig",
        "deleteBufferViewConfig",
        "requestCreateBufferView",
        "QVariantMap",
        "properties",
        "requestCreateBufferViews",
        "requestDeleteBufferView",
        "bufferViewId",
        "requestDeleteBufferViews",
        "bufferViews"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'bufferViewConfigAdded'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'bufferViewConfigDeleted'
        QtMocHelpers::SignalData<void(int)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'initBufferViewIds'
        QtMocHelpers::SlotData<QVariantList() const>(5, 2, QMC::AccessPublic, 0x80000000 | 6),
        // Slot 'initSetBufferViewIds'
        QtMocHelpers::SlotData<void(const QVariantList)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 8 },
        }}),
        // Slot 'addBufferViewConfig'
        QtMocHelpers::SlotData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'deleteBufferViewConfig'
        QtMocHelpers::SlotData<void(int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'requestCreateBufferView'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Slot 'requestCreateBufferViews'
        QtMocHelpers::SlotData<void(const QVariantList &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 13 },
        }}),
        // Slot 'requestDeleteBufferView'
        QtMocHelpers::SlotData<void(int)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 16 },
        }}),
        // Slot 'requestDeleteBufferViews'
        QtMocHelpers::SlotData<void(const QVariantList &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 18 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BufferViewManager, qt_meta_tag_ZN17BufferViewManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BufferViewManager::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17BufferViewManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17BufferViewManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17BufferViewManagerE_t>.metaTypes,
    nullptr
} };

void BufferViewManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BufferViewManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->bufferViewConfigAdded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->bufferViewConfigDeleted((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: { QVariantList _r = _t->initBufferViewIds();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->initSetBufferViewIds((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 4: _t->addBufferViewConfig((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->deleteBufferViewConfig((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->requestCreateBufferView((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 7: _t->requestCreateBufferViews((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 8: _t->requestDeleteBufferView((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->requestDeleteBufferViews((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BufferViewManager::*)(int )>(_a, &BufferViewManager::bufferViewConfigAdded, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BufferViewManager::*)(int )>(_a, &BufferViewManager::bufferViewConfigDeleted, 1))
            return;
    }
}

const QMetaObject *BufferViewManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BufferViewManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17BufferViewManagerE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int BufferViewManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyncableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void BufferViewManager::bufferViewConfigAdded(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void BufferViewManager::bufferViewConfigDeleted(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
