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

#ifndef WIDGETS_DOCKS_CONTEXTDOCKS_P_H
#define WIDGETS_DOCKS_CONTEXTDOCKS_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file contextdocks_p.h
 * @short Definition of Widgets::Docks::ContextDocksPrivate
 */

#include "contextbase_p.h"
#include "dockmodel.h"
#include "dockedviewmanager.h"

namespace Widgets
{

namespace Docks
{

/**
 * @internal
 * @brief Manage context for docks plugin
 *
 * This class extends Widgets::ContextBasePrivate and
 * provide unique instance of global objects for the
 * docks plugin.
 */
class ContextDocksPrivate: public ContextBasePrivate
{
public:
    /**
     * @brief Dock model
     *
     * Returns the dock model registered in the provided QML
     * context. Creates it using the provided parent if no
     * dock model was registered in the context.
     *
     * @param context QML context
     * @param parent parent object.
     * @return the dock model.
     */
    static DockModel * dockModel(QDeclarativeContext *context, QObject *parent = 0);
    /**
     * @brief Docked view manager
     *
     * Returns the docked view manager registered in the provided QML
     * context. Creates it using the provided parent if no
     * docked view manager was registered in the context.
     *
     * @param context QML context
     * @param parent parent object.
     * @return the dock model.
     */
    static DockedViewManager * dockedViewManager(QDeclarativeContext *context, QObject *parent = 0);
};

}

}

#endif // WIDGETS_DOCKS_CONTEXTDOCKS_P_H
