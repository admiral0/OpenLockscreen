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

#ifndef WIDGETS_GRAPHICALCOMPONENTBASE_P_H
#define WIDGETS_GRAPHICALCOMPONENTBASE_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file graphicalcomponentbase_p.h
 * @short Definition of Widgets::GraphicalComponentBasePrivate
 */

#include "graphicalcomponentbase.h"
#include "builderpatterninterfaces_p.h"

#include <QtCore/QString>
#include <QtCore/QVariantHash>
#include <QtXml/QDomElement>

namespace Widgets
{

/**
 * @internal
 * @brief Private class for Widgets::GraphicalComponentBase
 */
class GraphicalComponentBasePrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    GraphicalComponentBasePrivate(GraphicalComponentBase *q);
    /**
     * @internal
     * @brief Filename of the component
     */
    QString fileName;
    /**
     * @internal
     * @brief Disambiguation parameter of the component
     */
    QVariantHash disambiguation;
    /**
     * @internal
     * @brief Filename of the settings component of this component
     */
    QString settingsFileName;
protected:
    /**
     * @internal
     * @brief Q-pointer
     */
    GraphicalComponentBase *q_ptr;
private:
    Q_DECLARE_PUBLIC(GraphicalComponentBase)
};

/**
 * @internal
 * @brief Helper class for component builder for Widgets::GraphicalComponentBase
 *
 * This helper class provides all the information for the
 * builder class to create the component. It take cares of the
 * XML component, and parse it, and store the parent of the new
 * component as well.
 *
 * These parameters are set using setProperties().
 *
 * It also provides an information about the validity of the XML
 * element, that can be retrieved using isValid().
 */
class GraphicalComponentBaseComponentBuilderHelper
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit GraphicalComponentBaseComponentBuilderHelper();
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~GraphicalComponentBaseComponentBuilderHelper();
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
     * @brief parent
     * @return parent object.
     */
    QObject *parent() const;
    /**
     * @internal
     * @brief If the XML element is valid
     *
     * This method is used in buildElement() in
     * order to check if the XML element contains
     * valid information.
     *
     * @return if the XML element is valid.
     */
    virtual bool isValid() const;
    /**
     * @internal
     * @brief filename
     * @return filename.
     */
    QString fileName() const;
    /**
     * @internal
     * @brief Settings filename
     * @return settings filename.
     */
    QString settingsFileName() const;
    /**
     * @internal
     * @brief Disambiguation
     * @return disambiguation.
     */
    QVariantHash disambiguation() const;
protected:
    /**
     * @internal
     * @brief XML element
     */
    QDomElement xmlElement;
private:
    /**
     * @internal
     * @brief Parent object
     */
    QObject *m_parent;
};

/**
 * @internal
 * @brief Component builder for Widgets::GraphicalComponentBase
 *
 * This class is used to get a Widgets::GraphicalComponentBase
 * from an XML component.
 *
 * This class build the component in 2 steps.
 * - call to setProperties() to get the XML element and parent object.
 * - call to buildElement() to build the component.
 */
class GraphicalComponentBaseComponentBuilder:
        public AbstractBuilder<GraphicalComponentBase *>
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit GraphicalComponentBaseComponentBuilder();
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~GraphicalComponentBaseComponentBuilder();
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
     * @brief Built the component
     */
    virtual void buildElement();
private:
    /**
     * @internal
     * @brief Helper class
     */
    GraphicalComponentBaseComponentBuilderHelper *m_helper;
};

/**
 * @internal
 * @brief XML builder for Widgets::GraphicalComponentBase
 *
 * This class is used to get an XML component from
 * a Widgets::GraphicalComponentBase
 *
 * This class build the component in 2 steps.
 * - call to setProperties() to get the component, tag and document
 *   that are used to create the XML element.
 * - call to buildElement() to build the component.
 */
class GraphicalComponentBaseXmlBuilder: public AbstractBuilder<QDomElement>
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit GraphicalComponentBaseXmlBuilder();
    /**
     * @internal
     * @brief Set properties
     * @param component the component that will be saved in XML.
     * @param tagName the tag that will be used to create this element.
     * @param document a pointer to the document that is used to create elements.
     */
    virtual void setProperties(GraphicalComponentBase *component, const QString &tagName,
                               QDomDocument *document);
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
    virtual GraphicalComponentBase *component() const;
    /**
     * @internal
     * @brief Tag
     */
    QString tagName;
    /**
     * @internal
     * @brief Document
     */
    QDomDocument *document;
private:
    /**
     * @internal
     * @brief Component
     */
    GraphicalComponentBase *m_component;
};

}

#endif // WIDGETS_GRAPHICALCOMPONENTBASE_P_H
