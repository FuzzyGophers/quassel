// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "signalproxy.h"

#include <algorithm>
#include <utility>

#include <QCoreApplication>
#include <QHostAddress>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QRegularExpression>
#include <QSslSocket>
#include <QThread>

#include "peer.h"
#include "protocol.h"
#include "syncableobject.h"
#include "types.h"
#include "util.h"

using namespace QuasselProtocol;

class RemovePeerEvent : public QEvent
{
public:
    RemovePeerEvent(Peer* peer)
        : QEvent(QEvent::Type(SignalProxy::RemovePeerEvent))
        , peer(peer)
    {
    }
    Peer* peer;
};

// ==================================================
//  SignalProxy
// ==================================================

namespace {
thread_local SignalProxy* _current{nullptr};
}

SignalProxy::SignalProxy(QObject* parent)
    : QObject(parent)
{
    setProxyMode(Client);
    init();
}

SignalProxy::SignalProxy(ProxyMode mode, QObject* parent)
    : QObject(parent)
{
    setProxyMode(mode);
    init();
}

SignalProxy::~SignalProxy()
{
    QHash<QByteArray, ObjectId>::iterator classIter = _syncSlave.begin();
    while (classIter != _syncSlave.end()) {
        ObjectId::iterator objIter = classIter->begin();
        while (objIter != classIter->end()) {
            SyncableObject* obj = objIter.value();
            objIter = classIter->erase(objIter);
            obj->stopSynchronize(this);
        }
        ++classIter;
    }
    _syncSlave.clear();

    removeAllPeers();

    // Ensure that we don't try to clean up while destroying ourselves
    disconnect(this, &QObject::destroyed, this, &SignalProxy::detachSlotObjects);

    _current = nullptr;
}

SignalProxy* SignalProxy::current()
{
    return _current;
}

void SignalProxy::setProxyMode(ProxyMode mode)
{
    if (!_peerMap.empty()) {
        qWarning() << Q_FUNC_INFO << "Cannot change proxy mode while connected";
        return;
    }

    _proxyMode = mode;
    if (mode == Server)
        initServer();
    else
        initClient();
}

void SignalProxy::init()
{
    _heartBeatInterval = 0;
    _maxHeartBeatCount = 0;
    setHeartBeatInterval(30);
    setMaxHeartBeatCount(2);
    _secure = false;
    _current = this;
    updateSecureState();
}

void SignalProxy::initServer() {}

void SignalProxy::initClient()
{
    attachSlot("__objectRenamed__", this, &SignalProxy::objectRenamed);
}

void SignalProxy::setHeartBeatInterval(int secs)
{
    if (_heartBeatInterval != secs) {
        _heartBeatInterval = secs;
        emit heartBeatIntervalChanged(secs);
    }
}

void SignalProxy::setMaxHeartBeatCount(int max)
{
    if (_maxHeartBeatCount != max) {
        _maxHeartBeatCount = max;
        emit maxHeartBeatCountChanged(max);
    }
}

bool SignalProxy::addPeer(Peer* peer)
{
    if (!peer)
        return false;

    if (_peerMap.values().contains(peer))
        return true;

    if (!peer->isOpen()) {
        qWarning("SignalProxy: peer needs to be open!");
        return false;
    }

    if (proxyMode() == Client) {
        if (!_peerMap.isEmpty()) {
            qWarning("SignalProxy: only one peer allowed in client mode!");
            return false;
        }
        connect(peer, &Peer::lagUpdated, this, &SignalProxy::lagUpdated);
    }

    connect(peer, &Peer::disconnected, this, &SignalProxy::removePeerBySender);
    connect(peer, &Peer::secureStateChanged, this, &SignalProxy::updateSecureState);

    if (!peer->parent())
        peer->setParent(this);

    if (peer->id() < 0) {
        peer->setId(nextPeerId());
        peer->setConnectedSince(QDateTime::currentDateTimeUtc());
    }

    _peerMap[peer->id()] = peer;

    peer->setSignalProxy(this);

    if (peerCount() == 1)
        emit connected();

    updateSecureState();
    return true;
}

