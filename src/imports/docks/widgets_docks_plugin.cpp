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
 * @file widgets_docks_plugin.cpp
 * @short Implementation of Widgets::Docks::WidgetsDocksPlugin
 */

#include "widgets_docks_plugin.h"

#include <QtDeclarative/QtDeclarative>

#include "contextdocks_p.h"
#include "dockbaseproperties.h"
#include "dockproperties.h"
#include "dockedviewmanager.h"
#include "dockmodel.h"

namespace Widgets
{

namespace Docks
{

void WidgetsDocksPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    ContextDocksPrivate::dockModel(engine->rootContext(), this);
    ContextDocksPrivate::dockedViewManager(engine->rootContext(), this);
}

void WidgetsDocksPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets.docks
    qmlRegisterType<DockBaseProperties>(uri, 1, 0, "DockBaseProperties");
    qmlRegisterType<DockProperties>(uri, 1, 0, "DockProperties");
    QString reason = "Only one instance of DockManager is allowed.";
    qmlRegisterUncreatableType<DockedViewManager>(uri, 1, 0, "DockedViewManager",
                                                                  reason);
    reason = "Only one instance of DockModel is allowed.";
    qmlRegisterUncreatableType<DockModel>(uri, 1, 0, "DockModel", reason);
}

}

}

Q_EXPORT_PLUGIN2(Widgets, Widgets::Docks::WidgetsDocksPlugin)

