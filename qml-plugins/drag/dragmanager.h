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

#ifndef WIDGETS_DRAG_DRAGMANAGER_H
#define WIDGETS_DRAG_DRAGMANAGER_H

#include <QtCore/QObject>
#include "widgetproperties.h"
#include "gridmanager.h"

class QDeclarativeContext;
class QDeclarativeItem;
namespace Widgets
{

namespace Drag
{

class DragManagerPrivate;
class DragManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)
    Q_PROPERTY(bool locked READ locked WRITE setLocked NOTIFY lockedChanged)
    Q_PROPERTY(Widgets::GridManager *gridManager READ gridManager WRITE setGridManager
               NOTIFY gridManagerChanged)
public:
    explicit DragManager(QObject *parent = 0);
    virtual ~DragManager();
    void setContext(QDeclarativeContext *context);
    bool busy() const;
    bool locked() const;
    GridManager * gridManager() const;
Q_SIGNALS:
    void busyChanged();
    void lockedChanged();
    void gridManagerChanged();
    void requestDisableDraggers();
    void requestCreateDragger(Widgets::WidgetProperties *widget);
    void requestDeleteDraggers();
    void widgetDragged(Widgets::WidgetProperties *widget, const QRect &rect);
public Q_SLOTS:
    void load();
    void setBusy(bool busy);
    void setLocked(bool locked);
    void setGridManager(Widgets::GridManager *gridManager);
    void drag(Widgets::WidgetProperties *widgetProperties, const QRect &rect);
    void finishDrag(Widgets::WidgetProperties *widgetProperties, QDeclarativeItem *dragger,
                    const QRect &rect);
protected:
    const QScopedPointer<DragManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DragManager)
    Q_PRIVATE_SLOT(d_func(), void createDraggers())
    Q_PRIVATE_SLOT(d_func(), void establishPageConnection())
};

}

}

#endif // WIDGETS_DRAG_DRAGMANAGER_H
