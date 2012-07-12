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

#include "widgets_drag_plugin.h"

#include <QtDeclarative/QtDeclarative>

#include "dragmanager.h"

void WidgetsDragPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    Widgets::Drag::DragManager *dragManager = new Widgets::Drag::DragManager(this);
    dragManager->setContext(engine->rootContext());
    engine->rootContext()->setContextProperty("DragManagerInstance", dragManager);
}

void WidgetsDragPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets.drag
    QString reason = "Only one instance of DragManager is allowed.";
    qmlRegisterUncreatableType<Widgets::Drag::DragManager>(uri, 1, 0, "DragManager", reason);
}

Q_EXPORT_PLUGIN2(Widgets, WidgetsDragPlugin)

