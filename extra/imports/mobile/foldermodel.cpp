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
 * @file foldermodel.cpp
 * @short Implementation of Mobile::Launcher::FolderModel
 */

#include "foldermodel.h"
#include "foldermodel_p.h"
#include "applicationinformations.h"

namespace Mobile
{

namespace Launcher
{

/**
 * @internal
 * @short Private structure for Widgets::MobileExtra::FolderModel
 */
struct FolderModelItem
{
    /**
     * @internal
     * @short Name
     */
    QString name;
    /**
     * @internal
     * @short Type
     */
    FolderModel::Type type;
    /**
     * @internal
     * @short Subfolder model
     *
     * If this entry is an application, this
     * pointer is set to 0.
     */
    FolderModel *subfolderModel;
    /**
     * @internal
     * @short Applications informations
     *
     * If this entry is a subfolder, this
     * pointer is set to 0.
     */
    ApplicationInformations *applicationInformations;
};

FolderModelPrivate::~FolderModelPrivate()
{
    // Delete allocated items
    while (!data.isEmpty()) {
        deleteItem(data.takeFirst());
    }
}

void FolderModelPrivate::deleteItem(FolderModelItem *item)
{
    if (item->subfolderModel != 0) {
        delete item->subfolderModel;
    }
    if (item->applicationInformations != 0) {
        delete item->applicationInformations;
    }

    delete item;
}

////// End of private class //////

FolderModel::FolderModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new FolderModelPrivate)
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(IndexRole, "index");
    roles.insert(NameRole, "name");
    roles.insert(TypeRole, "type");
    roles.insert(PropertiesRole, "properties");
    setRoleNames(roles);
}

FolderModel::FolderModel(FolderModelPrivate *dd, QObject *parent):
    QAbstractListModel(parent), d_ptr(dd)
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(IndexRole, "index");
    roles.insert(NameRole, "name");
    roles.insert(TypeRole, "type");
    roles.insert(PropertiesRole, "properties");
    setRoleNames(roles);
}

FolderModel::~FolderModel()
{
}

int FolderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const FolderModel);
    return d->data.count();
}

int FolderModel::count() const
{
    return rowCount();
}

QVariant FolderModel::data(const QModelIndex &index, int role) const
{
    Q_D(const FolderModel);

    if (index.row() < 0 || index.row() > rowCount()) {
        return QVariant();
    }

    FolderModelItem *item = d->data.at(index.row());
    switch (role) {
    case IndexRole:
        return index.row();
        break;
    case NameRole:
        return item->name;
        break;
    case TypeRole:
        return item->type;
        break;
    case PropertiesRole:
        switch(item->type) {
        case ApplicationType:
            return QVariant::fromValue(item->applicationInformations);
            break;
        case FolderType:
            return QVariant::fromValue(item->subfolderModel);
            break;
        default:
            return QVariant();
            break;
        }
        break;
    default:
        return QVariant();
        break;
    }
}

QString FolderModel::icon(int index) const
{
    Q_D(const FolderModel);
    if(index < 0 || index > rowCount()) {
        return QString();
    }

    FolderModelItem *item = d->data.at(index);
    if(item->type == FolderType) {
        return QString();
    }

    return item->applicationInformations->icon();
}

void FolderModel::addApplication(const QString &name,
                                 ApplicationInformations *applicationInformations)
{
    Q_D(FolderModel);
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    FolderModelItem *item = new FolderModelItem;
    item->name = name;
    item->type = ApplicationType;
    item->subfolderModel = 0;
    item->applicationInformations = applicationInformations;

    d->data.append(item);

    emit countChanged();
    endInsertRows();
}

void FolderModel::addSubfolder(const QString &name, FolderModel *subfolderModel)
{
    Q_D(FolderModel);
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    FolderModelItem *item = new FolderModelItem;
    item->name = name;
    item->type = FolderType;
    item->subfolderModel = subfolderModel;
    item->applicationInformations = 0;

    d->data.append(item);

    emit countChanged();
    endInsertRows();
}

}

}
