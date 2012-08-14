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
 * @file packagemanager.cpp
 * @short Implementation of Widgets::PackageManager
 */

#include "packagemanager.h"
#include "packagemanager_p.h"

#include <QtCore/QDebug>

#include "databaseinterface_p.h"
#include "filterconditionlist.h"


namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

PackageManagerPrivate::PackageManagerPrivate(PackageManager *q):
    q_ptr(q)
{
    interface = new DatabaseInterface();
    filter = new FilterConditionList();
}

PackageManagerPrivate::~PackageManagerPrivate()
{
    interface->deleteLater();
    filter->deleteLater();
}

////// End of private class ///////


PackageManager::PackageManager(QObject *parent) :
    Docks::MixedProviderBase(new PackageManagerPrivate(this), parent)
{
    Q_D(PackageManager);
    d->interface->prepareDatabase();
    d->interface->scan();
    setAvailable(true);
}

PackageManager::PackageManager(PackageManagerPrivate *dd, QObject *parent):
    Docks::MixedProviderBase(dd, parent)
{
    Q_D(PackageManager);
    d->interface->prepareDatabase();
    d->interface->scan();
    setAvailable(true);
}

PackageManager::~PackageManager()
{
}

QList<QVariantHash> PackageManager::disambiguationList() const
{
    Q_D(const PackageManager);
    QList<QVariantHash> data;
    foreach (QString packageIdentifier, d->interface->registeredPackages(filter())) {
        data.append(d->interface->disambiguation(packageIdentifier));
    }

    return data;
}

QString PackageManager::dockFile(const QString &fileName,
                                 const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->dockFile(d->interface->packageIdentifier(disambiguation), fileName);
}

QString PackageManager::dockSettingsFile(const QString &fileName,
                                         const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->dockSettingsFile(d->interface->packageIdentifier(disambiguation),
                                          fileName);
}

Docks::DockBaseProperties * PackageManager::dock(const QString &fileName,
                                                 const QVariantHash &disambiguation)
{
    Q_D(PackageManager);
    return d->interface->dock(d->interface->packageIdentifier(disambiguation), fileName, this);
}

QString PackageManager::dockName(const QString &fileName,
                                 const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->dockName(d->interface->packageIdentifier(disambiguation), fileName);
}

QString PackageManager::dockDescription(const QString &fileName,
                                        const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->dockDescription(d->interface->packageIdentifier(disambiguation),
                                         fileName);
}


QStringList PackageManager::registeredDocks(const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->registeredDocks(d->interface->packageIdentifier(disambiguation));
}

QString PackageManager::widgetFile(const QString &fileName,
                                   const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->widgetFile(d->interface->packageIdentifier(disambiguation), fileName);
}

QString PackageManager::widgetSettingsFile(const QString &fileName,
                                           const QVariantHash &disambiguation) const

{
    Q_D(const PackageManager);
    return d->interface->widgetSettingsFile(d->interface->packageIdentifier(disambiguation),
                                            fileName);
}

Widgets::WidgetBaseProperties * PackageManager::widget(const QString &fileName,
                                                       const QVariantHash &disambiguation)
{
    Q_D(const PackageManager);
    return d->interface->widget(d->interface->packageIdentifier(disambiguation), fileName, this);
}

QString PackageManager::widgetName(const QString &fileName,
                                   const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->widgetName(d->interface->packageIdentifier(disambiguation), fileName);
}

QString PackageManager::widgetDescription(const QString &fileName,
                                          const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->widgetDescription(d->interface->packageIdentifier(disambiguation),
                                           fileName);
}


QStringList PackageManager::registeredWidgets(const QVariantHash &disambiguation) const
{
    Q_D(const PackageManager);
    return d->interface->registeredWidgets(d->interface->packageIdentifier(disambiguation));
}

FilterConditionList * PackageManager::filter() const
{
    Q_D(const PackageManager);
    return d->filter;
}

void PackageManager::update()
{
    Q_D(const PackageManager);
    d->interface->cleanDatabase();
    d->interface->scan();
}

void PackageManager::setFilter(FilterConditionList *filter)
{
    Q_D(PackageManager);
    if (d->filter != filter) {
        d->filter = filter;
        emit filterChanged();

        connect(d->filter, SIGNAL(conditionListChanged()), this, SIGNAL(filterChanged()));
    }
}

}

}

}
