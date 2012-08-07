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

/**
 * @file package.cpp
 * @short Implementation of Widgets::Package
 */

#include "package.h"

#include <QtCore/QFileInfo>
#include <QtCore/QVariant>

#include "componentbase_p.h"
#include "desktopparser.h"
#include "desktopparserdefines.h"
#include "tools.h"

namespace Widgets
{

/**
 * @internal
 * @brief DESKTOP_FILE_SERVICE_VALUE
 */
static const char *DESKTOP_FILE_SERVICE_VALUE = "plugin";
/**
 * @internal
 * @brief DESKTOP_FILE_PLUGIN_INFO_ID
 */
static const char *DESKTOP_FILE_PLUGIN_INFO_ID = "X-Widgets-PluginInfo-Id";
/**
 * @internal
 * @brief DESKTOP_FILE_PLUGIN_INFO_AUTHOR
 */
static const char *DESKTOP_FILE_PLUGIN_INFO_AUTHOR = "X-Widgets-PluginInfo-Author";
/**
 * @internal
 * @brief DESKTOP_FILE_PLUGIN_INFO_EMAIL
 */
static const char *DESKTOP_FILE_PLUGIN_INFO_EMAIL = "X-Widgets-PluginInfo-Email";
/**
 * @internal
 * @brief DESKTOP_FILE_PLUGIN_INFO_WEBSITE
 */
static const char *DESKTOP_FILE_PLUGIN_INFO_WEBSITE = "X-Widgets-PluginInfo-Website";
/**
 * @internal
 * @brief DESKTOP_FILE_PLUGIN_INFO_NAME
 */
static const char *DESKTOP_FILE_PLUGIN_INFO_NAME = "X-Widgets-PluginInfo-Name";
/**
 * @internal
 * @brief DESKTOP_FILE_PLUGIN_INFO_VERSION
 */
static const char *DESKTOP_FILE_PLUGIN_INFO_VERSION = "X-Widgets-PluginInfo-Version";
/**
 * @internal
 * @brief DESKTOP_FILE_PLUGIN_INFO_VISIBLE
 */
static const char *DESKTOP_FILE_PLUGIN_INFO_VISIBLE = "X-Widgets-PluginInfo-Visible";
/**
 * @internal
 * @brief DESKTOP_FILE_PLUGIN_INFO_TAGS
 */
static const char *DESKTOP_FILE_PLUGIN_INFO_TAGS = "X-Widgets-PluginInfo-Tags";

/**
 * @internal
 * @brief Private class for Widgets::Package
 */
class PackagePrivate: public ComponentBasePrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    PackagePrivate(Package *q);
    /**
     * @internal
     * @brief Identifier
     */
    QString identifier;
    /**
     * @internal
     * @brief Directory
     */
    QString directory;
    /**
     * @internal
     * @brief Plugin
     */
    QString plugin;
    /**
     * @internal
     * @brief Authors
     */
    QString author;
    /**
     * @internal
     * @brief Email
     */
    QString email;
    /**
     * @internal
     * @brief Website
     */
    QString website;
    /**
     * @internal
     * @brief %Version
     */
    Version version;
    /**
     * @internal
     * @brief Visible
     */
    bool visible;
    /**
     * @internal
     * @brief Tags
     */
    QStringList tags;
protected:
    /**
     * @internal
     * @brief Parse the desktop file
     * @param parser parser used to parse the desktop file.
     */
    virtual void parseDesktopFile(const DesktopParser &parser);
    virtual bool checkValid(const DesktopParser &parser);
private:
    Q_DECLARE_PUBLIC(Package)
};

PackagePrivate::PackagePrivate(Package *q):
    ComponentBasePrivate(q)
{
    visible = true;
}

