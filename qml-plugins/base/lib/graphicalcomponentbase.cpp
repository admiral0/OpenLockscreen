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

#include "graphicalcomponentbase.h"
#include "graphicalcomponentbase_p.h"
#include "graphicalcomponentbasedefines.h"

#include <QtCore/QDebug>

#include "tools.h"

namespace Widgets
{

GraphicalComponentBase::GraphicalComponentBase(QObject *parent) :
    ComponentBase(new GraphicalComponentBasePrivate(this), parent),
    XmlSerializableInterface()
{
    W_D(GraphicalComponentBase);
    d->settingsEnabled = false;
}

GraphicalComponentBase::GraphicalComponentBase(const QString &fileName,
                                               const QString &packageIdentifier,
                                               bool settingsEnabled,
                                               QObject *parent):
    ComponentBase(new GraphicalComponentBasePrivate(fileName, packageIdentifier, this), parent),
    XmlSerializableInterface()
{
    W_D(GraphicalComponentBase);
    d->settingsEnabled = settingsEnabled;
}

GraphicalComponentBase::GraphicalComponentBase(GraphicalComponentBasePrivate *dd, QObject *parent):
    ComponentBase(dd, parent),
    XmlSerializableInterface()
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

QString GraphicalComponentBase::packageIdentifier() const
{
    W_D(const GraphicalComponentBase);
    return d->packageIdentifier;
}

bool GraphicalComponentBase::isSettingsEnabled() const
{
    W_D(const GraphicalComponentBase);
    return d->settingsEnabled;
}

bool GraphicalComponentBase::fromXmlElement(const QDomElement &element)
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

QDomElement GraphicalComponentBase::toXmlElement(const QString &tagName,
                                                         QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE, fileName());
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGEIDENTIFIER_ATTRIBUTE,
                         packageIdentifier());
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HAS_SETTINGS_ATTRIBUTE,
                         Tools::boolToString(isSettingsEnabled()));

    return element;
}

void GraphicalComponentBase::setFileName(const QString &name)
{
    W_D(GraphicalComponentBase);
    if (d->fileName != name) {
        d->fileName = name;
        emit fileNameChanged(name);
    }
}

void GraphicalComponentBase::setPackageIdentifier(const QString &packageName)
{
    W_D(GraphicalComponentBase);
    if (d->packageIdentifier != packageName) {
        d->packageIdentifier = packageName;
        emit packageIdentifierChanged(packageName);
    }
}

void GraphicalComponentBase::setSettingsEnabled(bool settingsEnabled)
{
    W_D(GraphicalComponentBase);
    if (d->settingsEnabled != settingsEnabled) {
        d->settingsEnabled = settingsEnabled;
        emit settingsEnabledChanged(settingsEnabled);
    }
}

QDebug operator<<(QDebug debug, GraphicalComponentBase *component)
{
    debug.nospace() << "Package (";
    debug.nospace() << "defaultName: " << component->defaultName() << " ";
    debug.nospace() << "defaultDesription: " << component->defaultDescription() << " ";
    debug.nospace() << "name: " << component->name() << " ";
    debug.nospace() << "desription: " << component->description() << " ";
    debug.nospace() << "icon: " << component->icon() << " ";
    debug.nospace() << "fileName: " << component->fileName() << " ";
    debug.nospace() << "packageIdentifier: " << component->packageIdentifier() << " ";
    debug.nospace() << "settingsEnabled: " << component->isSettingsEnabled();
    debug.nospace() << ")";
    return debug.space();
}

}
