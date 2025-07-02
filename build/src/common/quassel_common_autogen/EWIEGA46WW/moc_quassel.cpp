/****************************************************************************
** Meta object code from reading C++ file 'quassel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/common/quassel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quassel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7QuasselE_t {};
} // unnamed namespace

template <> constexpr inline auto Quassel::qt_create_metaobjectdata<qt_meta_tag_ZN7QuasselE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Quassel",
        "messageLogged",
        "",
        "timeStamp",
        "msg",
        "quit",
        "randomGenerator",
        "QRandomGenerator*",
        "handleSignal",
        "AbstractSignalWatcher::Action",
        "action",
        "LegacyFeature",
        "SynchronizedMarkerLine",
        "SaslAuthentication",
        "SaslExternal",
        "HideInactiveNetworks",
        "PasswordChange",
        "CapNegotiation",
        "VerifyServerSSL",
        "CustomRateLimits",
        "AwayFormatTimestamp",
        "Authenticators",
        "BufferActivitySync",
        "CoreSideHighlights",
        "SenderPrefixes",
        "RemoteDisconnect",
        "ExtendedFeatures",
        "Feature",
        "LongTime",
        "RichMessages",
        "BacklogFilterType",
        "EcdsaCertfpKeys",
        "LongMessageId",
        "SyncedCoreInfo",
        "LoadBacklogForwards",
        "SkipIrcCaps"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'messageLogged'
        QtMocHelpers::SignalData<void(const QDateTime &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QDateTime, 3 }, { QMetaType::QString, 4 },
        }}),
        // Slot 'quit'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'randomGenerator'
        QtMocHelpers::SlotData<QRandomGenerator *()>(6, 2, QMC::AccessPublic, 0x80000000 | 7),
        // Slot 'handleSignal'
        QtMocHelpers::SlotData<void(AbstractSignalWatcher::Action)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'LegacyFeature'
        QtMocHelpers::EnumData<LegacyFeature>(11, 11, QMC::EnumIsScoped).add({
            {   12, LegacyFeature::SynchronizedMarkerLine },
            {   13, LegacyFeature::SaslAuthentication },
            {   14, LegacyFeature::SaslExternal },
            {   15, LegacyFeature::HideInactiveNetworks },
            {   16, LegacyFeature::PasswordChange },
            {   17, LegacyFeature::CapNegotiation },
            {   18, LegacyFeature::VerifyServerSSL },
            {   19, LegacyFeature::CustomRateLimits },
            {   20, LegacyFeature::AwayFormatTimestamp },
            {   21, LegacyFeature::Authenticators },
            {   22, LegacyFeature::BufferActivitySync },
            {   23, LegacyFeature::CoreSideHighlights },
            {   24, LegacyFeature::SenderPrefixes },
            {   25, LegacyFeature::RemoteDisconnect },
            {   26, LegacyFeature::ExtendedFeatures },
        }),
        // enum 'Feature'
        QtMocHelpers::EnumData<Feature>(27, 27, QMC::EnumIsScoped).add({
            {   12, Feature::SynchronizedMarkerLine },
            {   13, Feature::SaslAuthentication },
            {   14, Feature::SaslExternal },
            {   15, Feature::HideInactiveNetworks },
            {   16, Feature::PasswordChange },
            {   17, Feature::CapNegotiation },
            {   18, Feature::VerifyServerSSL },
            {   19, Feature::CustomRateLimits },
            {   20, Feature::AwayFormatTimestamp },
            {   21, Feature::Authenticators },
            {   22, Feature::BufferActivitySync },
            {   23, Feature::CoreSideHighlights },
            {   24, Feature::SenderPrefixes },
            {   25, Feature::RemoteDisconnect },
            {   26, Feature::ExtendedFeatures },
            {   28, Feature::LongTime },
            {   29, Feature::RichMessages },
            {   30, Feature::BacklogFilterType },
            {   31, Feature::EcdsaCertfpKeys },
            {   32, Feature::LongMessageId },
            {   33, Feature::SyncedCoreInfo },
            {   34, Feature::LoadBacklogForwards },
            {   35, Feature::SkipIrcCaps },
        }),
    };
    return QtMocHelpers::metaObjectData<Quassel, qt_meta_tag_ZN7QuasselE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Quassel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QuasselE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QuasselE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7QuasselE_t>.metaTypes,
    nullptr
} };

void Quassel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Quassel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->messageLogged((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->quit(); break;
        case 2: { QRandomGenerator* _r = _t->randomGenerator();
            if (_a[0]) *reinterpret_cast< QRandomGenerator**>(_a[0]) = std::move(_r); }  break;
        case 3: _t->handleSignal((*reinterpret_cast< std::add_pointer_t<AbstractSignalWatcher::Action>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< AbstractSignalWatcher::Action >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Quassel::*)(const QDateTime & , const QString & )>(_a, &Quassel::messageLogged, 0))
            return;
    }
}

const QMetaObject *Quassel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Quassel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7QuasselE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Singleton<Quassel>"))
        return static_cast< Singleton<Quassel>*>(this);
    return QObject::qt_metacast(_clname);
}

int Quassel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Quassel::messageLogged(const QDateTime & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}
QT_WARNING_POP
