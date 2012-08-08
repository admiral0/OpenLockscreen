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

#ifndef WIDGETS_TOOLS_H
#define WIDGETS_TOOLS_H

/**
 * @file tools.h
 *@short Definition of Widgets::Tools
 */

#include <QtCore/QString>
#include <QtCore/QVariantHash>

class QDomElement;
class QDomDocument;
namespace Widgets
{

/**
 * @brief Tool class
 *
 * This class groups some tools, that are used to
 * perform conversions. One of the most notable
 * convertion is the convertion from a string to
 * a boolean. There is also convertions between
 * a variant hash and an XML element.
 */
class Tools
{
public:
    /**
     * @brief Convert a string to a boolean
     *
     * This method converts a string to a boolean,
     * returning true if the passed string is "true",
     * and returning false elsewhere.
     *
     * @param value the string to convert.
     * @return the string as a boolean.
     */
    inline static bool stringToBool(const QString &value) {
        if (value == QString("true")) {
            return true;
        } else {
            return false;
        }
    }
    /**
     * @brief Convert a boolean to a string
     *
     * This method converts a boolean to a string,
     * using "true" and "false" to represent them.
     *
     * @param value the boolean to convert.
     * @return the boolean as a string.
     */
    inline static QString boolToString(bool value) {
        if (value) {
            return QString("true");
        } else {
            return QString("false");
        }
    }
    /**
     * @brief Convert a XML element to a variant hash
     *
     * This method converts an XML element to a variant hash,
     * identifying the "item" tag as a hash item, and
     * using the "key", "value" and "type" attributes of this
     * element to get the key, and the value as a correctly typed
     * variant.
     *
     * @param element XML element to convert.
     * @return the XML element as a variant hash.
     */
    static QVariantHash fromXmlElementToVariantHash(const QDomElement &element);
    /**
     * @brief Convert a variant hash to an XML element
     *
     * This method converts a variant hash to an XML element,
     * using elements with "item" tag to store the values, and
     * using the "key", "value" and "type" attributes of this
     * element to set the key, and the value as a correctly typed
     * variant.
     *
     * @param variantHash the variant hash to convert.
     * @param tagName the tag that will be used to create this element.
     * @param document a pointer to the document that is used to create elements.
     * @return the variant hash as an XML element.
     */
    static QDomElement toXmlElementFromVariantHash(const QVariantHash &variantHash,
                                                   const QString &tagName,
                                                   QDomDocument *document);
};

}

#endif // WIDGETS_TOOLS_H
