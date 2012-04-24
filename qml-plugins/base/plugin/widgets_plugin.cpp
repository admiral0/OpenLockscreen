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
 * @short Implementation of WidgetsPlugin
 *
 * This file contains the implemetation of the
 * WidgetsPlugin class.
 */

#include "widgets_plugin.h"

#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeEngine>

#include "dockbaseproperties.h"
#include "dockproperties.h"
#include "gridmanager.h"
#include "packagemanager.h"
#include "settings.h"
#include "settingsentry.h"
#include "dockbaseproperties.h"
#include "dockproperties.h"
#include "dockmodel.h"
#include "dockmanager.h"

void WidgetsPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    engine->rootContext()->setContextProperty("PackageManagerInstance",
                                              new Widgets::PackageManager(this));

}

void WidgetsPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets
    qmlRegisterType<Widgets::Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<Widgets::SettingsEntry>(uri, 1, 0, "SettingsEntry");
    qmlRegisterType<Widgets::GridManager>(uri, 1, 0, "GridManager");
    QString reason = "Only one instance of PackageManager is allowed";
    qmlRegisterUncreatableType<Widgets::PackageManager>(uri, 1, 0, "PackageManager", reason);
    qmlRegisterType<Widgets::DockBaseProperties>(uri, 1, 0, "DockBaseProperties");
    qmlRegisterType<Widgets::DockProperties>(uri, 1, 0, "DockProperties");
    qmlRegisterType<Widgets::DockModel>(uri, 1, 0, "DockModel");
    qmlRegisterType<Widgets::DockManager>(uri, 1, 0, "DockManager");
}

Q_EXPORT_PLUGIN2(Widgets, WidgetsPlugin)

