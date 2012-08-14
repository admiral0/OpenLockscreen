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

#ifndef WIDGETS_DRAG_CONTEXTDRAG_P_H
#define WIDGETS_DRAG_CONTEXTDRAG_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file contextdrag_p.h
 * @short Definition of Widgets::Drag::ContextDragPrivate
 */

#include "contextbase_p.h"
#include "dragmanager.h"

namespace Widgets
{

namespace Drag
{

/**
 * @internal
 * @brief Manage context for drag plugin
 *
 * This class extends Widgets::ContextBasePrivate and
 * provide unique instance of global objects for the
 * drag plugin.
 */
class ContextDragPrivate: public ContextBasePrivate
{
public:
    /**
     * @internal
     * @brief Drag manager
     *
     * Returns the drag manager registered in the provided QML
     * context. Creates it using the provided parent if no
     * drag manager was registered in the context.
     *
     * @param context QML context
     * @param parent parent object.
     * @return the drag manager.
     */
    static DragManager * dragManager(QDeclarativeContext *context, QObject *parent = 0);
};

}

}

#endif // WIDGETS_DRAG_CONTEXTDRAG_P_H
