// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef KEYSEQUENCEWIDGET_H
#define KEYSEQUENCEWIDGET_H

#include <QKeySequence>
#include <QPushButton>
#include <QSet>
#include <QWidget>

#include "shortcutsmodel.h"

class Action;
class ActionCollection;
class KeySequenceButton;
class QToolButton;

class KeySequenceWidget : public QWidget
{
    Q_OBJECT
public:
    KeySequenceWidget(QWidget* parent = nullptr);

    void setModel(ShortcutsModel* model);

public slots:
    void setKeySequence(const QKeySequence& seq);

signals:
    /**
     * This signal is emitted when the current key sequence has changed by user input
     * \param seq         The key sequence the user has chosen
     * \param conflicting The index of an action that needs to have its shortcut removed. The user has already been
     *                    asked to agree (if he declines, this signal won't be emitted at all).
     */
    void keySequenceChanged(const QKeySequence& seq, const QModelIndex& conflicting = QModelIndex());

    void clicked();

private slots:
    void updateShortcutDisplay();
    void startRecording();
    void cancelRecording();
    void clear();

private:
    inline bool isRecording() const { return _isRecording; }
    void doneRecording();

    bool isOkWhenModifierless(int keyQt) const;
    bool isShiftAsModifierAllowed(int keyQt) const;
    bool isKeySequenceAvailable(const QKeySequence& seq);

    ShortcutsModel* _shortcutsModel{nullptr};
    bool _isRecording{false};
    QKeySequence _keySequence, _oldKeySequence;
    uint _modifierKeys{0};
    QModelIndex _conflictingIndex;

    KeySequenceButton* _keyButton;
    QToolButton* _clearButton;

    friend class KeySequenceButton;
};

/*****************************************************************************/

class KeySequenceButton : public QPushButton
{
    Q_OBJECT
public:
    explicit KeySequenceButton(KeySequenceWidget* d, QWidget* parent = nullptr);

protected:
    bool event(QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    KeySequenceWidget* d;
};

#endif  // KEYSEQUENCEWIDGET_H
