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
 * @file widgets_provider_packagemanager_plugin.h
 * @short Definition of Widgets::Provider::PackageManager::WidgetsProviderPlugin
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

/**
 * @page pluginProviderPackageManager QML plugin for a package manager based widget provider
 *
 * @todo write this page
 *
 * @section packageCreationSection Package creation
 *
 * Extending libwidgets is done through packages, that are an organized filesystem
 * hiearchy. Each package is named with an unique identifier, and each component,
 * either widget or dock also have an identifier. The following organization should
 * be respected.
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
 *
 * @subsection packageCreationWidgetSubsection Widget creation
 *
 * A widget is a declarative item that subclass \e Widget. It needs
 * to provide some informations about size. \e Widget is defined as follow
 *
 * @code{.qml}
 * Item {
 *     id: container
 *     property bool enabled
 *     property variant settings
 *     property int minimumWidth
 *     property int minimumHeight
 *     property int maximumWidth
 *     property int maximumHeight
 * }
 * @endcode
 *
 * Defining the size of the widget can be done in two ways. Either by setting \e width
 * and \e height, so the widget is fixed size, or providing  \e minimumWidth, \e minimumHeight,
 * \e maximumWidth and \e maximumHeight, that creates a resizable widget (in the future).
 *
 * \e enabled property is used to enable the widget. If it is disabled, the widget
 * should stop processing and heavy tasks. \e settings is used to communicate settings
 * to the widget. It uses a QVariantMap to store key / values pairs.
 *
 * @todo showSettings is not used, and should be replaced soon. Document these changes.
 *
 * Only one widget should be defined per folder. It have to be passed to the desktop file to
 * be identified by the package manager. Other QML files that are used in this widget can be
 * declared if needed.
 *
 * @subsection packageCreationDockSubsection Dock creation
 *
 * A dock is a declarative item that subclass \e Dock. It needs
 * to provide some informations about size and anchoring. \e Dock is defined as follow
 *
 * @code{.qml}
 * Item {
 *     id: container
 *     property bool enabled
 *     property variant settings
 * }
 * @endcode
 *
 * Size and anchors should be provided in such a fashion that the dock is well defined.
 * For example, the dock can be anchors top / left / right, and a specific height.
 *
 * \e enabled property is used to enable the dock. If it is disabled, the dock
 * should stop processing and heavy tasks. \e settings is used to communicate settings
 * to the widget. It uses a QVariantMap to store key / values pairs.
 *
 * Only one dock should be defined per folder. It have to be passed to the desktop file to
 * be identified by the package manager. Other QML files that are used in this dock can be
 * declared if needed.
 *
 * @section Configuring a widget or a dock
 *
 * @todo write this
 *
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
 * @see Widgets::PackageManager
 */
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
     * @brief Initialize engine
     * @param engine QML engine.
     * @param uri uri used in the import.
     */
    void initializeEngine(QDeclarativeEngine *engine, const char *uri);
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

