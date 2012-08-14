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
 * @file contextdocks_p.cpp
 * @short Implementation of Widgets::Docks::ContextDocksPrivate
 */

#include "contextdocks_p.h"

#include <QtDeclarative/QDeclarativeContext>

namespace Widgets
{

namespace Docks
{

DockModel * ContextDocksPrivate::dockModel(QDeclarativeContext *context, QObject *parent)
{
    QVariant modelVariant = context->property("DockModelInstance");
    QObject *modelObject = modelVariant.value<QObject *>();
    DockModel *model = qobject_cast<DockModel *>(modelObject);

    if (model) {
        return model;
    }


    model = new DockModel(parent);
    model->setProviderManager(providerManager(context, parent));
    context->setContextProperty("DockModelInstance", model);

    return model;
}

DockedViewManager * ContextDocksPrivate::dockedViewManager(QDeclarativeContext *context,
                                                           QObject *parent)
{
    QVariant managerVariant = context->property("DockedViewManagerInstance");
    QObject *managerObject = managerVariant.value<QObject *>();
    DockedViewManager *manager = qobject_cast<DockedViewManager *>(managerObject);

    if (manager) {
        return manager;
    }

    manager = new DockedViewManager(parent);
    manager->setDockModel(dockModel(context, parent));
    context->setContextProperty("DockedViewManagerInstance", manager);
    return manager;
}

}

}
