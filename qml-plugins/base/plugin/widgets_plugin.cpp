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
 * @file widgets_plugin.cpp
 * @short Implementation of Widgets::WidgetsPlugin
 */

#include "widgets_plugin.h"

#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeEngine>

//#include "dockbaseproperties.h"
//#include "dockproperties.h"
//#include "widgetbaseproperties.h"
//#include "widgetproperties.h"
#include "gridmanager.h"
//#include "packagemanager.h"
#include "settings.h"
#include "settingsentry.h"
//#include "filterconditionlist.h"
//#include "filtercondition.h"
//#include "widgetspagelistmodel.h"
//#include "configurationmanager.h"

namespace Widgets
{

void WidgetsPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
//    Widgets::PackageManager *packageManager = new Widgets::PackageManager(this);
//    Widgets::WidgetsPageListModel *widgetsPageListModel = new Widgets::WidgetsPageListModel(this);
//    widgetsPageListModel->setPackageManager(packageManager);

//    Widgets::ConfigurationManager *configurationManager = new Widgets::ConfigurationManager(this);

//    engine->rootContext()->setContextProperty("PackageManagerInstance", packageManager);
//    engine->rootContext()->setContextProperty("WidgetsPageListModelInstance", widgetsPageListModel);
//    engine->rootContext()->setContextProperty("ConfigurationManagerInstance", configurationManager);
}

void WidgetsPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets
    qmlRegisterType<Widgets::Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<Widgets::SettingsEntry>(uri, 1, 0, "SettingsEntry");
    qmlRegisterType<Widgets::GridManager>(uri, 1, 0, "GridManager");
//    QString reason = "Only one instance of PackageManager is allowed";
//    qmlRegisterUncreatableType<Widgets::PackageManager>(uri, 1, 0, "PackageManager", reason);
//    qmlRegisterType<Widgets::FilterConditionList>(uri, 1, 0,"FilterConditionList");
//    qmlRegisterType<Widgets::FilterCondition>(uri, 1, 0,"FilterCondition");
//    qmlRegisterType<Widgets::DockBaseProperties>(uri, 1, 0, "DockBaseProperties");
//    qmlRegisterType<Widgets::DockProperties>(uri, 1, 0, "DockProperties");
//    qmlRegisterType<Widgets::WidgetBaseProperties>(uri, 1, 0, "WidgetBaseProperties");
//    qmlRegisterType<Widgets::WidgetProperties>(uri, 1, 0, "WidgetProperties");
//    reason = "Only one instance of WidgetsPageListModel is allowed";
//    qmlRegisterUncreatableType<Widgets::WidgetsPageListModel>(uri, 1, 0,
//                                                              "WidgetsPageListModel", reason);
//    qmlRegisterType<Widgets::WidgetsPageModel>(uri, 1, 0, "WidgetsPageModel");
//    reason = "Only one instance of ConfigurationManager is allowed";
//    qmlRegisterUncreatableType<Widgets::ConfigurationManager>(uri, 1, 0,
//                                                              "ConfigurationManager", reason);
}

}

Q_EXPORT_PLUGIN2(Widgets, Widgets::WidgetsPlugin)

