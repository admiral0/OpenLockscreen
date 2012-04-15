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

#include "desktopparserpackage.h"
#include "desktopparserbase_p.h"
#include "desktopparserdefines.h"

#include <QtCore/QDebug>

namespace Widgets
{

static const char *DESKTOP_FILE_SERVICE_VALUE = "plugin";
static const char *DESKTOP_FILE_PLUGIN_INFO_ID = "X-Widgets-PluginInfo-Id";
static const char *DESKTOP_FILE_PLUGIN_INFO_AUTHOR = "X-Widgets-PluginInfo-Author";
static const char *DESKTOP_FILE_PLUGIN_INFO_EMAIL = "X-Widgets-PluginInfo-Email";
static const char *DESKTOP_FILE_PLUGIN_INFO_WEBSITE = "X-Widgets-PluginInfo-Website";
static const char *DESKTOP_FILE_PLUGIN_INFO_NAME = "X-Widgets-PluginInfo-Name";
static const char *DESKTOP_FILE_PLUGIN_INFO_VERSION = "X-Widgets-PluginInfo-Version";

class DesktopParserPackagePrivate: public DesktopParserBasePrivate
{
public:
    DesktopParserPackagePrivate(const QString &file, DesktopParserPackage *q);
    void checkValid();
    QString defaultName;
    QString defaultComment;
    QHash<QString, QPair<QString, QString> > nameAndComment;
    QString identifier;
    QString plugin;
    QString icon;
    QString author;
    QString email;
    QString webSite;
    Version version;
    bool valid;
private:
    DesktopParserPackage * const q_ptr;
    Q_DECLARE_PUBLIC(DesktopParserPackage)
};

DesktopParserPackagePrivate::DesktopParserPackagePrivate(const QString &file,
                                                         DesktopParserPackage *q):
    DesktopParserBasePrivate(file), q_ptr(q)
{
}

void DesktopParserPackagePrivate::checkValid()
{
    valid = false;
    Q_Q(DesktopParserPackage);
    if (!q->contains(DESKTOP_FILE_NAME)) {
        return;
    }
    if (!q->contains(DESKTOP_FILE_COMMENT)) {
        return;
    }
    if (q->value(DESKTOP_FILE_TYPE).toString() != DESKTOP_FILE_TYPE_VALUE) {
        return;
    }
    if (q->value(DESKTOP_FILE_SERVICE_TYPE).toString() != DESKTOP_FILE_SERVICE_VALUE) {
        return;
    }
    if (!q->contains(DESKTOP_FILE_PLUGIN_INFO_ID)) {
        return;
    }

    valid = true;
    return;
}

////// End of private class //////

DesktopParserPackage::DesktopParserPackage(const QString &file):
    DesktopParserBase(new DesktopParserPackagePrivate(file, this))
{
    Q_D(DesktopParserPackage);
    // Automatically parse the important content of the
    // desktop file
    beginGroup("Desktop Entry");

    // Some checks
    d->checkValid();
    if (!d->valid){
        return;
    }

    QStringList keyList = keys();
    int count = keyList.count();

    // Fetch names and comments
    d->defaultName = value(DESKTOP_FILE_NAME).toString();
    d->defaultComment = value(DESKTOP_FILE_COMMENT).toString();
    d->nameAndComment.reserve(count / 2);

    QRegExp nameRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_NAME));
    QRegExp commentRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_COMMENT));

    foreach (QString key, keyList) {
        if (nameRegEx.indexIn(key) != -1) {

            QString lang = nameRegEx.cap(1);
            QPair<QString, QString> data;

            if (d->nameAndComment.contains(lang)) {
                data = d->nameAndComment.value(lang);
            }
            data.first = value(DESKTOP_FILE_NAME, lang).toString();
            d->nameAndComment.insert(lang, data);
        }
        if (commentRegEx.indexIn(key) != -1) {

            QString lang = commentRegEx.cap(1);
            QPair<QString, QString> data;

            if (d->nameAndComment.contains(lang)) {
                data = d->nameAndComment.value(lang);
            }
            data.second = value(DESKTOP_FILE_COMMENT, lang).toString();
            d->nameAndComment.insert(lang, data);
        }
    }

    // Fetch plugin informations
    d->icon = value(DESKTOP_FILE_ICON).toString();
    d->identifier = value(DESKTOP_FILE_PLUGIN_INFO_ID).toString();
    d->plugin = value(DESKTOP_FILE_PLUGIN_INFO_NAME).toString();
    d->author = value(DESKTOP_FILE_PLUGIN_INFO_AUTHOR).toString();
    d->email = value(DESKTOP_FILE_PLUGIN_INFO_EMAIL).toString();
    d->webSite = value(DESKTOP_FILE_PLUGIN_INFO_WEBSITE).toString();
    QString version = value(DESKTOP_FILE_PLUGIN_INFO_VERSION).toString();
    d->version = Version::fromString(version);

    endGroup();
}

bool DesktopParserPackage::isValid() const
{
    Q_D(const DesktopParserPackage);
    return d->valid;
}

QString DesktopParserPackage::identifier() const
{
    Q_D(const DesktopParserPackage);
    return d->identifier;
}

QString DesktopParserPackage::name(const QString &lang) const
{
    Q_D(const DesktopParserPackage);
    QString value = d->nameAndComment.value(lang).first;
    if (value.isEmpty()) {
        value = d->defaultName;
    }

    return value;
}

QString DesktopParserPackage::comment(const QString &lang) const
{
    Q_D(const DesktopParserPackage);
    QString value = d->nameAndComment.value(lang).second;
    if (value.isEmpty()) {
        value = d->defaultComment;
    }

    return value;
}

QStringList DesktopParserPackage::languages() const
{
    Q_D(const DesktopParserPackage);
    return d->nameAndComment.keys();
}

QString DesktopParserPackage::icon() const
{
    Q_D(const DesktopParserPackage);
    return d->icon;
}

QString DesktopParserPackage::plugin() const
{
    Q_D(const DesktopParserPackage);
    return d->plugin;
}

QString DesktopParserPackage::author() const
{
    Q_D(const DesktopParserPackage);
    return d->author;
}

QString DesktopParserPackage::email() const
{
    Q_D(const DesktopParserPackage);
    return d->email;
}

QString DesktopParserPackage::webSite() const
{
    Q_D(const DesktopParserPackage);
    return d->webSite;
}

Version DesktopParserPackage::version() const
{
    Q_D(const DesktopParserPackage);
    return d->version;
}

}
