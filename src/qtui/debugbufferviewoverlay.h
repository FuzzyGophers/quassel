// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef DEBUGBUFFERVIEWOVERLAY_H
#define DEBUGBUFFERVIEWOVERLAY_H

#include "ui_debugbufferviewoverlay.h"

class QLabel;
class QLineEdit;
class QTextEdit;

class DebugBufferViewOverlay : public QWidget
{
    Q_OBJECT

public:
    DebugBufferViewOverlay(QWidget* parent = nullptr);

private slots:
    void update();

private:
    Ui::DebugBufferViewOverlay ui;
    QLineEdit* _bufferViews;
    QLabel* _allNetworks;
    QLineEdit* _networks;
    QTextEdit* _bufferIds;
    QTextEdit* _removedBufferIds;
    QTextEdit* _tempRemovedBufferIds;
    QLabel* _addBuffersAutomatically;
    QLabel* _hideInactiveBuffers;
    QLabel* _allowedBufferTypes;
    QLabel* _minimumActivity;
    QLabel* _isInitialized;
};

#endif  // DEBUGBUFFERVIEWOVERLAY_H
