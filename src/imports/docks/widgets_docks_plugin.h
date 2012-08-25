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

#ifndef WIDGETS_DOCKS_PLUGIN_H
#define WIDGETS_DOCKS_PLUGIN_H

/**
 * @file widgets_docks_plugin.h
 * @short Definition of Widgets::Docks::WidgetsDocksPlugin
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>


/**
 * \page pluginDocks QML plugins for docks
 *
 * This plugin extends libwidgets by bringing docking capabilities.
 * %Docks are compoents that are around the screen. Then can have either
 * a fixed width or a fixed height depending on where they are anchored.
 *
 * Docks emulates capabilities of most mobile UI main screens, by bringing
 * a toolbar that have basic controls, like shortcuts, launcher button,
 * or multitasking management.
 *
 * In order to use this plugin, you have to import the following plugin
 * @code{.qml}
 * import org.SfietKonstantin.widgets.docks 1.0
 * @endcode
 *
 * \section pluginDocksContent Content
 *
 * \subsection pluginDocksComponents Components
 *
 * This plugin provides several components, that are all related to
 * dock management. The following QML components are declared
 *
 * - \ref qmlDock
 * - \ref qmlDockedView
 * - \ref qmlEmptyDockedView
 *
 * See also \subpage pluginDocksQmlComponents for the list of declared
 * QML components.
 *
 * \section pluginDocksWriteDock Writing your dock
 *
 * \subsection pluginDockWriteDockDock Write a dock
 *
 * A dock is very simple to write too, since it is also a QML Item component.
 * Like \ref qmlWidget, it also have some properties that are used to make
 * them customizable (see \ref qmlDock).
 *
 * A dock have to be anchored somewhere around the screen. Either it can be
 * anchored in a corner, and have to have a fixed width and height, as well
 * as either anchors.top set to parent.top or anchors.bottom set to parent.bottom,
 * and either anchors.left set to parent.left or anchors.right set to parent.right.
 *
 * A dock can also be anchored in an edge, so three anchors should be set and
 * either the width, or the height be fixed.
 *
 * You can use several files for your widget, but be sure to register the base
 * dock file to a provider (see \ref providers for more information).
 *
 * \subsection pluginDockWriteDockSettings Write a dock settings
 *
 * Dock settings are not supported currently, but will have the same approach
 * as for widgets.
 *
 */
/**
 * @page pluginDocksQmlComponents QML components
 *
 * \section qmlDock Dock
 *
 * Inherits from \b Item.
 *
 * \b Dock is the base QML component that is used to
 * represent a dock. All docks used in libwidgets have
 * to have this component as a parent.
 *
 * While writing a dock, you should provide a correct
 * combinaison of anchors and size that can make a dock
 * being docked, either in an edge, or in a corner.
 *
 * \subsection qmlDockProperties Properties
 *
 * - \b enabled
 *
 * This property is used to notify if the dock should be enabled
 * and thus, do heavy processing or should be suspended.
 *
 * - \b settings
 *
 * This property holds the dock properties, that are passed as
 * a variant-map. On QML side, settings can be accessed as an object.
 *
 * \section qmlDockedView DockedView
 *
 * Inherits from \b Item.
 *
 * This component is used to display docks. It creates docks around
 * an area, and provide a space to display content inside of the docks.
 *
 * \subsection qmlDockedViewProperties Properties
 *
 * - \b content
 *
 * This property is the area that is inside of the docks. A widgets view
 * can be inserted inside that area for example.
 *
 * \section qmlEmptyDockedView EmptyDockedView
 *
 * Inherits from \b Item.
 *
 * This component is used to emulate the space that docks are taking. It
 * can be useful for editing widgets for example.
 *
 * \subsection qmlDockedViewProperties Properties
 *
 * - \b content
 *
 * This property is the area that is inside of the docks. A widgets view
 * can be inserted inside that area for example.
 *
 * \section qmlDockContainer [Internal] DockContainer
 *
 * This component is used internally to create the dock to display.
 */
/**
 * \page pluginDocksInternals QML plugin for docks
 *
 * \section pluginDocksInternalComponents Internal components
 *
 * These components should not be used by the developer that want
 * to take advantage of libwidgets, but by those that want to extend
 * it.
 *
 * - Widgets::Docks::MixedProviderBase
 * - Widgets::Docks::DockModel
 * - Widgets::Docks::DockBaseProperties
 * - Widgets::Docks::DockProperties
 * - Widgets::Docks::DockedViewManager
 * - \ref qmlDockContainer
 *
 * These global instances are also set
 * - \b DockModelInstance
 * - \b DockedViewManagerInstance
 *
 * \section pluginBaseInternalWidgetSystem The dock system
 *
 * Instances of docks are controlled by a model, that
 * contains the type, the anchoring, and some settings of
 * all the docks.
 *
 * The global \b DockModelInstance is the model that
 * represents all the displayed docks. It is
 * an instance of Widgets::Docks::DockModelWidgetsPageListModel
 * and stores Widgets::Docks::DockProperties. These objects
 * stores all information that are required to create widgets,
 * including anchoring and settings.
 *
 * These objects are created using Widgets::Docks::DockBaseProperties,
 * that only contain the basic information of the dock, such as
 * the anchoring and the file name.
 *
 * All the models are also used to save settings related to
 * docks, and do this in an automated way. Settings are
 * stored using QDesktopServices::DataLocation.
 */


namespace Widgets
{

/**
 * @short Namespace for docks
 */
namespace Docks
{

/**
 * @internal
 * @short QML plugin for docks
 */
class WidgetsDocksPlugin : public QDeclarativeExtensionPlugin
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

#endif // WIDGETS_DOCKS_PLUGIN_H

