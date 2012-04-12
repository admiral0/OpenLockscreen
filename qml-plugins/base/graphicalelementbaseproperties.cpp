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

#include "graphicalelementbaseproperties.h"
#include "graphicalelementbaseproperties_p.h"
#include "graphicalelementbasepropertiesdefines.h"

namespace Widgets
{

GraphicalElementBaseProperties::GraphicalElementBaseProperties(QObject *parent) :
    QObject(parent), d_ptr(new GraphicalElementBasePropertiesPrivate)
{
}

GraphicalElementBaseProperties::GraphicalElementBaseProperties(
        GraphicalElementBasePropertiesPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

GraphicalElementBaseProperties::~GraphicalElementBaseProperties()
{
}

QString GraphicalElementBaseProperties::name() const
{
    Q_D(const GraphicalElementBaseProperties);
    return d->name;
}

QString GraphicalElementBaseProperties::packageName() const
{
    Q_D(const GraphicalElementBaseProperties);
    return d->packageName;
}

QString GraphicalElementBaseProperties::qmlFile() const
{
    Q_D(const GraphicalElementBaseProperties);
    return d->qmlFile;
}

bool GraphicalElementBaseProperties::hasSettings() const
{
    Q_D(const GraphicalElementBaseProperties);
    return d->hasSettings;
}

bool GraphicalElementBaseProperties::fromXmlElement(const QDomElement &element)
{
    Q_D(GraphicalElementBaseProperties);
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_NAME_ATTRIBUTE)) {
        return false;
    }
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGENAME_ATTRIBUTE)) {
        return false;
    }
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_QMLFILE_ATTRIBUTE)) {
        return false;
    }
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HASSETTINGS_ATTRIBUTE)) {
        return false;
    }

    d->name = element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_NAME_ATTRIBUTE);
    d->packageName = element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGENAME_ATTRIBUTE);
    d->qmlFile = element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_QMLFILE_ATTRIBUTE);
    d->hasSettings =
            (element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HASSETTINGS_ATTRIBUTE) == "true");

    return true;
}

QDomElement GraphicalElementBaseProperties::toXmlElement(const QString &tagName,
                                                         QDomDocument *document) const
{
    Q_D(const GraphicalElementBaseProperties);
    QDomElement element = document->createElement(tagName);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_NAME_ATTRIBUTE, d->name);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGENAME_ATTRIBUTE, d->packageName);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_QMLFILE_ATTRIBUTE, d->qmlFile);
    QString hasSettingsString;
    if (d->hasSettings) {
        hasSettingsString = "true";
    } else {
        hasSettingsString = "false";
    }
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HASSETTINGS_ATTRIBUTE,
                         hasSettingsString);

    return QDomElement();
}

}
