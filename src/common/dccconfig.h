// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QHostAddress>

#include "syncableobject.h"

/**
 * Class holding the core-side DCC configuration.
 *
 * @warning Equality and assignment operators are optimized for use in a settings page
 *          and do not cover all attributes!
 */
class COMMON_EXPORT DccConfig : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

    /// Whether DCC is enabled
    Q_PROPERTY(bool dccEnabled READ isDccEnabled WRITE setDccEnabled)
    /// The IP to use for outgoing traffic
    Q_PROPERTY(QHostAddress outgoingIp READ outgoingIp WRITE setOutgoingIp)
    /// The IP detection mode
    Q_PROPERTY(DccConfig::IpDetectionMode ipDetectionMode READ ipDetectionMode WRITE setIpDetectionMode)
    /// The port range selection mode
    Q_PROPERTY(DccConfig::PortSelectionMode portSelectionMode READ portSelectionMode WRITE setPortSelectionMode)
    /// Minimum port to use for incoming connections
    Q_PROPERTY(quint16 minPort READ minPort WRITE setMinPort)
    /// Maximum port to use for incoming connections
    Q_PROPERTY(quint16 maxPort READ maxPort WRITE setMaxPort)
    /// The chunk size to be used
    Q_PROPERTY(int chunkSize READ chunkSize WRITE setChunkSize)
    /// The timeout for DCC transfers
    Q_PROPERTY(int sendTimeout READ sendTimeout WRITE setSendTimeout)
    /// Whether passive (reverse) DCC should be used
    Q_PROPERTY(bool usePassiveDcc READ usePassiveDcc WRITE setUsePassiveDcc)
    /// Whether fast sending should be used
    Q_PROPERTY(bool useFastSend READ useFastSend WRITE setUseFastSend)

public:
    /**
     * Mode for detecting the outgoing IP
     */
    enum class IpDetectionMode : quint8
    {
        Automatic,  ///< Automatic detection (network socket or USERHOST)
        Manual,     ///< Manually specified IP
    };
    Q_ENUMS(IpDetectionMode)

    /**
     * Mode for selecting the port range for DCC
     */
    enum class PortSelectionMode : quint8
    {
        Automatic,  ///< Automatic port selection
        Manual,     ///< Manually specified port range
    };
    Q_ENUMS(PortSelectionMode)

    /**
     * Constructor.
     *
     * Initializes the object with useful default values.
     *
     * @param[in] parent QObject parent
     */
    DccConfig(QObject* parent = nullptr);

    /**
     * Equality operator.
     *
     * @note Only compares properties relevant for config management!
     *
     * @param[in] other Right-hand side instance
     * @returns Whether the two instances have equal properties
     */
    bool operator==(const DccConfig& other);

    /// @name Getters
    /// @{
    bool isDccEnabled() const;
    QHostAddress outgoingIp() const;
    IpDetectionMode ipDetectionMode() const;
    PortSelectionMode portSelectionMode() const;
    quint16 minPort() const;
    quint16 maxPort() const;
    int chunkSize() const;
    int sendTimeout() const;
    bool usePassiveDcc() const;
    bool useFastSend() const;
    /// @}

public slots:
    /// @name Setters
    /// @{
    void setDccEnabled(bool enabled);
    void setOutgoingIp(const QHostAddress& outgoingIp);
    void setIpDetectionMode(DccConfig::IpDetectionMode ipDetectionMode);
    void setPortSelectionMode(DccConfig::PortSelectionMode portSelectionMode);
    void setMinPort(quint16 port);
    void setMaxPort(quint16 port);
    void setChunkSize(int chunkSize);
    void setSendTimeout(int timeout);
    void setUsePassiveDcc(bool use);
    void setUseFastSend(bool use);
    /// @}

private:
    // The given values are used as default for both initialization and settings
    bool _dccEnabled{false};
    QHostAddress _outgoingIp{QHostAddress::LocalHost};
    IpDetectionMode _ipDetectionMode{IpDetectionMode::Automatic};
    PortSelectionMode _portSelectionMode{PortSelectionMode::Automatic};
    quint16 _minPort{1024};
    quint16 _maxPort{32767};
    int _chunkSize{16};
    int _sendTimeout{180};
    bool _usePassiveDcc{false};
    bool _useFastSend{false};
};

Q_DECLARE_METATYPE(DccConfig::IpDetectionMode)
Q_DECLARE_METATYPE(DccConfig::PortSelectionMode)
