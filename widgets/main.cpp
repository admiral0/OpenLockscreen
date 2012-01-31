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

/**
 * @file widgets/main.cpp
 * @short Entry point of the application
 */
/**
 * @mainpage %Widgets
 *
 * @section appSection The application
 *
 * %Widgets is yet another widgeting system for Harmattan. It aims at creating
 * a rich and useful widgets interface. It is designed with both usability and
 * customization in mind, and tries to bring the best from all existing widget
 * systems.
 *
 * Currently, widgets tries to mimic nearly every widgeting interface and is
 * able to get both Android and Maemo home screens.
 *
 * @section apiSection API
 *
 * Creating a widget or a dock is very simple because all widgets are QML
 * based. %Widgets provides some API to extend default QML.
 *
 * These page give more information about widget creation and API.
 *
 * - @ref widgetsDocksCreation
 * - @ref basicApi
 *
 * @section thisDoc About this documentation
 *
 * This documentation provides informations for those who want to create
 * new widgets and those who want to hack and enhance %Widgets. In
 * this documentation, every class is documented. Classes that are important
 * for widget creation are documented in API page. How this app works is
 * documented in the engine page.
 *
 * These page gives more information about how %Widgets works :
 *
 * - @ref basicApi
 * - @ref engine
 */


/**
 * @page widgetsDocksCreation %Widgets and docks creation
 *
 * This page provides the basis about widget creation.
 *
 * @section widgetCreationSection Widget creation
 *
 * A widget for %Widgets is basically a QML file. Here is a basic widget :
 * @verbatim
import QtQuick 1.1
import org.sk.widgets 1.0

Widget {
    id: container
    width: 100; height: 100

    Rectangle {
        id: rect
        anchors.centerIn: parent
        width: 100; height: 100
        radius: 10
    }
}
@endverbatim
 *
 * Each widget must inherits from the "Widget" element. This element
 * provides some properties that are used by the widgeting system.
 * It can be found in the "org.sk.widgets 1.0" folder.
 *
 * @section dockCreationSection Dock creation
 *
 * Creating a dock is even more simple. The API is quite similar and
 * instead of using "Widget" as base element, the "Dock" element is used :
 *
 * @verbatim
import QtQuick 1.1
import org.sk.widgets 1.0

Dock {
    id: container
    height: 100

    Rectangle {
        anchors.fill: parent
    }
}
@endverbatim
 *
 * @section widgetsDocksPackaging Packaging widgets and docks
 *
 * In order to be distributed easily, created widgets and docks should be
 * packaged. There is no convention on what kind of package should be used.
 * It is then possible to distribute the packages in any form, even if the
 * deb package is recommanded.
 *
 * %Widgets should be installed in /opt/widgets/widgets/\<package-identifier\>/.
 * In this folder, there should be all the QML files that describes widgets and
 * docks as well as a package information file. Of cause, other files like images
 * or included QML / JS files can be put in subfolders.
 *
 * The package information file has this form :
 *
 * @verbatim
 <package id="packageIdentifier"
          name="Package name" description="Set of basic widgets.">
     <widget name="Widget 1 name"
             qmlfile="Widget1.qml"
             hassettings="false">
         <size width="200" height="200" />
     </widget>
     <widget name="Widget 2 name"
             qmlfile="Widget2.qml"
             hassettings="true">
         <size width="200" height="200" />
     </widget>
     <dock name="Dock name"
           qmlfile="Dock.qml"
           hassettings="false">
         <size width="100" heigh="100" />
         <anchors top="false" bottom="false" left="false" right="false" />
     </dock>
 </package>
@endverbatim
 *
 * Please note that the package identifier attribute must also be the name
 * of the folder where the file is.
 *
 * This information file provides information about size of widgets, or position
 * of docks. Each widget must provide a name that will be displayed in the widget
 * picker, as well as the name of the QML file associated to the widget. It also
 * have to provide information about it's maximum width and height (these parameters
 * are used to compute the size of the widget container) and if the widget has
 * a settings dialog. Note that any widgets can save settings even if they don't
 * have settings dialog.
 *
 * A dock should also provide a name and the QML file associated to it, and if it
 * has settings, but it must provide informations about it's anchoring. A widget
 * can be anchored in any edge of the screen (or can even be fullscreen). Width or
 * height are mandatory if the dock don't anchor in the left and right edges or the
 * top and bottom edge.
 *
 * @section widgetsDocksRemark Remarks
 *
 * An example of packaged widgets is in the basicwidgets folder. It is actually
 * the widgets that are provided by default by the application.
 *
 * See also @ref basicApi for %Widgets API.
 *
 * @todo Set QML properties "private" by using _
 */


