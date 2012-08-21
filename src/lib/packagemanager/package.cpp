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
 * @short Implementation of Widgets::Provider::PackageManager::Package
 */

#include "package.h"

#include <QtCore/QFileInfo>
#include <QtCore/QVariant>

#include "desktopcomponent_p.h"
#include "desktopfileparser_p.h"

#include "desktopfileparserdefines_p.h"
#include "tools.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

/**
 * @internal
 * @brief SERVICE_VALUE
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *SERVICE_VALUE = "plugin";
/**
 * @internal
 * @brief PLUGIN_INFO_ID
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *PLUGIN_INFO_ID = "X-Widgets-PluginInfo-Id";
/**
 * @internal
 * @brief PLUGIN_INFO_AUTHOR
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *PLUGIN_INFO_AUTHOR = "X-Widgets-PluginInfo-Author";
/**
 * @internal
 * @brief PLUGIN_INFO_EMAIL
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *PLUGIN_INFO_EMAIL = "X-Widgets-PluginInfo-Email";
/**
 * @internal
 * @brief PLUGIN_INFO_WEBSITE
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *PLUGIN_INFO_WEBSITE = "X-Widgets-PluginInfo-Website";
/**
 * @internal
 * @brief PLUGIN_INFO_NAME
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *PLUGIN_INFO_NAME = "X-Widgets-PluginInfo-Name";
/**
 * @internal
 * @brief PLUGIN_INFO_VERSION
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *PLUGIN_INFO_VERSION = "X-Widgets-PluginInfo-Version";
/**
 * @internal
 * @brief PLUGIN_INFO_VISIBLE
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *PLUGIN_INFO_VISIBLE = "X-Widgets-PluginInfo-Visible";
/**
 * @internal
 * @brief PLUGIN_INFO_TAGS
 *
 * Used in Widgets::Provider::PackageManager::Package.
 */
static const char *PLUGIN_INFO_TAGS = "X-Widgets-PluginInfo-Tags";

/**
 * @internal
 * @brief Private class for Widgets::Provider::PackageManager::Package
 */
class PackagePrivate: public DesktopComponentPrivate
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
private:
    Q_DECLARE_PUBLIC(Package)
};

/**
 * @internal
 * @brief Helper class for component builder for Widgets::Provider::PackageManager::Package
 *
 * In extend to Widgets::Provider::Package::DesktopComponentBuilderHelper,
 * this class also takes care of extracting properties related
 * to package.
 */
class PackageBuilderHelper: public DesktopComponentBuilderHelper
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit PackageBuilderHelper();
    /**
     * @internal
     * @brief If the XML element is valid
     * @return if the XML element is valid.
     */
    virtual bool isValid() const;
    /**
     * @internal
     * @brief Identifier
     * @return identifier.
     */
    QString identifier() const;
    /**
     * @internal
     * @short Directory
     * @return directory.
     */
    QString directory() const;
    /**
     * @internal
     * @short Plugin
     * @return plugin.
     */
    QString plugin() const;
    /**
     * @internal
     * @short Author
     * @return author.
     */
    QString author() const;
    /**
     * @internal
     * @short Email
     * @return email.
     */
    QString email() const;
    /**
     * @internal
     * @short Website
     * @return website.
     */
    QString website() const;
    /**
     * @internal
     * @short Version
     * @return version.
     */
    Version version() const;
    /**
     * @internal
     * @brief Is visible
     * @return is visible.
     */
    bool isVisible() const;
    /**
     * @internal
     * @brief Tags
     * @return tags.
     */
    QStringList tags() const;
};

/**
 * @internal
 * @brief Component builder for Widgets::Provider::PackageManager::Package
 *
 * This class is used to get a Widgets::Provider::PackageManager::Package
 * from a desktop file.
 *
 * This class build the component in 2 steps.
 * - call to setProperties() to get the desktop file path and parent object.
 * - call to buildElement() to build the component.
 */
class PackageBuilder: public AbstractBuilder<Package *>
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit PackageBuilder();
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~PackageBuilder();
    /**
     * @internal
     * @brief Set properties
     *
     * @param desktopFile Desktop file to parse.
     * @param parent parent object.
     */
    virtual void setProperties(const QString &desktopFile, QObject *parent = 0);
    /**
     * @internal
     * @brief Built the component
     */
    virtual void buildElement();
private:
    /**
     * @internal
     * @brief Helper class
     */
    PackageBuilderHelper *m_helper;
};


PackagePrivate::PackagePrivate(Package *q):
    DesktopComponentPrivate(q)
{
    visible = true;
}

