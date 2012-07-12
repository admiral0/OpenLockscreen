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

namespace Widgets
{

namespace Drag
{

class DragManagerPrivate
{
public:
    DragManagerPrivate(DragManager *q);
    void createDraggers();
    bool locked;
    QDeclarativeContext *context;
    WidgetsPageListModel *widgetsPageListModel;
private:
    DragManager * const q_ptr;
    Q_DECLARE_PUBLIC(DragManager)
};

DragManagerPrivate::DragManagerPrivate(DragManager *q):
    q_ptr(q)
{
    locked = true;
    context = 0;
    widgetsPageListModel = 0;
}

void DragManagerPrivate::createDraggers()
{
    Q_Q(DragManager);
    int currentIndex = widgetsPageListModel->currentPage();
    qDebug() << currentIndex;

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

bool DragManager::locked() const
{
    Q_D(const DragManager);
    return d->locked;
}

void DragManager::load()
{
    Q_D(DragManager);
    if (d->context == 0) {
        return;
    }

    if (d->widgetsPageListModel == 0) {

        QVariant pageListModelVariant = d->context->contextProperty("WidgetsPageListModelInstance");
        QObject *pageListModelObject = pageListModelVariant.value<QObject *>();

        WidgetsPageListModel *pageListModel =
                qobject_cast<WidgetsPageListModel *>(pageListModelObject);
        if (pageListModel == 0) {
            return;
        }

        d->widgetsPageListModel = pageListModel;
    }
}

void DragManager::setLocked(bool locked)
{
    Q_D(DragManager);
    if (d->locked != locked) {
        d->locked = locked;
        emit lockedChanged();
    }

    // Create draggers
    if (!d->locked) {
        d->createDraggers();
    }
}

}

}
