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
    Q_D(GraphicalElementBaseProperties);
    d->settingsEnabled = false;
}

GraphicalElementBaseProperties::GraphicalElementBaseProperties(const QString &name,
                                                               const QString &packageName,
//                                                               const QString &qmlFile,
                                                               bool settingsEnabled,
                                                               QObject *parent):
    QObject(parent), d_ptr(new GraphicalElementBasePropertiesPrivate)
{
    Q_D(GraphicalElementBaseProperties);
    d->name = name;
    d->packageName = packageName;
//    d->qmlFile = qmlFile;
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

//QString GraphicalElementBaseProperties::qmlFile() const
//{
//    Q_D(const GraphicalElementBaseProperties);
//    return d->qmlFile;
//}

bool GraphicalElementBaseProperties::isSettingsEnabled() const
{
    Q_D(const GraphicalElementBaseProperties);
    return d->settingsEnabled;
}

bool GraphicalElementBaseProperties::fromXmlElement(const QDomElement &element)
{
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_NAME_ATTRIBUTE)) {
        return false;
    }
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGENAME_ATTRIBUTE)) {
        return false;
    }
//    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_QMLFILE_ATTRIBUTE)) {
//        return false;
//    }
    if (!element.hasAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HAS_SETTINGS_ATTRIBUTE)) {
        return false;
    }

    setName(element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_NAME_ATTRIBUTE));
    setPackageName(element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGENAME_ATTRIBUTE));
//    setQmlFile(element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_QMLFILE_ATTRIBUTE));
    QString hasSettingsString =
            element.attribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HAS_SETTINGS_ATTRIBUTE);
    setSettingsEnabled(stringToBool(hasSettingsString));

    return true;
}

QDomElement GraphicalElementBaseProperties::toXmlElement(const QString &tagName,
                                                         QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_NAME_ATTRIBUTE, name());
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_PACKAGENAME_ATTRIBUTE, packageName());
//    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_QMLFILE_ATTRIBUTE, d->qmlFile);
    element.setAttribute(GRAPHICAL_ELEMENT_BASE_PROPERTIES_HAS_SETTINGS_ATTRIBUTE,
                         boolToString(isSettingsEnabled()));

    return element;
}

void GraphicalElementBaseProperties::setName(const QString &name)
{
    Q_D(GraphicalElementBaseProperties);
    if (d->name != name) {
        d->name = name;
        emit nameChanged(name);
    }
}

void GraphicalElementBaseProperties::setPackageName(const QString &packageName)
{
    Q_D(GraphicalElementBaseProperties);
    if (d->packageName != packageName) {
        d->packageName = packageName;
        emit packageNameChanged(packageName);
    }
}

//void GraphicalElementBaseProperties::setQmlFile(const QString &qmlFile)
//{
//    Q_D(GraphicalElementBaseProperties);
//    if (d->qmlFile != qmlFile) {
//        d->qmlFile = qmlFile;
//        emit qmlFileChanged(qmlFile);
//    }
//}

void GraphicalElementBaseProperties::setSettingsEnabled(bool settingsEnabled)
{
    Q_D(GraphicalElementBaseProperties);
    if (d->settingsEnabled != settingsEnabled) {
        d->settingsEnabled = settingsEnabled;
        emit settingsEnabledChanged(settingsEnabled);
    }
}

}
