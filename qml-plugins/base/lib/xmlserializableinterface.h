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

#ifndef WIDGETS_XMLSERIALIZABLEINTERFACE_H
#define WIDGETS_XMLSERIALIZABLEINTERFACE_H

/**
 * @file xmlserializableinterface.h
 * @short Definition of XmlSerializableInterface
 *
 * This file contains the definition of the
 * XmlSerializableInterface interface.
 */

#include <QtXml/QDomElement>

namespace Widgets
{

/**
 * @short Interface for classes that can be serialized into XML
 *
 * This interface provides two methods that are used to
 * save a class instance into XML and to load the instance
 * from XML, they are
 *
 * - fromXmlElement()
 * - toXmlElement()
 *
 * The first method is used to retrieve an instance of the class.
 * It should be called on an instance that is already created
 * (but invalid), and reload all information from the XML element.
 *
 * The second method is used to dump all the information from the
 * instance to an XML element.
 */
class XmlSerializableInterface
{
public:
    /**
     * @brief Load from XML element
     *
     * This method is used to load information from an
     * XML element to a class instance.
     *
     * @param element the source XML element.
     * @return if the loading succeded.
     */
    virtual bool fromXmlElement(const QDomElement &element) = 0;
    /**
     * @brief Save to XML element
     *
     * This method is used to save the information that is
     * contained in the instance to an XML element.
     *
     * This element and all children elements should be created using
     * the provided QDomDocument, otherwise, it will be invalid.
     *
     * @param tagName the tag that will be used to create this element.
     * @param document a pointer to the document that is used to create elements.
     * @return the class as an XML element.
     */
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const = 0;
};

}

#endif // WIDGETS_XMLSERIALIZABLEINTERFACE_H
