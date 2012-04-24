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

#include "abstractsettings_p.h"
#include "dockproperties.h"

namespace Widgets
{

namespace Docks
{

class DockModelPrivate: public AbstractSettingsPrivate
{
public:
    DockModelPrivate(DockModel *q);
    ~DockModelPrivate();
    virtual void clear();
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
    QList<DockProperties *> data;
private:
    DockModel * const q_ptr;
    Q_DECLARE_PUBLIC(DockModel)
};

DockModelPrivate::DockModelPrivate(DockModel *q):
    AbstractSettingsPrivate(q), q_ptr(q)
{
}

DockModelPrivate::~DockModelPrivate()
{
    clear();
}

void DockModelPrivate::clear()
{
    Q_Q(DockModel);
    q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
    q->endRemoveRows();
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
    QHash <int, QByteArray> roles;
    roles.insert(DockRole, "dock");
    setRoleNames(roles);
}

DockModel::DockModel(DockModelPrivate *dd, QObject *parent):
    QAbstractListModel(parent), d_ptr(dd)
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

bool DockModel::hasDock(const QString &packageIdentifier, const QString &fileName) const
{
    Q_D(const DockModel);
    bool added = false;
    QListIterator<DockProperties *> iterator = QListIterator<DockProperties *>(d->data);
    while (!added && iterator.hasNext()) {
        DockProperties *addedDock = iterator.next();
        if (packageIdentifier == addedDock->packageIdentifier() &&
            fileName == addedDock->fileName()) {
            added = true;
        }
    }

    return added;
}

void DockModel::addDock(DockBaseProperties *dock, const QVariantMap &settings,
                        const QString &identifier)
{
    Q_D(DockModel);

    if(dock == 0) {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    DockProperties *newDock;
    if (identifier.isEmpty()) {
        newDock = new DockProperties(dock, settings, this);
    } else {
        newDock = new DockProperties(dock, identifier, settings, this);
    }

    d->data.append(newDock);

    emit countChanged(rowCount());
    endInsertRows();
}

bool DockModel::event(QEvent *event)
{
    Q_D(DockModel);
//    if (event->type() == QEvent::UpdateRequest) {
//        d->save();
//        return true;
//    }
    return QObject::event(event);
}

}

}