void SignalProxy::removeAllPeers()
{
    Q_ASSERT(proxyMode() == Server || peerCount() <= 1);
    // we need to copy that list since we modify it in the loop
    QList<Peer*> peers = _peerMap.values();
    for (auto peer : peers) {
        removePeer(peer);
    }
}

void SignalProxy::removePeer(Peer* peer)
{
    if (!peer) {
        qWarning() << Q_FUNC_INFO << "Trying to remove a null peer!";
        return;
    }

    if (_peerMap.isEmpty()) {
        qWarning() << "SignalProxy::removePeer(): No peers in use!";
        return;
    }

    if (!_peerMap.values().contains(peer)) {
        qWarning() << "SignalProxy: unknown Peer" << peer;
        return;
    }

    disconnect(peer, nullptr, this, nullptr);
    peer->setSignalProxy(nullptr);

    _peerMap.remove(peer->id());
    emit peerRemoved(peer);

    if (peer->parent() == this)
        peer->deleteLater();

    updateSecureState();

    if (_peerMap.isEmpty())
        emit disconnected();
}

void SignalProxy::removePeerBySender()
{
    removePeer(qobject_cast<Peer*>(sender()));
}

void SignalProxy::renameObject(const SyncableObject* obj, const QString& newname, const QString& oldname)
{
    if (proxyMode() == Client)
        return;

    const QMetaObject* meta = obj->syncMetaObject();
    const QByteArray className(meta->className());
    objectRenamed(className, newname, oldname);

    // Convert className to QString for RpcCall
    dispatch(RpcCall("__objectRenamed__", QVariantList() << QString::fromLatin1(className) << newname << oldname));
}

void SignalProxy::objectRenamed(const QByteArray& classname, const QString& newname, const QString& oldname)
{
    if (newname != oldname) {
        if (_syncSlave.contains(classname) && _syncSlave[classname].contains(oldname)) {
            SyncableObject* obj = _syncSlave[classname][newname] = _syncSlave[classname].take(oldname);
            obj->setObjectName(newname);
            requestInit(obj);
        }
    }
}

const QMetaObject* SignalProxy::metaObject(const QObject* obj)
{
    if (const auto* syncObject = qobject_cast<const SyncableObject*>(obj))
        return syncObject->syncMetaObject();
    else
        return obj->metaObject();
}

SignalProxy::ExtendedMetaObject* SignalProxy::extendedMetaObject(const QMetaObject* meta) const
{
    if (_extendedMetaObjects.contains(meta))
        return _extendedMetaObjects[meta];
    else
        return nullptr;
}

SignalProxy::ExtendedMetaObject* SignalProxy::createExtendedMetaObject(const QMetaObject* meta, bool checkConflicts)
{
    if (!_extendedMetaObjects.contains(meta)) {
        _extendedMetaObjects[meta] = new ExtendedMetaObject(meta, checkConflicts);
    }
    return _extendedMetaObjects[meta];
}

void SignalProxy::attachSlotObject(const QByteArray& signalName, std::unique_ptr<SlotObjectBase> slotObject)
{
    // Remove all attached slots related to the context upon its destruction
    connect(slotObject->context(), &QObject::destroyed, this, &SignalProxy::detachSlotObjects, Qt::UniqueConnection);

    _attachedSlots.emplace(QMetaObject::normalizedSignature(signalName.constData()), std::move(slotObject));
}

void SignalProxy::detachSlotObjects(const QObject* context)
{
    for (auto&& it = _attachedSlots.begin(); it != _attachedSlots.end();) {
        if (it->second->context() == context) {
            it = _attachedSlots.erase(it);
        }
        else {
            ++it;
        }
    }
}

void SignalProxy::synchronize(SyncableObject* obj)
{
    createExtendedMetaObject(obj, true);

    // attaching as slave to receive sync Calls
    QByteArray className(obj->syncMetaObject()->className());
    _syncSlave[className][obj->objectName()] = obj;

    if (proxyMode() == Server) {
        obj->setInitialized();
        emit objectInitialized(obj);
    }
    else {
        if (obj->isInitialized())
            emit objectInitialized(obj);
        else
            requestInit(obj);
    }

    obj->synchronize(this);
}

