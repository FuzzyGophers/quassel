// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QItemSelection>

#include "settingspage.h"

#include "ui_buffervieweditdlg.h"
#include "ui_bufferviewsettingspage.h"

class BufferViewConfig;

class BufferViewSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    BufferViewSettingsPage(QWidget* parent = nullptr);
    ~BufferViewSettingsPage() override;

public slots:
    void save() final override;
    void load() final override;
    void reset();

private slots:
    void coreConnectionStateChanged(bool state);

    void addBufferView(BufferViewConfig* config);
    void addBufferView(int bufferViewId);
    void bufferViewDeleted();
    void newBufferView(const QString& bufferViewName);
    void updateBufferView();

    void enableStatusBuffers(int networkIdx);

    void on_addBufferView_clicked();
    void on_renameBufferView_clicked();
    void on_deleteBufferView_clicked();
    void bufferViewSelectionChanged(const QItemSelection& current, const QItemSelection& previous);

    void widgetHasChanged();

private:
    Ui::BufferViewSettingsPage ui;
    bool _ignoreWidgetChanges{false};
    bool _useBufferViewHint{false};
    int _bufferViewHint{0};

    // list of bufferviews to create
    QList<BufferViewConfig*> _newBufferViews;

    // list of buferViews to delete
    QList<int> _deleteBufferViews;

    // Hash of pointers to cloned bufferViewConfigs holding the changes
    QHash<BufferViewConfig*, BufferViewConfig*> _changedBufferViews;

    int listPos(BufferViewConfig* config);
    BufferViewConfig* bufferView(int listPos);
    bool selectBufferViewById(int bufferViewId);
    BufferViewConfig* cloneConfig(BufferViewConfig* config);
    BufferViewConfig* configForDisplay(BufferViewConfig* config);

    void loadConfig(BufferViewConfig* config);
    void saveConfig(BufferViewConfig* config);
    bool testHasChanged();
};

/**************************************************************************
 * BufferViewEditDlg
 *************************************************************************/
class BufferViewEditDlg : public QDialog
{
    Q_OBJECT

public:
    BufferViewEditDlg(const QString& old, QStringList existing = QStringList(), QWidget* parent = nullptr);

    inline QString bufferViewName() const { return ui.bufferViewEdit->text(); }

private slots:
    void on_bufferViewEdit_textChanged(const QString&);

private:
    Ui::BufferViewEditDlg ui;

    QStringList existing;
};
