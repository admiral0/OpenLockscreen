/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#include "componentmetadata_p.h"
#include "desktopcomponent_p.h"

#include <QtCore/QVariant>

#include "desktopfileparser_p.h"
#include "desktopparserdefines.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

/**
 * @internal
 * @brief SERVICE_WIDGET
 *
 * Used in Widgets::Provider::PackageManager::ComponentMetadata.
 */
static const char *SERVICE_WIDGET = "widget";
/**
 * @internal
 * @brief SERVICE_DOCK
 *
 * Used in Widgets::Provider::PackageManager::ComponentMetadata.
 */
static const char *SERVICE_DOCK = "dock";
/**
 * @internal
 * @brief COMPONENT_INFO_FILE
 *
 * Used in Widgets::Provider::PackageManager::ComponentMetadata.
 */
static const char *COMPONENT_INFO_FILE = "X-Widgets-ComponentInfo-File";
/**
 * @internal
 * @brief COMPONENT_INFO_SETTINGS_FILE
 *
 * Used in Widgets::Provider::PackageManager::ComponentMetadata.
 */
static const char *COMPONENT_INFO_SETTINGS_FILE = "X-Widgets-ComponentInfo-SettingsFile";

class ComponentMetadataPrivate: public DesktopComponentPrivate
{
public:
    ComponentMetadataPrivate(DesktopComponent *q);
    QString fileName;
    QString settingsFileName;
    ComponentMetadata::ComponentType type;
};

/**
 * @internal
 * @brief Helper class for component builder for
 *        Widgets::Provider::PackageManager::ComponentMetadata
 *
 * In extend to Widgets::Provider::Package::DesktopComponentBuilderHelper,
 * this class also takes care of extracting properties related
 * to widgets and docks.
 */
class ComponentMetadataBuilderHelper: public DesktopComponentBuilderHelper
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit ComponentMetadataBuilderHelper();
    /**
     * @internal
     * @brief If the XML element is valid
     * @return if the XML element is valid.
     */
    virtual bool isValid() const;
    QString fileName() const;
    QString settingsFileName() const;
    ComponentMetadata::ComponentType type() const;
};

/**
 * @internal
 * @brief Component builder for Widgets::Provider::PackageManager::ComponentMetadata
 *
 * This class is used to get a Widgets::Provider::PackageManager::ComponentMetadata
 * from a desktop file.
 *
 * This class build the component in 2 steps.
 * - call to setProperties() to get the desktop file path and parent object.
 * - call to buildElement() to build the component.
 */
class ComponentMetadataBuilder: public AbstractBuilder<ComponentMetadata *>
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit ComponentMetadataBuilder();
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~ComponentMetadataBuilder();
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
    ComponentMetadataBuilderHelper *m_helper;
};

ComponentMetadataPrivate::ComponentMetadataPrivate(DesktopComponent *q):
    DesktopComponentPrivate(q)
{
    type = ComponentMetadata::InvalidComponentType;
}

ComponentMetadataBuilderHelper::ComponentMetadataBuilderHelper():
    DesktopComponentBuilderHelper()
{
}

bool ComponentMetadataBuilderHelper::isValid() const
{
    if (desktopFileParser->value(SERVICE_TYPE).toString() != SERVICE_DOCK
        && desktopFileParser->value(SERVICE_TYPE).toString() != SERVICE_WIDGET) {
        return false;
    }

    if (!desktopFileParser->contains(COMPONENT_INFO_FILE)) {
        return false;
    }

    return DesktopComponentBuilderHelper::isValid();
}

QString ComponentMetadataBuilderHelper::fileName() const
{
    return desktopFileParser->value(COMPONENT_INFO_FILE).toString();
}

QString ComponentMetadataBuilderHelper::settingsFileName() const
{
    if (!desktopFileParser->contains(COMPONENT_INFO_SETTINGS_FILE)) {
        return QString();
    }
    return desktopFileParser->value(COMPONENT_INFO_SETTINGS_FILE).toString();
}

ComponentMetadata::ComponentType ComponentMetadataBuilderHelper::type() const
{
    if (desktopFileParser->value(SERVICE_TYPE).toString() == SERVICE_DOCK) {
        return ComponentMetadata::DockComponentType;
    } else if (desktopFileParser->value(SERVICE_TYPE).toString() == SERVICE_WIDGET) {
        return ComponentMetadata::WidgetComponentType;
    } else {
        return ComponentMetadata::InvalidComponentType;
    }
}

ComponentMetadataBuilder::ComponentMetadataBuilder():
    AbstractBuilder<ComponentMetadata *>()
{
    m_helper = new ComponentMetadataBuilderHelper();
}

ComponentMetadataBuilder::~ComponentMetadataBuilder()
{
    delete m_helper;
}

void ComponentMetadataBuilder::setProperties(const QString &desktopFile, QObject *parent)
{
    m_helper->setProperties(desktopFile, parent);
}

void ComponentMetadataBuilder::buildElement()
{
    if (!m_helper->isValid()) {
        builtElement = 0;
        return;
    }

    builtElement = new ComponentMetadata(m_helper->icon(),
                                         m_helper->defaultName(), m_helper->defaultDescription(),
                                         m_helper->names(), m_helper->descriptions(),
                                         m_helper->type(),
                                         m_helper->fileName(), m_helper->settingsFileName(),
                                         m_helper->parent());
}


////// End of private class //////

ComponentMetadata::ComponentMetadata(const QString &icon,
                                     const QString &defaultName, const QString &defaultDescription,
                                     const QHash<QString, QString> &names,
                                     const QHash<QString, QString> &descriptions,
                                     ComponentType type,
                                     const QString fileName, const QString settingsFileName,
                                     QObject *parent):
    DesktopComponent(new ComponentMetadataPrivate(this), parent)
{
    W_D(ComponentMetadata);
    d->icon = icon;
    d->defaultName = defaultName;
    d->defaultDescription = defaultDescription;
    d->names = names;
    d->descriptions = descriptions;
    d->type = type;
    d->fileName = fileName;
    d->settingsFileName = settingsFileName;
}

ComponentMetadata::ComponentType ComponentMetadata::type() const
{
    W_D(const ComponentMetadata);
    return d->type;
}

QString ComponentMetadata::fileName() const
{
    W_D(const ComponentMetadata);
    return d->fileName;
}

QString ComponentMetadata::settingsFileName() const
{
    W_D(const ComponentMetadata);
    return d->settingsFileName;
}

ComponentMetadata * ComponentMetadata::fromDesktopFile(const QString &desktopFile, QObject *parent)
{
    ComponentMetadataBuilder *builder = new ComponentMetadataBuilder();
    BuildManager<ComponentMetadata *> *buildManager = new BuildManager<ComponentMetadata *>();
    buildManager->setBuilder(builder);

    builder->setProperties(desktopFile, parent);
    buildManager->build();

    ComponentMetadata *componentMetadata = buildManager->element();

    delete builder;
    delete buildManager;

    return componentMetadata;
}

}

}

}