void PackagePrivate::parseDesktopFile(const DesktopParser &parser)
{
    Q_Q(Package);
    ComponentBasePrivate::parseDesktopFile(parser);

    QFileInfo fileInfo (parser.file());
    q->setDirectory(fileInfo.absolutePath());
    q->setIdentifier(parser.value(DESKTOP_FILE_PLUGIN_INFO_ID).toString());
    q->setPlugin(parser.value(DESKTOP_FILE_PLUGIN_INFO_NAME).toString());
    q->setAuthor(parser.value(DESKTOP_FILE_PLUGIN_INFO_AUTHOR).toString());
    q->setEmail(parser.value(DESKTOP_FILE_PLUGIN_INFO_EMAIL).toString());
    q->setWebsite(parser.value(DESKTOP_FILE_PLUGIN_INFO_WEBSITE).toString());
    QString version = parser.value(DESKTOP_FILE_PLUGIN_INFO_VERSION).toString();
    QString tagString = parser.value(DESKTOP_FILE_PLUGIN_INFO_TAGS).toString();
    QStringList tags = tagString.split(";", QString::SkipEmptyParts);
    q->setTags(tags);
    q->setVersion(Version::fromString(version));
    if (parser.contains(DESKTOP_FILE_PLUGIN_INFO_VISIBLE)) {
        q->setVisible(
                    Tools::stringToBool(parser.value(DESKTOP_FILE_PLUGIN_INFO_VISIBLE).toString()));
    }
}

bool PackagePrivate::checkValid(const DesktopParser &parser)
{
    if (parser.value(DESKTOP_FILE_SERVICE_TYPE).toString() != DESKTOP_FILE_SERVICE_VALUE) {
        return false;
    }
    if (parser.value(DESKTOP_FILE_PLUGIN_INFO_ID).toString().isEmpty()) {
        return false;
    }

    return ComponentBasePrivate::checkValid(parser);
}

////// End of private class //////

Package::Package(QObject *parent):
    ComponentBase(new PackagePrivate(this), parent)
{
}

Package::Package(const QString &desktopFile, QObject *parent):
    ComponentBase(new PackagePrivate(this), parent)
{
    W_D(Package);
    d->fromDesktopFile(desktopFile);
}

Package::Package(PackagePrivate *dd, QObject *parent):
    ComponentBase(dd, parent)
{
}

Package::~Package()
{
}

QString Package::identifier() const
{
    W_D(const Package);
    return d->identifier;
}

QString Package::directory() const
{
    W_D(const Package);
    return d->directory;
}

QString Package::plugin() const
{
    W_D(const Package);
    return d->plugin;
}

QString Package::author() const
{
    W_D(const Package);
    return d->author;
}

QString Package::email() const
{
    W_D(const Package);
    return d->email;
}

QString Package::website() const
{
    W_D(const Package);
    return d->website;
}

Version Package::version() const
{
    W_D(const Package);
    return d->version;
}

bool Package::isVisible() const
{
    W_D(const Package);
    return d->visible;
}

QStringList Package::tags() const
{
    W_D(const Package);
    return d->tags;
}

void Package::setIdentifier(const QString &identifier)
{
    W_D(Package);
    d->valid = !identifier.isEmpty() && !directory().isEmpty();
    if (d->identifier != identifier) {
        d->identifier = identifier;
        emit identifierChanged();
    }
}

void Package::setDirectory(const QString &directory)
{
    W_D(Package);
    d->valid = !identifier().isEmpty() && !directory.isEmpty();
    if (d->directory != directory) {
        d->directory = directory;
        emit directoryChanged();
    }
}

void Package::setPlugin(const QString &plugin)
{
    W_D(Package);
    if (d->plugin != plugin) {
        d->plugin = plugin;
        emit pluginChanged();
    }
}

void Package::setAuthor(const QString &author)
{
    W_D(Package);
    if (d->author != author) {
        d->author = author;
        emit authorChanged();
    }
}

void Package::setEmail(const QString &email)
{
    W_D(Package);
    if (d->email != email) {
        d->email = email;
        emit emailChanged();
    }
}

void Package::setWebsite(const QString &website)
{
    W_D(Package);
    if (d->website != website) {
        d->website = website;
        emit websiteChanged();
    }
}

void Package::setVersion(const Version &version)
{
    W_D(Package);
    if (d->version != version) {
        d->version = version;
        emit versionChanged();
    }
}

void Package::setVisible(bool visible)
{
    W_D(Package);
    d->visible = visible;
}

void Package::setTags(const QStringList tags)
{
    W_D(Package);
    d->tags = tags;
}

Package * Package::fromDesktopFile(const QString &desktopFile, QObject *parent)
{
    return new Package(desktopFile, parent);
}

}
