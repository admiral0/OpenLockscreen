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

#include "packageinformationmodel.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

#include "package.h"

namespace Widgets
{

namespace Extra
{

class PackageInformationModelPrivate
{
public:
    PackageInformationModelPrivate();
    ~PackageInformationModelPrivate();
    void clear();
    Provider::PackageManager::PackageManager *packageManager;
    QList<Provider::PackageManager::Package *> data;
};

PackageInformationModelPrivate::PackageInformationModelPrivate()
{
    packageManager = 0;
}

PackageInformationModelPrivate::~PackageInformationModelPrivate()
{
    clear();
}

void PackageInformationModelPrivate::clear()
{
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
}

////// End of private class //////

PackageInformationModel::PackageInformationModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new PackageInformationModelPrivate)
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    roles.insert(AuthorRole, "author");
    roles.insert(EmailRole, "email");
    roles.insert(WebsiteRole, "website");
    roles.insert(VersionRole, "version");
    setRoleNames(roles);
}

PackageInformationModel::~PackageInformationModel()
{
}

Provider::PackageManager::PackageManager * PackageInformationModel::packageManager() const
{
    Q_D(const PackageInformationModel);
    return d->packageManager;
}

int PackageInformationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const PackageInformationModel);
    return d->data.count();
}

int PackageInformationModel::count() const
{
    return rowCount();
}

QVariant PackageInformationModel::data(const QModelIndex &index, int role) const
{
    Q_D(const PackageInformationModel);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    Provider::PackageManager::Package *package = d->data.at(row);
    switch(role) {
    case NameRole:
        return package->name();
        break;
    case DescriptionRole:
        return package->description();
        break;
    case AuthorRole:
        return package->author();
        break;
    case EmailRole:
        return package->email();
        break;
    case WebsiteRole:
        return package->website();
        break;
    case VersionRole:
        return package->version().toString();
        break;
    default:
        return QVariant();
    }
}

void PackageInformationModel::clear()
{
    Q_D(PackageInformationModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

    d->clear();

    emit countChanged(rowCount());
    endRemoveRows();
}

void PackageInformationModel::setPackageManager(
        Provider::PackageManager::PackageManager *packageManager)
{
    Q_D(PackageInformationModel);
    if (d->packageManager != packageManager) {
        d->packageManager = packageManager;
        emit packageManagerChanged();

        update();
        connect(d->packageManager, SIGNAL(filterChanged()), this, SLOT(update()));
    }
}

void PackageInformationModel::update()
{
    Q_D(PackageInformationModel);
    if (packageManager() == 0) {
        return;
    }
    clear();

    QList<QVariantMap> disambiguationList = d->packageManager->disambiguationList();
    foreach(QVariantMap disambiguation, disambiguationList) {

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        Provider::PackageManager::Package *package = packageManager()->package(disambiguation);
        d->data.append(package);
        endInsertRows();

    }
    emit countChanged(rowCount());
}

}

}
