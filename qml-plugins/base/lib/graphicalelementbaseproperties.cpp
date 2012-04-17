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

#include "tools.h"

namespace Widgets
{

GraphicalElementBaseProperties::GraphicalElementBaseProperties(QObject *parent) :
    QObject(parent), d_ptr(new GraphicalElementBasePropertiesPrivate)
{
    Q_D(GraphicalElementBaseProperties);
    d->settingsEnabled = false;
}

GraphicalElementBaseProperties::GraphicalElementBaseProperties(const QString &fileName,
                                                               const QString &packageIdentifier,
                                                               bool settingsEnabled,
                                                               QObject *parent):
    QObject(parent), d_ptr(new GraphicalElementBasePropertiesPrivate)
{
    Q_D(GraphicalElementBaseProperties);
    d->fileName = fileName;
    d->packageIdentifier = packageIdentifier;
    d->settingsEnabled = settingsEnabled;
}

GraphicalElementBaseProperties::GraphicalElementBaseProperties(
        GraphicalElementBasePropertiesPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

GraphicalElementBaseProperties::~GraphicalElementBaseProperties()
{
}

QString GraphicalElementBaseProperties::fileName() const
{
    Q_D(const GraphicalElementBaseProperties);
    return d->fileName;
}

QString GraphicalElementBaseProperties::packageIdentifier() const
{
    Q_D(const GraphicalElementBaseProperties);
    return d->packageIdentifier;
}

bool GraphicalElementBaseProperties::isSettingsEnabled() const
{
    Q_D(const GraphicalElementBaseProperties);
    return d->settingsEnabled;
}

bool GraphicalElementBaseProperties::fromXmlElement(const QDomElement &element)
{
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE)) {
        return false;
    }
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGEIDENTIFIER_ATTRIBUTE)) {
        return false;
    }
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HAS_SETTINGS_ATTRIBUTE)) {
        return false;
    }

    setFileName(element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE));
    setPackageIdentifier(
                element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGEIDENTIFIER_ATTRIBUTE));
    QString hasSettingsString =
            element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HAS_SETTINGS_ATTRIBUTE);
    setSettingsEnabled(Tools::stringToBool(hasSettingsString));

    return true;
}

QDomElement GraphicalElementBaseProperties::toXmlElement(const QString &tagName,
                                                         QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE, fileName());
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGEIDENTIFIER_ATTRIBUTE, packageIdentifier());
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HAS_SETTINGS_ATTRIBUTE,
                         Tools::boolToString(isSettingsEnabled()));

    return element;
}

void GraphicalElementBaseProperties::setFileName(const QString &name)
{
    Q_D(GraphicalElementBaseProperties);
    if (d->fileName != name) {
        d->fileName = name;
        emit fileNameChanged(name);
    }
}

void GraphicalElementBaseProperties::setPackageIdentifier(const QString &packageName)
{
    Q_D(GraphicalElementBaseProperties);
    if (d->packageIdentifier != packageName) {
        d->packageIdentifier = packageName;
        emit packageIdentifierChanged(packageName);
    }
}

void GraphicalElementBaseProperties::setSettingsEnabled(bool settingsEnabled)
{
    Q_D(GraphicalElementBaseProperties);
    if (d->settingsEnabled != settingsEnabled) {
        d->settingsEnabled = settingsEnabled;
        emit settingsEnabledChanged(settingsEnabled);
    }
}

}