/**
 * @page basicApi Basic API
 *
 * @section ApiSubsection Api
 *
 * %Widgets provides a QML global component that wrap a basic
 * API. That can be very useful for writing widgets and docks.
 * The identifier of this global component is "api"
 *
 * @subsection ApiProperties Properties
 *   - api.currentPage [const]
 *
 * Give the current displayed page. It is a number between 0 and pagesCount - 1.
 *
 *   - api.pagesCount [const]
 *
 * Gives the total number of pages.
 *
 *   - api.locked
 *
 * This property is used to check if the widgets are locked. It can be set to false
 * for unlocking widgets;
 *
 *   - api.launcherVisible
 *
 * This property is used to check if the launcher is visible. It can be set to true
 * to show and to false to hide the launcher.
 *
 * @subsection ApiFunctions Functions
 *
 *   - api.launchApplication(command)
 *
 * This function is used to run an application that is provided as
 * a command to execute.
 *
 * @section WidgetSubsection Widget
 *
 * %Widget component is used to build widgets. All widgets should inherit
 * the %Widget component.
 *
 * @subsection widgetPropertiesSubSection Properties
 *  - string identifier
 *
 * This property is used to uniquely identify the widget. It is
 * used internally. Please do not set this property as it will
 * break the entire system.
 *
 *  - bool hasBackground
 *  - color backgroundColor
 *
 * %Widgets can have a square background that covers all the surface
 * that is allocated to them. These properties can be used to enable
 * this background and setting the color.
 *
 *  - bool enabled
 *
 * %Widgets that are using resources like timers or the network should
 * be stopped when the application is not active anymore. This property
 * is used to provide information about the status of the application.
 * It is false when the application is not active. Responding to
 * changes of this variable is very important for energy efficiency.
 *
 *  - variant settings
 *
 * %Widgets can save settings that can be loaded after. This object that
 * is of type Widgets::ElementSettings is used for loading and saving
 * these settings.
 *
 * Important note : every modification of the widget's appearence should
 * be dependant on settings (and saved if they occur) since the widget
 * dragging system creates copies of the widget to drag and may not have
 * the same apparence if settings are not set.
 *
 * @subsection widgetSignalsSubSection Signals
 *  - showSettings
 *
 * This signal is used to notify the widget that the settings button
 * has been pressed. This signal should be connected to some Sheet or Dialog
 * that display the settings.
 *
 * @section dockSubsection Dock
 *
 * Dock component is used to build docks. All docks should inherit
 * the Dock component.
 *
 * @subsection dockPropertiesSubSection Properties
 *
 *  - string identifier
 *
 * This property is used to uniquely identify the dock. It is
 * used internally. Please do not set this property as it will
 * break the entire system.
 *
 *  - bool enabled
 *
 * Docks that are using resources like timers or the network should
 * be stopped when the application is not active anymore. This property
 * is used to provide information about the status of the application.
 * It is false when the application is not active. Responding to
 * changes of this variable is very important for energy efficiency.
 *
 *  - variant settings
 *
 * Docks can save settings that can be loaded after. This object that
 * is of type Widgets::ElementSettings is used for loading and saving
 * these settings.
 *
 * @subsection dockSignalsSubSection Signals
 *  - showSettings
 *
 * This signal is used to notify the dock that the settings button
 * has been pressed. This signal should be connected to some Sheet or Dialog
 * that display the settings.
 *
 * @section cppApi C++ API
 *
 * C++ classes that are available in QML context API are documented in their
 * own page :
 * - Widgets::SelectorModel
 *
 */


