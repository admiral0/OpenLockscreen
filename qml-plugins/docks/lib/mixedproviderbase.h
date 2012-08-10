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

#ifndef WIDGETS_DOCKS_MIXEDPROVIDERBASE_H
#define WIDGETS_DOCKS_MIXEDPROVIDERBASE_H

/**
 * @file mixedproviderbase.h
 * @short Definition of Widgets::Docks::MixedProviderBase
 */

#include "widgetproviderbase.h"
#include "dockbaseproperties.h"


namespace Widgets
{

namespace Docks
{

/**
 * @brief Base for both widget and dock providers
 *
 * Extending Widgets::WidgetProviderBase, this class
 * also provides docks. The dock providing behaves
 * exactly like widget providing
 *
 * This interface extends the providing capabilities
 * with these methods
 *
 * - registeredDocks()
 * - dockFile()
 * - dockSettingsFile()
 * - dock()
 * - dockName()
 * - dockDescription()
 *
 * They behave as in Widgets::WidgetProviderBase, but
 * are used for providing docks instead.
 *
 * Remark: this class is fully implemented due to the need
 * of an implemented class for QML metatype system. But this
 * provider do not provide anything. It should not be used.
 *
 * @see Widgets::WidgetProviderBase
 */
class MixedProviderBase: public WidgetProviderBase
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit MixedProviderBase(QObject *parent = 0);
    /**
     * @short Registered docks
     *
     * This method lists all the available docks for
     * a given disambiguation parameter. The list contains
     * the dock filename.
     *
     * @param disambiguation disambiguation parameter.
     * @return a list of registered docks.
     */
    Q_INVOKABLE virtual QStringList
                registeredDocks(const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Absolute path to the dock file
     *
     * This method is used to provide the absolute path to
     * the dock file, given the filename and a
     * disambiguation parameter.
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the dock file.
     */
    Q_INVOKABLE virtual QString
                dockFile(const QString &fileName,
                           const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Absolute path to the dock configuration component file
     *
     * This method is used to provide the absolute path to
     * the configuration component file, associated to a
     * dock, given the filename of this dock and a
     * disambiguation parameter.
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the dock configuration component file.
     */
    Q_INVOKABLE virtual QString
                dockSettingsFile(const QString &fileName,
                                   const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Dock properties
     *
     * This method is used to provide properties
     * of a dock, given the filename and a
     * disambiguation parameter.
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return dock properties.
     */
    Q_INVOKABLE virtual Widgets::Docks::DockBaseProperties *
                        dock(const QString &fileName,
                               const QVariantHash &disambiguation = QVariantHash());

    /**
     * @short Name of the dock
     *
     * This method is used to provide a human-readable name
     * of the dock. By default, it returns the filename.
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return name of the dock.
     */
    Q_INVOKABLE virtual QString
                dockName(const QString &fileName,
                         const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Description
     *
     * This method is used to provide a human-readable of the
     * description of the dock. By default, it returns noting.
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return description of the dock.
     */
    Q_INVOKABLE virtual QString
                dockDescription(const QString &fileName,
                                const QVariantHash &disambiguation = QVariantHash()) const;
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    MixedProviderBase(WidgetProviderBasePrivate *dd, QObject *parent = 0);
};

}

}

#endif // WIDGETS_DOCKS_MIXEDPROVIDERBASE_H
