/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_P_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file databaseinterface_p_p.h
 * @short Definition of Widgets::Provider::PackageManager::DatabaseInterfacePrivate
 */

#include <QtCore/QString>
#include <QtCore/QVariantHash>
#include <QtSql/QSqlDatabase>

#include "widgetbaseproperties.h"
#include "dockbaseproperties.h"
#include "componentmetadata_p.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class FilterConditionList;
class Package;
/**
 * @internal
 * @brief Private class for Widgets::Provider::PackageManager::DatabaseInterface
 */
class DatabaseInterfacePrivate
{
public:
    /**
     * @internal
     * @brief Database path
     * @return database path.
     */
    static QString databasePath();
    /**
     * @internal
     * @brief Execute a query
     * @param query the query to execute.
     * @return if the query succeeded.
     */
    static bool executeQuery(QSqlQuery *query);
    /**
     * @internal
     * @brief Execute a query
     *
     * This method execute the query and finish it
     * directly after.
     *
     * @param query the query to execute.
     * @param db database.
     * @return if the query succeeded.
     */
    static bool executeQuery(const QString &query, const QSqlDatabase &db);
    /**
     * @internal
     * @brief Execute a batch query
     * @param query the query to execute.
     * @return if the query succeeded.
     */
    static bool executeQueryBatch(QSqlQuery *query);
    /**
     * @brief Execute a query for a count
     *
     * This method execute a query that should
     * provide a count. It returns the count
     * and terminate the query.
     *
     * @param query the query to execute.
     * @return the count.
     */
    static int executeQueryCount(QSqlQuery *query);
    /**
     * @internal
     * @brief Prepare the database
     */
    static void prepareDatabase();
    /**
     * @internal
     * @brief Add components types
     * @param names name of the components.
     */
    static void addComponentType(const QStringList &names);
    /**
     * @internal
     * @brief Add components informations properties
     * @param names name of the properties.
     */
    static void addComponentInformationProperties(const QStringList &names);
    /**
     * @internal
     * @brief Database id associated to a component type
     * @param type component type
     * @return database id associated to a component type.
     */
    static qlonglong componentTypeId(const char *type);
    /**
     * @internal
     * @brief Add localized information
     *
     * This method is used to add localized information
     * to any component. The information is provided
     * with three lists, containing the languages, the
     * names and the descriptions.
     *
     * @param type type of the component.
     * @param componentId database id of the component.
     * @param languages list of languages.
     * @param names list of names.
     * @param descriptions list of descriptions.
     */
    static void addLocalizedInformation(const char *type, qlonglong componentId,
                                        const QStringList &languages, const QStringList &names,
                                        const QStringList &descriptions);
    /**
     * @internal
     * @brief Add information
     *
     * This method is used to add information to
     * any component. The information is provided as
     * a variant hash, with the name of the information
     * associated to the value.
     *
     * @param type type of the component.
     * @param componentId database id of the component.
     * @param informations informations to add.
     */
    static void addInformation(const char *type, qlonglong componentId,
                               const QVariantHash &informations);
    /**
     * @internal
     * @brief Database id associated to a tag
     * @param tag tag.
     * @return database id associated to the tag.
     */
    static qlonglong tagId(const QString &tag);
    /**
     * @internal
     * @brief Check if a tag exists
     *
     * This method is used to check if an association
     * between a package and a tag exists.
     *
     * @param packageId database id of the package.
     * @param tag tag.
     * @return if the association between the package and the tag exists.
     */
    static bool tagExists(qlonglong packageId, const QString &tag);
    /**
     * @internal
     * @brief Add tags
     *
     * This method is used to add tags to
     * a package.
     *
     * @param packageId database id of the package.
     * @param tags list of tags to add.
     */
    static void addTags(qlonglong packageId, const QStringList &tags);
    /**
     * @internal
     * @brief Add a package
     * @param package the package to add.
     * @param path absolute path of the package.
     */
    static void addPackage(Package *package, const QString &path);
    /**
     * @internal
     * @brief Database id of the package
     * @param packageIdentifier package identifier.
     * @return database id of the package.
     */
    static qlonglong packageId(const QString &packageIdentifier);
    /**
     * @internal
     * @brief Add a dock
     * @param packageId database id of the package.
     * @param subdirectory subdirectory where the dock is.
     * @param dock dock base properties.
     * @param metadata dock metadata.
     */
    static void addDock(qlonglong packageId, const QString &subdirectory,
                        Docks::DockBaseProperties *dock, ComponentMetadata *metadata);
    /**
     * @internal
     * @brief Add a widget
     * @param packageId database id of the package.
     * @param subdirectory subdirectory where the widget is.
     * @param widget widget base properties.
     * @param metadata dock metadata.
     */
    static void addWidget(qlonglong packageId, const QString &subdirectory,
                          WidgetBaseProperties *widget, ComponentMetadata *metadata);

