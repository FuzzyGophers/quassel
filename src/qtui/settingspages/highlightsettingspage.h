// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef _HIGHLIGHTSETTINGSPAGE_H_
#define _HIGHLIGHTSETTINGSPAGE_H_

#include <QTableWidgetItem>
#include <QVariantList>

#include "settingspage.h"

#include "ui_highlightsettingspage.h"

class HighlightSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    HighlightSettingsPage(QWidget* parent = nullptr);

    bool hasDefaults() const override;

public slots:
    void save() override;
    void load() override;
    void defaults() override;

private slots:
    void widgetHasChanged();
    void addNewRow(QString name = tr("highlight rule"),
                   bool regex = false,
                   bool cs = false,
                   bool enable = true,
                   QString chanName = "",
                   bool self = false);
    void removeSelectedRows();
    void selectRow(QTableWidgetItem* item);
    void tableChanged(QTableWidgetItem* item);

    /**
     * Event handler for Local Highlights Details button
     */
    void on_localHighlightsDetails_clicked();

private:
    Ui::HighlightSettingsPage ui;
    QVariantList highlightList;
    // QVariant -> QHash<QString, QVariant>:
    //    regex:  bool
    //    name:   QString
    //    enable: bool
    enum column
    {
        EnableColumn = 0,
        NameColumn = 1,
        RegExColumn = 2,
        CsColumn = 3,
        ChanColumn = 4,
        ColumnCount = 5
    };

    void emptyTable();

    bool testHasChanged();
};

#endif
