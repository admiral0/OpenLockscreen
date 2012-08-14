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

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file contextdrag_p.cpp
 * @short Implementation of Widgets::Drag::ContextDragPrivate
 */

#include "contextdrag_p.h"
#include <QtDeclarative/QDeclarativeContext>

namespace Widgets
{

namespace Drag
{

DragManager * ContextDragPrivate::dragManager(QDeclarativeContext *context, QObject *parent)
{
    QVariant dragManagerVariant = context->property("DragManagerInstance");
    QObject *dragManagerObject = dragManagerVariant.value<QObject *>();
    DragManager *dragManager = qobject_cast<DragManager *>(dragManagerObject);

    if (dragManager) {
        return dragManager;
    }

    dragManager = new DragManager(parent);
    dragManager->setWidgetsPageListModel(widgetsPageListModel(context, parent));
    context->setContextProperty("DragManagerInstance", dragManager);
    return dragManager;
}

}

}
