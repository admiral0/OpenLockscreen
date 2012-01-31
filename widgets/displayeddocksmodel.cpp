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
 * @file displayeddocksmodel.cpp
 * @short Implementation of Widgets::DisplayedDocksModel
 *
 * This file contains the implemetation of the
 * Widgets::DisplayedDocksModel class and the declaration and
 * implementation of Widgets::DisplayedDocksModel::DisplayedDocksModelPrivate.
 */

#include "displayeddocksmodel.h"
#include "dockproperties.h"
#include "settings.h"
#include "packagemanager.h"

#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QSize>

namespace Widgets
{

/**
 * @internal
 * @short Private class for ViewDocksModel
 */
class DisplayedDocksModel::DisplayedDocksModelPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param settings Settings object used to manage settings.
     * @param packageManager PackageManager object used to provide available docks.
     * @param parent parent Q-pointer.
     */
    DisplayedDocksModelPrivate(Settings *settings, PackageManager *packageManager,
                               DisplayedDocksModel *parent);
    ~DisplayedDocksModelPrivate();
    /**
     * @short Load settings
     *
     * This method is used to retrieve
     * the saved docks and create them.
     */
    void loadSettings();
    /**
     * @short A list of DockProperties
     *
     * This list of DockBaseProperties is part
     * of the internal storage of the model.
     * 
     * It is used to store the docks that are
     * used to describe the displayed docks.
     */
    QList<DockProperties *> docks;
    /**
     * @short A list of DockBaseProperties
     * 
     * This list of DockBaseProperties is part
     * of the internal storage of the model.
     * 
     * It is used to store the dock base properties
     * that are used to create the docks that are 
     * displayed.
     */
    QList<DockBaseProperties *> dockBases;
    /**
     * @short Identifiers
     *
     * This list of identifiers is used to
     * track the docks that were added.
     *
     * This list is used in settings.
     */
    QStringList identifiers;
    /**
     * @short %Settings
     */
    Settings * const settings;
    /**
     * @short Package manager
     */
    PackageManager * const packageManager;
    /**
     * short Q-pointer
     */
    DisplayedDocksModel *q;
};

DisplayedDocksModel::DisplayedDocksModelPrivate::
                     DisplayedDocksModelPrivate(Settings *settings,
                                                PackageManager * packageManager,
                                                DisplayedDocksModel *parent):
    settings(settings), packageManager(packageManager), q(parent)
{
}

DisplayedDocksModel::DisplayedDocksModelPrivate::~DisplayedDocksModelPrivate()
{
    while (!docks.isEmpty()) {
        docks.takeFirst()->deleteLater();
    }
}

void DisplayedDocksModel::DisplayedDocksModelPrivate::loadSettings()
{
    // Key and identifiers
    QString key = QString("dock/identifiers");
    QStringList identifiers = settings->value(key).toStringList();

    // Retrieve all docks
    foreach (QString identifier, identifiers) {

        // Key to the dock
        QString key = QString("dock/dock_%1").arg(identifier);
        QVariantMap dockMap = settings->value(key).toMap();

        // Get the dock base properties
        QString qmlFile = dockMap.value("qmlFile").toString();
        DockBaseProperties *dockBase = packageManager->dock(qmlFile);

        // Construct the dock and add it
        if (dockBase != 0) {
            QVariantMap settings = dockMap.value("settings").toMap();
            q->addDock(dockBase, settings, identifier);
        }
    }

}

////// End of private class //////

DisplayedDocksModel::DisplayedDocksModel(Settings *settings, PackageManager *packageManager,
                                         QObject *parent):
    QAbstractListModel(parent), d(new DisplayedDocksModelPrivate(settings, packageManager, this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(DockRole, "dock");
    setRoleNames(roles);

    d->loadSettings();
}

DisplayedDocksModel::~DisplayedDocksModel()
{
    delete d;
}

int DisplayedDocksModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->docks.count();
}

int DisplayedDocksModel::count() const
{
    return rowCount();
}

QVariant DisplayedDocksModel::data(const QModelIndex &index, int role) const
{
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

bool DisplayedDocksModel::hasDock(DockBaseProperties *dock)
{
    return d->dockBases.contains(dock);
}

void DisplayedDocksModel::addDock(DockBaseProperties *dock, const QVariantMap &settings,
                                  const QString &identifier)
{
    if(dock == 0) {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    // Create a new widget by either using the passed identifier
    // either by generating a new one
    DockProperties *newDock;
    if (identifier.isEmpty()) {
        newDock = new DockProperties(dock->name(),
                                     dock->width(), dock->height(),
                                     dock->anchorsTop(), dock->anchorsBottom(),
                                     dock->anchorsLeft(), dock->anchorsRight(),
                                     dock->qmlFile(), dock->package(),
                                     dock->hasSettings(), settings,
                                     this);
    } else {
        newDock = new DockProperties(dock->name(),
                                     dock->width(), dock->height(),
                                     dock->anchorsTop(), dock->anchorsBottom(),
                                     dock->anchorsLeft(), dock->anchorsRight(),
                                     dock->qmlFile(), dock->package(),
                                     dock->hasSettings(), identifier, settings,
                                     this);
    }

    // Append the dock to the list
    d->dockBases.append(dock);
    d->docks.append(newDock);

    emit countChanged(rowCount());
    endInsertRows();

    // Save settings
    // Add the new widget to the list of identifiers
    d->identifiers.append(newDock->identifier());
    QString key = QString("dock/identifiers");
    d->settings->setValue(key, d->identifiers);

    // Save the widget as a map
    key = QString("dock/dock_%1").arg(newDock->identifier());
    d->settings->setValue(key, newDock->toMap());
}

void DisplayedDocksModel::removeDock(DockBaseProperties *dock)
{
    int index = d->dockBases.indexOf(dock);
    if (index == -1) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);

    d->dockBases.removeAt(index);
    DockProperties * dockToDelete = d->docks.takeAt(index);


    emit countChanged(rowCount());
    endRemoveRows();

    // Save settings
    // Remove the dock from the list of identifiers
    d->identifiers.removeAll(dockToDelete->identifier());
    QString key = QString("dock/identifiers");
    d->settings->setValue(key, d->identifiers);

    // Remove the dock settings
    key = QString("dock/dock_%1").arg(dockToDelete->identifier());
    d->settings->remove(key);
    dockToDelete->deleteLater();
}

}
