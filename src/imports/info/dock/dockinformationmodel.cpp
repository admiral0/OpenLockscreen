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
 * @file dockinformationmodel.cpp
 * @short Implementation of Widgets::Info::DockInformationModel
 */

#include "dockinformationmodel.h"

#include <QtCore/QList>

#include "dockbaseproperties.h"

namespace Widgets
{

namespace Info
{

/**
 * @internal
 * @short Private structure for Widgets::Info::DockInformationModel
 */
struct DockInformationModelItemPrivate
{
    /**
     * @internal
     * @brief Filename
     */
    QString fileName;
    /**
     * @internal
     * @brief Disambiguation
     */
    QVariantMap disambiguation;
    /**
     * @internal
     * @brief Name
     */
    QString name;
    /**
     * @internal
     * @brief Description
     */
    QString description;
};

/**
 * @internal
 * @short Private class for Widgets::Info::DockInformationModel
 */
class DockInformationModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    DockInformationModelPrivate(DockInformationModel *q);
    /**
     * @internal
     * @brief Destructor
     */
    ~DockInformationModelPrivate();
    /**
     * @internal
     * @brief Provider status changed
     *
     * This slot is used to refresh the model.
     * It is called when the provider status changed.
     */
    void slotProviderStatusChanged();
    /**
     * @internal
     * @brief Clear
     */
    void clear();
    /**
     * @internal
     * @brief Provider manager
     */
    ProviderManager *providerManager;
    /**
     * @internal
     * @short Data
     */
    QList<DockInformationModelItemPrivate *> data;
private:
    /**
     * @internal
     * @brief Q-pointer
     */
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

    DockInformationModelItemPrivate *item = d->data.at(row);
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

    emit countChanged();
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
            DockInformationModelItemPrivate *item = new DockInformationModelItemPrivate;
            item->fileName = file;
            item->disambiguation = disambiguation;
            item->name = name;
            item->description = description;
            d->data.append(item);
            endInsertRows();
        }

    }
    emit countChanged();
}

}

}

#include "moc_dockinformationmodel.cpp"
