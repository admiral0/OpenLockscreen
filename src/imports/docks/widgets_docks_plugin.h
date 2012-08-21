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
 * While imported, this plugin provides a docks model, that is used to contain
 * all the created docks. This model have loading and saving capabilities,
 * and can be edited easliy. The model can be accessed through the global
 * variable \e DockModelInstance.
 *
 * This plugin also provides a docked view manager, that is used to compute
 * the space that each dock takes, and can be used to adjust the inner view,
 * where other components sits. This component can be accessed through the
 * global variable \e DockedViewManagerInstance.
 *
 * You can take advantage of a docked view by using the \e DockedView
 * component. The \e EmptyDockedView can also be used to simulate the place
 * taken by the docks without displaying them.
 *
 * @see Widgets::Docks::DockModel
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

