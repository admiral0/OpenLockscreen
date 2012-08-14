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

#ifndef WIDGETS_CONTEXTBASE_P_H
#define WIDGETS_CONTEXTBASE_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file contextbase_p.h
 * @short Definition of Widgets::ContextBasePrivate
 */

#include "providermanager.h"
#include "widgetspagelistmodel.h"

class QDeclarativeContext;
namespace Widgets
{

/**
 * @internal
 * @brief Manage context for base plugin
 *
 * This class is used to manage the QML context, and provide
 * unique instance of global objects for the base widgets plugin.
 *
 * Each static method of this class creates an instance if no instance
 * was registered in the provided context, otherwise, they return
 * the registered component in the context.
 */
class ContextBasePrivate
{
public:
    /**
     * @internal
     * @brief Provider manager
     *
     * Returns the provider manager registered in the provided QML
     * context. Creates it using the provided parent if no provider
     * manager was registered in the context.
     *
     * @param context QML context
     * @param parent parent object.
     * @return the provider manager.
     */
    static ProviderManager * providerManager(QDeclarativeContext *context, QObject *parent = 0);
    /**
     * @internal
     * @brief Widgets page list model
     *
     * Returns the widgets page list model registered in the provided QML
     * context. Creates it using the provided parent if no widgets
     * page list model was registered in the context.
     *
     * @param context QML context
     * @param parent parent object.
     * @return the widgets page list model.
     */
    static WidgetsPageListModel * widgetsPageListModel(QDeclarativeContext *context,
                                                       QObject *parent = 0);
};

}

#endif // WIDGETS_CONTEXTBASE_P_H