void SignalProxy::stopSynchronize(SyncableObject* obj)
{
    // we can't use a className here, since it might be effed up, if we receive the call as a result of a decon
    // gladly the objectName() is still valid. So we have only to iterate over the classes not each instance! *sigh*
    QHash<QByteArray, ObjectId>::iterator classIter = _syncSlave.begin();
    while (classIter != _syncSlave.end()) {
        if (classIter->contains(obj->objectName()) && classIter.value()[obj->objectName()] == obj) {
            classIter->remove(obj->objectName());
            break;
        }
        ++classIter;
    }
    obj->stopSynchronize(this);
}

void SignalProxy::dispatchSignal(QByteArray sigName, QVariantList params)
{
    // Normalize sigName to match SIGNAL macro output
    QByteArray normalizedSig = QMetaObject::normalizedSignature(sigName.constData());
    RpcCall rpcCall{normalizedSig, std::move(params)};
    if (_restrictMessageTarget) {
        for (auto&& peer : _restrictedTargets) {
            dispatch(peer, rpcCall);
        }
    }
    else {
        dispatch(rpcCall);
    }
}

template<class T>
void SignalProxy::dispatch(const T& protoMessage)
{
    for (auto&& peer : _peerMap.values()) {
        dispatch(peer, protoMessage);
    }
}

template<class T>
void SignalProxy::dispatch(Peer* peer, const T& protoMessage)
{
    _targetPeer = peer;

    if (peer && peer->isOpen())
        peer->dispatch(protoMessage);
    else
        QCoreApplication::postEvent(this, new ::RemovePeerEvent(peer));

    _targetPeer = nullptr;
}

void SignalProxy::handle(Peer* peer, const SyncMessage& syncMessage)
{
    if (!_syncSlave.contains(syncMessage.className) || !_syncSlave[syncMessage.className].contains(syncMessage.objectName)) {
        qWarning() << QString("no registered receiver for sync call: %1::%2 (objectName=\"%3\"). Params are:")
                          .arg(QString(syncMessage.className), QString(syncMessage.slotName), syncMessage.objectName)
                   << syncMessage.params;
        return;
    }

    SyncableObject* receiver = _syncSlave[syncMessage.className][syncMessage.objectName];
    ExtendedMetaObject* eMeta = extendedMetaObject(receiver);
    if (!eMeta->slotMap().contains(syncMessage.slotName)) {
        qWarning() << QString("no matching slot for sync call: %1::%2 (objectName=\"%3\"). Params are:")
                          .arg(QString(syncMessage.className), QString(syncMessage.slotName), syncMessage.objectName)
                   << syncMessage.params;
        return;
    }

    int slotId = eMeta->slotMap()[syncMessage.slotName];
    if (proxyMode() != eMeta->receiverMode(slotId)) {
        qWarning("SignalProxy::handleSync(): invokeMethod for \"%s\" failed. Wrong ProxyMode!", eMeta->methodName(slotId).constData());
        return;
    }

    // We can no longer construct a QVariant from QMetaType::Void
    QVariant returnValue;
    int returnType = eMeta->returnType(slotId);
    if (returnType != QMetaType::UnknownType)
        returnValue = QVariant(QMetaType(returnType));

    if (!invokeSlot(receiver, slotId, syncMessage.params, returnValue, peer)) {
        qWarning("SignalProxy::handleSync(): invokeMethod for \"%s\" failed ", eMeta->methodName(slotId).constData());
        return;
    }

    if (returnValue.metaType() != QMetaType() && eMeta->receiveMap().contains(slotId)) {
        int receiverId = eMeta->receiveMap()[slotId];
        QVariantList returnParams;
        if (eMeta->argTypes(receiverId).size() > 1)
            returnParams << syncMessage.params;
        returnParams << returnValue;
        _targetPeer = peer;
        peer->dispatch(SyncMessage(syncMessage.className, syncMessage.objectName, eMeta->methodName(receiverId), returnParams));
        _targetPeer = nullptr;
    }

    // send emit update signal
    invokeSlot(receiver, eMeta->updatedRemotelyId());
}

