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
 * @file package.cpp
 * @short Implementation of Widgets::Package
 *
 * This file contains the implemetation of the
 * Widgets::Package class and the declaration and
 * implementation of Widgets::Package::PackagePrivate.
 */

#include "package.h"
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtXml/QDomDocument>

namespace Widgets
{

/**
 * @internal
 * @short Private structure for Package
 */
struct Package::PackagePrivate
{
    /**
     * @short Name of the package
     */
    QString name;
    /**
     * @short Identifier of the package
     */
    QString identifier;
    /**
     * @short Description of the package
     */
    QString description;
    /**
     * @short If this package is visible
     */
    bool visible;
    /**
     * @short Widgets that this package provides
     */
    QList<WidgetBaseProperties *> widgets;
    /**
     * @short Docks that this package provides
     */
    QList<DockBaseProperties *> docks;
};

////// End of private class //////

Package::Package(const QString &name, const QString &identifier, const QString &description,
                 bool visible,
                 const QList<WidgetBaseProperties *> widgets,
                 const QList<DockBaseProperties *> docks):
    d(new PackagePrivate)
{
    d->name = name;
    d->identifier = identifier;
    d->description = description;
    d->visible = visible;
    d->widgets = widgets;
    d->docks = docks;
}

Package::Package(const Package &other):
    d(new PackagePrivate)
{
    d->name = other.name();
    d->identifier = other.identifier();
    d->description = other.description();
    d->visible = other.isVisible();
    d->widgets = other.widgets();
    d->docks = other.docks();
}

Package & Package::operator=(const Package &other)
{
    d->name = other.name();
    d->identifier = other.identifier();
    d->description = other.description();
    d->visible = other.isVisible();
    d->widgets = other.widgets();
    d->docks = other.docks();

    return *this;
}

Package::~Package()
{
    delete d;
}

QString Package::identifier() const
{
    return d->identifier;
}

QString Package::name() const
{
    return d->name;
}

QString Package::description() const
{
    return d->description;
}

bool Package::isVisible() const
{
    return d->visible;
}

QList<WidgetBaseProperties *> Package::widgets() const
{
    return d->widgets;
}

QList<DockBaseProperties *> Package::docks() const
{
    return d->docks;
}

Package Package::fromInformationFile(const QString &filePath, QObject *parent)
{
    // Get the folder where the file is
    QFileInfo fileInfo = QFile(filePath);
    QDir dir = fileInfo.dir();


    // Create the DOM document
    QDomDocument document = QDomDocument();
    QFile file (filePath);
    QString errorMsg;
    document.setContent(&file, &errorMsg);

    // Parse the package properties
    QDomElement rootElement = document.documentElement();
    QString packageName = rootElement.attribute("name");
    QString packageIdentifier = rootElement.attribute("id");
    QString packageDescription = rootElement.attribute("description");
    QString visibleString = rootElement.attribute("visible", "true");
    bool visible = (visibleString == "true");

    // Prepare widgets
    QList<WidgetBaseProperties *> widgets;
    QList<DockBaseProperties *> docks;

    // Parse the package widgets
    QDomNode childNode = rootElement.firstChild();
    while (!childNode.isNull()) {
        QDomElement childElement = childNode.toElement();

        if (!childElement.isNull()) {
            if (childElement.tagName() == "widget") {
                // Get QML file
                QString widgetQmlFile = childElement.attribute("qmlfile");
                if (dir.exists(widgetQmlFile)) {
                    // Parse the widget properties
                    QString widgetName = childElement.attribute("name");
                    QString widgetHasSettingsString = childElement.attribute("hassettings");
                    QDomElement widgetSizeElement = childElement.firstChildElement("size");
                    int width = widgetSizeElement.attribute("width").toInt();
                    int height = widgetSizeElement.attribute("height").toInt();
                    bool hasSettings = (widgetHasSettingsString == "true");

                    // Allocate new widget
                    WidgetBaseProperties *widget = new WidgetBaseProperties(
                                widgetName, width, height,
                                dir.absoluteFilePath(widgetQmlFile), packageIdentifier,
                                hasSettings, parent);
                    widgets.append(widget);
                }
            } else if (childElement.tagName() == "dock") {
                // Get QML file
                QString dockQmlFile = childElement.attribute("qmlfile");
                if (dir.exists(dockQmlFile)) {
                    // Parse the dock properties
                    QString dockName = childElement.attribute("name");
                    QString dockHasSettingsString = childElement.attribute("hassettings");
                    QDomElement dockSizeElement = childElement.firstChildElement("size");
                    int width = dockSizeElement.attribute("width", "-1").toInt();
                    int height = dockSizeElement.attribute("height", "-1").toInt();
                    QDomElement dockAnchorsElement = childElement.firstChildElement("anchors");
                    QString anchorsTopStr = dockAnchorsElement.attribute("top", "false");
                    QString anchorsBottomStr = dockAnchorsElement.attribute("bottom", "false");
                    QString anchorsLeftStr = dockAnchorsElement.attribute("left", "false");
                    QString anchorsRightStr = dockAnchorsElement.attribute("right", "false");
                    bool hasSettings = (dockHasSettingsString == "true");

                    // Allocate new dock
                    DockBaseProperties *dock = new DockBaseProperties(dockName, width, height,
                                                                      anchorsTopStr == "true",
                                                                      anchorsBottomStr == "true",
                                                                      anchorsLeftStr == "true",
                                                                      anchorsRightStr == "true",
                                                                      dir.absoluteFilePath(
                                                                          dockQmlFile),
                                                                      packageIdentifier,
                                                                      hasSettings,
                                                                      parent);
                    docks.append(dock);
                }

            }
        }
        childNode = childNode.nextSibling();
    }

    return Package(packageName, packageIdentifier, packageDescription, visible, widgets, docks);
}

}
