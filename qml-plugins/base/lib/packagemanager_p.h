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

#ifndef WIDGETS_PACKAGEMANAGER_P_H
#define WIDGETS_PACKAGEMANAGER_P_H

#include "packagemanager.h"

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

#include <QtCore/QVariantMap>
#include <QtSql/QSqlQuery>


namespace Widgets
{

class DockBaseProperties;
class PackageManagerPrivate
{
public:
    PackageManagerPrivate(PackageManager *q);
    virtual QString databasePath() const;
    bool executeQuery(QSqlQuery *query) const;
    bool executeQueryBatch(QSqlQuery *query) const;
    void addComponentType(const QStringList &names);
    void addComponentInformationProperties(const QStringList &names);
    void prepareDatabase();
    int componentTypeId(const char *type) const;
    void addInformation(const char *type, int componentId, const QVariantMap &informations);
    void addLocalizedInformation(const char *type, int componentId,
                                 const QStringList &languages, const QStringList &names,
                                 const QStringList &descriptions);
    void addPackage(const QString &path);
    void scanPackageFolder(int packageId, const QString &path, const QString &packageIdentifier);
    void addDock(int packageId, const QString &subdirectory, DockBaseProperties *dock);
private:
    Q_DECLARE_PUBLIC(PackageManager)
    PackageManager * const q_ptr;
};

}

#endif // WIDGETS_PACKAGEMANAGER_P_H