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

#include "dragmanager.h"
#include "widgetspagelistmodel.h"

#include <QtCore/QDebug>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeItem>

namespace Widgets
{

namespace Drag
{

class DragManagerPrivate
{
public:
    DragManagerPrivate(DragManager *q);
    void establishPageConnection();
    void createDraggers();
    void slotCurrentPageChanged(int page);
    bool busy;
    bool locked;
    QDeclarativeContext *context;
    WidgetsPageListModel *widgetsPageListModel;
    GridManager *gridManager;
    QRect previousPosition;
private:
    DragManager * const q_ptr;
    Q_DECLARE_PUBLIC(DragManager)
};

DragManagerPrivate::DragManagerPrivate(DragManager *q):
    q_ptr(q)
{
    busy = false;
    locked = true;
    context = 0;
    widgetsPageListModel = 0;
    gridManager = 0;
}

void DragManagerPrivate::establishPageConnection()
{
    Q_Q(DragManager);
    int index = widgetsPageListModel->count() - 1;
    QVariant pageModelVariant = widgetsPageListModel->data(widgetsPageListModel->index(index),
                                                           WidgetsPageListModel::PageModelRole);
    WidgetsPageModel *pageModel = pageModelVariant.value<WidgetsPageModel *>();
    q->connect(pageModel, SIGNAL(countChanged(int)), q, SLOT(createDraggers()));

}

void DragManagerPrivate::createDraggers()
{
    Q_Q(DragManager);
    if (locked) {
        return;
    }
    emit q->requestDisableDraggers();

    int currentIndex = widgetsPageListModel->currentPage();
    QVariant modelVariant = widgetsPageListModel->data(widgetsPageListModel->index(currentIndex),
                                                       WidgetsPageListModel::PageModelRole);
    WidgetsPageModel *model = modelVariant.value<WidgetsPageModel *>();
    if (!model) {
        return;
    }

    for (int i = 0; i < model->rowCount(); i++) {
        QVariant widgetVariant = model->data(model->index(i), WidgetsPageModel::WidgetRole);
        WidgetProperties *widget = widgetVariant.value<WidgetProperties *>();
        emit q->requestCreateDragger(widget);
    }
}

////// End of private class //////

DragManager::DragManager(QObject *parent) :
    QObject(parent), d_ptr(new DragManagerPrivate(this))
{
}

DragManager::~DragManager()
{
}

void DragManager::setContext(QDeclarativeContext *context)
{
    Q_D(DragManager);
    d->context = context;
    load();
}

bool DragManager::busy() const
{
    Q_D(const DragManager);
    return d->busy;
}

bool DragManager::locked() const
{
    Q_D(const DragManager);
    return d->locked;
}

GridManager * DragManager::gridManager() const
{
    Q_D(const DragManager);
    return d->gridManager;
}

void DragManager::load()
{
    Q_D(DragManager);
    if (d->context == 0) {
        return;
    }

    if (d->widgetsPageListModel == 0) {

        QVariant pageListModelVariant = d->context->contextProperty("WidgetsPageListModelInstance");
        QObject *pageListModelObject
                = qobject_cast<QObject *>(pageListModelVariant.value<QObject *>());
        WidgetsPageListModel *pageListModel
                = qobject_cast<WidgetsPageListModel *>(pageListModelObject);

        if (pageListModel == 0) {
            return;
        }

        d->widgetsPageListModel = pageListModel;
        // Connections
        connect(d->widgetsPageListModel, SIGNAL(countChanged(int)),
                this, SLOT(establishPageConnection()));
    }
}

void DragManager::setBusy(bool busy)
{
    Q_D(DragManager);
    if (d->busy != busy) {
        d->busy = busy;
        emit busyChanged();
    }

    if (busy) {
        emit requestDisableDraggers();
    } else {
        if (!locked()) {
            d->createDraggers();
        }
    }
}

void DragManager::setLocked(bool locked)
{
    Q_D(DragManager);
    if (d->locked != locked) {
        d->locked = locked;
        emit lockedChanged();
    }

    if (!d->locked) {
        d->createDraggers();
    } else {
        emit requestDeleteDraggers();
    }
}

void DragManager::setGridManager(GridManager *gridManager)
{
    Q_D(DragManager);
    if (d->gridManager != gridManager) {
        d->gridManager = gridManager;
        emit gridManagerChanged();
    }
}

void DragManager::drag(WidgetProperties *widgetProperties, const QRect &rect)
{
    Q_D(DragManager);
    widgetProperties->setVisible(false);

    if (!d->gridManager) {
        return;
    }

    QRect currentPosition = d->gridManager->fit(rect);
    if (d->previousPosition != currentPosition) {
        d->previousPosition = currentPosition;

        emit widgetDragged(widgetProperties, currentPosition);
    }

}

void DragManager::finishDrag(WidgetProperties *widgetProperties, QDeclarativeItem *dragger,
                             const QRect &rect)
{
    Q_D(DragManager);
    if (!d->gridManager) {
        return;
    }

    QRect currentPosition = d->gridManager->fit(rect);
    widgetProperties->setX(currentPosition.x());
    widgetProperties->setY(currentPosition.y());
    widgetProperties->setWidth(currentPosition.width());
    widgetProperties->setHeight(currentPosition.height());
    widgetProperties->setVisible(true);

    dragger->setX(currentPosition.x());
    dragger->setY(currentPosition.y());
    dragger->setWidth(currentPosition.width());
    dragger->setHeight(currentPosition.height());

    d->previousPosition = QRect();

    emit widgetDragged(0, QRect(0, 0, 0, 0));
}

}

}

#include "moc_dragmanager.cpp"
