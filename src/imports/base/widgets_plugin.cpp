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

#include "contextbase_p.h"
#include "widgetbaseproperties.h"
#include "widgetproperties.h"
#include "gridmanager.h"
#include "settings.h"
#include "settingsentry.h"
#include "widgetspagelistmodel.h"
#include "providermanager.h"
#include "widgetproviderbase.h"
#include "eventtimer.h"

namespace Widgets
{

void WidgetsPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri);

    ContextBase::providerManager(engine->rootContext(), this);
    ContextBase::widgetsPageListModel(engine->rootContext(), this);
    ContextBase::widgetConfigurationHelper(engine->rootContext(), this);
}

void WidgetsPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets
    qmlRegisterType<Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<SettingsEntry>(uri, 1, 0, "SettingsEntry");
    qmlRegisterType<GridManager>(uri, 1, 0, "GridManager");
    QString reason = "Only one instance of ProviderManager is allowed";
    qmlRegisterUncreatableType<ProviderManager>(uri, 1, 0, "ProviderManager", reason);
    qmlRegisterType<WidgetBaseProperties>(uri, 1, 0, "WidgetBaseProperties");
    qmlRegisterType<WidgetProperties>(uri, 1, 0, "WidgetProperties");
    reason = "Only one instance of WidgetsPageListModel is allowed";
    qmlRegisterUncreatableType<WidgetsPageListModel>(uri, 1, 0, "WidgetsPageListModel", reason);
    qmlRegisterType<WidgetsPageModel>(uri, 1, 0, "WidgetsPageModel");
    reason = "This provider is invalid";
    qmlRegisterUncreatableType<WidgetProviderBase>(uri, 1, 0, "WidgetProviderBase", reason);
    qmlRegisterType<EventTimer>(uri, 1, 0, "EventTimer");
}

}

Q_EXPORT_PLUGIN2(Widgets, Widgets::WidgetsPlugin)

