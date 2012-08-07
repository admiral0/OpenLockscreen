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
}

GraphicalComponentBase::GraphicalComponentBase(const QString &fileName,
                                               const QString &packageIdentifier,
                                               const QString &settingsFileName,
                                               QObject *parent):
    ComponentBase(new GraphicalComponentBasePrivate(fileName, packageIdentifier, this), parent),
    XmlSerializableInterface()
{
    W_D(GraphicalComponentBase);
    d->settingsFileName = settingsFileName;
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
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGEIDENTIFIER_ATTRIBUTE)) {
        return false;
    }

    setFileName(element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE));
    setPackageIdentifier(
                element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGEIDENTIFIER_ATTRIBUTE));

    return true;
}

QDomElement GraphicalComponentBase::toXmlElement(const QString &tagName,
                                                         QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_FILENAME_ATTRIBUTE, fileName());
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGEIDENTIFIER_ATTRIBUTE,
                         packageIdentifier());
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
