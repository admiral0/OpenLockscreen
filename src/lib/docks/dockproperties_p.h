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

#ifndef WIDGETS_DOCKS_DOCKPROPERTIES_P_H
#define WIDGETS_DOCKS_DOCKPROPERTIES_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file dockproperties_p.h
 * @short Definition of Widgets::Docks::DockPropertiesPrivate
 */

#include "dockproperties.h"
#include "dockbaseproperties_p.h"

namespace Widgets
{

namespace Docks
{

/**
 * @internal
 * @brief Private class for Widgets::DockBaseProperties
 */
class DockPropertiesPrivate: public DockBasePropertiesPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    DockPropertiesPrivate(DockProperties *q);
    /**
     * @internal
     * @brief Copy information from base
     * @param base bwidget base properties.
     */
    void copyFromBase(DockBaseProperties *base);
    /**
     * @internal
     * @brief Identifier
     */
    QString identifier;
    /**
     * @internal
     * @brief Settings
     */
    QVariantMap settings;

private:
    Q_DECLARE_PUBLIC(DockProperties)
};

/**
 * @internal
 * @brief Helper class for component builder for Widgets::Docks::DockProperties
 *
 * In extend to Widgets::GraphicalComponentBaseComponentBuilderHelper,
 * this class also takes care of a Widgets::Docks::DockBaseProperties, that
 * is set with setDockBaseProperties().
 */
class DockPropertiesComponentBuilderHelper: public GraphicalComponentBaseComponentBuilderHelper
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit DockPropertiesComponentBuilderHelper();
    /**
     * @internal
     * @brief Set properties
     *
     * Remark: this method also sets the attribute settingsXmlElement.
     *
     * @param xmlElement XML element that represents the component.
     * @param parent parent object.
     */
    virtual void setProperties(const QDomElement &xmlElement, QObject *parent = 0);
    /**
     * @internal
     * @brief Set dock base properties
     * @param dockBaseProperties dock base properties.
     */
    void setDockBaseProperties(DockBaseProperties *dockBaseProperties);
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
     * @short Settings
     * @return settings.
     */
    QVariantMap settings() const;
    /**
     * @internal
     * @brief Dock base properties
     * @return dock base properties
     */
    DockBaseProperties *dockBaseProperties() const;
protected:
    /**
     * @internal
     * @brief XML element that stores the settings
     */
    QDomElement settingsXmlElement;
private:
    /**
     * @internal
     * @brief Dock base properties
     */
    DockBaseProperties *m_dockBaseProperties;
};

/**
 * @internal
 * @brief Component builder for Widgets::Docks::DockProperties
 *
 * This class is used to get a Widgets::Docks::DockProperties
 * from an XML component.
 *
 * This class build the component in 3 steps.
 * - call to setProperties() to get the XML element and parent object.
 * - call to setDockBaseProperties() to get the dock base properties.
 * - call to buildElement() to build the component.
 */
class DockPropertiesComponentBuilder: public AbstractBuilder<DockProperties *>
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit DockPropertiesComponentBuilder();
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~DockPropertiesComponentBuilder();
    /**
     * @internal
     * @brief Set properties
     *
     * @param xmlElement XML element that represents the component.
     * @param parent parent object.
     */
    virtual void setProperties(const QDomElement &xmlElement, QObject *parent = 0);
    /**
     * @internal
     * @brief filename
     * @return filename.
     */
    QString fileName() const;
    /**
     * @internal
     * @brief Disambiguation
     * @return disambiguation.
     */
    QVariantMap disambiguation() const;
    /**
     * @internal
     * @brief Set dock base properties
     * @param dockBaseProperties dock base properties.
     */
    void setDockBaseProperties(DockBaseProperties *dockBaseProperties);
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
    DockPropertiesComponentBuilderHelper *m_helper;
};

/**
 * @internal
 * @brief XML builder for Widgets::Docks::DockProperties
 *
 * This class is used to get an XML component from
 * a Widgets::Docks::DockProperties.
 */
class DockPropertiesXmlBuilder: public GraphicalComponentBaseXmlBuilder
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit DockPropertiesXmlBuilder();
    /**
     * @internal
     * @brief Built the component
     */
    virtual void buildElement();
protected:
    /**
     * @internal
     * @brief Component
     * @return component
     */
    virtual DockProperties * component() const;
};

}

}

#endif // WIDGETS_DOCKS_DOCKPROPERTIES_P_H
