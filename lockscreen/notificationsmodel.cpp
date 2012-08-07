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

#include "notificationsmodel.h"

struct NotificationsModelItem
{
    QString body;
    QString summary;
    QString icon;
};

class NotificationsModel::NotificationsModelPrivate
{
public:
    ~NotificationsModelPrivate();
    void deleteItem(NotificationsModelItem *item);
    QList<NotificationsModelItem *> items;
};

NotificationsModel::NotificationsModelPrivate::~NotificationsModelPrivate()
{
    while(!items.isEmpty()) {
        deleteItem(items.takeFirst());
    }
}

void NotificationsModel::NotificationsModelPrivate::deleteItem(NotificationsModelItem *item)
{
    delete item;
}

NotificationsModel::NotificationsModel(QObject *parent) :
    QAbstractListModel(parent), d(new NotificationsModelPrivate())
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(BodyRole, "body");
    roles.insert(SummaryRole, "summary");
    roles.insert(IconRole, "icon");
    setRoleNames(roles);
}

NotificationsModel::~NotificationsModel()
{
    delete d;
}

int NotificationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->items.count();
}

int NotificationsModel::count() const
{
    return rowCount();
}

QVariant NotificationsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > rowCount()) {
        return QVariant();
    }

    NotificationsModelItem *item = d->items.at(index.row());
    switch (role) {
    case BodyRole:
        return item->body;
        break;
    case SummaryRole:
        return item->summary;
        break;
    case IconRole:
        return item->icon;
        break;
    default:
        return QVariant();
        break;
    }

}

void NotificationsModel::addNotification(const QString &body,
                                         const QString &summary,
                                         const QString &icon)
{
    beginInsertRows(QModelIndex(), 0, 0);

    NotificationsModelItem *item = new NotificationsModelItem;
    item->body = body;
    item->summary = summary;
    item->icon = icon;

    d->items.prepend(item);

    emit countChanged(rowCount());
    endInsertRows();
}

