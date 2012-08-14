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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file databaseinterface_p.h
 * @short Definition of Widgets::Provider::PackageManager::DatabaseInterface
 */

#include <QtCore/QObject>
#include <QtCore/QVariantHash>

namespace Widgets
{

class WidgetBaseProperties;
namespace Docks {
class DockBaseProperties;
}

namespace Provider
{

namespace PackageManager
{

class FilterConditionList;
class DatabaseInterfacePrivate;

/**
 * @internal
 * @brief Interface for the database
 *
 * This class is an interface for the database used
 * by the package manager. It provides a list of
 * methods that are used to manipulate the database
 * and interact with it.
 *
 * The following methods are used to initialize the
 * database
 * - cleanDatabase()
 * - prepareDatabase()
 * - scan()
 * The first method will clear all the database, the second
 * will create default fields in the database and
 * the third will perform a scan of the system, finding
 * all packages, widgets and docks.
 *
 * Quering the database is done through
 * - registeredPackages()
 * - registeredWidgets()
 * - registeredDocks()
 * - widgetFile()
 * - widgetSettingsFile()
 * - widget()
 * - dockFile()
 * - dockSettingsFile()
 * - dock()
 * The first three methods are used to get lists of components
 * that are registered in the database. The second set of
 * three methods are used to retrieve information about widgets
 * and the last three methods are used to retrieve information
 * about widgets.
 *
 * This class also provides some small utilities functions, like
 * - disambiguation()
 * - packageIdentifier()
 * that are used to switch from the variant-hash based disambiguation
 * system and the string based package identifier system.
 */
class DatabaseInterface: public QObject
{
    Q_OBJECT
public:
    /**
     * @internal
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit DatabaseInterface(QObject *parent = 0);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~DatabaseInterface();
    /**
     * @internal
     * @brief Disambiguation
     *
     * This method is used to get a disambiguation
     * parameter from a package identifier.
     *
     * @param packageIdentifier package identifier.
     * @return disambiguation parameter.
     */
    QVariantHash disambiguation(const QString &packageIdentifier);
    /**
     * @internal
     * @brief Package identifier
     *
     * This method is used to get a package identifier
     * from a disambiguation parameter .
     *
     * @param disambiguation disambiguation parameter.
     * @return package identifier.
     */
    static QString packageIdentifier(const QVariantHash &disambiguation);
    /**
     * @internal
     * @brief Prepare the database
     *
     * Prepare the database by adding default
     * entries.
     */
    void prepareDatabase();
    /**
     * @internal
     * @brief Clean the database
     */
    void cleanDatabase();
    /**
     * @internal
     * @brief Scan
     *
     * Scan the system for packages, widgets and docks.
     */
    void scan();
    /**
     * @internal
     * @brief Registered packages identifiers
     * @param filter filters.
     * @return all the registered packages identifiers.
     */
    QStringList registeredPackages(FilterConditionList *filter) const;
    /**
     * @internal
     * @brief Registered widgets identifiers
     * @param packageIdentifier package identifier.
     * @return all the registered widgets identifiers.
     */
    QStringList registeredWidgets(const QString &packageIdentifier) const;
    /**
     * @internal
     * @brief Registered docks identifiers
     * @param packageIdentifier package identifier.
     * @return all the registered docks identifiers.
     */
    QStringList registeredDocks(const QString &packageIdentifier) const;
    /**
     * @internal
     * @brief Absolute path to the widget file
     *
     * @param packageIdentifier package identifier.
     * @param fileName widget filename.
     * @return absolute path to the widget file.
     */
    QString widgetFile(const QString &packageIdentifier, const QString &fileName);
    /**
     * @internal
     * @brief Absolute path to the widget settings file
     *
     * @param packageIdentifier package identifier.
     * @param fileName widget filename.
     * @return absolute path to the widget settings file.
     */
    QString widgetSettingsFile(const QString &packageIdentifier, const QString &fileName);
    /**
     * @short Get a widget
     *
     * @param packageIdentifier package identifier.
     * @param fileName widget file name.
     * @param parent parent object.
     * @return information about the widget.
     */
    WidgetBaseProperties * widget(const QString &packageIdentifier, const QString &fileName,
                                  QObject *parent = 0);
    /**
     * @internal
     * @brief Absolute path to the dock file
     *
     * @param packageIdentifier package identifier.
     * @param fileName dock filename.
     * @return absolute path to the dock file.
     */
    QString dockFile(const QString &packageIdentifier, const QString &fileName);
    /**
     * @internal
     * @brief Absolute path to the dock settings file
     *
     * @param packageIdentifier package identifier.
     * @param fileName dock filename.
     * @return absolute path to the dock settings file.
     */
    QString dockSettingsFile(const QString &packageIdentifier, const QString &fileName);
    /**
     * @short Get a dock
     *
     * @param packageIdentifier package identifier.
     * @param fileName dock file name.
     * @param parent parent object.
     * @return information about the dock.
     */
    Docks::DockBaseProperties * dock(const QString &packageIdentifier, const QString &fileName,
                                     QObject *parent = 0);
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer <DatabaseInterfacePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DatabaseInterface)
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_H
