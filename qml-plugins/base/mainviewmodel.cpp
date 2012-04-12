/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
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
 * @file displayedpagesmodel.cpp
 * @short Implementation of Widgets::DisplayedPagesModel
 *
 * This file contains the implemetation of the
 * Widgets::DisplayedPagesModel class and the declaration and
 * implementation of Widgets::DisplayedPagesModel::DisplayedPagesModelPrivate
 * and Widgets::WidgetViewModelItem.
 */

#include "mainviewmodel.h"
#include "settings.h"
#include "packagemanager.h"

#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @internal
 * @short Structure used in the DisplayedPagesModel
 *
 * This structure is used to store
 * the components in DisplayedPagesModel.
 */
struct DisplayedPagesModelItem
{
    /**
     * @short Index
     */
    int index;
    /**
     * @short Page model
     */
    DisplayedPageWidgetsModel *model;
};

/**
 * @internal
 * @short Private class for DisplayedPagesModel
 */
class DisplayedPagesModel::DisplayedPagesModelPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param settings Settings object used to manage settings.
     * @param packageManager PackageManager object used to provide available widgets.
     * @param parent parent Q-pointer.
     */
    DisplayedPagesModelPrivate(Settings *settings,
                               PackageManager *packageManager,
                               DisplayedPagesModel *parent);
    /**
     * @short Destructor
     */
    ~DisplayedPagesModelPrivate();
    /**
     * @short Helper method used to delete WidgetViewModelItem
     *
     * This helper method makes deletion of WidgetViewModelItem
     * easier by deleting the unused pointers.
     *
     * @param item the WidgetViewModelItem to delete.
     */
    void deleteItem(DisplayedPagesModelItem *item);
    /**
     * @short Slot that watch the pages
     *
     * This slot is connected to DisplayedPagesModel::rowsInserted()
     * and is used to watch if the models has changed,
     * and to emit DisplayedPagesModel::pageRowInserted() if needed.
     *
     * @param parent parent model index.
     * @param start the first row that is new.
     * @param end the last row that is new.
     */
    void slotRowsInserted(const QModelIndex &parent, int start, int end);
    /**
     * @short A list of WidgetViewModelItem
     *
     * This list of WidgetViewModelItem is the
     * internal storage of the model.
     */
    QList<DisplayedPagesModelItem *> items;
    /**
     * @short %Settings
     */
    Settings * const settings;
    /**
     * @short Package manager
     */
    PackageManager * const packageManager;
    /**
     * @short Q-pointer
     */
    DisplayedPagesModel * const q;
};

DisplayedPagesModel::DisplayedPagesModelPrivate::
                     DisplayedPagesModelPrivate(Settings *settings,
                                                PackageManager *packageManager,
                                                DisplayedPagesModel*parent):
    settings(settings), packageManager(packageManager), q(parent)
{
}

DisplayedPagesModel::DisplayedPagesModelPrivate::~DisplayedPagesModelPrivate()
{
    // Delete allocated items
    while (!items.isEmpty()) {
        deleteItem(items.takeFirst());
    }
}

void DisplayedPagesModel::DisplayedPagesModelPrivate::deleteItem(DisplayedPagesModelItem *item)
{
    // Delete the model in the item
    item->model->deleteLater();

    delete item;
}

void DisplayedPagesModel::DisplayedPagesModelPrivate::slotRowsInserted(const QModelIndex &parent,
                                                                 int start, int end)
{
    DisplayedPageWidgetsModel * model = qobject_cast<DisplayedPageWidgetsModel *>(q->sender());
    emit q->pageRowInserted(model, parent, start, end);
}

////// End of private class //////

DisplayedPagesModel::DisplayedPagesModel(Settings *settings, PackageManager *packageManager,
                                         QObject *parent):
    QAbstractListModel(parent), d(new DisplayedPagesModelPrivate(settings, packageManager, this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(IndexRole, "index");
    roles.insert(PageModelRole, "pageModel");
    setRoleNames(roles);
}

DisplayedPagesModel::~DisplayedPagesModel()
{
    delete d;
}

int DisplayedPagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->items.count();
}

int DisplayedPagesModel::count() const
{
    return rowCount();
}

QVariant DisplayedPagesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 or index.row() >= rowCount())
    {
        return QVariant();
    }

    DisplayedPagesModelItem *item = d->items.at(index.row());
    switch(role) {
    case IndexRole:
        return item->index;
        break;
    case PageModelRole:
        return QVariant::fromValue(item->model);
        break;
    default:
        return QVariant();
        break;
    }
}

DisplayedPageWidgetsModel * DisplayedPagesModel::pageModel(int index) const
{
    if (index < 0 or index > rowCount())
    {
        return 0;
    }

    DisplayedPagesModelItem *item = d->items.at(index);
    return  item->model;
}

void DisplayedPagesModel::setPageCount(int count)
{
    if (rowCount() < count) {
        for(int i = rowCount(); i < count; i++) {
            addPage();
        }
    } else if (rowCount() > count) {
        for(int i = count; i < rowCount(); i++) {
            removePage();
        }
    }
}

void DisplayedPagesModel::addPage()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    DisplayedPagesModelItem *item = new DisplayedPagesModelItem;
    item->index = rowCount();
    item->model = new DisplayedPageWidgetsModel(rowCount(), d->settings, d->packageManager, this);

    d->items.append(item);
    connect(item->model, SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(slotRowsInserted(QModelIndex, int, int)));

    emit countChanged(rowCount());
    endInsertRows();
}

void DisplayedPagesModel::removePage()
{
    if (rowCount() == 0) {
        return;
    }

    beginRemoveRows(QModelIndex(), rowCount() - 1, rowCount() - 1);

    DisplayedPagesModelItem *item = d->items.takeLast();
    disconnect(item->model, SIGNAL(rowsInserted(QModelIndex, int, int)),
               this, SLOT(slotRowsInserted(QModelIndex, int, int)));
    d->deleteItem(item);

    emit countChanged(rowCount());
    endRemoveRows();
}

}

#include "moc_displayedpagesmodel.cpp"
