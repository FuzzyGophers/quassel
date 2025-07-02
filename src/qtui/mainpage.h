// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef MAINPAGE_H_
#define MAINPAGE_H_

#include <QWidget>

class QPushButton;

class MainPage : public QWidget
{
    Q_OBJECT

public:
    MainPage(QWidget* parent = nullptr);

private slots:
    void showCoreConnectionDlg();
    void coreConnectionStateChanged();

private:
    QPushButton* _connectButton;
};

#endif
