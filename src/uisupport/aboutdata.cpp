// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "aboutdata.h"

#include <utility>

#include <QImage>

#include "quassel.h"

AboutPerson::AboutPerson(QString name, QString nick, QString task, QString emailAddress, QLocale::Language translatedLanguage)
    : _name(std::move(name))
    , _nick(std::move(nick))
    , _task(std::move(task))
    , _emailAddress(std::move(emailAddress))
    , _language(translatedLanguage)
{
}

QString AboutPerson::name() const
{
    return _name;
}

QString AboutPerson::nick() const
{
    return _nick;
}

QString AboutPerson::task() const
{
    return _task;
}

QString AboutPerson::emailAddress() const
{
    return _emailAddress;
}

QLocale::Language AboutPerson::translatedLanguage() const
{
    return _language;
}

QString AboutPerson::prettyName() const
{
    if (!name().isEmpty() && !nick().isEmpty())
        return name() + " (" + nick() + ')';

    if (name().isEmpty() && !nick().isEmpty())
        return nick();

    return name();
}

/**************************************************************************************************/

AboutData::AboutData(QObject* parent)
    : QObject(parent)
{
}

QList<AboutPerson> AboutData::authors() const
{
    return _authors;
}

QList<AboutPerson> AboutData::credits() const
{
    return _credits;
}

AboutData& AboutData::addAuthor(const AboutPerson& author)
{
    _authors.append(author);
    return *this;
}

AboutData& AboutData::addAuthors(std::initializer_list<AboutPerson> authors)
{
    _authors.append(authors);
    return *this;
}

AboutData& AboutData::addCredit(const AboutPerson& credit)
{
    _credits.append(credit);
    return *this;
}

AboutData& AboutData::addCredits(std::initializer_list<AboutPerson> credits)
{
    _credits.append(credits);
    return *this;
}

/**************************************************************************************************/

/*
 * NOTE: The list of contributors was retrieved from the Git history, but sometimes things fall
 *       through the cracks... especially for translations, we don't have an easy way to track
 *       contributors' names.
 *       If you find wrong data for yourself, want your nickname and/or mail addresses added or
 *       removed, or feel left out or unfairly credited, please don't hesitate to let us know! We
 *       do want to credit everyone who has contributed to Quassel development.
 */

