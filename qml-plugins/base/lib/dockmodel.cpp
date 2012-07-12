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

#include <QtCore/QEvent>
#include <QtCore/QMap>

#include "abstractsettings_p.h"
#include "dockproperties.h"

namespace Widgets
{

class DockModelPrivate: public AbstractSettingsPrivate
{
public:
    DockModelPrivate(DockModel *q);
    ~DockModelPrivate();
    virtual void clear();
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
    QList<DockProperties *> docks;
    QMap<QString, bool> docksPackageAndIdentifier;
};

DockModelPrivate::DockModelPrivate(DockModel *q):
    AbstractSettingsPrivate(q)
{
}

DockModelPrivate::~DockModelPrivate()
{
    while (!docks.isEmpty()) {
        docks.takeFirst()->deleteLater();
    }
}

void DockModelPrivate::clear()
{

}

bool DockModelPrivate::fromXmlElement(const QDomElement &element)
{

}

QDomElement DockModelPrivate::toXmlElement(const QString &tagName, QDomDocument *document) const
{

}

////// End of private class //////

DockModel::DockModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new DockModelPrivate(this))
{
    // Definition of roles
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
    return d->docks.count();
}

int DockModel::count() const
{
    return rowCount();
}

QVariant DockModel::data(const QModelIndex &index, int role) const
{
    Q_D(const DockModel);
    if (index.row() < 0 or index.row() > rowCount()) {
        return QVariant();
    }

    switch(role) {
    case DockRole:
        return QVariant::fromValue(d->docks.at(index.row()));
        break;
    default:
        return QVariant();
        break;
    }
}

bool DockModel::hasDock(const QString &packageIdentifier, const QString &fileName) const
{
    Q_D(const DockModel);
    QString key = QString("%1/%2").arg(packageIdentifier).arg(fileName);
    return d->docksPackageAndIdentifier.contains(key);
}

void DockModel::addDock(DockBaseProperties *dock,
                        const QVariantMap &settings,
                        const QString &identifier)
{
    Q_D(DockModel);
    if (dock == 0) {
        return;
    }

    if (hasDock(dock->packageIdentifier(), dock->fileName())) {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    DockProperties *newDock = new DockProperties(dock);
    d->docks.append(newDock);

    QString packageAndIdentifier =
            QString("%1/%2").arg(dock->packageIdentifier()).arg(dock->fileName());
    d->docksPackageAndIdentifier.insert(packageAndIdentifier, true);

    emit countChanged(rowCount());
    endInsertRows();
}

bool DockModel::event(QEvent *event)
{
    Q_D(DockModel);
    if (event->type() == QEvent::UpdateRequest) {
        d->save();
        return true;
    }
    return QObject::event(event);
}


}
