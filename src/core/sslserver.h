// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QFile>
#include <QSslCertificate>
#include <QSslKey>
#include <QTcpServer>

#include "metricsserver.h"

class SslServer : public QTcpServer
{
    Q_OBJECT

public:
    SslServer(QObject* parent = nullptr);

    const QSslCertificate& certificate() const { return _cert; }
    const QSslKey& key() const { return _key; }
    bool isCertValid() const { return _isCertValid; }

    /**
     * Reloads SSL certificates used for connections
     *
     * If this command fails, it will try to maintain the most recent working certificate.  Error
     * conditions are automatically written to the log.
     *
     * @return True if certificates reloaded successfully, otherwise false.
     */
    bool reloadCerts();

    void setMetricsServer(MetricsServer* metricsServer);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

    bool setCertificate(const QString& path, const QString& keyPath);

private:
    /**
     * Loads SSL certificates used for connections
     *
     * If this command fails, it will try to maintain the most recent working certificate.  Will log
     * specific failure points, but does not offer verbose guidance.
     *
     * @return True if certificates loaded successfully, otherwise false.
     */
    bool loadCerts();
    QSslKey loadKey(QFile* keyFile);

    MetricsServer* _metricsServer{nullptr};

    QSslCertificate _cert;
    QSslKey _key;
    QList<QSslCertificate> _ca;
    bool _isCertValid{false};

    // Used when reloading certificates later
    QString _sslCertPath;  /// Path to the certificate file
    QString _sslKeyPath;   /// Path to the private key file (may be in same file as above)

    QDateTime _certificateExpires;
};
