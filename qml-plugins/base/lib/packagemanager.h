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

#ifndef WIDGETS_PACKAGEMANAGER_H
#define WIDGETS_PACKAGEMANAGER_H

/**
 * @file packagemanager.h
 * @short Definition of Widgets::PackageManager
 */

#include <QtCore/QObject>

#include "package.h"
#include "dockbaseproperties.h"
#include "widgetbaseproperties.h"
#include "filterconditionlist.h"

namespace Widgets
{

class PackageManagerPrivate;
/**
 * @brief The package manager
 *
 * The package manager is used to manage the packages, it
 * uses a database to store all packages that are installed
 * on a device.
 *
 * The package manager is also used to provide informations
 * about the installed packages, including widgets and docks.
 *
 * Finally, the package manager can make use of filters to
 * get rid of widgets that should not be used on the device.
 * For a desktop for example, it might be interesting to get
 * rid of the mobile widgets.
 *
 * To manage the packages, the following methods can be used
 * - package()
 * - registeredPackages()
 * - update()
 *
 * The first method is used to query a package is the database,
 * knowing the identifier. The second lists The third is used to perform a
 * full rescan of the device to find packages and register them.
 *
 * Querying the registered packages is done using
 * - registeredDocks()
 * - registeredWidgets()
 * - dockFile()
 * - dock()
 * - widgetFile()
 * - widget()
 *
 * The first two methods are used to list the registered widgets
 * and docks that are contained in a specific package. The other
 * methods are used to either get the absolute path to the QML file
 * that is used to create a dock or a widget, or to get more
 * information about this dock or widget.
 *
 * Finally, managing the filter is done through
 * - filter()
 * - setFilter()
 *
 * The page about \ref packageCreationSection "package creation" provides more
 * information about how packages are managed, and created.
 *
 * @see Widgets::Package
 * @see Widgets::DockBaseProperties
 * @see Widgets::WidgetBaseProperties
 * @see Widgets::FilterConditionList
 */
class PackageManager : public QObject
{
    Q_OBJECT
    /**
     * @short %Package manager filter
     */
    Q_PROPERTY(Widgets::FilterConditionList * filter READ filter WRITE setFilter
               NOTIFY filterChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit PackageManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~PackageManager();
    /**
     * @brief Get a package
     *
     * This method is used to get a package through an identifier.
     * If there is no package corresponding to the identifier, a
     * null package is returned.
     *
     * @param identifier the identifier of the package.
     * @return a package corresponding to the identifier.
     */
    Package * package(const QString &identifier);
    /**
     * @brief Registered packages identifiers
     *
     * This method is used to get a list of the registered packages
     * through their identifiers.
     *
     * @return all the registered packages identifiers.
     */
    QStringList registeredPackages() const;
    /**
     * @short Dock file
     *
     * This method is used to get the absolute file path to the QML file
     * corresponding to a dock, providing the package identifier and
     * the dock file name.
     *
     * If the dock is not found, an empty string is returned.
     *
     * @param packageIdentifier package identifier.
     * @param dockFilename dock file name.
     * @return absolute file path to the QML file.
     */
    Q_INVOKABLE QString dockFile(const QString &packageIdentifier, const QString &dockFilename);
    /**
     * @short Dock
     *
     * This method is used to get the information about a dock, providing
     * the package identifier and the dock file name.
     *
     * If the dock is not found, a null pointer is returned.
     *
     * @param packageIdentifier package identifier.
     * @param dockFilename dock file name.
     * @return information about the dock.
     */
    Q_INVOKABLE Widgets::DockBaseProperties * dock(const QString &packageIdentifier,
                                                   const QString &dockFilename);
    /**
     * @brief Registered docks
     *
     * This method is used to get the list of registered docks through their
     * identifiers, corresponding to a package, that is provided through
     * it's identifier.
     *
     * @param packageIdentifier package identifier.
     * @return all the registered docks identifiers for a given package.
     */
    QStringList registeredDocks(const QString &packageIdentifier) const;
    /**
     * @short Widget file
     *
     * This method is used to get the absolute file path to the QML file
     * corresponding to a widget, providing the package identifier and
     * the widget file name.
     *
     * If the widget is not found, an empty string is returned.
     *
     * @param packageIdentifier package identifier.
     * @param widgetFilename widget file name.
     * @return absolute file path to the QML file.
     */
    Q_INVOKABLE QString widgetFile(const QString &packageIdentifier, const QString &widgetFilename);
    /**
     * @short Widget
     *
     * This method is used to get the information about a widget, providing
     * the package identifier and the widget file name.
     *
     * If the widget is not found, a null pointer is returned.
     *
     * @param packageIdentifier package identifier.
     * @param widgetFilename widget file name.
     * @return information about the widget.
     */
    Q_INVOKABLE Widgets::WidgetBaseProperties * widget(const QString &packageIdentifier,
                                                       const QString &widgetFilename);
    /**
     * @brief Registered widgets
     *
     * This method is used to get the list of registered widgets through their
     * identifiers, corresponding to a package, that is provided through
     * it's identifier.
     *
     * @param packageIdentifier package identifier.
     * @return all the registered widgets identifiers for a given package.
     */
    QStringList registeredWidgets(const QString &packageIdentifier) const;
    /**
     * @brief %Package manager filter
     * @return the package manager filter.
     */
    FilterConditionList * filter() const;
Q_SIGNALS:
    /**
     * @brief %Package manager filter changed
     */
    void filterChanged();
public Q_SLOTS:
    /**
     * @brief Update the package list
     *
     * This method is used to update the content of the package manager,
     * by searching again on the whole system packages that can be loaded,
     * and caching their location in the package manager.
     *
     * This operation is time consuming and may block the application.
     */
    void update();
    /**
     * @brief Set the package manager filter
     * @param filter the package manager filter to set.
     */
    void setFilter(FilterConditionList *filter);
protected:
    /**
     * @brief Constructor for d-pointer
     * @param dd parent d-pointer.
     * @param parent parent object.
     */
    PackageManager(PackageManagerPrivate *dd, QObject *parent = 0);
    /**
     * @brief D-pointer
     */
    const QScopedPointer<PackageManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(PackageManager)
};

}

#endif // WIDGETS_PACKAGEMANAGER_H
