// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef TOPICWIDGET_H_
#define TOPICWIDGET_H_

#include "abstractitemview.h"

#include "ui_topicwidget.h"

class TopicWidget : public AbstractItemView
{
    Q_OBJECT

public:
    TopicWidget(QWidget* parent = nullptr);

    void setTopic(const QModelIndex& index);
    void setCustomFont(const QFont&);
    void setReadOnly(const bool& readonly);

    bool eventFilter(QObject* obj, QEvent* event) override;
    inline bool isReadOnly() const { return _readonly; }

signals:
    void switchedPlain();

protected slots:
    void currentChanged(const QModelIndex& current, const QModelIndex& previous) override;
    void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight) override;

private slots:
    void on_topicLineEdit_textEntered();
    void on_topicEditButton_clicked();
    void switchEditable();
    void switchPlain();
    void clickableActivated(const Clickable&);
    void updateResizeMode();
    void setCustomFont(const QVariant&);
    void setUseCustomFont(const QVariant&);

private:
    QString sanitizeTopic(const QString& topic);

    Ui::TopicWidget ui;

    QString _topic;
    bool _mouseEntered;
    bool _readonly;
};

#endif