void SignalProxy::handle(Peer* peer, const RpcCall& rpcCall)
{
    Q_UNUSED(peer)

    auto range = _attachedSlots.equal_range(rpcCall.signalName);
    std::for_each(range.first, range.second, [&rpcCall](const auto& p) {
        if (!p.second->invoke(rpcCall.params)) {
            qWarning() << "Could not invoke slot for remote signal" << rpcCall.signalName;
        }
    });
}

void SignalProxy::handle(Peer* peer, const InitRequest& initRequest)
{
    if (!_syncSlave.contains(initRequest.className)) {
        qWarning() << "SignalProxy::handleInitRequest() received initRequest for unregistered Class:" << initRequest.className;
        return;
    }

    if (!_syncSlave[initRequest.className].contains(initRequest.objectName)) {
        qWarning() << "SignalProxy::handleInitRequest() received initRequest for unregistered Object:" << initRequest.className
                   << initRequest.objectName;
        return;
    }

    SyncableObject* obj = _syncSlave[initRequest.className][initRequest.objectName];
    _targetPeer = peer;
    peer->dispatch(InitData(initRequest.className, initRequest.objectName, initData(obj)));
    _targetPeer = nullptr;
}

void SignalProxy::handle(Peer* peer, const InitData& initData)
{
    Q_UNUSED(peer)

    if (!_syncSlave.contains(initData.className)) {
        qWarning() << "SignalProxy::handleInitData() received initData for unregistered Class:" << initData.className;
        return;
    }

    if (!_syncSlave[initData.className].contains(initData.objectName)) {
        qWarning() << "SignalProxy::handleInitData() received initData for unregistered Object:" << initData.className << initData.objectName;
        return;
    }

    SyncableObject* obj = _syncSlave[initData.className][initData.objectName];
    setInitData(obj, initData.initData);
}

bool SignalProxy::invokeSlot(QObject* receiver, int methodId, const QVariantList& params, QVariant& returnValue, Peer* peer)
{
    ExtendedMetaObject* eMeta = extendedMetaObject(receiver);
    const QList<int> args = eMeta->argTypes(methodId);
    const int numArgs = params.count() < args.count() ? params.count() : args.count();

    if (eMeta->minArgCount(methodId) > params.count()) {
        qWarning() << "SignalProxy::invokeSlot(): not enough params to invoke" << eMeta->methodName(methodId);
        return false;
    }

    void* _a[] = {nullptr,  // return type...
                  nullptr,
                  nullptr,
                  nullptr,
                  nullptr,
                  nullptr,  // and 10 args - that's the max size qt can handle with signals and slots
                  nullptr,
                  nullptr,
                  nullptr,
                  nullptr,
                  nullptr};

    // check for argument compatibility and build params array
    for (int i = 0; i < numArgs; i++) {
        if (!params[i].isValid()) {
            qWarning() << "SignalProxy::invokeSlot(): received invalid data for argument number" << i << "of method"
                       << QString("%1::%2()")
                              .arg(receiver->metaObject()->className())
                              .arg(receiver->metaObject()->method(methodId).methodSignature().constData());
            qWarning() << "                            - make sure all your data types are known by the Qt MetaSystem";
            return false;
        }
        if (args[i] != QMetaType::fromName(params[i].metaType().name()).id()) {
            qWarning() << "SignalProxy::invokeSlot(): incompatible param types to invoke" << eMeta->methodName(methodId);
            return false;
        }

        _a[i + 1] = const_cast<void*>(params[i].constData());
    }

    if (returnValue.metaType() != QMetaType())
        _a[0] = const_cast<void*>(returnValue.constData());

    Qt::ConnectionType type = QThread::currentThread() == receiver->thread() ? Qt::DirectConnection : Qt::QueuedConnection;

    if (type == Qt::DirectConnection) {
        _sourcePeer = peer;
        auto result = receiver->qt_metacall(QMetaObject::InvokeMetaMethod, methodId, _a) < 0;
        _sourcePeer = nullptr;
        return result;
    }
    else {
        qWarning() << "Queued Connections are not implemented yet";
        // note to self: qmetaobject.cpp:990 ff
        return false;
    }
}

