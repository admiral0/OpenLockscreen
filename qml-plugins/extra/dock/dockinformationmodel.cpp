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

#include "dockbaseproperties.h"

namespace Widgets
{

namespace Extra
{

struct DockInformationModelPrivateItem
{
    QVariantMap disambiguation;
    QString fileName;
    QString name;
    QString description;
};

class DockInformationModelPrivate
{
public:
    DockInformationModelPrivate(DockInformationModel *q);
    ~DockInformationModelPrivate();
    void slotProviderStatusChanged();
    void clear();
    ProviderManager *providerManager;
    QList<DockInformationModelPrivateItem *> data;
private:
    DockInformationModel * const q_ptr;
    Q_DECLARE_PUBLIC(DockInformationModel)
};

DockInformationModelPrivate::DockInformationModelPrivate(DockInformationModel *q):
    q_ptr(q)
{
    providerManager = 0;
}

DockInformationModelPrivate::~DockInformationModelPrivate()
{
    clear();
}

void DockInformationModelPrivate::slotProviderStatusChanged()
{
    Q_Q(DockInformationModel);
    q->update();
}

void DockInformationModelPrivate::clear()
{
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
}

////// End of private class //////

DockInformationModel::DockInformationModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new DockInformationModelPrivate(this))
{
    QHash<int, QByteArray> roles;
    roles.insert(FileRole, "file");
    roles.insert(DisambiguationRole, "disambiguation");
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    setRoleNames(roles);
}

DockInformationModel::~DockInformationModel()
{
}

ProviderManager * DockInformationModel::providerManager() const
{
    Q_D(const DockInformationModel);
    return d->providerManager;
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

    DockInformationModelPrivateItem *item = d->data.at(row);
    switch(role) {
    case FileRole:
        return item->fileName;
        break;
    case DisambiguationRole:
        return item->disambiguation;
        break;
    case NameRole:
        return item->name;
        break;
    case DescriptionRole:
        return item->description;
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

void DockInformationModel::setProviderManager(ProviderManager *providerManager)
{
    Q_D(DockInformationModel);
    if (d->providerManager != providerManager) {
        d->providerManager = providerManager;
        emit providerManagerChanged();

        connect(d->providerManager, SIGNAL(providerStatusChanged()),
                this, SLOT(slotProviderStatusChanged()));
        update();
    }
}

void DockInformationModel::update()
{
    Q_D(DockInformationModel);
    if (providerManager() == 0) {
        return;
    }
    if (providerManager()->providerStatus() != ProviderManager::ProviderAvailable) {
        return;
    }
    clear();

    Docks::MixedProviderBase *provider
            = qobject_cast<Docks::MixedProviderBase *>(d->providerManager->provider());
    if (!provider) {
        return;
    }

    QList<QVariantMap> disambiguationList = provider->disambiguationList();
    foreach (QVariantMap disambiguation, disambiguationList) {
        QStringList registeredDocks = provider->registeredDocks(disambiguation);

        foreach (QString file, registeredDocks) {
            beginInsertRows(QModelIndex(), rowCount(), rowCount());

            QString name = provider->dockName(file, disambiguation);
            QString description = provider->dockDescription(file, disambiguation);
            DockInformationModelPrivateItem *item = new DockInformationModelPrivateItem;
            item->fileName = file;
            item->disambiguation = disambiguation;
            item->name = name;
            item->description = description;
            d->data.append(item);
            endInsertRows();
        }

    }
    emit countChanged(rowCount());
}

}

}

#include "moc_dockinformationmodel.cpp"
