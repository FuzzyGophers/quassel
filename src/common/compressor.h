// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>

#include <zlib.h>

class QTcpSocket;

class Compressor : public QObject
{
    Q_OBJECT

public:
    enum CompressionLevel
    {
        NoCompression,
        DefaultCompression,
        BestCompression,
        BestSpeed
    };

    enum Error
    {
        NoError,
        StreamError,
        DeviceError
    };

    enum WriteBufferHint
    {
        NoFlush,
        Flush
    };

    Compressor(QTcpSocket* socket, CompressionLevel level, QObject* parent = nullptr);
    ~Compressor() override;

    CompressionLevel compressionLevel() const { return _level; }

    qint64 bytesAvailable() const;

    qint64 read(char* data, qint64 maxSize);
    qint64 write(const char* data, qint64 count, WriteBufferHint flush = Flush);

    void flush();

signals:
    void readyRead();
    void error(Compressor::Error errorCode = StreamError);

private slots:
    void readData();

private:
    bool initStreams();
    void writeData();

private:
    QTcpSocket* _socket;
    CompressionLevel _level;

    QByteArray _readBuffer;
    QByteArray _writeBuffer;

    QByteArray _inputBuffer;
    QByteArray _outputBuffer;

    z_streamp _inflater;
    z_streamp _deflater;
};
