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
 * @file availablewidgetsmodel.cpp
 * @short Implementation of Widgets::AvailableWidgetsModel
 *
 * This file contains the implemetation of the
 * Widgets::SelectorWidgetsModel class and the declaration and
 * implementation of Widgets::AvailableWidgetsModel::AvailableWidgetsModelPrivate
 * and Widgets::AvailableWidgetsModelItem.
 */

#include "availablewidgetsmodel.h"
#include "widgetbaseproperties.h"

#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @internal
 * @short Structure used in the AvailableWidgetsModel
 *
 * This structure is used to store
 * the default components in AvailableWidgetsModel.
 */
struct AvailableWidgetsModelItem
{
    /**
     * @short Widget
     */
    WidgetBaseProperties *widget;
    /**
     * @short Name of the package
     */
    QString package;
};

/**
 * @internal
 * @short Private class for AvailableWidgetsModel
 */
class AvailableWidgetsModel::AvailableWidgetsModelPrivate
{
public:
    /**
     * @short Destructor
     */
    ~AvailableWidgetsModelPrivate();
    /**
     * @short Helper method used to delete AvailableWidgetsModelItem
     *
     * This helper method makes deletion of AvailableWidgetsModelItem
     * easier by deleting the unused pointers.
     *
     * @param item the SelectorWidgetsModelItem to delete.
     */
    void deleteItem(AvailableWidgetsModelItem *item);
    /**
     * @short A list of SelectorWidgetsModelItem
     *
     * This list of AvailableWidgetsModelItem is the
     * internal storage of the model.
     */
    QList<AvailableWidgetsModelItem *> items;
};

AvailableWidgetsModel::AvailableWidgetsModelPrivate::~AvailableWidgetsModelPrivate()
{
    // Delete allocated items
    while (!items.isEmpty()) {
        deleteItem(items.takeFirst());
    }
}

void AvailableWidgetsModel::AvailableWidgetsModelPrivate::
                            deleteItem(AvailableWidgetsModelItem *item)
{
    // Delete the widget in the item
    item->widget->deleteLater();

    delete item;
}

////// End of private class //////

AvailableWidgetsModel::AvailableWidgetsModel(QObject *parent) :
    QAbstractListModel(parent), d(new AvailableWidgetsModelPrivate())
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(WidgetRole, "widget");
    roles.insert(PackageRole, "package");
    setRoleNames(roles);
}

AvailableWidgetsModel::~AvailableWidgetsModel()
{
    delete d;
}

int AvailableWidgetsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->items.count();
}

int AvailableWidgetsModel::count() const
{
    return rowCount();
}

QVariant AvailableWidgetsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > rowCount()) {
        return QVariant();
    }

    AvailableWidgetsModelItem *item = d->items.at(index.row());
    switch (role) {
    case WidgetRole:
        return QVariant::fromValue(item->widget);
        break;
    case PackageRole:
        return item->package;
        break;
    default:
        return QVariant();
        break;
    }

}

void AvailableWidgetsModel::addWidget(const QString &package, WidgetBaseProperties *widget)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    AvailableWidgetsModelItem *item = new AvailableWidgetsModelItem;
    item->package = package;
    item->widget = widget;

    d->items.append(item);

    emit countChanged(rowCount());
    endInsertRows();
}

}
