// SPDX-License-Identifier: GPL-2.0-or-later

#include "dccconfig.h"

#include <QDataStream>
#include <QMetaProperty>

#include "types.h"

DccConfig::DccConfig(QObject* parent)
    : SyncableObject("DccConfig", parent)
{
    static auto regTypes = []() -> bool {
        qRegisterMetaType<DccConfig::IpDetectionMode>("DccConfig::IpDetectionMode");
        qRegisterMetaType<DccConfig::PortSelectionMode>("DccConfig::PortSelectionMode");
        return true;
    }();
    Q_UNUSED(regTypes);

    setAllowClientUpdates(true);
}

QDataStream& operator<<(QDataStream& out, const DccConfig::IpDetectionMode& mode)
{
    out << static_cast<quint8>(mode);
    return out;
}

QDataStream& operator>>(QDataStream& in, DccConfig::IpDetectionMode& mode)
{
    quint8 value;
    in >> value;
    mode = static_cast<DccConfig::IpDetectionMode>(value);
    return in;
}

QDataStream& operator<<(QDataStream& out, const DccConfig::PortSelectionMode& mode)
{
    out << static_cast<quint8>(mode);
    return out;
}

QDataStream& operator>>(QDataStream& in, DccConfig::PortSelectionMode& mode)
{
    quint8 value;
    in >> value;
    mode = static_cast<DccConfig::PortSelectionMode>(value);
    return in;
}

bool DccConfig::operator==(const DccConfig& other)
{
    // NOTE: We don't compare the SyncableObject attributes (isInitialized, clientUpdatesAllowed())
    static auto propCount = staticMetaObject.propertyCount();
    for (int i = 0; i < propCount; ++i) {
        auto propName = staticMetaObject.property(i).name();
        if (QLatin1String(propName) == QLatin1String("objectName"))
            continue;
        if (QLatin1String(propName) == QLatin1String("outgoingIp")) {
            // QVariant can't compare QHostAddress
            if (property(propName).value<QHostAddress>() != other.property(propName).value<QHostAddress>())
                return false;
        }
        else if (property(propName) != other.property(propName))
            return false;
    }
    return true;
}

bool DccConfig::isDccEnabled() const
{
    return _dccEnabled;
}

void DccConfig::setDccEnabled(bool enabled)
{
    _dccEnabled = enabled;
}

QHostAddress DccConfig::outgoingIp() const
{
    return _outgoingIp;
}

void DccConfig::setOutgoingIp(const QHostAddress& outgoingIp)
{
    _outgoingIp = outgoingIp;
}

DccConfig::IpDetectionMode DccConfig::ipDetectionMode() const
{
    return _ipDetectionMode;
}

void DccConfig::setIpDetectionMode(DccConfig::IpDetectionMode detectionMode)
{
    _ipDetectionMode = detectionMode;
}

DccConfig::PortSelectionMode DccConfig::portSelectionMode() const
{
    return _portSelectionMode;
}

void DccConfig::setPortSelectionMode(DccConfig::PortSelectionMode portSelectionMode)
{
    _portSelectionMode = portSelectionMode;
}

quint16 DccConfig::minPort() const
{
    return _minPort;
}

void DccConfig::setMinPort(quint16 port)
{
    _minPort = port;
}

quint16 DccConfig::maxPort() const
{
    return _maxPort;
}

void DccConfig::setMaxPort(quint16 port)
{
    _maxPort = port;
}

int DccConfig::chunkSize() const
{
    return _chunkSize;
}

void DccConfig::setChunkSize(int chunkSize)
{
    _chunkSize = chunkSize;
}

int DccConfig::sendTimeout() const
{
    return _sendTimeout;
}

void DccConfig::setSendTimeout(int timeout)
{
    _sendTimeout = timeout;
}

bool DccConfig::usePassiveDcc() const
{
    return _usePassiveDcc;
}

void DccConfig::setUsePassiveDcc(bool use)
{
    _usePassiveDcc = use;
}

bool DccConfig::useFastSend() const
{
    return _useFastSend;
}

void DccConfig::setUseFastSend(bool use)
{
    _useFastSend = use;
}
