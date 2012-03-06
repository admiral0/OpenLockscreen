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

#include "oxygencolors.h"
#include "settings.h"
#include "settingsentry.h"
#include "gridmanager.h"

//class WidgetsPlugin::WidgetsPluginPrivate
//{
//public:
//    WidgetsPluginPrivate(WidgetsPlugin *parent);
//    Widgets::OxygenColors *colors;
//    Widgets::Settings *settings;
//};

//WidgetsPlugin::WidgetsPluginPrivate::WidgetsPluginPrivate(WidgetsPlugin *parent)
//{

//}

////// End of private class /////

void WidgetsPlugin::registerTypes(const char *uri)
{
    // @uri org.sk.widgets
    qmlRegisterType<Widgets::OxygenColors>(uri, 1, 0, "Colors");
    qmlRegisterType<Widgets::Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<Widgets::SettingsEntry>(uri, 1, 0, "SettingsEntry");
    qmlRegisterType<Widgets::GridManager>(uri, 1, 0, "GridManager");
}

//void WidgetsPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
//{
//    Q_UNUSED(uri)
//    engine->rootContext()->setContextProperty("Colors", d->colors);
//}

Q_EXPORT_PLUGIN2(Widgets, WidgetsPlugin)

