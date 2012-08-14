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
 * @file contextbase_p.cpp
 * @short Implementation of Widgets::ContextBasePrivate
 */

#include "contextbase_p.h"

#include <QtDeclarative/QDeclarativeContext>

namespace Widgets
{

ProviderManager * ContextBase::providerManager(QDeclarativeContext *context, QObject *parent)
{
    QVariant providerManagerVariant = context->property("ProviderManagerInstance");
    QObject *providerManagerObject = providerManagerVariant.value<QObject *>();
    ProviderManager *providerManager = qobject_cast<ProviderManager *>(providerManagerObject);

    if (providerManager) {
        return providerManager;
    }

    providerManager = new ProviderManager(parent);
    context->setContextProperty("ProviderManagerInstance", providerManager);
    return providerManager;
}

WidgetsPageListModel * ContextBase::widgetsPageListModel(QDeclarativeContext *context,
                                                         QObject *parent)
{
    QVariant modelVariant = context->property("WidgetsPageListModelInstance");
    QObject *modelObject = modelVariant.value<QObject *>();
    WidgetsPageListModel *model = qobject_cast<WidgetsPageListModel *>(modelObject);

    if (model) {
        return model;
    }

    model = new WidgetsPageListModel(parent);
    model->setProviderManager(providerManager(context, parent));
    context->setContextProperty("WidgetsPageListModelInstance", model);
    return model;
}

WidgetConfigurationHelper * ContextBase::widgetConfigurationHelper(QDeclarativeContext *context,
                                                                     QObject *parent)
{
    QVariant managerVariant = context->property("WidgetConfigurationHelperInstance");
    QObject *managerObject = managerVariant.value<QObject *>();
    WidgetConfigurationHelper *manager = qobject_cast<WidgetConfigurationHelper *>(managerObject);

    if (manager) {
        return manager;
    }

    manager = new WidgetConfigurationHelper(parent);
    context->setContextProperty("WidgetConfigurationHelperInstance", manager);
    return manager;
}

}
