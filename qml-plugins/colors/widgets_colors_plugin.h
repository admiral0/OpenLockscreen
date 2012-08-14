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

#ifndef WIDGETS_COLORS_PLUGIN_H
#define WIDGETS_COLORS_PLUGIN_H

/**
 * @file widgets_colors_plugin.h
 * @short Definition of Widgets::Colors::WidgetsColorsPlugin
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>

namespace Widgets
{

/**
 * @short Namespace for colors
 */
namespace Colors
{

/**
 * @page pluginColors QML plugin for colors
 *
 * libwidgets comes with a plugin that registers many colors, that can be
 * used to provide a consistent and beautiful look and feel. These colors
 * comes from KDE Oxygen palette.
 *
 * To access the colors, you have to import the QML plugin
 * @code{.qml}
 * import org.SfietKonstantin.widgets.colors 1.0
 * @endcode
 *
 * This import creates a global object in the QML context called \e Colors.
 * To use the registered colors, you have to do as follow :
 *
 * @code{.qml}
 * Rectangle {
 *     id: rectangle
 *     color: Colors.woodBrown3
 * }
 * @endcode
 *
 * This plugin do not depend on any plugin. You can use it without importing
 * the main libwidgets plugin.
 */
/**
 * @internal
 * @brief QML plugin for colors
 */
class WidgetsColorsPlugin : public QDeclarativeExtensionPlugin
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

#endif // WIDGETS_COLORS_PLUGIN_H