bool SignalProxy::invokeSlot(QObject* receiver, int methodId, const QVariantList& params, Peer* peer)
{
    QVariant ret;
    return invokeSlot(receiver, methodId, params, ret, peer);
}

void SignalProxy::requestInit(SyncableObject* obj)
{
    if (proxyMode() == Server || obj->isInitialized())
        return;

    dispatch(InitRequest(obj->syncMetaObject()->className(), obj->objectName()));
}

QVariantMap SignalProxy::initData(SyncableObject* obj) const
{
    QVariantMap initData = obj->toVariantMap();
    // Convert FooData from QByteArray to QString if present
    if (initData.contains("FooData") && initData["FooData"].metaType() == QMetaType::fromType<QByteArray>()) {
        initData["FooData"] = QString::fromUtf8(initData["FooData"].toByteArray());
    }
    return initData;
}

void SignalProxy::setInitData(SyncableObject* obj, const QVariantMap& properties)
{
    if (obj->isInitialized())
        return;
    obj->fromVariantMap(properties);
    obj->setInitialized();
    emit objectInitialized(obj);
    invokeSlot(obj, extendedMetaObject(obj)->updatedRemotelyId());
}

void SignalProxy::customEvent(QEvent* event)
{
    switch ((int)event->type()) {
    case RemovePeerEvent: {
        auto* e = static_cast<::RemovePeerEvent*>(event);
        removePeer(e->peer);
        event->accept();
        break;
    }

    default:
        qWarning() << Q_FUNC_INFO << "Received unknown custom event:" << event->type();
        return;
    }
}

void SignalProxy::sync_call__(const SyncableObject* obj, SignalProxy::ProxyMode modeType, const char* funcname, va_list ap)
{
    if (modeType != _proxyMode)
        return;

    ExtendedMetaObject* eMeta = extendedMetaObject(obj);

    QVariantList params;

    const QList<int>& argTypes = eMeta->argTypes(eMeta->methodId(QByteArray(funcname)));

    for (int i = 0; i < argTypes.size(); i++) {
        if (argTypes[i] == 0) {
            qWarning() << Q_FUNC_INFO << "received invalid data for argument number" << i << "of signal"
                       << QString("%1::%2").arg(eMeta->metaObject()->className()).arg(funcname);
            qWarning() << "        - make sure all your data types are known by the Qt MetaSystem";
            return;
        }
        params << QVariant(QMetaType(argTypes[i]), va_arg(ap, const void*));
    }

    if (_restrictMessageTarget) {
        for (auto peer : _restrictedTargets) {
            if (peer != nullptr)
                dispatch(peer, SyncMessage(eMeta->metaObject()->className(), obj->objectName(), QByteArray(funcname), params));
        }
    }
    else
        dispatch(SyncMessage(eMeta->metaObject()->className(), obj->objectName(), QByteArray(funcname), params));
}

void SignalProxy::disconnectDevice(QIODevice* dev, const QString& reason)
{
    if (!reason.isEmpty())
        qWarning() << qPrintable(reason);
    auto* sock = qobject_cast<QAbstractSocket*>(dev);
    if (sock)
        qWarning() << qPrintable(tr("Disconnecting")) << qPrintable(sock->peerAddress().toString());
    dev->close();
}

void SignalProxy::dumpProxyStats()
{
    QString mode;
    if (proxyMode() == Server)
        mode = "Server";
    else
        mode = "Client";

    int slaveCount = 0;
    for (const ObjectId& oid : _syncSlave)
        slaveCount += oid.size();

    qDebug() << this;
    qDebug() << "              Proxy Mode:" << mode;
    qDebug() << "          attached Slots:" << _attachedSlots.size();
    qDebug() << " number of synced Slaves:" << slaveCount;
    qDebug() << "number of Classes cached:" << _extendedMetaObjects.size();
}

