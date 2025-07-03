// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QList>
#include <QLocale>
#include <QString>

class UISUPPORT_EXPORT AboutPerson
{
public:
    AboutPerson(QString name, QString nick, QString task, QString emailAddress = QString(), QLocale::Language translatedLanguage = QLocale::AnyLanguage);

    QString name() const;
    QString nick() const;
    QString task() const;
    QString emailAddress() const;
    QLocale::Language translatedLanguage() const;
    QString prettyName() const;

private:
    QString _name;
    QString _nick;
    QString _task;
    QString _emailAddress;
    QLocale::Language _language;
};

class UISUPPORT_EXPORT AboutData : public QObject
{
    Q_OBJECT
public:
    AboutData(QObject* parent = nullptr);

    AboutData& addAuthor(const AboutPerson& author);
    AboutData& addAuthors(std::initializer_list<AboutPerson> authors);
    AboutData& addCredit(const AboutPerson& credit);
    AboutData& addCredits(std::initializer_list<AboutPerson> credits);

    QList<AboutPerson> authors() const;
    QList<AboutPerson> credits() const;

    static void setQuasselPersons(AboutData* aboutData);

private:
    QList<AboutPerson> _authors;
    QList<AboutPerson> _credits;
};
