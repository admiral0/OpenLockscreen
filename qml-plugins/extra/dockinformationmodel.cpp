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

#include "dockinformationmodel.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

#include "dockbaseproperties.h"

namespace Widgets
{

namespace Extra
{

class DockInformationModelPrivate
{
public:
    DockInformationModelPrivate();
    ~DockInformationModelPrivate();
    void clear();
    PackageManager *packageManager;
    QList<DockBaseProperties *> data;
//    QStringList packageName;
};

DockInformationModelPrivate::DockInformationModelPrivate()
{
    packageManager = 0;
}

DockInformationModelPrivate::~DockInformationModelPrivate()
{
    clear();
}

void DockInformationModelPrivate::clear()
{
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
}

////// End of private class //////

DockInformationModel::DockInformationModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new DockInformationModelPrivate)
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    roles.insert(PackageRole, "package");
    roles.insert(FileRole, "file");
    setRoleNames(roles);
}

DockInformationModel::~DockInformationModel()
{
}

PackageManager * DockInformationModel::packageManager() const
{
    Q_D(const DockInformationModel);
    return d->packageManager;
}

int DockInformationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const DockInformationModel);
    return d->data.count();
}

int DockInformationModel::count() const
{
    return rowCount();
}

QVariant DockInformationModel::data(const QModelIndex &index, int role) const
{
    Q_D(const DockInformationModel);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    DockBaseProperties *dock = d->data.at(row);
    switch(role) {
    case NameRole:
        return dock->name();
        break;
    case DescriptionRole:
        return dock->description();
        break;
    case PackageRole:
        return dock->packageIdentifier();
        break;
    case FileRole:
        return dock->fileName();
        break;
    default:
        return QVariant();
    }
}

void DockInformationModel::clear()
{
    Q_D(DockInformationModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

    d->clear();

    emit countChanged(rowCount());
    endRemoveRows();
}

void DockInformationModel::setPackageManager(PackageManager *packageManager)
{
    Q_D(DockInformationModel);
    if (d->packageManager != packageManager) {
        d->packageManager = packageManager;
        emit packageManagerChanged();

        update();
    }
}

void DockInformationModel::update()
{
    Q_D(DockInformationModel);
    if (packageManager() == 0) {
        return;
    }
    clear();

    QStringList registeredPackages = d->packageManager->registeredPackages();
    foreach(QString identifier, registeredPackages) {
        QStringList registeredDocks = d->packageManager->registeredDocks(identifier);
        foreach(QString file, registeredDocks) {
            beginInsertRows(QModelIndex(), rowCount(), rowCount());

            DockBaseProperties *dock = packageManager()->dock(identifier, file);
            d->data.append(dock);
            endInsertRows();
        }
    }
    emit countChanged(rowCount());
}

}

}