PackageBuilderHelper::PackageBuilderHelper():
    DesktopComponentBuilderHelper()
{
}

bool PackageBuilderHelper::isValid() const
{
    if (desktopFileParser->value(SERVICE_TYPE).toString() != SERVICE_VALUE) {
        return false;
    }
    if (desktopFileParser->value(PLUGIN_INFO_ID).toString().isEmpty()) {
        return false;
    }

    return DesktopComponentBuilderHelper::isValid();
}

QString PackageBuilderHelper::identifier() const
{
    return desktopFileParser->value(PLUGIN_INFO_ID).toString();
}

QString PackageBuilderHelper::directory() const
{
    QFileInfo fileInfo (desktopFileParser->file());
    return fileInfo.absolutePath();
}

QString PackageBuilderHelper::plugin() const
{
    return desktopFileParser->value(PLUGIN_INFO_NAME).toString();
}

QString PackageBuilderHelper::author() const
{
    return desktopFileParser->value(PLUGIN_INFO_AUTHOR).toString();
}

QString PackageBuilderHelper::email() const
{
    return desktopFileParser->value(PLUGIN_INFO_EMAIL).toString();
}

QString PackageBuilderHelper::website() const
{
    return desktopFileParser->value(PLUGIN_INFO_WEBSITE).toString();
}

Version PackageBuilderHelper::version() const
{
    QString versionString = desktopFileParser->value(PLUGIN_INFO_VERSION).toString();
    return Version::fromString(versionString);
}

bool PackageBuilderHelper::isVisible() const
{
    if (desktopFileParser->contains(PLUGIN_INFO_VISIBLE)) {
        QVariant visibleVariant = desktopFileParser->value(PLUGIN_INFO_VISIBLE);
        return Tools::stringToBool(visibleVariant.toString());
    } else {
        return true;
    }
}

QStringList PackageBuilderHelper::tags() const
{
    QString tagString = desktopFileParser->value(PLUGIN_INFO_TAGS).toString();
    return tagString.split(";", QString::SkipEmptyParts);
}

PackageBuilder::PackageBuilder():
    AbstractBuilder<Package *>()
{
    m_helper = new PackageBuilderHelper();
}

PackageBuilder::~PackageBuilder()
{
    delete m_helper;
}

void PackageBuilder::setProperties(const QString &desktopFile, QObject *parent)
{
    m_helper->setProperties(desktopFile, parent);
}

void PackageBuilder::buildElement()
{
    if (!m_helper->isValid()) {
        builtElement = 0;
        return;
    }

    builtElement = new Package(m_helper->icon(), m_helper->defaultName(),
                               m_helper->defaultDescription(),
                               m_helper->names(), m_helper->descriptions(),
                               m_helper->identifier(), m_helper->directory(), m_helper->plugin(),
                               m_helper->author(), m_helper->email(), m_helper->website(),
                               m_helper->version(), m_helper->isVisible(), m_helper->tags(),
                               m_helper->parent());
}

////// End of private class //////

Package::Package(QObject *parent):
    DesktopComponent(new PackagePrivate(this), parent)
{
}

Package::Package(const QString &icon,
                 const QString &defaultName, const QString &defaultDescription,
                 const QMap<QString, QString> &names, const QMap<QString, QString> &descriptions,
                 const QString &identifier,
                 const QString &directory, const QString &plugin,
                 const QString &author, const QString &email, const QString &website,
                 const Version &version, bool visible, const QStringList &tags,
                 QObject *parent):
    DesktopComponent(new PackagePrivate(this), parent)
{
    W_D(Package);
    d->icon = icon;
    d->defaultName = defaultName;
    d->defaultDescription = defaultDescription;
    d->names = names;
    d->descriptions = descriptions;
    d->identifier = identifier;
    d->directory = directory;
    d->plugin = plugin;
    d->author = author;
    d->email = email;
    d->website = website;
    d->version = version;
    d->visible = visible;
    d->tags = tags;
}

Package::Package(PackagePrivate *dd, QObject *parent):
    DesktopComponent(dd, parent)
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

Package * Package::fromDesktopFile(const QString &desktopFile, QObject *parent)
{
    PackageBuilder *builder = new PackageBuilder();
    BuildManager<Package *> *buildManager = new BuildManager<Package *>();
    buildManager->setBuilder(builder);

    builder->setProperties(desktopFile, parent);
    buildManager->build();

    Package *package = buildManager->element();

    delete builder;
    delete buildManager;

    return package;
}

}

}

}
