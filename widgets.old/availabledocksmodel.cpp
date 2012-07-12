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
 * @file availabledocksmodel.cpp
 * @short Implementation of Widgets::AvailableDocksModel
 *
 * This file contains the implemetation of the
 * Widgets::AvailableDocksModel class and the declaration and
 * implementation of Widgets::AvailableDocksModel::AvailableDocksModelPrivate
 * and Widgets::AvailableDocksModelItem.
 */

#include "availabledocksmodel.h"
#include "dockbaseproperties.h"
#include "dockproperties.h"

#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @internal
 * @short Structure used in the AvailableDocksModel
 *
 * This structure is used to store
 * the default components in AvailableDocksModel.
 */
struct AvailableDocksModelItem
{
    /**
     * @short Dock
     */
    DockBaseProperties *dock;
    /**
     * @short Name of the package
     */
    QString package;
    /**
     * @short If the dock is enabled
     */
    bool enabled;
};

/**
 * @internal
 * @short Private class for AvailableDocksModel
 */
class AvailableDocksModel::AvailableDocksModelPrivate
{
public:
    /**
     * @short Destructor
     */
    ~AvailableDocksModelPrivate();
    /**
     * @short Helper method used to delete AvailableDocksModelItem
     *
     * This helper method makes deletion of AvailableDocksModelItem
     * easier by deleting the unused pointers.
     *
     * @param item the SelectorDocksModelItem to delete.
     */
    void deleteItem(AvailableDocksModelItem *item);
    /**
     * @short A list of AvailableDocksModelItem
     *
     * This list of SelectorDocksModelItem is the
     * internal storage of the model.
     */
    QList<AvailableDocksModelItem *> items;
};

AvailableDocksModel::AvailableDocksModelPrivate::~AvailableDocksModelPrivate()
{
    // Delete allocated items
    while (!items.isEmpty()) {
        deleteItem(items.takeFirst());
    }
}

void AvailableDocksModel::AvailableDocksModelPrivate::deleteItem(AvailableDocksModelItem *item)
{
    // Delete the docks in the item
    item->dock->deleteLater();

    delete item;
}

////// End of private class //////

AvailableDocksModel::AvailableDocksModel(QObject *parent) :
    QAbstractListModel(parent), d(new AvailableDocksModelPrivate())
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(DockRole, "dock");
    roles.insert(EnabledRole, "enabled");
    roles.insert(PackageRole, "package");
    setRoleNames(roles);
}

AvailableDocksModel::~AvailableDocksModel()
{
    delete d;
}

int AvailableDocksModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->items.count();
}

int AvailableDocksModel::count() const
{
    return rowCount();
}

QVariant AvailableDocksModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > rowCount()) {
        return QVariant();
    }

    AvailableDocksModelItem *item = d->items.at(index.row());
    switch (role) {
    case DockRole:
        return QVariant::fromValue(item->dock);
        break;
    case EnabledRole:
        return item->enabled;
        break;
    case PackageRole:
        return item->package;
        break;
    default:
        return QVariant();
        break;
    }

}

void AvailableDocksModel::addDock(const QString &package, DockBaseProperties *dock)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    AvailableDocksModelItem *item = new AvailableDocksModelItem;
    item->package = package;
    item->dock = dock;
    item->enabled = false;

    d->items.append(item);

    emit countChanged(rowCount());
    endInsertRows();
}

}
