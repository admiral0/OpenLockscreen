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

#ifndef WIDGETS_DRAG_DRAGGERMANAGER_H
#define WIDGETS_DRAG_DRAGGERMANAGER_H

#include <QtCore/QObject>

class QDeclarativeItem;
namespace Widgets
{

class WidgetProperties;
namespace Drag
{

class DraggerManagerPrivate;
class DraggerManager : public QObject
{
    Q_OBJECT
public:
    explicit DraggerManager(QObject *parent = 0);
    virtual ~DraggerManager();
    Q_INVOKABLE bool draggerExists(Widgets::WidgetProperties *widgetProperties);
public Q_SLOTS:
    void registerDragger(Widgets::WidgetProperties *widgetProperties, QDeclarativeItem *dragger);
    void unregisterDragger(Widgets::WidgetProperties *widgetProperties);
    void unregisterDraggers();
protected:
    const QScopedPointer<DraggerManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DraggerManager)
};

}

}

#endif // WIDGETS_DRAG_DRAGGERMANAGER_H
