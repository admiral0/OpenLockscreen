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
 * @file tools.cpp
 *@short Implementation of Widgets::Tools
 */

#include "tools.h"

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @brief MAP_ITEM_TAG
 *
 * Used in Widgets::Tools.
 */
static const char *MAP_ITEM_TAG = "item";
/**
 * @brief MAP_ITEM_KEY_ATTRIBUTE
 *
 * Used in Widgets::Tools.
 */
static const char *MAP_ITEM_KEY_ATTRIBUTE = "key";
/**
 * @brief MAP_ITEM_VALUE_ATTRIBUTE
 *
 * Used in Widgets::Tools.
 */
static const char *MAP_ITEM_VALUE_ATTRIBUTE = "value";
/**
 * @brief MAP_ITEM_VALUE_TYPE_ATTRIBUTE
 *
 * Used in Widgets::Tools.
 */
static const char *MAP_ITEM_VALUE_TYPE_ATTRIBUTE= "type";

QVariantMap Tools::fromXmlElementToVariantMap(const QDomElement &element)
{
    QVariantMap variantMap;

    QDomElement mapElement = element.firstChildElement(MAP_ITEM_TAG);
    while (!mapElement.isNull()) {

        // Extract the key
        QString key = mapElement.attribute(MAP_ITEM_KEY_ATTRIBUTE);

        if (!key.isNull()) {
            // Extract the value and type
            QString valueString = mapElement.attribute(MAP_ITEM_VALUE_ATTRIBUTE);
            QString valueTypeString = mapElement.attribute(MAP_ITEM_VALUE_TYPE_ATTRIBUTE);
            QVariant::Type type = QVariant::Type(QMetaType::type(valueTypeString.toAscii()));

            if (type) {
                QVariant value = QVariant(valueString);
                if (value.convert(type) || value.isNull()) {
                    // Insert the value
                    variantMap.insert(key, value);
                }
            }
        }
        mapElement = mapElement.nextSiblingElement(MAP_ITEM_TAG);
    }
    return variantMap;
}

QDomElement Tools::toXmlElementFromVariantMap(const QVariantMap &variantMap,
                                               const QString &tagName,
                                               QDomDocument *document)
{
    QDomElement element = document->createElement(tagName);
    QMapIterator<QString, QVariant> iterator = QMapIterator<QString, QVariant>(variantMap);
    while (iterator.hasNext()) {
        iterator.next();

        QDomElement mapElement = document->createElement(MAP_ITEM_TAG);

        // Store the key
        mapElement.setAttribute(MAP_ITEM_KEY_ATTRIBUTE, iterator.key());

        // Store the value and it's type
        mapElement.setAttribute(MAP_ITEM_VALUE_ATTRIBUTE, iterator.value().toString());
        mapElement.setAttribute(MAP_ITEM_VALUE_TYPE_ATTRIBUTE,
                                 QMetaType::typeName(iterator.value().type()));

        element.appendChild(mapElement);
    }

    return element;
}

}
