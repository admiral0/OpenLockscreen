/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/ 

#include "package.h"

#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QLocale>

#include "desktopparser.h"
#include "desktopparserdefines.h"

namespace Widgets
{

static const char *DESKTOP_FILE_SERVICE_VALUE = "plugin";
static const char *DESKTOP_FILE_PLUGIN_INFO_ID = "X-Widgets-PluginInfo-Id";
static const char *DESKTOP_FILE_PLUGIN_INFO_AUTHOR = "X-Widgets-PluginInfo-Author";
static const char *DESKTOP_FILE_PLUGIN_INFO_EMAIL = "X-Widgets-PluginInfo-Email";
static const char *DESKTOP_FILE_PLUGIN_INFO_WEBSITE = "X-Widgets-PluginInfo-Website";
static const char *DESKTOP_FILE_PLUGIN_INFO_NAME = "X-Widgets-PluginInfo-Name";
static const char *DESKTOP_FILE_PLUGIN_INFO_VERSION = "X-Widgets-PluginInfo-Version";

class PackagePrivate
{
public:
    PackagePrivate();
    void checkValid(const DesktopParser &parser);
    void copyFrom(const Package &other);
    QString identifier;
    QString directory;
    QString defaultName;
    QString defaultDescription;
    QHash<QString, QPair<QString, QString> > nameAndDescription;
    QString plugin;
    QString icon;
    QString author;
    QString email;
    QString website;
    Version version;
    bool valid;
};

PackagePrivate::PackagePrivate()
{
    valid = false;
}

void PackagePrivate::checkValid(const DesktopParser &parser)
{
    if (!parser.contains(DESKTOP_FILE_NAME)) {
        return;
    }
    if (!parser.contains(DESKTOP_FILE_COMMENT)) {
        return;
    }
    if (parser.value(DESKTOP_FILE_TYPE).toString() != DESKTOP_FILE_TYPE_VALUE) {
        return;
    }
    if (parser.value(DESKTOP_FILE_SERVICE_TYPE).toString() != DESKTOP_FILE_SERVICE_VALUE) {
        return;
    }
    if (parser.value(DESKTOP_FILE_PLUGIN_INFO_ID).toString().isEmpty()) {
        return;
    }

    valid = true;
}

void PackagePrivate::copyFrom(const Package &other)
{
    identifier = other.identifier();
    defaultName = other.defaultName();
    defaultDescription = other.defaultDesription();
    nameAndDescription = other.nameAndDescription();
    plugin = other.plugin();
    icon = other.icon();
    author = other.author();
    email = other.email();
    website = other.website();
    version = other.version();
    valid = other.isValid();
}

////// End of private class //////

Package::Package():
    d_ptr(new PackagePrivate())
{
}

Package::Package(const Package &other):
    d_ptr(new PackagePrivate())
{
    Q_D(Package);
    d->copyFrom(other);
}

Package::Package(const QString &file):
    d_ptr(new PackagePrivate())
{
    Q_D(Package);
    DesktopParser parser (file);
    parser.beginGroup("Desktop Entry");

    d->checkValid(parser);
    if (!d->valid) {
        return;
    }

    QStringList keyList = parser.keys();
    int count = keyList.count();

    // Fetch names and comments
    setDefaultName(parser.value(DESKTOP_FILE_NAME).toString());
    setDefaultDescription(parser.value(DESKTOP_FILE_COMMENT).toString());
    d->nameAndDescription.reserve(count / 2);

    QRegExp nameRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_NAME));
    QRegExp commentRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_COMMENT));

    foreach (QString key, keyList) {
        if (nameRegEx.indexIn(key) != -1) {

            QString language = nameRegEx.cap(1);
            addName(language, parser.value(DESKTOP_FILE_NAME, language).toString());
        }
        if (commentRegEx.indexIn(key) != -1) {

            QString language = commentRegEx.cap(1);
            addDescription(language, parser.value(DESKTOP_FILE_COMMENT, language).toString());
        }
    }

    // Fetch plugin informations
    QFileInfo fileInfo (file);
    setDirectory(fileInfo.absolutePath());
    setIdentifier(parser.value(DESKTOP_FILE_PLUGIN_INFO_ID).toString());
    setPlugin(parser.value(DESKTOP_FILE_PLUGIN_INFO_NAME).toString());
    setIcon(parser.value(DESKTOP_FILE_ICON).toString());
    setAuthor(parser.value(DESKTOP_FILE_PLUGIN_INFO_AUTHOR).toString());
    setEmail(parser.value(DESKTOP_FILE_PLUGIN_INFO_EMAIL).toString());
    setWebsite(parser.value(DESKTOP_FILE_PLUGIN_INFO_WEBSITE).toString());
    QString version = parser.value(DESKTOP_FILE_PLUGIN_INFO_VERSION).toString();
    setVersion(Version::fromString(version));

    parser.endGroup();
}

Package::Package(PackagePrivate *dd):
    d_ptr(dd)
{
}

Package::~Package()
{
}

Package & Package::operator=(const Package &other)
{
    Q_D(Package);
    d->copyFrom(other);

    return *this;
}


