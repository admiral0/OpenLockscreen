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
 * @file packagemanager.h
 * @short Definition of Widgets::PackageManager
 *
 * This file contains the definition of the
 * Widgets::PackageManager class.
 */

#ifndef WIDGETS_PACKAGEMANAGER_H
#define WIDGETS_PACKAGEMANAGER_H

#include <QtCore/QObject>
#include "widgetbaseproperties.h"
#include "dockbaseproperties.h"

namespace Widgets
{

class AvailableWidgetsModel;
class AvailableDocksModel;
/**
 * @short %Package manager
 *
 * The package manager is used load packages
 * and store them in a cache that can be
 * queried after.
 *
 * It also manages models that are used
 * to select available widgets or
 * configure docks.
 *
 * Quering the widgets and packages cache
 * is done using
 * - widget()
 * - internalWidget()
 * - dock()
 * - internalDock()
 *
 * Accessing the models is done using
 * - availableWidgetsModel()
 * - availableDocksModel()
 *
 * It should be the only source to check
 * base properties of both widgets and
 * docks. (No DockBaseProperties and
 * WidgetBaseProperties should be
 * instantiated in other classes).
 *
 * This class is used in QML context. Accessing
 * it is done using the "packageManager" global object.
 *
 * @section packageFolders Package folders
 *
 * The package folders are
 * - /opt/widgets/qml
 * - /opt/widgets/widgets/\<widgetpackagename\>
 */
class PackageManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit PackageManager(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~PackageManager();
    /**
     * @short Widget base properties
     *
     * This method is used to retrieve the
     * base properties of a widget
     * associated to a QML file.
     *
     * The QML file have to be provided in absolute
     * path.
     *
     * @param qmlFile widget QML file name.
     * @return widget base properties.
     */
    Q_INVOKABLE Widgets::WidgetBaseProperties * widget(const QString &qmlFile) const;
    /**
     * @short Dock base properties
     *
     * This method is used to retrieve the
     * base properties of a dock
     * associated to a QML file.
     *
     * The QML file have to be provided in absolute
     * path.
     *
     * @param qmlFile dock QML file name.
     * @return dock base properties.
     */
    Q_INVOKABLE Widgets::DockBaseProperties * dock(const QString &qmlFile) const;
    /**
     * @short Available widgets models
     *
     * This method is used to retrieve the model
     * that describes available widgets and that
     * is loaded by the package manager.
     *
     * @return model that describes the available widgets.
     */
    AvailableWidgetsModel * availableWidgetsModel() const;
    /**
     * @short Available docks models
     *
     * This method is used to retrieve the model
     * that describes available docks and that
     * is loaded by the package manager.
     *
     * @return model that describes the available docks.
     */
    AvailableDocksModel * availableDocksModel() const;

private:
    class PackageManagerPrivate;
    /**
     * @short D-pointer
     */
    PackageManagerPrivate * const d;
};

}

#endif // PACKAGEMANAGER_H
