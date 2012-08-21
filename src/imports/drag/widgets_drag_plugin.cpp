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
 * @file widgets_drag_plugin.cpp
 * @short Implementation of Widgets::Drag::WidgetsDragPlugin
 */

#include "widgets_drag_plugin.h"

#include <QtDeclarative/QtDeclarative>

#include "contextdrag_p.h"
#include "dragmanager.h"
#include "draggermanager.h"
#include "dragparameters.h"

namespace Widgets
{

namespace Drag
{

void WidgetsDragPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    ContextDragPrivate::dragManager(engine->rootContext(), this);
//    Widgets::Drag::DragManager *dragManager = new Widgets::Drag::DragManager(this);
//    dragManager->setContext(engine->rootContext());
//    engine->rootContext()->setContextProperty("DragManagerInstance", dragManager);

    Widgets::Drag::DragParameters *dragParameters = new Widgets::Drag::DragParameters(this);
    engine->rootContext()->setContextProperty("DragParametersInstance", dragParameters);
}

void WidgetsDragPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets.drag
    QString reason = "Only one instance of DragManager is allowed.";
    qmlRegisterUncreatableType<DragManager>(uri, 1, 0, "DragManager", reason);

    reason = "Only one instance of DragParameters is allowed";
    qmlRegisterUncreatableType<DragParameters>(uri, 1, 0, "DragParameters", reason);
    qmlRegisterType<DraggerManager>(uri, 1, 0, "DraggerManager");
}

}

}

Q_EXPORT_PLUGIN2(Widgets, Widgets::Drag::WidgetsDragPlugin)