void SignalProxy::updateSecureState()
{
    bool wasSecure = _secure;

    _secure = !_peerMap.isEmpty();
    for (auto peer : _peerMap.values()) {
        _secure &= peer->isSecure();
    }

    if (wasSecure != _secure)
        emit secureStateChanged(_secure);
}

QVariantList SignalProxy::peerData()
{
    QVariantList result;
    for (auto&& peer : _peerMap.values()) {
        QVariantMap data;
        data["id"] = peer->id();
        data["clientVersion"] = peer->clientVersion();
        // We explicitly rename this, as, due to the Debian reproducibility changes, buildDate isn’t actually the build
        // date anymore, but on newer clients the date of the last git commit
        data["clientVersionDate"] = peer->buildDate();
        data["remoteAddress"] = peer->address();
        data["connectedSince"] = peer->connectedSince();
        data["secure"] = peer->isSecure();
        data["features"] = static_cast<quint32>(peer->features().toLegacyFeatures());
        data["featureList"] = peer->features().toStringList();
        result << data;
    }
    return result;
}

Peer* SignalProxy::peerById(int peerId)
{
    return _peerMap.value(peerId);
}

void SignalProxy::restrictTargetPeers(QSet<Peer*> peers, std::function<void()> closure)
{
    auto previousRestrictMessageTarget = _restrictMessageTarget;
    auto previousRestrictedTargets = _restrictedTargets;
    _restrictMessageTarget = true;
    _restrictedTargets = peers;

    closure();

    _restrictMessageTarget = previousRestrictMessageTarget;
    _restrictedTargets = previousRestrictedTargets;
}

Peer* SignalProxy::sourcePeer()
{
    return _sourcePeer;
}

void SignalProxy::setSourcePeer(Peer* sourcePeer)
{
    _sourcePeer = sourcePeer;
}

Peer* SignalProxy::targetPeer()
{
    return _targetPeer;
}

void SignalProxy::setTargetPeer(Peer* targetPeer)
{
    _targetPeer = targetPeer;
}

// ---- SlotObjectBase ---------------------------------------------------------------------------------------------------------------------

SignalProxy::SlotObjectBase::SlotObjectBase(const QObject* context)
    : _context{context}
{
}

const QObject* SignalProxy::SlotObjectBase::context() const
{
    return _context;
}

//  ---- ExtendedMetaObject ----------------------------------------------------------------------------------------------------------------

SignalProxy::ExtendedMetaObject::ExtendedMetaObject(const QMetaObject* meta, bool checkConflicts)
    : _meta(meta)
    , _updatedRemotelyId(_meta->indexOfSignal("updatedRemotely()"))
{
    for (int i = 0; i < _meta->methodCount(); i++) {
        if (_meta->method(i).methodType() != QMetaMethod::Slot)
            continue;

        if (_meta->method(i).methodSignature().contains('*'))
            continue;  // skip methods with ptr params

        QByteArray method = methodName(_meta->method(i));
        if (method.startsWith("init"))
            continue;  // skip initializers

        if (_methodIds.contains(method)) {
            /* funny... moc creates for methods containing default parameters multiple metaMethod with separate methodIds.
               we don't care... we just need the full fledged version
             */
            const QMetaMethod& current = _meta->method(_methodIds[method]);
            const QMetaMethod& candidate = _meta->method(i);
            if (current.parameterTypes().count() > candidate.parameterTypes().count()) {
                int minCount = candidate.parameterTypes().count();
                QList<QByteArray> commonParams = current.parameterTypes().mid(0, minCount);
                if (commonParams == candidate.parameterTypes())
                    continue;  // we already got the full featured version
            }
            else {
                int minCount = current.parameterTypes().count();
                QList<QByteArray> commonParams = candidate.parameterTypes().mid(0, minCount);
                if (commonParams == current.parameterTypes()) {
                    _methodIds[method] = i;  // use the new one
                    continue;
                }
            }
            if (checkConflicts) {
                qWarning() << "class" << meta->className() << "contains overloaded methods which is currently not supported!";
                qWarning() << " - " << _meta->method(i).methodSignature() << "conflicts with"
                           << _meta->method(_methodIds[method]).methodSignature();
            }
            continue;
        }
        _methodIds[method] = i;
    }
}

