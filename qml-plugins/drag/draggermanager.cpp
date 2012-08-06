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

#include "draggermanager.h"

#include <QtCore/QHash>
#include <QtDeclarative/QDeclarativeItem>

#include "widgetproperties.h"

namespace Widgets
{

namespace Drag
{

class DraggerManagerPrivate
{
public:
    ~DraggerManagerPrivate();
    void clear();
    QHash<WidgetProperties *, QDeclarativeItem *> draggers;
};

DraggerManagerPrivate::~DraggerManagerPrivate()
{
    clear();
}

void DraggerManagerPrivate::clear()
{
    QHashIterator<WidgetProperties *, QDeclarativeItem *> iterator =
            QHashIterator<WidgetProperties *, QDeclarativeItem *>(draggers);
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

}

}
