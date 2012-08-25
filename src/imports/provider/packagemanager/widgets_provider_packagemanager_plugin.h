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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_PLUGIN_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_PLUGIN_H

/**
 * @internal
 * @file widgets_provider_packagemanager_plugin.h
 * @short Definition of Widgets::Provider::PackageManager::WidgetsProviderPlugin
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>

/**
 * @page pluginProviderPackageManager Package manager based provider
 *
 * The package manager based provider is more complex. It uses a cache for
 * storing installed packages, and comes with a helper program that is used
 * to update this cache and add new packages.
 *
 * %Widgets and docks should be "packaged", and installed in a defined hiearchy
 * in order to be detected and included in the cache.
 *
 * @section packageCreationSection Package creation
 *
 * A package is an organized filesystem hiearchy plus some information that are
 * used for both information and organization. Each package is named with an
 * unique identifier. The following organization should be respected.
 * @code{.txt}
 * |-- package.desktop
 * |-- widgets/
 *   |-- widget1/
 *     |-- metadata.desktop
 *     |-- somewidgetqmlfile.qml
 *     |-- somewidgetdatafile.png
 *   |-- widget2/
 *   |-- ...
 * |-- docks/
 *   |-- dock1/
 *     |-- metadata.desktop
 *     |-- somedockqmlfile.qml
 *     |-- somedockdatafile.png
 *   |-- dock2/
 *   |-- ...
 * @endcode
 * @subsection packageCreationMetaSubsection Desktop file creation
 *
 * Two types of desktop files are used to provide metadata to the package. The first type
 * is used to provide metadata to the package itself. The typical desktop file are
 * described as follow
 *
 * @code{.desktop}
 * [Desktop Entry]
 * Name=My package
 * Name[en_GB]=My package in british english
 * ...
 * Comment=Comment on the package
 * Comment[en_GB]=Comment on the package in british english
 * ...
 * Icon=Some icon
 * Type=Service
 * X-Widgets-ServiceType=plugin
 * X-Widgets-PluginInfo-Id=com.mycompany.mypluginname
 * X-Widgets-PluginInfo-Author=Some author
 * X-Widgets-PluginInfo-Email=some@email.com
 * X-Widgets-PluginInfo-Website=http://some.website.com
 * X-Widgets-PluginInfo-Tags=sometag;someothertag
 * X-Widgets-PluginInfo-Name=pluginname
 * X-Widgets-PluginInfo-Version=X.Y.Z
 * X-Widgets-PluginInfo-Visible=true
 * @endcode
 *
 * This file must be named \b package.desktop, and be in the package root folder.
 *
 * The first entries are like a normal desktop file. Name, comment, and icon should
 * be provided to display information about the package. The \e Type entry must be set
 * to \b Service.
 *
 * All the entries starting with \e X-Widgets are mandatory, except \e X-Widgets-PluginInfo-Visible.
 * - \b X-Widgets-ServiceType must be set to \b plugin.
 * - \b X-Widgets-PluginInfo-Id is the unique identifier of this package. This id is used
 * everywhere, in the package manager to store information about the package, as well as to
 * retrieve docks and widgets associated to this package.
 * - \b X-Widgets-PluginInfo-Author is the author of this package.
 * - \b X-Widgets-PluginInfo-Email is the email of the author.
 * - \b X-Widgets-PluginInfo-Website is the website of this package.
 * - \b X-Widgets-PluginInfo-Tags are the tags that can be used to find this package.
 * - \b X-Widgets-PluginInfo-Name is the C++ plugin that should be loaded with this package.
 * - \b X-Widgets-PluginInfo-Version is the version of this package, in the \e X.Y.Z format, where
 * X, Y and Z are numbers.
 * - \b X-Widgets-PluginInfo-Visible set if the package is visible in the package manager. If this
 * parameter is set to false, the package is hidden, but can still be used. Packages that are
 * hidden can be useful for system components. If not present, this parameter is considered to
 * be true.
 *
 * The second type of desktop file are those describing widgets or docks. They are described as
 * follow, with slight differences between widgets and docks. They are described as follow
 *
 * @code{.desktop}
 * [Desktop Entry]
 * Name=My widget
 * Name[en_GB]=My widget in british english
 * ...
 * Comment=Comment on the widget
 * Comment[en_GB]=Comment on the widget in british english
 * ...
 * Icon=
 * Type=Service
 * X-Widgets-ServiceType=widget
 * X-Widgets-WidgetInfo-File=WidgetFile.qml
 * @endcode
 *
 * for a widget.
 *
 * @code{.desktop}
 * [Desktop Entry]
 * Name=My dock
 * Name[en_GB]=My dock in british english
 * ...
 * Comment=Comment on the dock
 * Comment[en_GB]=Comment on the dock in british english
 * ...
 * Icon=
 * Type=Service
 * X-Widgets-ServiceType=dock
 * X-Widgets-DockInfo-File=DockFile.qml
 * @endcode
 *
 * for a dock.
 *
 * These file must be named \b metadata.desktop, and be in the widget or dock folder.
 *
 * The first entries are like a normal desktop file. Name, comment, and icon should
 * be provided to display information about the dock or widget. The \e Type entry must be set
 * to \b Service.
 *
 * After that, we have two of these three entries
 * - \b X-Widgets-ServiceType that should be set either to widget or to dock.
 * - \b X-Widgets-WidgetInfo-File that is used to provide the QML file for a widget.
 * - \b X-Widgets-DockInfo-File that is used to provide the QML file for a dock.
 */

namespace Widgets
{

namespace Provider
{

/**
 * @short Namespace for package manager based providers
 */
namespace PackageManager
{


/**
 * @internal
 * @brief QML plugin for package manager based widget provider
 */
class WidgetsProviderPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    /**
     * @internal
     * @short Register types
     * @param uri uri used in the import.
     */
    void registerTypes(const char *uri);
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_PLUGIN_H

