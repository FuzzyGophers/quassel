/***************************************************************************
 *   Copyright (C) 2005-2022 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

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
