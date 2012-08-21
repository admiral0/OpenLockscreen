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

#ifndef WIDGETS_WIDGETPROPERTIES_P_H
#define WIDGETS_WIDGETPROPERTIES_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file widgetproperties_p.h
 * @short Definition of Widgets::WidgetPropertiesPrivate
 */

#include "widgetbaseproperties_p.h"
#include "widgetproperties.h"

#include <QtCore/QRect>

namespace Widgets
{

/**
 * @internal
 * @brief Private class for Widgets::WidgetProperties
 */
class WidgetPropertiesPrivate: public WidgetBasePropertiesPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    WidgetPropertiesPrivate(WidgetProperties *q);
    /**
     * @internal
     * @brief Copy information from base
     * @param base bwidget base properties.
     */
    void copyFromBase(WidgetBaseProperties *base);
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
    /**
     * @internal
     * @brief Geometry
     */
    QRect geometry;
    /**
     * @internal
     * @brief Z
     */
    int z;
    /**
     * @internal
     * @brief Visibility
     */
    bool visible;
private:
    Q_DECLARE_PUBLIC(WidgetBaseProperties)
};

/**
 * @internal
 * @brief Helper class for component builder for Widgets::WidgetProperties
 *
 * In extend to Widgets::GraphicalComponentBaseComponentBuilderHelper,
 * this class also takes care of a Widgets::WidgetBaseProperties, that
 * is set with setWidgetBaseProperties().
 */
class WidgetPropertiesComponentBuilderHelper: public GraphicalComponentBaseComponentBuilderHelper
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit WidgetPropertiesComponentBuilderHelper();
    /**
     * @internal
     * @brief Set properties
     *
     * Remark: this method also sets the two attributes,
     * geometryXmlElement and settingsXmlElement.
     *
     * @param xmlElement XML element that represents the component.
     * @param parent parent object.
     */
    virtual void setProperties(const QDomElement &xmlElement, QObject *parent = 0);
    /**
     * @internal
     * @brief Set widget base properties
     * @param widgetBaseProperties widget base properties.
     */
    void setWidgetBaseProperties(WidgetBaseProperties *widgetBaseProperties);
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
     * @short X coordinate
     * @return x coordinate.
     */
    int x() const;
    /**
     * @internal
     * @short Y coordinate
     * @return y coordinate.
     */
    int y() const;
    /**
     * @internal
     * @short Z coordinate
     * @return z coordinate.
     */
    int z() const;
    /**
     * @internal
     * @short Width
     * @return width.
     */
    int width() const;
    /**
     * @internal
     * @short Height
     * @return height.
     */
    int height() const;
    /**
     * @internal
     * @short Settings
     * @return settings.
     */
    QVariantMap settings() const;
    /**
     * @internal
     * @brief Widget base properties
     * @return widget base properties
     */
    WidgetBaseProperties *widgetBaseProperties() const;
protected:
    /**
     * @internal
     * @brief XML element that stores the geometry
     */
    QDomElement geometryXmlElement;
    /**
     * @internal
     * @brief XML element that stores the settings
     */
    QDomElement settingsXmlElement;
private:
    /**
     * @internal
     * @brief Widget base properties
     */
    WidgetBaseProperties *m_widgetBaseProperties;
};

/**
 * @internal
 * @brief Component builder for Widgets::WidgetProperties
 *
 * This class is used to get a Widgets::WidgetProperties
 * from an XML component.
 *
 * This class build the component in 3 steps.
 * - call to setProperties() to get the XML element and parent object.
 * - call to setWidgetBaseProperties() to get the widget base properties.
 * - call to buildElement() to build the component.
 */
class WidgetPropertiesComponentBuilder: public AbstractBuilder<WidgetProperties *>
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit WidgetPropertiesComponentBuilder();
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~WidgetPropertiesComponentBuilder();
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
     * @brief Set widget base properties
     * @param widgetBaseProperties widget base properties.
     */
    void setWidgetBaseProperties(WidgetBaseProperties *widgetBaseProperties);
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
    WidgetPropertiesComponentBuilderHelper *m_helper;
};

/**
 * @internal
 * @brief XML builder for Widgets::WidgetProperties
 *
 * This class is used to get an XML component from
 * a Widgets::WidgetProperties.
 */
class WidgetPropertiesXmlBuilder: public GraphicalComponentBaseXmlBuilder
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit WidgetPropertiesXmlBuilder();
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
    virtual WidgetProperties * component() const;
};

}

#endif // WIDGETS_WIDGETPROPERTIES_P_H

