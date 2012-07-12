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

#include "widgets_docks_plugin.h"

#include <QtDeclarative/QtDeclarative>

#include "dockmanager.h"
#include "dockmodel.h"

void WidgetsDocksPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    Widgets::Docks::DockModel *model = new Widgets::Docks::DockModel(this);
    model->setContext(engine->rootContext());
    engine->rootContext()->setContextProperty("DockModelInstance", model);
    Widgets::Docks::DockManager *manager = new Widgets::Docks::DockManager(this);
    manager->setDockModel(model);
    engine->rootContext()->setContextProperty("DockManagerInstance", manager);
}

void WidgetsDocksPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets.docks
    QString reason = "Only one instance of DockManager is allowed.";
    qmlRegisterUncreatableType<Widgets::Docks::DockManager>(uri, 1, 0, "DockManager", reason);
    reason = "Only one instance of DockModel is allowed.";
    qmlRegisterUncreatableType<Widgets::Docks::DockModel>(uri, 1, 0, "DockModel", reason);
}

Q_EXPORT_PLUGIN2(Widgets, WidgetsDocksPlugin)

