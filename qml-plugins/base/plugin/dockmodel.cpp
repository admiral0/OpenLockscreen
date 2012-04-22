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

#include "dockmodel.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

#include "dockproperties.h"

namespace Widgets
{

class DockModelPrivate
{
public:
    DockModelPrivate();
    ~DockModelPrivate();
    void clear();
    QList<DockProperties *> data;
};

DockModelPrivate::DockModelPrivate()
{
}

DockModelPrivate::~DockModelPrivate()
{
    clear();
}

void DockModelPrivate::clear()
{
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
}

////// End of private class //////

DockModel::DockModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new DockModelPrivate)
{
    QHash <int, QByteArray> roles;
    roles.insert(DockRole, "dock");
    setRoleNames(roles);
}

DockModel::~DockModel()
{
}

int DockModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const DockModel);
    return d->data.count();
}

int DockModel::count() const
{
    return rowCount();
}

QVariant DockModel::data(const QModelIndex &index, int role) const
{
    Q_D(const DockModel);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    DockProperties *dock = d->data.at(row);
    switch(role) {
    case DockRole:
        return QVariant::fromValue(dock);
        break;
    default:
        return QVariant();
    }
}

void DockModel::clear()
{
    Q_D(DockModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

    d->clear();

    emit countChanged(rowCount());
    endRemoveRows();
}

void DockModel::addDock(DockBaseProperties *dock, const QVariantMap &settings)
{
    Q_D(DockModel);

    if(dock == 0) {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    DockProperties *newDock;
    newDock = new DockProperties(dock->fileName(), dock->packageIdentifier(),
                                 dock->isSettingsEnabled(),
                                 dock->width(), dock->height(),
                                 dock->anchorsTop(), dock->anchorsBottom(),
                                 dock->anchorsLeft(), dock->anchorsRight(),
                                 settings, this);

    // Append the dock to the list
    d->data.append(newDock);

    emit countChanged(rowCount());
    endInsertRows();
}


}
