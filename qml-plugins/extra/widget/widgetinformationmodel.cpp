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

#include "widgetbaseproperties.h"

namespace Widgets
{

namespace Extra
{

struct WidgetInformationModelPrivateItem
{
    QVariantHash disambiguation;
    QString fileName;
    QString name;
    QString description;
};

class WidgetInformationModelPrivate
{
public:
    WidgetInformationModelPrivate(WidgetInformationModel *q);
    ~WidgetInformationModelPrivate();
    void slotProviderStatusChanged();
    void clear();
    ProviderManager *providerManager;
    QList<WidgetInformationModelPrivateItem *> data;
private:
    WidgetInformationModel * const q_ptr;
    Q_DECLARE_PUBLIC(WidgetInformationModel)
};

WidgetInformationModelPrivate::WidgetInformationModelPrivate(WidgetInformationModel *q):
    q_ptr(q)
{
    providerManager = 0;
}

WidgetInformationModelPrivate::~WidgetInformationModelPrivate()
{
    clear();
}

void WidgetInformationModelPrivate::slotProviderStatusChanged()
{
    Q_Q(WidgetInformationModel);
    q->update();
}

void WidgetInformationModelPrivate::clear()
{
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
}

////// End of private class //////

WidgetInformationModel::WidgetInformationModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new WidgetInformationModelPrivate(this))
{
    QHash<int, QByteArray> roles;
    roles.insert(FileRole, "file");
    roles.insert(DisambiguationRole, "disambiguation");
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    setRoleNames(roles);
}

WidgetInformationModel::~WidgetInformationModel()
{
}

ProviderManager * WidgetInformationModel::providerManager() const
{
    Q_D(const WidgetInformationModel);
    return d->providerManager;
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

    WidgetInformationModelPrivateItem *item = d->data.at(row);
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

void WidgetInformationModel::clear()
{
    Q_D(WidgetInformationModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

    d->clear();

    emit countChanged(rowCount());
    endRemoveRows();
}

void WidgetInformationModel::setProviderManager(ProviderManager *providerManager)
{
    Q_D(WidgetInformationModel);
    if (d->providerManager != providerManager) {
        d->providerManager = providerManager;
        emit providerManagerChanged();

        connect(d->providerManager, SIGNAL(providerStatusChanged()),
                this, SLOT(slotProviderStatusChanged()));
        update();
    }
}

void WidgetInformationModel::update()
{

    Q_D(WidgetInformationModel);
    if (providerManager() == 0) {
        return;
    }
    if (providerManager()->providerStatus() != ProviderManager::ProviderAvailable) {
        return;
    }
    clear();

    WidgetProviderBase *provider = d->providerManager->provider();

    QList<QVariantHash> disambiguationList = provider->disambiguationList();
    foreach (QVariantHash disambiguation, disambiguationList) {
        QStringList registeredWidgets = provider->registeredWidgets(disambiguation);

        foreach (QString file, registeredWidgets) {
            beginInsertRows(QModelIndex(), rowCount(), rowCount());

            QString name = provider->widgetName(file, disambiguation);
            QString description = provider->widgetDescription(file, disambiguation);
            WidgetInformationModelPrivateItem *item = new WidgetInformationModelPrivateItem;
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

#include "moc_widgetinformationmodel.cpp"
