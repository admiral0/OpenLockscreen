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
 * @file graphicalcomponentbase.cpp
 * @short Implementation of Widgets::GraphicalComponentBase
 */


#include "graphicalcomponentbase.h"
#include "graphicalcomponentbase_p.h"

#include <QtCore/QDebug>

#include "tools.h"

namespace Widgets
{

/**
 * @brief GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE
 *
 * Used in GraphicalComponentBase::fromXmlElement() and GraphicalComponentBase::toXmlElement().
 */
static const char *GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE = "filename";
/**
 * @brief GRAPHICAL_ELEMENT_BASE_DISAMBIGUATION_TAG
 * Used in GraphicalComponentBase::fromXmlElement() and GraphicalComponentBase::toXmlElement().
 */
static const char *GRAPHICAL_ELEMENT_BASE_DISAMBIGUATION_TAG = "disambiguation";

GraphicalComponentBasePrivate::GraphicalComponentBasePrivate(GraphicalComponentBase *q):
    q_ptr(q)
{
}


////// End of private class //////

GraphicalComponentBase::GraphicalComponentBase(QObject *parent) :
    QObject(parent),XmlSerializableInterface(), d_pointer(new GraphicalComponentBasePrivate(this))
{
}

GraphicalComponentBase::GraphicalComponentBase(const QString &fileName,
                                               const QVariantHash &disambiguation,
                                               const QString &settingsFileName,
                                               QObject *parent):
    QObject(parent),XmlSerializableInterface(), d_pointer(new GraphicalComponentBasePrivate(this))
{
    W_D(GraphicalComponentBase);
    d->fileName = fileName;
    d->disambiguation = disambiguation;
    d->settingsFileName = settingsFileName;
}

GraphicalComponentBase::GraphicalComponentBase(GraphicalComponentBasePrivate *dd, QObject *parent):
    QObject(parent), XmlSerializableInterface(), d_pointer(dd)
{
}

GraphicalComponentBase::~GraphicalComponentBase()
{
}

QString GraphicalComponentBase::fileName() const
{
    W_D(const GraphicalComponentBase);
    return d->fileName;
}

QVariantHash GraphicalComponentBase::disambiguation() const
{
    W_D(const GraphicalComponentBase);
    return d->disambiguation;
}

bool GraphicalComponentBase::isSettingsEnabled() const
{
    W_D(const GraphicalComponentBase);
    return !d->settingsFileName.isEmpty();
}

QString GraphicalComponentBase::settingsFileName() const
{
    W_D(const GraphicalComponentBase);
    return d->settingsFileName;
}

bool GraphicalComponentBase::fromXmlElement(const QDomElement &element)
{
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE)) {
        return false;
    }

    QDomElement disambiguationElement
            = element.firstChildElement(GRAPHICAL_ELEMENT_BASE_DISAMBIGUATION_TAG);


    if (disambiguationElement.isNull()) {
        return false;
    }

    setFileName(element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE));
    setDisambiguation(Tools::fromXmlElementToVariantHash(disambiguationElement));

    return true;
}

QDomElement GraphicalComponentBase::toXmlElement(const QString &tagName,
                                                         QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE, fileName());

    QDomElement disambiguationElement
            = Tools::toXmlElementFromVariantHash(disambiguation(), GRAPHICAL_ELEMENT_BASE_DISAMBIGUATION_TAG,
                                      document);
    element.appendChild(disambiguationElement);
    return element;
}

void GraphicalComponentBase::setFileName(const QString &name)
{
    W_D(GraphicalComponentBase);
    if (d->fileName != name) {
        d->fileName = name;
        emit fileNameChanged();
    }
}

void GraphicalComponentBase::setDisambiguation(const QVariantHash &disambiguation)
{
    W_D(GraphicalComponentBase);
    if (d->disambiguation != disambiguation) {
        d->disambiguation = disambiguation;
        emit disambiguationChanged();
    }
}

void GraphicalComponentBase::setSettingsFileName(const QString &settingsFileName)
{
    W_D(GraphicalComponentBase);
    if (d->settingsFileName != settingsFileName) {
        d->settingsFileName = settingsFileName;

        emit settingsEnabledChanged();
        emit settingsFileNameChanged();
    }
}

}
