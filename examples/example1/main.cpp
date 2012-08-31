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

/**
 * \file examples/example1/main.cpp
 * Entry point of the example 1
 */

/**
 * \page example1 Example 1: a basic widgets view
 *
 * This example describes how to create a very basic
 * widgets view.
 *
 * Please refer to
 * - main.cpp
 * - main.qml
 * - Banner.qml
 * - Button.qml
 *
 * for the examples files.
 *
 * \section example1Preparation Preparation
 *
 * \subsection example1PreparingCpp Preparing the view (C++ side)
 *
 * Some small bits of information must be provided
 * in a C++ main file in order to make a widgets view
 * working. Since libwidgets depends on QCoreApplication::organizationName()
 * and QCoreApplication::applicationName() to get settings files
 * location, these entries are mandatory, otherwise there is
 * a risk of clashing with other applications using libwidgets.
 *
 * If libwidgets is not installed in one of Qt default
 * import path, you might also need to add the correct
 * import path to the declarative engine.
 *
 * \subsection example1PreparingQml Preparing the view (QML side)
 *
 * libwidgets depends on some components that are mandatory and
 * that should be set when the view is created.
 *
 * libwidgets uses a system of providers in order to get rid of
 * location problems. Providers converts a filename with a
 * disambiguation parameter to a full path to the file. A provider
 * should be set in order to enable all the components in libwidgets
 * to work. This is done by doing
 *
 * \code{.qml}
 * Item {
 *     id: container
 *     Component.onCompleted: {
 *         ProviderManagerInstance.provider = provider
 *     }
 *     ...
 *     SomeProvider {id: provider}
 * }
 * \endcode
 *
 * libwidgets also provides, by default, a model that is a list of
 * widgets pages. Unfortunately, by default, this model have 0
 * page. In order to have at least one page, a settings object should
 * be passed to it. This is done like this (completed from the
 * previous snippet)
 *
 * \code{.qml}
 * Item {
 *     id: container
 *     Component.onCompleted: {
 *         WidgetsPageListModelInstance.settings = settings
 *         ProviderManagerInstance.provider = provider
 *     }
 *     ...
 *     SomeProvider {id: provider}
 *     Settings {
 *        id: settings
 *        defaultSettings: [
 *            SettingsEntry {
 *                group: "widgets"
 *                key: "pageCount"
 *                value: NUMBER_OF_TOTAL_PAGE
 *            },
 *            SettingsEntry {
 *                group: "widgets"
 *                key: "initialPage"
 *                value: INDEX_OF_INITIAL_PAGE
 *            }
 *        ]
 *    }
 * }
 * \endcode
 *
 * See also \ref pluginBase.
 *
 * \section example1ManagingWidgets Managing widgets
 *
 * Operations on widgets like adding and removing are simple,
 * although the function to call seems to be frightening.
 *
 * Adding a widget is done by first getting the widget to add.
 * This is done using a provider. You have to use
 * Widgets::WidgetProviderBase::widget() to get this information.
 *
 * After that, you have to use Widgets::WidgetsPageListModel::addWidget()
 * to add the widget to a given page. It needs a Widgets::GridManager, and
 * you should use the one that is shipped with the widgets view
 * (See also \ref qmlWidgetsView)
 *
 * The following JS snippet can be used to add a widget
 * \code{.js}
 * var widget = ProviderManagerInstance.provider.widget(FILENAME, DISAMBIGUATION)
 * if (!WidgetsPageListModelInstance.addWidget(0, widget, widgetsView.gridManagerInstance)) {
 *     // Something wrong happened
 * }
 * \endcode
 *
 * In the example, the widgets are not removed one by one, although if
 * it is possible. Instead, Widgets::WidgetsPageListModel::clearWidgets() is
 * called. This method simply removes all the widgets.
 *
 * \section example1CheckList Checklist
 *
 * This section lists all the things that have to be done in
 * order to create a good widgets view
 * -# Set organization and application name in C++.
 * -# Set settings and provider in QML.
 * -# Configure the provider
 */

#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeView>

/**
 * @brief main Main
 * @param argc argc.
 * @param argv argv.
 * @return exit code.
 */
int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    // Set the organization and application name
    app.setOrganizationName("SfietKonstantin");
    app.setApplicationName("widgets-example1");

    // Declare the view
    QDeclarativeView view;

    // (Optional: add an import dir to widgets plugin)
#ifdef IMPORT_DIR
    view.engine()->addImportPath(IMPORT_DIR);
#endif

    // (Optional: provide a platform indepandant way
    //  to get widgets)
    view.rootContext()->setContextProperty("WIDGETS_PROVIDER_FILE", WIDGETS_PROVIDER_FILE);

    // Set source and show
    view.setSource(QUrl(MAIN_QML_PATH));
    view.show();

    return app.exec();
}