const SignalProxy::ExtendedMetaObject::MethodDescriptor& SignalProxy::ExtendedMetaObject::methodDescriptor(int methodId)
{
    if (!_methods.contains(methodId)) {
        _methods[methodId] = MethodDescriptor(_meta->method(methodId));
    }
    return _methods[methodId];
}

const QHash<int, int>& SignalProxy::ExtendedMetaObject::receiveMap()
{
    if (_receiveMap.isEmpty()) {
        QHash<int, int> receiveMap;

        QMetaMethod requestSlot;
        QByteArray returnTypeName;
        QByteArray signature;
        QByteArray methodName;
        QByteArray params;
        int paramsPos;
        int receiverId;
        const int methodCount = _meta->methodCount();
        for (int i = 0; i < methodCount; i++) {
            requestSlot = _meta->method(i);
            if (requestSlot.methodType() != QMetaMethod::Slot)
                continue;

            returnTypeName = requestSlot.typeName();
            if (QMetaType::UnknownType == QMetaType::fromName(returnTypeName).id())
                continue;

            signature = requestSlot.methodSignature();
            if (!signature.startsWith("request"))
                continue;

            paramsPos = signature.indexOf('(');
            if (paramsPos == -1)
                continue;

            methodName = signature.left(paramsPos);
            params = signature.mid(paramsPos);

            methodName = methodName.replace("request", "receive");
            params = params.left(params.size() - 1) + ", " + returnTypeName + ")";

            signature = QMetaObject::normalizedSignature(methodName + params);
            receiverId = _meta->indexOfSlot(signature);

            if (receiverId == -1) {
                signature = QMetaObject::normalizedSignature(methodName + "(" + returnTypeName + ")");
                receiverId = _meta->indexOfSlot(signature);
            }

            if (receiverId != -1) {
                receiveMap[i] = receiverId;
            }
        }
        _receiveMap = receiveMap;
    }
    return _receiveMap;
}

QByteArray SignalProxy::ExtendedMetaObject::methodName(const QMetaMethod& method)
{
    QByteArray sig(method.methodSignature());
    return sig.left(sig.indexOf("("));
}

QString SignalProxy::ExtendedMetaObject::methodBaseName(const QMetaMethod& method)
{
    QString methodname = QString(method.methodSignature()).section("(", 0, 0);

    // determine where we have to chop:
    int upperCharPos;
    if (method.methodType() == QMetaMethod::Slot) {
        // we take everything from the first uppercase char if it's slot
        upperCharPos = methodname.indexOf(QRegularExpression("[A-Z]"));
        if (upperCharPos == -1)
            return QString();
        methodname = methodname.mid(upperCharPos);
    }
    else {
        // and if it's a signal we discard everything from the last uppercase char
        upperCharPos = methodname.lastIndexOf(QRegularExpression("[A-Z]"));
        if (upperCharPos == -1)
            return QString();
        methodname = methodname.left(upperCharPos);
    }

    methodname[0] = methodname[0].toUpper();

    return methodname;
}

SignalProxy::ExtendedMetaObject::MethodDescriptor::MethodDescriptor(const QMetaMethod& method)
    : _methodName(SignalProxy::ExtendedMetaObject::methodName(method))
    , _returnType(QMetaType::fromName(method.typeName()).id())
{
    // determine argTypes
    QList<QByteArray> paramTypes = method.parameterTypes();
    QList<int> argTypes;
    for (int i = 0; i < paramTypes.count(); i++) {
        argTypes.append(QMetaType::fromName(paramTypes[i]).id());
    }
    _argTypes = argTypes;

    // determine minArgCount
    QString signature(method.methodSignature());
    _minArgCount = paramTypes.count() - signature.count("=");

    _receiverMode = (_methodName.startsWith("request") || _methodName.startsWith("set")) ? SignalProxy::Server : SignalProxy::Client;
}
