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

#ifndef WIDGETS_PROVIDER_BASIC_WIDGET_PLUGIN_H
#define WIDGETS_PROVIDER_BASIC_WIDGET_PLUGIN_H

/**
 * @file widgets_provider_basic_widget_plugin.h
 * @short Definition of Widgets::Provider::Basic::WidgetsProviderBasicPlugin
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>

/**
 * \page pluginProviderBasic Basic providers
 *
 * There are two basic providers, that behave the same. The first
 * one only provides widgets, the second provides both widgets and docks.
 *
 * In order to use one of these plugins, you should use one of these two
 * imports
 * \code{.qml}
 * import org.SfietKonstantin.widgets.provider.basic.widget 1.0
 * import org.SfietKonstantin.widgets.provider.basic.mixed 1.0
 * \endcode
 *
 * These providers search in a folder where widgets are stored. A text file
 * named \b widgets.txt should be put inside this folder. It should have
 * the content organized as follow
 * \verbatim
Widget1.qml
Widget2.qml;WidgetConfiguration2.qml
Widget3.qml;WidgetConfiguration3.qml
Widget4.qml
...
\endverbatim
 * Only one QML file that corresponds to a widget should be in one line.
 * This file can be followed by a semicolon and the name of the QML item
 * that is used to do the settings of the widget.
 *
 * The widget folder is set through the property
 * Widgets::Provider::Basic::BasicWidgetProvider::widgetsPath() or
 * Widgets::Provider::Basic::BasicMixedProvider::widgetsPath().
 *
 * The mixed provider also have a second property,
 * Widgets::Provider::Basic::BasicMixedProvider::docksPath(),
 * that is used to search for docks. In this folder, a file named
 * \b docks.txt should be set, with the same syntax as previous.
 *
 */

namespace Widgets
{

/**
 * @short Namespace for providers
 */
namespace Provider
{

/**
 * @short Namespace for basic providers
 */
namespace Basic
{

/**
 * @internal
 * @brief QML plugin for basic widget provider
 */
class WidgetsProviderBasicPlugin: public QDeclarativeExtensionPlugin
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

#endif // WIDGETS_PROVIDER_BASIC_WIDGET_PLUGIN_H