/**
 * @page engine Engine
 *
 * @section someNames Some names
 *
 * This widgets has many components that have (strange) names. Here
 * is a small list of important ones :
 * - (QML) Context
 * - View
 * - Grid
 * - Manager
 *
 * @subsection contextName (QML) context
 *
 * The word context, that usually means QML context, is used to describe
 * everything that is in the declarative world. Some C++ objects are
 * ported to the declarative world using either
 * QDeclarativeContext::setContextProperty() or qmlRegisterType.
 *
 * @subsection viewName View
 *
 * The view is what is displayed. In %Widgets, the view usually is the
 * widgets panels. But, in MVC world, the view is also the graphical
 * representation of things that are described in models. So the view
 * is also the name of everything that comes from models, for example
 * the QML file that implements widget selector actually implements
 * a view based on the model that describes the available widgets.
 *
 * @subsection gridName Grid
 *
 * What is called grid is the widget grid. It is where the widgets are
 * placed. There is one grid per page, and the grid is a component of
 * the widgets view (actually the most important component).
 *
 * The grid can be customized, and the size of each cell as well
 * as the margins between cells can be changed.
 *
 * @subsection managerName Manager
 *
 * A manager is a C++ object that is declared in the QML context using
 * QDeclarativeContext::setContextProperty(). Since this method can
 * only be used to declare one object at a time, the declared object
 * behaves like a global singleton. So managers are a sort of
 * singleton in QML context.
 *
 * Managers can have different roles. Most of the time, they provide
 * extended API for QML components, and are used to interact with
 * either the widget system or the whole system.
 *
 * @section engineGlobalSection Global behaviour
 *
 * This application uses heavily models. Each displayed
 * page is managed by a model, and the set of all pages
 * are again, a model. Both widgets and dock pickers are models.
 * Finally the application launcher uses a model to manage
 * the different applications.
 *
 * The models are
 * - Widgets::DisplayedPagesModel
 * - Widgets::DisplayedPage%WidgetsModel
 * - Widgets::DisplayedDocksModel
 * - Widgets::Available%WidgetsModel
 * - Widgets::AvailableDocksModel
 * - Widgets::ApplicationsModel
 *
 * Using models makes the application using less memory since
 * the delegates are destroyed when not visible. This is actually not
 * true for the widgets view because of lack of smoothness when
 * destroying and recreating the widgets all the time.
 *
 * This applications also relies heavily on C++ managers that
 * behaves like singletons in QML contexts and are used to provide
 * widget positioning, settings management, or extra features.
 *
 * The managers are
 * - Widgets::Settings
 * - Widgets::SettingsWrapper
 * - Widgets::ViewManager
 * - Widgets::PackageManager
 * - Widgets::LauncherManager
 * - Widgets::OxygenColors
 *
 * @section initialization Initialization
 *
 * Since there is a lot of things to load, the
 * initialization is quite long.
 *
 * -# Register classes to declarative context. These
 *  class are registered :
 *  - Widgets::ElementSettings
 *  - Widgets::WidgetBaseProperties
 *  - Widgets::WidgetProperties
 *  - Widgets::DockBaseProperties
 *  - Widgets::DockProperties
 *  - Widgets::ApplicationProperties
 *  - Widgets::DisplayedPage%WidgetsModel.
 *    - Remark : Widgets::DisplayedPage%WidgetsModel has to be declared because
 *      it is returned as a model data from Widgets::DisplayedPagesModel. If
 *      this class is not registered, it will not be identified in a QML
 *      context.
 *  - Widgets::Settings
      - Remark : Widgets::Settings is used for displaying informations about
        the current version.
 * -# Initialize all models and managers in this order
 *  - Widgets::OxygenColors
 *  - Widgets::PackageManager
 *   - When the package manager is initialized, it automatically loads all
 *     available packages and initialize the Widgets::Available%WidgetsModel
 *     and Widgets::AvailableDocksModel.
 *  - Widgets::DisplayedPagesModel
 *   - When the displayed pages model is initialized, it creates all the
 *     Widgets::DisplayedPage%WidgetsModel and loads all the widgets.
 *  - Widgets::DisplayedDocksModel
 *   - When the displayed docks model is initialized, it loads all
 *     the docks.
 *  - Widgets::ViewManager
 * -# Register all models and managers
 * -# QML views uses the models to display the widgets
 *
 * @section draggingManagement Dragging management
 *
 * Due to API limitations, it is impossible to set the status of a QML
 * component as dragged. It is then impossible to drag a delegate outside
 * of it's view.
 *
 * A new dragger system has been set in order to address this issue.
 * Components that can be dragged are created in a layer that is on top
 * of the views and the widgets. Each widget has it's dragger that is
 * used to move the corresponding widget. This system of draggers allows items
 * to be moved more freely.
 *
 * The draggers management are shared between two items. The DragManager
 * QML component and Widgets::ViewManager. The first is used to hold all the
 * draggers and to create them if needed. The second controls when the draggers
 * are created, and take care of the destruction of the draggers too.
 *
 * @subsection draggerCreation Dragger creation and destruction
 *
 * Creating the draggers is done in a few steps :
 * -# The widgets are unlocked : the view manager reacts and sends
 *    signals (Widgets::ViewManager::requestCreateDragger()) that are
 *    listened by the DragManager.
 * -# The drag manager creates one dragger per widget that was notified
 *    by the view manager.
 * -# The drag manager register the created draggers in the view manager,
 *    using Widgets::ViewManager::registerDragger().
 *
 * Destroying the draggers is fairly simple :
 * -# The widgets are locked : the view manager reacts and destroys the
 *    registered draggers.
 *
 * @section widgetsManagement %Widgets management
 *
 * @subsection addingWidget Adding a widget
 *
 * When the user clicks on the widget to add, there
 * are a few steps before the widget is displayed :
 * -# The view manager is queried to check if there is space
 *    available on the current screen, using
 *    Widgets::ViewManager::availableRect()
 * -# If space is available the widget is added using
 *    Widgets::DisplayedPage%WidgetsModel::addWidget().
 * -# The model is updated and updates the view. The new
 *    widget is displayed.
 * -# The model notifies the view manager that a new
 *    widget is added, and the view manager has to request
 *    the creation of a new dragger.
 *
 * @subsection removingWidget Removing a widget
 *
 * When the user clicks on the remove widget button, the
 * drag manager only needs to do two things :
 * -# Remove the widget by calling
 *    Widgets::DisplayedPage%WidgetsModel::removeWidget()
 * -# Unregister the associated dragger, by calling
 *    Widgets::ViewManager::unregisterDragger()
 *
 * @subsection movingWidget Moving a widget
 *
 * When moving a widget, this sequence of action is executed :
 * -# The dragger is being dragged. It sets the variable
 *    Widgets::ViewManager::currentDraggedWidget() in order
 *    to inform the widgets that a widget is being dragged.
 * -# The widget that have the same identifier as the one
 *    that is hold by the view manager is then hidden when
 *    a copy of the widget, which is in the WidgetDragger, is
 *    shown.
 * -# When the dragger is moved, it computes the highlight rect
 *    using the view manager. The view manager is also responsible
 *    to provide the coordinates of the highlight rect.
 * -# When the dragging ends, the widget updates the position
 *    in the page model and is visible again.
 *
 * @subsection configuringWidget Configuring a widget
 *
 * When the configure button of the dragger is clicked, this
 * happens :
 * -# The drag manager calls the show settings method using
 *    Widgets::ViewManager::showWidgetSettings()
 * -# The view manager emits a signal that is used to inform
 *    the widget that it have to show it's settings. The signal
 *    is Widgets::ViewManager::requestShowWidgetSettings()
 * -# The WidgetContainer transmits the signal to the widget
 *    using showSettings() signal.
 *
 * @section dockManagement Docks management
 *
 * @subsection addingDock Adding a dock
 *
 * Adding a dock works like adding a widget, but much
 * more simpler since it is done only in 2 setps
 * -# The dock is added using
 *    Widgets::DisplayedDocksModel::addDock().
 * -# The model is updated and updates the view.
 *
 * @subsection removingDock Removing a dock
 *
 * Removing a dock is also very simple, since it uses
 * the same process :
 * -# The dock is removed using
 *    Widgets::DisplayedDocksModel::removeDock().
 * -# The model is updated and updates the view.
 *
 * @subsection configuringDock Configuring a dock
 *
 * @todo Work in progress
 *
 */

#include "app.h"

/**
 * @short Main
 *
 * Entry point of the application.
 *
 * @param argc argc
 * @param argv argv
 * @return exit code.
 */
Q_DECL_EXPORT int main(int argc, char *argv[])
{
    Widgets::App app (argc, argv);
    return app.exec();
}