void AboutData::setQuasselPersons(AboutData* aboutData)
{
    aboutData->addAuthors({
        {"Manuel Nickschas", "Sputnick", tr("Project founder, lead developer"), "sputnick@quassel-irc.org"},
        {"Marcus Eggenberger", "EgS", tr("Project motivator, lead developer"), "egs@quassel-irc.org"},
        {"Alexander von Renteln", "phon", tr("Former lead developer"), "phon@quassel-irc.org"},
        {"Daniel Albers", "al", tr("Master of Translation, many fixes and enhancements, Travis support")},
        {"Sebastian Goth", "seezer", tr("Many features, fixes and improvements")},
        {"Bas Pape", "Tucos", tr("Many fixes and improvements, bug and patch triaging, community support")},
        {"Shane Synan", "digitalcircuit", tr("IRCv3 support, documentation, many other improvements, testing, outstanding PRs")},
        {"Janne Koschinski", "justJanne", tr("Quasseldroid, architecture, (mobile) performance, many other improvements and fixes, testing")},
    });

    aboutData->addCredits(
        {{"A. V. Lukyanov", "", tr("OSX UI improvements")},
         {"A. Wilcox", "", tr("Fixes")},
         {"Adam Harwood", "2kah", tr("Chatview improvements")},
         {"Adam Tulinius", "adamt", tr("Early beta tester and bughunter, Danish translation"), "", QLocale::Danish},
         {"Adolfo Jayme Barrientos", "", tr("Spanish translation"), "", QLocale::Spanish},
         {"Adriaan de Groot", "", tr("Build system fixes")},
         {"Alex Ingram", "", tr("Database performance improvements")},
         {"Alex McGrath", "", tr("UI improvements")},
         {"Alexander Stein", "", tr("Tray icon fix")},
         {"Alf Gaida", "agaida", tr("Language improvements")},
         {"Allan Jude", "", tr("Documentation improvements")},
         {"", "alturiak", tr("Various improvements")},
         {"André Marcelo Alvarenga", "", tr("Brazilian translation"), "", QLocale::Portuguese},
         {"Andrej Mernik", "", tr("Slovenian translation"), "", QLocale::Slovenian},
         {"Andrew Brown", "", tr("Fixes")},
         {"Arthur Țițeică", "roentgen", tr("Romanian translation"), "", QLocale::Romanian},
         {"A S Alam", "", tr("Punjabi translation"), "", QLocale::Punjabi},
         {"Atte Virtanen", "", tr("Finnish translation"), "", QLocale::Finnish},
         {"Aurélien Gâteau", "agateau", tr("Message indicator support")},
         {"Awad Mackie", "firesock", tr("Chatview improvements")},
         {"Armin K", "", tr("Build system fix")},
         {"", "Ayonix", tr("Build system fix")},
         {"Benjamin Zeller", "zbenjamin", tr("Windows build system fixes")},
         {"Ben Rosser", "", tr("AppData metadata, LDAP support")},
         {"Bernhard Scheirle", "", tr("Nicer tooltips, spell check and other improvements")},
         {"Bruno Brigras", "", tr("Crash fixes")},
         {"Bruno Patri", "", tr("French translation"), "", QLocale::French},
         {"Cédric Valmary", "", tr("Occitan translation"), "", QLocale::Occitan},
         {"Celeste Paul", "seele", tr("Usability review")},
         {"Chris Fuenty", "stitch", tr("SASL support")},
         {"Chris Holland", "Shade / Zren", tr("Various improvements")},
         {"Chris Le Sueur", "Fish-Face", tr("Various fixes and improvements")},
         {"Chris Moeller", "kode54", tr("Various fixes and improvements")},
         {"Christian Schwarz", "", tr("Settings fixes")},
         {"", "Condex", tr("Galician translation"), "", QLocale::Galician},
         {"", "cordata", tr("Esperanto translation"), "", QLocale::Esperanto},
         {"Daniel E. Moctezuma", "", tr("Japanese translation"), "", QLocale::Japanese},
         {"Daniel Meltzer", "hydrogen", tr("Various fixes and improvements")},
         {"Daniel Pielmeier", "billie", tr("Gentoo maintainer")},
         {"Daniel Schaal", "", tr("Certificate handling improvements")},
         {"Daniel Silverstone", "", tr("Fixes")},
         {"Daniel Steinmetz", "son", tr("Early beta tester and bughunter (on Vista™!)")},
         {"David Planella", "", tr("Translation system fixes")},
         {"David Roden", "Bombe", tr("Fixes")},
         {"David Sansome", "", tr("OSX Notification Center support")},
         {"Demiray Muhterem", "", tr("Turkish translation"), "", QLocale::Turkish},
         {"Deniz Türkoglu", "", tr("Mac fixes")},
         {"Dennis Schridde", "devurandom", tr("D-Bus notifications")},
         {"", "derpella", tr("Polish translation"), "", QLocale::Polish},
         {"Diego Pettenò", "Flameeyes", tr("Build system improvements")},
         {"Dirk Rettschlag", "MarcLandis", tr("Formatting support and other input line improvements, many other fixes")},
         {"", "Dorian", tr("French translation"), "", QLocale::French},
         {"Drew Patridge", "LinuxDolt", tr("BluesTheme stylesheet")},
         {"Edward Hades", "", tr("Russian translation"), "", QLocale::Russian},
         {"Fabiano Francesconi", "elbryan", tr("Italian translation"), "", QLocale::Italian},
         {"Felix Geyer", "debfx", tr("Certificate handling improvements")},
         {"Felix Kaechele", "", tr("German translation"), "", QLocale::German},
         {"Florent Castelli", "", tr("Sanitize topic handling, twitch.tv support")},
         {"Frederik M.J. Vestre", "freqmod", tr("Norwegian translation"), "", QLocale::NorwegianBokmal},
         {"Gábor Németh", "ELITE_x", tr("Hungarian translation"), "", QLocale::Hungarian},
         {"Gryllida A", "gry", tr("IRC parser improvements")},
         {"György Balló", "", tr("Fixes")},
         {"H. İbrahim Güngör", "igungor", tr("Turkish translation"), "", QLocale::Turkish},
         {"Hannah von Reth", "TheOneRing", tr("Windows build support and Appveyor maintenance, snorenotify backend")},
         {"Harald Fernengel", "harryF", tr("Initial Qt5 support")},
         {"Harald Sitter", "apachelogger", tr("{Ku|U}buntu packager, motivator, promoter")},
         {"Hendrik Leppkes", "nevcairiel", tr("Various features and improvements")},
         {"Henning Rohlfs", "honk", tr("Various fixes")},
         {"J-P Nurmi", "", tr("Various fixes")},
         {"Jaak Ristioja", "", tr("Bugfixes")},
         {"Jan Alexander Steffens", "heftig", tr("Fixes")},
         {"Jaroslav Lichtblau", "", tr("Czech translation"), "", QLocale::Czech},
         {"Jason Joyce", "", tr("Python improvements")},
         {"Jason Lynch", "", tr("Bugfixes")},
         {"Javier Llorente", "", tr("Proxy improvements, Spanish translation"), "", QLocale::Spanish},
         {"Jay Colson", "", tr("Postgres improvements")},
         {"Jens Arnold", "amiconn", tr("Postgres migration fixes")},
         {"Jens True", "", tr("Danish translation"), "", QLocale::Danish},
         {"Jerome Leclanche", "Adys", tr("Context menu fixes")},
         {"Jesper Thomschütz", "", tr("Various fixes")},
         {"Jiri Grönroos", "", tr("Finnish translation"), "", QLocale::Finnish},
         {"Joe Hansen", "", tr("Danish translation"), "", QLocale::Danish},
         {"Johannes Huber", "johu", tr("Many fixes and improvements, bug triaging")},
         {"John Hand", "nox", tr("Original \"All-Seeing Eye\" logo")},
         {"Jonas Heese", "Dante", tr("Project founder, various improvements")},
         {"Jonathan Farnham", "", tr("Spanish translation"), "", QLocale::Spanish},
         {"Joshua T Corbin", "tvakah", tr("Various fixes")},
         {"Jovan Jojkić", "", tr("Serbian translation"), "", QLocale::Serbian},
         {"Jure Repinc", "JLP", tr("Slovenian translation"), "", QLocale::Slovenian},
         {"Jussi Schultink", "jussi01", tr("Tireless tester, {Ku|U}buntu tester and lobbyist, liters of delicious Finnish alcohol")},
         {"K. Ernest Lee", "iFire", tr("Qt5 porting help, Travis CI setup")},
         {"Kai Uwe Broulik", "", tr("Various fixes")},
         {"Kevin Funk", "KRF", tr("German translation"), "", QLocale::German},
         {"Kimmo Huoman", "kipe", tr("Buffer merge improvements")},
         {"Konstantin Bläsi", "", tr("Fixes")},
         {"Kostas Koudaras", "", tr("Greek translation"), "", QLocale::Greek},
         {"", "Larso", tr("Finnish translation"), "", QLocale::Finnish},
         {"Lasse Liehu", "", tr("Finnish translation"), "", QLocale::Finnish},
         {"Lee Starnes", "", tr("Improvements")},
         {"Leo Franchi", "", tr("OSX improvements")},
         {"Liudas Alisauskas", "", tr("Lithuanian translation"), "", QLocale::Lithuanian},
         {"Luke Faraone", "", tr("Documentation fixes")},
         {"Maia Kozheva", "", tr("Russian translation"), "", QLocale::Russian},
         {"Manuel Hoffmann", "contradictioned", tr("German translation"), "", QLocale::German},
         {"Manuel Rüger", "", tr("IRC network list updates")},
         {"Marcin Jabrzyk", "", tr("Improvements")},
         {"Marco Genise", "kaffeedoktor", tr("Ideas, hacking, initial motivation")},
         {"Marco Paolone", "Quizzlo", tr("Italian translation"), "", QLocale::Italian},
         {"Martin Mayer", "m4yer", tr("German translation"), "", QLocale::German},
         {"Martin Sandsmark", "sandsmark", tr("Many fixes and improvements, Sonnet support, QuasselDroid")},
         {"Matt Schatz", "genius3000", tr("Various fixes")},
         {"Matthias Coy", "pennywise", tr("German translation"), "", QLocale::German},
         {"Mattia Basaglia", "", tr("Fixes")},
         {"Michael Groh", "brot", tr("German translation, fixes"), "", QLocale::German},
         {"Michael Kedzierski", "ycros", tr("Mac fixes")},
         {"Michael Marley", "mamarley", tr("Many fixes and improvements; Ubuntu PPAs")},
         {"Michał Sochoń", "", tr("SQL improvements")},
         {"Miguel Anxo Bouzada", "", tr("Galician translation"), "", QLocale::Galician},
         {"Miguel Revilla", "", tr("Spanish translation"), "", QLocale::Spanish},
         {"Nicolas Cornu", "", tr("Wayland fixes")},
         {"Nuno Pinheiro", "", tr("Tons of Oxygen icons including the Quassel logo")},
         {"Patrick Lauer", "bonsaikitten", tr("Gentoo maintainer")},
         {"Paul Klumpp", "Haudrauf", tr("Initial design and main window layout")},
         {"Pavel Volkovitskiy", "int", tr("Early beta tester and bughunter")},
         {"Pedro Araujo", "", tr("Brazilian translation"), "", QLocale::Portuguese},
         {"Per Nielsen", "", tr("Danish translation"), "", QLocale::Danish},
         {"Pete Beardmore", "elbeardmorez", tr("Linewrap for input line")},
         {"Petr Bena", "", tr("Performance improvements and cleanups")},
         {"", "phuzion", tr("Various fixes")},
         {"Pierre-Hugues Husson", "", tr("/print command")},
         {"Pierre Schweitzer", "", tr("Performance improvements")},
         {"Rafael Belmonte", "EagleScreen", tr("Spanish translation"), "", QLocale::Spanish},
         {"Rafael Kitover", "", tr("CMake fixes")},
         {"Raju Devidas Vindane", "", tr("Hindi and Marathi translations"), "", QLocale::Hindi},
         {"Ramanathan Sivagurunathan", "", tr("Bugfixes")},
         {"Raul Salinas-Monteagudo", "", tr("Fixes")},
         {"Regis Perrin", "ZRegis", tr("French translation"), "", QLocale::French},
         {"Rolf Eike Beer", "DerDakon", tr("Build system improvements")},
         {"Rolf Michael Bislin", "romibi", tr("Windows build support, automated OSX builds in Travis, various improvements")},
         {"Roscoe van Wyk", "", tr("Bugfixes")},
         {"Rüdiger Sonderfeld", "ruediger", tr("Emacs keybindings")},
         {"Ryan Bales", "selabnayr", tr("Improvements")},
         {"Sai Nane", "esainane", tr("Various fixes")},
         {"", "salnx", tr("Highlight configuration improvements")},
         {"Scott Kitterman", "ScottK", tr("Debian/Kubuntu packager, (packaging/build system) bughunter")},
         {"Sebastian Meyer", "", tr("Bugfixes, German translation"), "", QLocale::German},
         {"Sebastien Fricker", "", tr("Audio backend improvements")},
         {"Sergiu Bivol", "", tr("Romanian translation"), "", QLocale::Romanian},
         {"", "sfionov", tr("Russian translation"), "", QLocale::Russian},
         {"Shengjing Zhu", "", tr("Chinese translation"), "", QLocale::Chinese},
         {"Simon Philips", "", tr("Dutch translation"), "", QLocale::Dutch},
         {"Sjors Gielen", "dazjorz", tr("Bugfixes")},
         {"Stefanos Sofroniou", "", tr("Greek translation"), "", QLocale::Greek},
         {"Stella Rouzi", "differentreality", tr("Greek translation"), "", QLocale::Greek},
         {"Steve Groesz", "wolfpackmars2", tr("Documentation improvements")},
         {"Sungjin Kang", "", tr("Korean translation"), "", QLocale::Korean},
         {"Sven Anderson", "", tr("Database performance improvements")},
         {"Svetlana Tkachenko", "gry", tr("Alias improvements")},
         {"Tae-Hoon Kwon", "", tr("Korean translation"), "", QLocale::Korean},
         {"Terje Andersen", "tan", tr("Norwegian translation, documentation")},
         {"Theo Chatzimichos", "tampakrap", tr("Greek translation"), "", QLocale::Greek},
         {"Theofilos Intzoglou", "", tr("Greek translation"), "", QLocale::Greek},
         {"Thomas Hogh", "Datafreak", tr("Former Windows builder")},
         {"Thomas Müller", "", tr("Fixes, Debian packaging")},
         {"Tim Schumacher", "xAFFE", tr("Fixes and feedback")},
         {"Tinjo Kohen", "", tr("Esperanto translation"), "", QLocale::Esperanto},
         {"Tobias Frei", "ToBeFree", tr("German translation"), "", QLocale::German},
         {"Tomáš Chvátal", "scarabeus", tr("Czech translation"), "", QLocale::Czech},
         {"Veeti Paananen", "", tr("Certificate handling improvements")},
         {"Viktor Suprun", "", tr("Russian translation"), "", QLocale::Russian},
         {"Vít Pelčák", "", tr("Czech translation"), "", QLocale::Czech},
         {"Vitor Luis", "PeGaSuS-Coder", tr("Improvements")},
         {"Volkan Gezer", "", tr("Turkish translation"), "", QLocale::Turkish},
         {"Weng Xuetian", "wengxt", tr("Build system fix")},
         {"Willem Jan Palenstijn", "", tr("Fixes")},
         {"Wolfgang Müller", "wylfen", tr("Logger fixes")},
         {"Yaohan Chen", "hagabaka", tr("Network detection improvements")},
         {"Yuri Chornoivan", "", tr("Ukrainian translation"), "", QLocale::Ukrainian},
         {"Zé", "", tr("Portuguese translation"), "", QLocale::Portuguese},
         {"", "zeugma", tr("Turkish translation"), "", QLocale::Turkish}});
}
