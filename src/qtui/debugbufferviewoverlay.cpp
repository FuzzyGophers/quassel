// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "debugbufferviewoverlay.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include "buffermodel.h"
#include "bufferviewoverlay.h"
#include "bufferviewoverlayfilter.h"
#include "client.h"

DebugBufferViewOverlay::DebugBufferViewOverlay(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    auto* filter = new BufferViewOverlayFilter(Client::bufferModel(), Client::bufferViewOverlay());

    filter->setParent(ui.bufferView);

    ui.bufferView->setModel(filter);
    ui.bufferView->setColumnWidth(0, 250);
    ui.bufferView->setColumnWidth(1, 250);
    ui.bufferView->setColumnWidth(2, 80);
    ui.bufferView->resize(610, 300);
    ui.bufferView->show();

    auto* layout = new QFormLayout(ui.overlayProperties);
    layout->addRow(tr("BufferViews:"), _bufferViews = new QLineEdit(this));
    layout->addRow(tr("All Networks:"), _allNetworks = new QLabel(this));
    layout->addRow(tr("Networks:"), _networks = new QLineEdit(this));
    layout->addRow(tr("Buffers:"), _bufferIds = new QTextEdit(this));
    layout->addRow(tr("Removed buffers:"), _removedBufferIds = new QTextEdit(this));
    layout->addRow(tr("Temp. removed buffers:"), _tempRemovedBufferIds = new QTextEdit(this));

    layout->addRow(tr("Allowed buffer types:"), _allowedBufferTypes = new QLabel(this));
    layout->addRow(tr("Minimum activity:"), _minimumActivity = new QLabel(this));

    layout->addRow(tr("Is initialized:"), _isInitialized = new QLabel(this));

    update();
    connect(Client::bufferViewOverlay(), &BufferViewOverlay::hasChanged, this, &DebugBufferViewOverlay::update);
}

void DebugBufferViewOverlay::update()
{
    BufferViewOverlay* overlay = Client::bufferViewOverlay();

    _allNetworks->setText(overlay->allNetworks() ? "yes" : "no");

    QStringList ids;
    foreach (int bufferViewId, overlay->bufferViewIds()) {
        ids << QString::number(bufferViewId);
    }
    _bufferViews->setText(ids.join(", "));

    ids.clear();
    foreach (NetworkId networkId, overlay->networkIds()) {
        ids << QString::number(networkId.toInt());
    }
    _networks->setText(ids.join(", "));

    ids.clear();
    foreach (BufferId bufferId, overlay->bufferIds()) {
        ids << QString::number(bufferId.toInt());
    }
    _bufferIds->setText(ids.join(", "));

    ids.clear();
    foreach (BufferId bufferId, overlay->removedBufferIds()) {
        ids << QString::number(bufferId.toInt());
    }
    _removedBufferIds->setText(ids.join(", "));

    ids.clear();
    foreach (BufferId bufferId, overlay->tempRemovedBufferIds()) {
        ids << QString::number(bufferId.toInt());
    }
    _tempRemovedBufferIds->setText(ids.join(", "));

    _allowedBufferTypes->setText(QString::number(overlay->allowedBufferTypes()));
    _minimumActivity->setText(QString::number(overlay->minimumActivity()));

    _isInitialized->setText(overlay->isInitialized() ? "yes" : "no");
}
