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

/**
 * @file draggermanager.cpp
 * @short Implementation of Widgets::Drag::DraggerManager
 */


#include "draggermanager.h"

#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtDeclarative/QDeclarativeItem>

#include "widgetproperties.h"

namespace Widgets
{

namespace Drag
{

/**
 * @internal
 * @short Private class for Widgets::Drag::DraggerManager
 */
class DraggerManagerPrivate
{
public:
    /**
     * @internal
     * @short Destructor
     */
    ~DraggerManagerPrivate();
    /**
     * @internal
     * @brief Clear
     *
     * This method clears the draggers container, and
     * delete them.
     */
    void clear();
    /**
     * @internal
     * @brief Data
     */
    QMap<WidgetProperties *, QDeclarativeItem *> draggers;
};

DraggerManagerPrivate::~DraggerManagerPrivate()
{
    clear();
}

void DraggerManagerPrivate::clear()
{
    QMapIterator<WidgetProperties *, QDeclarativeItem *> iterator =
            QMapIterator<WidgetProperties *, QDeclarativeItem *>(draggers);
    while (iterator.hasNext()) {
        iterator.next();
        iterator.value()->deleteLater();
    }
    draggers.clear();
}

////// End of private class //////

DraggerManager::DraggerManager(QObject *parent):
    QObject(parent), d_ptr(new DraggerManagerPrivate())
{
}

DraggerManager::~DraggerManager()
{
}

bool DraggerManager::draggerExists(WidgetProperties *widgetProperties)
{
    Q_D(DraggerManager);
    return (d->draggers.contains(widgetProperties));
}

void DraggerManager::registerDragger(WidgetProperties *widgetProperties, QDeclarativeItem *dragger)
{
    Q_D(DraggerManager);
    if (draggerExists(widgetProperties)) {
        d->draggers.value(widgetProperties)->setVisible(true);
        dragger->deleteLater();
        return;
    }
    d->draggers.insert(widgetProperties, dragger);
}

void DraggerManager::unregisterDragger(WidgetProperties *widgetProperties)
{
    Q_D(DraggerManager);
    if (!draggerExists(widgetProperties)) {
        return;
    }
    d->draggers.value(widgetProperties)->deleteLater();
    d->draggers.remove(widgetProperties);
}

void DraggerManager::unregisterDraggers()
{
    Q_D(DraggerManager);
    d->clear();
}

void DraggerManager::disableDraggers()
{
    Q_D(DraggerManager);
    QMapIterator<WidgetProperties *, QDeclarativeItem *> iterator =
            QMapIterator<WidgetProperties *, QDeclarativeItem *>(d->draggers);
    while (iterator.hasNext()) {
        iterator.next();
        iterator.value()->setVisible(false);
    }
}

}

}
