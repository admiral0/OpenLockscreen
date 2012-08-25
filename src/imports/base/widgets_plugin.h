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
 * be used. Here is a small list of the features
 * - Displaying widgets in pages
 * - Alignment in a grid
 * - Docks to display tools
 * - Moving widgets
 *
 * \section gettingStarted Getting started
 * - \subpage writeWidgetsAndDocks
 * - \subpage tutorials
 * - \subpage pluginList
 *
 * \section Internals
 *
 * See \subpage internals for more information.
 */
/**
 * \page writeWidgetsAndDocks Write widgets and docks
 *
 * Information about widgets and docks creation are in
 * the main page of their respective plugin:
 * - \ref pluginBaseWriteWidget
 * - \ref pluginDocksWriteDock
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
 * - \subpage pluginDocks
 * - \subpage pluginDrag
 * - \subpage pluginInfo
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
 * \section pluginBaseComponents Components
 *
 * \subsection pluginBaseComponents Components
 *
 * This plugin provides several components, that are all related to
 * basic widgets management. The following C++ components are declared
 *
 * - Widgets::Settings
 * - Widgets::SettingsEntry
 * - Widgets::EventTimer
 *
 * And the following QML components are declared
 *
 * - \ref qmlWidget
 * - \ref qmlSettingsItem
 * - \ref qmlWidgetsPage
 * - \ref qmlWidgetsView
 * - \ref qmlWidgetsHorizontalPageView
 *
 * See also \subpage pluginBaseQmlComponents for the list of declared QML
 * components.
 *
 * \subsection pluginBaseGlobalInstance Global instance
 *
 * In addition to those components, importing this plugin also set
 * global instances of important classes.
 *
 * - \b WidgetConfigurationHelperInstance
 *
 * \section pluginBaseWriteWidget Writing your widget
 *
 * \subsection pluginBaseWriteWidgetWidget Write a widget
 *
 * A widget is very simple to write, since it is a simple QML Item
 * component. It have a some more properties, that are used to
 * make them customizable (see \ref qmlWidget).
 *
 * Be sure to set either the size or the minimum and maximum
 * size of the widget, or the widget would not be correct, and
 * would not be recognized.
 *
 * You can use several files for your widget, but be sure to
 * register the base widget file to a provider (see \ref providers
 * for more information).
 *
 * \subsection pluginBaseWriteWidgetSettings Write a widget settings
 *
 * Writing a widget settings is a bit trickier. Since QML do not
 * manage complex C++ types very nicely, it is hard to pass variant-map
 * to the property system.
 *
 * To avoid that, a helper system has been made, and the global
 * instance \b WidgetConfigurationHelperInstance is used to help
 * managing settings.
 *
 * When you create a widget settings components, you have to
 * subclass the \ref qmlSettingsItem element. This element have
 * a property where current settings are passed.
 *
 * When you want to save settings, you have to ask the configuration
 * helper using Widgets::WidgetConfigurationHelper::saveSettings().
 * You might also react from Widgets::WidgetConfigurationHelper::saveSettingsRequested()
 * signal to save your settings.
 */
/**
 * \page internals Internals
 *
 * This page list all the pages that describes the internals of
 * the different plugins
 *
 * - \subpage pluginBaseInternals
 */
/**
 *
 * \page pluginBaseInternals Base QML plugin for widgets
 *
 * \section pluginBaseInternalComponents Internal components
 *
 * These components should not be used by the developer that want
 * to take advantage of libwidgets, but by those that want to extend
 * it.
 *
 * - Widgets::GridManager
 * - Widgets::ProviderManager
 * - Widgets::WidgetBaseProperties
 * - Widgets::WidgetProperties
 * - \ref qmlWidgetContainer
 *
 * These global instances are also set
 * - \b WidgetsPageListModelInstance
 * - \b ProviderManagerInstance
 *
 * \section pluginBaseInternalWidgetSystem The widgets system
 *
 * Instances of widgets are controlled by models, that
 * contains the type, the position, and some settings of
 * all widgets in a given page.
 *
 * The global \b WidgetsPageListModelInstance is the model
 * that represents all the pages in the widgets view. It is
 * an instance of Widgets::WidgetsPageListModel and
 * is actually used to store models, that are instances of
 * Widgets::WidgetsPageModel.
 *
 * The page model stores widgets properties using
 * Widgets::WidgetProperties, that contains all information
 * required to create widgets, including position and settings.
 *
 * These objects are created using Widgets::WidgetBaseProperties,
 * that only contain the basic information of the widget, such as
 * the size and the file name.
 *
 * All the models are also used to store settings related to
 * widgets, and do this in an automated way. Settings are
 * stored using QDesktopServices::DataLocation.
 */
