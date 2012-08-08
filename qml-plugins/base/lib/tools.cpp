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
 * @brief HASH_ITEM_TAG
 *
 * Used in Tools::fromXmlVariantHash() and Tools::toXmlVariantHash().
 */
static const char *HASH_ITEM_TAG = "item";
/**
 * @brief HASH_ITEM_KEY_ATTRIBUTE
 *
 * Used in Tools::fromXmlVariantHash() and Tools::toXmlVariantHash().
 */
static const char *HASH_ITEM_KEY_ATTRIBUTE = "key";
/**
 * @brief HASH_ITEM_VALUE_ATTRIBUTE
 *
 * Used in Tools::fromXmlVariantHash() and Tools::toXmlVariantHash().
 */
static const char *HASH_ITEM_VALUE_ATTRIBUTE = "value";
/**
 * @brief HASH_ITEM_VALUE_TYPE_ATTRIBUTE
 *
 * Used in Tools::fromXmlVariantHash() and Tools::toXmlVariantHash().
 */
static const char *HASH_ITEM_VALUE_TYPE_ATTRIBUTE= "type";

QVariantHash Tools::fromXmlElementToVariantHash(const QDomElement &element)
{
    QVariantHash variantHash;

    QDomElement hashElement = element.firstChildElement(HASH_ITEM_TAG);
    while (!hashElement.isNull()) {

        // Extract the key
        QString key = hashElement.attribute(HASH_ITEM_KEY_ATTRIBUTE);

        if (!key.isNull()) {
            // Extract the value and type
            QString valueString = hashElement.attribute(HASH_ITEM_VALUE_ATTRIBUTE);
            QString valueTypeString = hashElement.attribute(HASH_ITEM_VALUE_TYPE_ATTRIBUTE);
            QVariant::Type type = QVariant::Type(QMetaType::type(valueTypeString.toAscii()));

            if (type) {
                QVariant value = QVariant(valueString);
                if (value.convert(type) || value.isNull()) {
                    // Insert the value
                    variantHash.insert(key, value);
                }
            }
        }
        hashElement = hashElement.nextSiblingElement(HASH_ITEM_TAG);
    }
    return variantHash;
}

QDomElement Tools::toXmlElementFromVariantHash(const QVariantHash &variantHash,
                                               const QString &tagName,
                                               QDomDocument *document)
{
    QDomElement element = document->createElement(tagName);
    QHashIterator<QString, QVariant> iterator = QHashIterator<QString, QVariant>(variantHash);
    while (iterator.hasNext()) {
        iterator.next();

        QDomElement hashElement = document->createElement(HASH_ITEM_TAG);

        // Store the key
        hashElement.setAttribute(HASH_ITEM_KEY_ATTRIBUTE, iterator.key());

        // Store the value and it's type
        hashElement.setAttribute(HASH_ITEM_VALUE_ATTRIBUTE, iterator.value().toString());
        hashElement.setAttribute(HASH_ITEM_VALUE_TYPE_ATTRIBUTE,
                                 QMetaType::typeName(iterator.value().type()));

        element.appendChild(hashElement);
    }

    return element;
}

}
