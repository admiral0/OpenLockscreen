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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_PACKAGEMANAGER_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_PACKAGEMANAGER_H

/**
 * @file packagemanager.h
 * @short Definition of Widgets::PackageManager
 */

#include "mixedproviderbase.h"

#include "package.h"
#include "filterconditionlist.h"

#include "widgetbaseproperties.h"
#include "dockbaseproperties.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class PackageManagerPrivate;
/**
 * @brief The package manager
 *
 * The package manager is used to manage the packages, it
 * uses a database to store all packages that are installed
 * on a device.
 *
 * It is also a mixed provider and implements the methods
 * to provide information about docks and widgets.
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
 * The provider capabilities are brought by these reimplemented
 * methods
 * - disambiguationList()
 * - registeredDocks()
 * - registeredWidgets()
 * - dockFile()
 * - dockSettingsFile()
 * - dock()
 * - widgetFile()
 * - widgetSettingsFile()
 * - widget()
 *
 * The disambiguation paramters are a variant hash that associate the key
 * "identifier" to the package identifier. Therefore, these methods will
 * only retrieve the dock or widget properties that corresponds to
 * a filename in a given package.
 *
 * Finally, managing the filter is done through
 * - filter()
 * - setFilter()
 *
 * The page about \ref packageCreationSection "package creation" provides more
 * information about how packages are managed, and created.
 */
class PackageManager : public Docks::MixedProviderBase
{
    Q_OBJECT
    /**
     * @short %Package manager filter
     */
    Q_PROPERTY(Widgets::Provider::PackageManager::FilterConditionList * filter
               READ filter WRITE setFilter NOTIFY filterChanged)
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
    /*
     * @brief Get a package
     *
     * This method is used to get a package through an identifier.
     * If there is no package corresponding to the identifier, a
     * null package is returned.
     *
     * @param identifier the identifier of the package.
     * @return a package corresponding to the identifier.
     */
//    Package * package(const QString &identifier);
    /*
     * @brief Registered packages identifiers
     *
     * This method is used to get a list of the registered packages
     * through their identifiers.
     *
     * @return all the registered packages identifiers.
     */
//    QStringList registeredPackages() const;
    /**
     * @brief List of disambiguation parameters
     * @return a list of disambiguation parameters.
     */
    QList<QVariantHash> disambiguationList() const;
    /**
     * @short Absolute path to the dock file
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the dock file.
     */
    Q_INVOKABLE QString dockFile(const QString &fileName,
                                 const QVariantHash &disambiguation) const;
    /**
     * @short Absolute path to the dock configuration component file
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the dock configuration component file.
     */
    Q_INVOKABLE QString dockSettingsFile(const QString &fileName,
                                         const QVariantHash &disambiguation) const;
    /**
     * @short Get a dock
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return information about the dock.
     */
    Q_INVOKABLE Widgets::Docks::DockBaseProperties * dock(const QString &fileName,
                                                          const QVariantHash &disambiguation);
    /**
     * @brief Registered docks identifiers
     * @param disambiguation disambiguation parameter.
     * @return all the registered docks identifiers.
     */
    QStringList registeredDocks(const QVariantHash &disambiguation) const;
    /**
     * @internal
     * @brief Absolute path to the widget file
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the widget file.
     */
    Q_INVOKABLE QString widgetFile(const QString &fileName,
                                   const QVariantHash &disambiguation) const;
    /**
     * @brief Absolute path to the widget settings file
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the widget settings file.
     */
    Q_INVOKABLE QString widgetSettingsFile(const QString &fileName,
                                           const QVariantHash &disambiguation) const;
    /**
     * @short Get a widget
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return information about the widget.
     */
    Q_INVOKABLE Widgets::WidgetBaseProperties * widget(const QString &fileName,
                                                       const QVariantHash &disambiguation);
    /**
     * @brief Registered widgets identifiers
     * @param disambiguation disambiguation parameter.
     * @return all the registered widgets identifiers.
     */
    QStringList registeredWidgets(const QVariantHash &disambiguation) const;
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
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    PackageManager(PackageManagerPrivate *dd, QObject *parent = 0);
private:
    Q_DECLARE_PRIVATE(PackageManager)
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_PACKAGEMANAGER_H
