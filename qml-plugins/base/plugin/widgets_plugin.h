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

#ifndef WIDGETS_PLUGIN_H
#define WIDGETS_PLUGIN_H

/**
 * @file widgets_plugin.h
 * @short Definition of Widgets::WidgetsPlugin
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>
/**
 * \mainpage libwidgets
 *
 * libwidgets is a Qt / QML library that brings widgets
 * to your application. libwidgets consists of libraries
 * and QML plugins, that can be imported in any QML project,
 * and that do not need C++ code to work.
 *
 * libwidgets have many features, and many plugins that can
 * be used.
 *
 * Getting started
 * - \subpage tutorials
 * - \subpage pluginList
 */
/**
 * \page tutorials Tutorials
 *
 * - \subpage tutorial1
 *
 */
/**
 * \page tutorial1 Tutorial 1: create your first widgets view.
 *
 * Creating a widgets view can be done with only a few steps, but some
 * of them are tricky. This tutorial is here to show the different points
 * to pay attention when creating a widgets view.
 *
 * A widgets view is composed of a display, and a model.
 * @todo continue this.
 */
/** \page pluginList List of all the plugins
 *
 * Here is a list of all the plugins that are provided by
 * libwidgets. Most of them can be disabled using compile-time
 * flags.
 *
 * - \subpage pluginBase
 * - \subpage providers
 *   - \ref pluginProviderBasic
 *   - \ref pluginProviderPackageManager
 * - \subpage pluginColors
 *
 */
/**
 * @page providers Providers
 *
 * A widget engine must be used with a provider, that provides widget
 * to the widget engine. Providers are C++ components that have to be
 * implemented and registered to the \e WidgetsPageListModelInstance
 * when they are initialized.
 *
 * Fortunately, some providers are alredy implemented :
 * - \subpage pluginProviderBasic
 * - \subpage pluginProviderPackageManager
 *
 * The documentation on implementing a provider is on the page of the
 * class Widgets::WidgetProviderInterface.
 */
/**
 * @page pluginBase Base QML plugin for widgets
 *
 * libwidgets is a QML library that can be used to create widgets in a
 * QML enabled app. This plugin provides all basic features and class of
 * libwidgets. Most plugins in libwidgets also needs this plugin to work
 * since they all use the basic features and classes that this plugin
 * provides.
 *
 * In order to use this plugin, you have to import the following plugin
 * @code{.qml}
 * import org.SfietKonstantin.widgets 1.0
 * @endcode
 *
 * While imported, this plugin provides a widgets pages model
 * that is a global model that is used to represent the widgets
 * in different screens. It provides loading and saving capabilities, and can
 * be edited easliy.
 *
 * This model is available as a global object, named \e WidgetsPageListModelInstance.
 *
 * You can use the @e WidgetsPageListModelInstance in any view, but we recommand
 * using provided views such as @e WidgetsHorizontalPageView, or subclassing the
 * provided @e WidgetsView.
 *
 * @see WidgetsPageListModel.
 */

/**
 * @short Namespace for libwidgets
 */
namespace Widgets
{
/**
 * @internal
 * @short Base QML plugin for Widgets
 */
class WidgetsPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    /**
     * @internal
     * @brief Initialize engine
     * @param engine QML engine.
     * @param uri uri used in the import.
     */
    virtual void initializeEngine(QDeclarativeEngine *engine, const char *uri);
    /**
     * @short Register types
     * @param uri uri used in the import.
     */
    virtual void registerTypes(const char *uri);
};

}

#endif // WIDGETS_PLUGIN_H

