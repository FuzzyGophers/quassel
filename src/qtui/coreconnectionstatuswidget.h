// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CORECONNECTIONSTATUSWIDGET_H
#define CORECONNECTIONSTATUSWIDGET_H

#include <QWidget>

#include "coreconnection.h"

#include "ui_coreconnectionstatuswidget.h"

class CoreConnectionStatusWidget : public QWidget
{
    Q_OBJECT

public:
    CoreConnectionStatusWidget(CoreConnection* connection, QWidget* parent = nullptr);

    inline CoreConnection* coreConnection() const { return _coreConnection; }

public slots:
    void update();
    void updateLag(int msecs);

private slots:
    void connectionStateChanged(CoreConnection::ConnectionState);
    void progressRangeChanged(int min, int max);

private:
    Ui::CoreConnectionStatusWidget ui;

    CoreConnection* _coreConnection;
};

#endif  // CORECONNECTIONSTATUSWIDGET_H
