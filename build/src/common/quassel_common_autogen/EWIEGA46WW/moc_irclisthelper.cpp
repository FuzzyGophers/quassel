/****************************************************************************
** Meta object code from reading C++ file 'irclisthelper.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/irclisthelper.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'irclisthelper.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13IrcListHelperE_t {};
} // unnamed namespace

template <> constexpr inline auto IrcListHelper::qt_create_metaobjectdata<qt_meta_tag_ZN13IrcListHelperE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "IrcListHelper",
        "requestChannelList",
        "QVariantList",
        "",
        "NetworkId",
        "netId",
        "channelFilters",
        "receiveChannelList",
        "reportFinishedList",
        "reportError",
        "error"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'requestChannelList'
        QtMocHelpers::SlotData<QVariantList(const NetworkId &, const QStringList &)>(1, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { 0x80000000 | 4, 5 }, { QMetaType::QStringList, 6 },
        }}),
        // Slot 'receiveChannelList'
        QtMocHelpers::SlotData<void(const NetworkId &, const QStringList &, const QVariantList &)>(7, 3, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 3 }, { QMetaType::QStringList, 3 }, { 0x80000000 | 2, 3 },
        }}),
        // Slot 'reportFinishedList'
        QtMocHelpers::SlotData<void(const NetworkId &)>(8, 3, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'reportError'
        QtMocHelpers::SlotData<void(const QString &)>(9, 3, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<IrcListHelper, qt_meta_tag_ZN13IrcListHelperE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject IrcListHelper::staticMetaObject = { {
    QMetaObject::SuperData::link<SyncableObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13IrcListHelperE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13IrcListHelperE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13IrcListHelperE_t>.metaTypes,
    nullptr
} };

void IrcListHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<IrcListHelper *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QVariantList _r = _t->requestChannelList((*reinterpret_cast< std::add_pointer_t<NetworkId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->receiveChannelList((*reinterpret_cast< std::add_pointer_t<NetworkId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3]))); break;
        case 2: _t->reportFinishedList((*reinterpret_cast< std::add_pointer_t<NetworkId>>(_a[1]))); break;
        case 3: _t->reportError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< NetworkId >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< NetworkId >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< NetworkId >(); break;
            }
            break;
        }
    }
}

const QMetaObject *IrcListHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IrcListHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13IrcListHelperE_t>.strings))
        return static_cast<void*>(this);
    return SyncableObject::qt_metacast(_clname);
}

int IrcListHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