    /**
     * @internal
     * @brief Registered packages identifiers
     * @param filter filters.
     * @return all the registered packages identifiers.
     */
    static QStringList registeredPackages(FilterConditionList *filter);
    /**
     * @brief Get a package
     *
     * @param identifier the identifier of the package.
     * @param parent parent object.
     * @return a package corresponding to the identifier.
     */
    static Package * package(const QString &identifier, QObject *parent = 0);
    /**
     * @internal
     * @brief Registered widgets identifiers
     * @param packageIdentifier package identifier.
     * @return all the registered widgets identifiers.
     */
    static QStringList registeredWidgets(const QString &packageIdentifier);
    /**
     * @internal
     * @brief Registered docks identifiers
     * @param packageIdentifier package identifier.
     * @return all the registered docks identifiers.
     */
    static QStringList registeredDocks(const QString &packageIdentifier);
    /**
     * @short Get a widget
     *
     * @param packageIdentifier package identifier.
     * @param fileName widget file name.
     * @param parent parent object.
     * @return information about the widget.
     */
    static WidgetBaseProperties * widget(const QString &packageIdentifier, const QString &fileName,
                                         QObject *parent = 0);
    /**
     * @short Get a dock
     *
     * @param packageIdentifier package identifier.
     * @param fileName dock file name.
     * @param parent parent object.
     * @return information about the dock.
     */
    static Docks::DockBaseProperties * dock(const QString &packageIdentifier,
                                            const QString &fileName,
                                            QObject *parent = 0);
    /**
     * @brief Absolute widget folder
     * @param packageIdentifier package identifier.
     * @param fileName filename.
     * @return absolute widget folder.
     */
    static QString widgetAbsoluteFolder(const QString &packageIdentifier, const QString &fileName);
    /**
     * @internal
     * @brief Absolute path to the widget file
     *
     * @param packageIdentifier package identifier.
     * @param fileName widget filename.
     * @return absolute path to the widget file.
     */
    static QString widgetFile(const QString &packageIdentifier, const QString &fileName);
    /**
     * @internal
     * @brief Absolute path to the widget settings file
     *
     * @param packageIdentifier package identifier.
     * @param fileName widget filename.
     * @return absolute path to the widget settings file.
     */
    static QString widgetSettingsFile(const QString &packageIdentifier, const QString &fileName);
    /**
     * @brief Absolute dock folder
     * @param packageIdentifier package identifier.
     * @param fileName filename.
     * @return absolute dock folder.
     */
    static QString dockAbsoluteFolder(const QString &packageIdentifier, const QString &fileName);
    /**
     * @internal
     * @brief Absolute path to the dock file
     *
     * @param packageIdentifier package identifier.
     * @param fileName dock filename.
     * @return absolute path to the dock file.
     */
    static QString dockFile(const QString &packageIdentifier, const QString &fileName);
    /**
     * @internal
     * @brief Absolute path to the dock settings file
     *
     * @param packageIdentifier package identifier.
     * @param fileName dock filename.
     * @return absolute path to the dock settings file.
     */
    static QString dockSettingsFile(const QString &packageIdentifier, const QString &fileName);

    /**
     * @internal
     * @brief Clean the database
     *
     * This method removes everything
     * from the database.
     */
    static void clean();
    /**
     * @internal
     * @brief Scan a folder for packages
     *
     * This method is used to search for packages
     * in a given folder, and returns the package identifier
     * if a package was found.
     *
     * @param path absolute path to the folder.
     * @return package identifier.
     */
    static QString scanFolderForPackage(const QString &path);
    /**
     * @internal
     * @brief Scan a folder for widgets
     *
     * This method is used to search for widgets
     * in a given folder. It scans all subfolders
     * inside a folder and check if there are widgets.
     *
     * @param path absolute path to the folder.
     * @param packageIdentifier package identifier.
     * @param packageId database id of the package.
     */
    static void scanFolderForWidgets(const QString &path, const QString &packageIdentifier,
                                     qlonglong packageId);
    /**
     * @internal
     * @brief Scan a folder for docks
     *
     * This method is used to search for docks
     * in a given folder. It scans all subfolders
     * inside a folder and check if there are docks.
     *
     * @param path absolute path to the folder.
     * @param packageIdentifier package identifier.
     * @param packageId database id of the package.
     */
    static void scanFolderForDocks(const QString &path, const QString &packageIdentifier,
                                   qlonglong packageId);
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_P_H