/**
 * @page pluginBaseQmlComponents QML components
 *
 * \section qmlWidget Widget
 *
 * \b Widget is the base QML component that is used to
 * represent a widget. All widgets used in libwidgets have
 * to have this component as a parent.
 *
 * While writing a widget, you should always provide at least
 * the size of the widget, using \b width and \b height. You
 * might also provide the minimum and maximum size, but this
 * feature is not yet used, and the widget will take the minimum
 * size.
 *
 * Widget inherits from Item, so you should also see documentation
 * for Item.
 *
 * \subsection qmlWidgetProperties Properties
 *
 * - \b enabled
 *
 * This property is used to notify if the widget should be enabled
 * and thus, do heavy processing or should be suspended.
 *
 * - \b settings
 *
 * This property holds the widget properties, that are passed as
 * a variant-map. On QML side, settings can be accessed as an object.
 *
 * - \b minimumWidth
 * - \b minimumHeight
 * - \b maximumWidth
 * - \b maximumHeight
 *
 * These properties hold the range of size that the widget can
 * take. They are currently unused.
 *
 * \section qmlSettingsItem SettingsItem
 *
 * This component is used as a base for components that are used
 * to represent settings panel, and that provides settings to
 * the widget.
 *
 * SettingsItem inherits from Item, so you should also see documentation
 * for Item.
 *
 * \subsection qmlSettingsItemProperties Properties
 *
 * - \b settings
 *
 * This property hold the current settings that the widget have. They
 * cannot be modified on their own, so you should use the helper to
 * set them. See \ref pluginBaseWriteWidgetSettings for more information.
 *
 * \section qmlWidgetsPage WidgetsPage
 *
 * The widget page is used to hold a page of widgets. It can be used to
 * implement a view with ease.
 *
 * WidgetsPage inherits from Item, so you should also see documentation
 * for Item.
 *
 * \subsection qmlWidgetsPageProperties Properties
 *
 * - \b pageModel
 *
 * This property is the model used to draw the widgets. It should be
 * a Widgets::WidgetsPageModel.
 *
 * \section qmlWidgetsView WidgetsView
 *
 * The widgets view is a view that provide some important components
 * for displaying widgets. It manages a grid manager and provides
 * settings to setup it.
 *
 * It also creates an item that is used to contain the widgets view,
 * and take the size of the grid in account.
 *
 * WidgetsView inherits from Item, so you should also see documentation
 * for Item.
 *
 * \subsection qmlWidgetsViewProperties Properties
 *
 * - \b gridManagerInstance
 *
 * This property holds the grid manager instance that this view uses
 * to manage the grid. It can be very useful for layouting widgets. It
 * is used, for example, by the drag manager to compute the correct
 * position of widgets.
 *
 * - \b content
 *
 * Content of the view. This property should be set to an item that
 * contains the implementation of the widgets view.
 *
 * - \b contentItem
 *
 * This property holds the item that is used to contain the widgets view.
 * It is provided only for indicating the position of the content. In
 * order to set a content, the \e content property should be used.
 *
 * - \b busy
 *
 * This property is used to indicate that the view is busy, for example
 * if it is scrolled. While busy, some indicators, like the drag indicators,
 * should not be displayed.
 *
 * While implementing a view, this property should be set while the view
 * is busy, in order to avoid some graphical glitches, like drag indicators
 * that are not synced with the view.
 *
 * \section qmlWidgetsHorizontalPageView WidgetsHorizontalPageView
 *
 * Inherits from \ref qmlWidgetsView.
 *
 * The horizontal page view is an implementation of a view, providing
 * many pages that can be scrolled horizontally. In most of the cases,
 * this component should be used to display widgets.
 *
 * \subsection qmlWidgetsHorizontalPageViewProperties Properties
 *
 * - \b view
 *
 * This property provides the QML ListView that is used to display the
 * different pages. This view can be used, for example, by a background
 * that have a parallax effect.
 *
 * - \b initialized() [signal]
 *
 * This signal is emitted when the view is initialized. It can be used, for
 * example, by a background that have a parallax effect, in order to take
 * in account the initialX offset.
 *
 * \section qmlWidgetContainer [Internal] WidgetContainer
 *
 * This component is used internally to create the widget to display.
 * It also creates a dummy widget when the widget failed to be loaded.
 */
/**
 * @short Namespace for base plugin
 */
namespace Widgets
{
/**
 * @internal
 * @short Base QML plugin for widgets
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
     * @internal
     * @short Register types
     * @param uri uri used in the import.
     */
    virtual void registerTypes(const char *uri);
};

}

#endif // WIDGETS_PLUGIN_H

