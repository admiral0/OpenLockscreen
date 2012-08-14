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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_COMPONENTMETADATA_P_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_COMPONENTMETADATA_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file componentmetadata_p.h
 * @short Definition of Widgets::Provider::PackageManager::ComponentMetadata
 */


#include "desktopcomponent.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class ComponentMetadataPrivate;
/**
 * @internal
 * @brief Component metadata
 *
 * This class is used to get the metadata
 * of a component, either a dock or a widget, and
 * can be accessible through QML even if, by default,
 * this class is private.
 *
 * These informations includes
 * - type(), that is the type of the component.
 * - fileName(), that is the name of the QML file of the component.
 * - settingsFileName(), that is the name of the QML file that is used to setup the component.
 *
 * These informations are extended with those that are shared
 * with the other components, and that are provided through
 * Widgets::ComponentBase.
 *
 * The page about \ref packageCreationMetaSubsection "desktop file creation" provides more
 * information about how desktop files should be written.
 */
class ComponentMetadata: public DesktopComponent
{
    Q_OBJECT
    Q_ENUMS(ComponentType)
    /**
     * @internal
     * @short Component type
     */
    Q_PROPERTY(ComponentType type READ type CONSTANT)
    /**
     * @internal
     * @short Filename
     */
    Q_PROPERTY(QString fileName READ fileName CONSTANT)
    /**
     * @internal
     * @short Settings filename
     */
    Q_PROPERTY(QString settingsFileName READ settingsFileName CONSTANT)
public:
    /**
     * @internal
     * @brief Component type
     */
    enum ComponentType {
        /**
         * @internal
         * @brief Invalid component
         */
        InvalidComponentType,
        /**
         * @internal
         * @brief Widget
         */
        WidgetComponentType,
        /**
         * @internal
         * @brief Dock
         */
        DockComponentType
    };
    /**
     * @brief Default constructor
     * @param icon icon of the component.
     * @param defaultName default name of the component.
     * @param defaultDescription default description of the component.
     * @param names a list of names associated to the language.
     * @param descriptions a list of descriptions associated to the language.
     * @param type component type.
     * @param fileName component filename.
     * @param settingsFileName component settings filename.
     * @param parent parent object.
     */
    explicit ComponentMetadata(const QString &icon,
                               const QString &defaultName, const QString &defaultDescription,
                               const QHash<QString, QString> &names,
                               const QHash<QString, QString> &descriptions,
                               ComponentType type,
                               const QString fileName, const QString settingsFileName,
                               QObject *parent = 0);
    /**
     * @brief Component type
     * @return component type.
     */
    ComponentType type() const;
    /**
     * @brief Filename
     * @return filename.
     */
    QString fileName() const;
    /**
     * @brief Settings filename.
     * @return settings filename.
     */
    QString settingsFileName() const;
    /**
     * @brief Create a component from a desktop file
     *
     * @param desktopFile path to the desktop file to parse.
     * @param parent parent object for the created component metadata.
     * @return a component metadata.
     */
    static ComponentMetadata * fromDesktopFile(const QString &desktopFile, QObject *parent = 0);
private:
    W_DECLARE_PRIVATE(ComponentMetadata)
};

}

}

}

#endif // COMPONENTMETADATA_P_H
