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

#include "foldermodel.h"
#include "applicationinformations.h"

/**
 * @file foldermodel.cpp
 * @short Implementation of Widgets::FolderModel
 *
 * This file contains the implemetation of the
 * Widgets::FolderModel class and the declaration and
 * implementation of Widgets::FolderModel::FolderModelPrivate
 * and Widgets::FolderModelItem.
 */

/**
 * @internal
 * @short Structure used in the FolderModel
 *
 * This structure is used to store
 * the components in FolderModel.
 */
struct FolderModelItem
{
    /**
     * @short Name of the entry
     */
    QString name;
    /**
     * @short Type of the entry
     */
    FolderModel::Type type;
    /**
     * @short Subfolder model
     *
     * If this entry is an application, this
     * pointer is set to 0.
     */
    FolderModel *subfolderModel;
    /**
     * @short Applications informations
     *
     * If this entry is a subfolder, this
     * pointer is set to 0.
     */
    ApplicationInformations *applicationInformations;
};

/**
 * @internal
 * @short Private class for FolderModel
 */
class FolderModel::FolderModelPrivate
{
public:
    /**
     * @short Destructor
     */
    ~FolderModelPrivate();
    /**
     * @short Helper method used to delete FolderModelItem
     *
     * This helper method makes deletion of FolderModelItem
     * easier by deleting the unused pointers.
     *
     * @param item the FolderModelItem to delete.
     */
    void deleteItem(FolderModelItem * item);
    /**
     * @short A list of FolderModelItem
     *
     * This list of FolderModelItem is the
     * internal storage of the model.
     */
    QList<FolderModelItem *> items;
};

FolderModel::FolderModelPrivate::~FolderModelPrivate()
{
    // Delete allocated items
    while (!items.isEmpty()) {
        deleteItem(items.takeFirst());
    }
}

void FolderModel::FolderModelPrivate::deleteItem(FolderModelItem *item)
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
    QAbstractListModel(parent), d(new FolderModelPrivate)
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
    delete d;
}

int FolderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->items.count();
}

int FolderModel::count() const
{
    return rowCount();
}

QVariant FolderModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > rowCount()) {
        return QVariant();
    }

    FolderModelItem *item = d->items.at(index.row());
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
    if(index < 0 || index > rowCount()) {
        return QString();
    }

    FolderModelItem *item = d->items.at(index);
    if(item->type == FolderType) {
        return QString();
    }

    return item->applicationInformations->icon();
}

void FolderModel::addApplication(const QString &name,
                                 ApplicationInformations *applicationInformations)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    FolderModelItem *item = new FolderModelItem;
    item->name = name;
    item->type = ApplicationType;
    item->subfolderModel = 0;
    item->applicationInformations = applicationInformations;

    d->items.append(item);

    emit countChanged(rowCount());
    endInsertRows();
}

void FolderModel::addSubfolder(const QString &name, FolderModel *subfolderModel)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    FolderModelItem *item = new FolderModelItem;
    item->name = name;
    item->type = FolderType;
    item->subfolderModel = subfolderModel;
    item->applicationInformations = 0;

    d->items.append(item);

    emit countChanged(rowCount());
    endInsertRows();
}
