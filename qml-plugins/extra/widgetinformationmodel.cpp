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

#include "widgetinformationmodel.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

#include "widgetbaseproperties.h"

namespace Widgets
{

namespace Extra
{

class WidgetInformationModelPrivate
{
public:
    WidgetInformationModelPrivate();
    ~WidgetInformationModelPrivate();
    void clear();
    PackageManager *packageManager;
    QList<WidgetBaseProperties *> data;
};

WidgetInformationModelPrivate::WidgetInformationModelPrivate()
{
    packageManager = 0;
}

WidgetInformationModelPrivate::~WidgetInformationModelPrivate()
{
    clear();
}

void WidgetInformationModelPrivate::clear()
{
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
}

////// End of private class //////

WidgetInformationModel::WidgetInformationModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new WidgetInformationModelPrivate)
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    roles.insert(PackageRole, "package");
    roles.insert(FileRole, "file");
    setRoleNames(roles);
}

WidgetInformationModel::~WidgetInformationModel()
{
}

PackageManager * WidgetInformationModel::packageManager() const
{
    Q_D(const WidgetInformationModel);
    return d->packageManager;
}

int WidgetInformationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const WidgetInformationModel);
    return d->data.count();
}

int WidgetInformationModel::count() const
{
    return rowCount();
}

QVariant WidgetInformationModel::data(const QModelIndex &index, int role) const
{
    Q_D(const WidgetInformationModel);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    WidgetBaseProperties *widget = d->data.at(row);
    switch(role) {
    case NameRole:
        return widget->name();
        break;
    case DescriptionRole:
        return widget->description();
        break;
    case PackageRole:
        return widget->packageIdentifier();
        break;
    case FileRole:
        return widget->fileName();
        break;
    default:
        return QVariant();
    }
}

void WidgetInformationModel::clear()
{
    Q_D(WidgetInformationModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

    d->clear();

    emit countChanged(rowCount());
    endRemoveRows();
}

void WidgetInformationModel::setPackageManager(PackageManager *packageManager)
{
    Q_D(WidgetInformationModel);
    if (d->packageManager != packageManager) {
        d->packageManager = packageManager;
        emit packageManagerChanged();

        update();
    }
}

void WidgetInformationModel::update()
{
    Q_D(WidgetInformationModel);
    if (packageManager() == 0) {
        return;
    }
    clear();

    QStringList registeredPackages = d->packageManager->registeredPackages();
    foreach(QString identifier, registeredPackages) {
        QStringList registeredWidgets = d->packageManager->registeredWidgets(identifier);
        foreach(QString file, registeredWidgets) {
            beginInsertRows(QModelIndex(), rowCount(), rowCount());

            WidgetBaseProperties *widget = packageManager()->widget(identifier, file);
            d->data.append(widget);
            endInsertRows();
        }
    }
    emit countChanged(rowCount());
}

}

}