bool Package::isValid() const
{
    Q_D(const Package);
    return d->valid;
}

QString Package::identifier() const
{
    Q_D(const Package);
    return d->identifier;
}

void Package::setIdentifier(const QString &identifier)
{
    Q_D(Package);
    d->valid = !identifier.isEmpty() && !directory().isEmpty();
    d->identifier = identifier;
}

QString Package::directory() const
{
    Q_D(const Package);
    return d->directory;
}

void Package::setDirectory(const QString &directory)
{
    Q_D(Package);
    d->valid = !identifier().isEmpty() && !directory.isEmpty();
    d->directory = directory;
}

QString Package::defaultName() const
{
    Q_D(const Package);
    return d->defaultName;
}

void Package::setDefaultName(const QString &name)
{
    Q_D(Package);
    d->defaultName = name;
}

QString Package::name() const
{
    Q_D(const Package);
    QStringList languages = QLocale::system().uiLanguages();
    QListIterator<QString> languagesIterator = QListIterator<QString>(languages);

    QString value = QString();
    QRegExp languageRegExp = QRegExp("(\\w+)(\\..+){0,1}");

    while (languagesIterator.hasNext() && value.isEmpty()) {
        QString language = languagesIterator.next();
        if (language.indexOf(languageRegExp) != -1) {
            QString trueLanguage = languageRegExp.cap(1);
            value = d->nameAndDescription.value(trueLanguage).first;
        }
    }

    if (value.isEmpty()) {
        value = d->defaultName;
    }
    return value;
}

QString Package::name(const QString &language) const
{
    Q_D(const Package);

    QString value = d->nameAndDescription.value(language).first;
    if (value.isEmpty()) {
        value = d->defaultName;
    }

    return value;
}

void Package::addName(const QString &language, const QString &name)
{
    Q_D(Package);
    QPair<QString, QString> data;

    if (d->nameAndDescription.contains(language)) {
        data = d->nameAndDescription.value(language);
    }
    data.first = name;
    d->nameAndDescription.insert(language, data);
}

QString Package::defaultDesription() const
{
    Q_D(const Package);
    return d->defaultDescription;
}

void Package::setDefaultDescription(const QString &description)
{
    Q_D(Package);
    d->defaultDescription = description;
}

QString Package::description() const
{
    Q_D(const Package);
    QStringList languages = QLocale::system().uiLanguages();
    QListIterator<QString> languagesIterator = QListIterator<QString>(languages);

    QString value = QString();
    QRegExp languageRegExp = QRegExp("(\\w+)(\\..+){0,1}");

    while (languagesIterator.hasNext() && value.isEmpty()) {
        QString language = languagesIterator.next();
        if (language.indexOf(languageRegExp) != -1) {
            QString trueLanguage = languageRegExp.cap(1);
            value = d->nameAndDescription.value(trueLanguage).second;
        }
    }

    if (value.isEmpty()) {
        value = d->defaultDescription;
    }
    return value;
}

QString Package::description(const QString &language) const
{
    Q_D(const Package);
    QString value = d->nameAndDescription.value(language).second;
    if (value.isEmpty()) {
        value = d->defaultDescription;
    }

    return value;
}

void Package::addDescription(const QString &language, const QString &description)
{
    Q_D(Package);
    QPair<QString, QString> data;

    if (d->nameAndDescription.contains(language)) {
        data = d->nameAndDescription.value(language);
    }
    data.second = description;
    d->nameAndDescription.insert(language, data);
}


QStringList Package::languages() const
{
    Q_D(const Package);
    return d->nameAndDescription.keys();
}

void Package::clearNamesAndDescriptions()
{
    Q_D(Package);
    d->nameAndDescription.clear();
}

QString Package::icon() const
{
    Q_D(const Package);
    return d->icon;
}

void Package::setIcon(const QString &icon)
{
    Q_D(Package);
    d->icon = icon;
}

QString Package::plugin() const
{
    Q_D(const Package);
    return d->plugin;
}

void Package::setPlugin(const QString &plugin)
{
    Q_D(Package);
    d->plugin = plugin;
}

QString Package::author() const
{
    Q_D(const Package);
    return d->author;
}

void Package::setAuthor(const QString &author)
{
    Q_D(Package);
    d->author = author;
}

QString Package::email() const
{
    Q_D(const Package);
    return d->email;
}

void Package::setEmail(const QString &email)
{
    Q_D(Package);
    d->email = email;
}

QString Package::website() const
{
    Q_D(const Package);
    return d->website;
}

void Package::setWebsite(const QString &website)
{
    Q_D(Package);
    d->website = website;
}

Version Package::version() const
{
    Q_D(const Package);
    return d->version;
}

void Package::setVersion(const Version &version)
{
    Q_D(Package);
    d->version = version;
}

Package Package::fromDesktopFile(const QString &file)
{
    return Package(file);
}

QHash<QString, QPair<QString, QString> > Package::nameAndDescription() const
{
    Q_D(const Package);
    return d->nameAndDescription;
}

}
