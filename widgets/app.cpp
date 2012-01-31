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
 * @file app.cpp
 * @short Implementation of Widgets::App
 *
 * This file contains the implemetation of the
 * Widgets::App class and the declaration and
 * implementation of Widgets::App::AppPrivate.
 */

#include "app.h"
#include "oxygencolors.h"
#include "settingswithdefault.h"
#include "settingswrapper.h"
#include "elementsettings.h"
#include "widgetbaseproperties.h"
#include "widgetproperties.h"
#include "dockbaseproperties.h"
#include "dockproperties.h"
#include "applicationinformations.h"
#include "viewmanager.h"
#include "displayedpagesmodel.h"
#include "displayedpagewidgetsmodel.h"
#include "displayeddocksmodel.h"
#include "availablewidgetsmodel.h"
#include "availabledocksmodel.h"
#include "packagemanager.h"
#include "applicationsmodel.h"
#include "launchermanager.h"

#include "qplatformdefs.h"
#include <QtCore/QDir>
#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>

#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @internal
 * @short Private class for App
 */
class App::AppPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param parent parent Q-pointer.
     */
    AppPrivate(App *parent);
    /**
     * @short Destructor
     */
    ~AppPrivate();
    /**
     * @short Register QML types
     *
     * This method is used to load the
     * types that will be used in QML context.
     */
    static void registerQmlTypes();
    /**
     * @short Initialize objects
     *
     * This method is used to initialize
     * the objects in the private class and
     * establish connections if needed.
     */
    void initializeObjects();
    /**
     * @short Setup view
     *
     * This method is used to prepare the QML view
     * by settings context components, as well as
     * loading the main QML file.
     */
    void setupView();
    /**
     * @short Show view
     *
     * Display the QML view. Depending on the
     * platform, the view should be either
     * full screen or windowed.
     */
    void showView();
    /**
     * @short QML declarative view
     */
    QDeclarativeView *view;
    /**
     * @short Colors
     */
    OxygenColors *colors;
    /**
     * @short %Settings
     */
    Settings *settings;
    /**
     * @short Wrapper for view settings
     */
    SettingsWrapper *settingsWrapper;
    /**
     * @short Package manager
     */
    PackageManager *packageManager;
    /**
     * @short Displayed pages
     */
    DisplayedPagesModel *displayedPagesModel;
    /**
     * @short Displayed docks
     */
    DisplayedDocksModel *displayedDocksModel;
    /**
     * @short View manager
     */
    ViewManager *viewManager;
    /**
     * @short Applications model
     */
    ApplicationsModel *applicationsModel;
    /**
     * @short Launcher manager
     */
    LauncherManager *launcherManager;

private:
    /**
     * @short Q-pointer
     */
    App * const q;
};

App::AppPrivate::AppPrivate(App *parent):
    q(parent)
{
    // Delay objects initializations
    // (Settings needs application name first)
    // Initialization is done with initializeObjects()
    view = 0;
    colors = 0;
    settings = 0;
    settingsWrapper = 0;
    packageManager = 0;
    displayedPagesModel = 0;
    displayedDocksModel = 0;
    viewManager = 0;
    applicationsModel = 0;
    launcherManager = 0;
}

App::AppPrivate::~AppPrivate()
{
    delete colors;
    view->deleteLater();
}

void App::AppPrivate::registerQmlTypes()
{
    qmlRegisterType<Widgets::ElementSettings>("org.sk.widgets", 1, 0, "ElementSettings");
    qmlRegisterType<Widgets::WidgetBaseProperties>("org.sk.widgets", 1, 0, "WidgetBaseProperties");
    qmlRegisterType<Widgets::WidgetProperties>("org.sk.widgets", 1, 0, "WidgetProperties");
    qmlRegisterType<Widgets::DockBaseProperties>("org.sk.widgets", 1, 0, "DockBaseProperties");
    qmlRegisterType<Widgets::DockProperties>("org.sk.widgets", 1, 0, "DockProperties");
    qmlRegisterType<Widgets::ApplicationInformations>("org.sk.widgets", 1, 0,
                                                      "ApplicationInformations");
    qmlRegisterType<Widgets::FolderModel>("org.sk.widgets", 1, 0, "FolderModel");
    qmlRegisterType<Widgets::DisplayedPageWidgetsModel>("org.sk.widgets", 1, 0,
                                                        "DisplayedPageWidgetsModel");
    qmlRegisterType<Widgets::Settings>("org.sk.widgets", 1, 0, "Settings");
}

void App::AppPrivate::initializeObjects()
{
    // Initialize objects
    view = new QDeclarativeView();
    colors = new OxygenColors();
    settings = new SettingsWithDefault(q);
    settingsWrapper = new SettingsWrapper(settings, q);
    packageManager = new PackageManager(q);
    displayedPagesModel = new DisplayedPagesModel(settings, packageManager, q);
    displayedDocksModel = new DisplayedDocksModel(settings, packageManager, q);
    viewManager = new ViewManager(settingsWrapper, displayedPagesModel, q);
    applicationsModel = new ApplicationsModel(q);
    launcherManager = new LauncherManager(q);

    // Load default settings
    settings->setDefaultSettings();

    // Pages
    displayedPagesModel->setPageCount(settings->value("view/pageCount").toInt());
}

void App::AppPrivate::setupView()
{
    // Context properties
    QDeclarativeContext *context = view->rootContext();
    context->setContextProperty("colors", colors);
    context->setContextProperty("settings", settings);
    context->setContextProperty("settingsWrapper", settingsWrapper);
    context->setContextProperty("packageManager", packageManager);
    context->setContextProperty("availableWidgetsModel", packageManager->availableWidgetsModel());
    context->setContextProperty("availableDocksModel", packageManager->availableDocksModel());
    context->setContextProperty("displayedPagesModel", displayedPagesModel);
    context->setContextProperty("displayedDocksModel", displayedDocksModel);
    context->setContextProperty("viewManager", viewManager);
    context->setContextProperty("applicationsModel", applicationsModel);
    context->setContextProperty("launcherManager", launcherManager);

    // QML file
    QDir qmlPath = QDir(q->applicationDirPath());
    qmlPath.cdUp();
    qmlPath.cd("qml");
    view->setSource(QUrl(qmlPath.absoluteFilePath("main.qml")));
}

void App::AppPrivate::showView()
{
#ifdef MEEGO_EDITION_HARMATTAN
    view->showFullScreen();
#else
    view->show();
#endif
}

////// End of private class //////

App::App(int &argc, char **argv):
    QApplication(argc, argv), d(new AppPrivate(this))
{
    setOrganizationName("sk");
    setApplicationName("Widgets");

    d->registerQmlTypes();
    d->initializeObjects();
    d->setupView();
    d->showView();
}

App::~App()
{
    delete d;
}

}
