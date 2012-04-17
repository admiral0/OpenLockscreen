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

#include "packagemanager.h"
#include "packagemanager_p.h"
#include "packagemanagerdefines.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>

#include "debug.h"
#include "package.h"
#include "version.h"

namespace Widgets
{

PackageManager::PackageManager(QObject *parent) :
    QObject(parent), d_ptr(new PackageManagerPrivate(this))
{
    Q_D(PackageManager);
    d->prepareDatabase();


    package("org.SfietKonstantin.basicwidgets");
}

PackageManager::PackageManager(PackageManagerPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
    Q_D(PackageManager);
    d->prepareDatabase();
}

PackageManager::~PackageManager()
{
}

Package PackageManager::package(const QString &identifier) const
{
    Q_D(const PackageManager);
    Package value;

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_package");
        db.setDatabaseName(d->databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT id, directory, plugin FROM packages WHERE identifier=:identifier");
        query.bindValue(":identifier", identifier);
        d->executeQuery(&query);
        if (!query.next()) {
            return value;
        }

        int packageId = query.value(0).toInt();
        QString folder = query.value(1).toString();
        QString plugin = query.value(2).toString();

        value.setIdentifier(identifier);
        value.setDirectory(folder);
        value.setPlugin(plugin);

        query.prepare("SELECT language, name, description FROM localizedPackageInformations WHERE packageId=:packageId");
        query.bindValue(":packageId", packageId);
        d->executeQuery(&query);
        while (query.next()) {
            QString language = query.value(0).toString();
            QString name = query.value(1).toString();
            QString description = query.value(2).toString();

            if (language == PACKAGE_INFORMATION_DEFAULT_LANGUAGE) {
                value.setDefaultName(name);
                value.setDefaultDescription(description);
            } else {
                value.addName(language, name);
                value.addDescription(language, description);
            }
        }
        query.finish();
        QMap<QString, QString> informations;

        query.prepare("SELECT name, value FROM packageInformations INNER JOIN packageInformationsProperties ON packageInformations.informationId = packageInformationsProperties.id WHERE packageId=:packageId");
        query.bindValue(":packageId", packageId);
        d->executeQuery(&query);

        while (query.next()) {
            QString name = query.value(0).toString();
            QString value = query.value(1).toString();
            informations.insert(name, value);
        }
        query.finish();

        value.setAuthor(informations.value(PACKAGE_INFORMATION_AUTHOR));
        value.setEmail(informations.value(PACKAGE_INFORMATION_EMAIL));
        value.setIcon(informations.value(PACKAGE_INFORMATION_ICON));
        value.setWebsite(informations.value(PACKAGE_INFORMATION_WEBSITE));
        value.setVersion(Version::fromString(informations.value(PACKAGE_INFORMATION_VERSION)));
    }
    QSqlDatabase::removeDatabase("get_package");

    return value;
}

QStringList PackageManager::registeredPackages() const
{
    Q_D(const PackageManager);
    QStringList values;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_registered_packages");
        db.setDatabaseName(d->databasePath());
        W_ASSERT(db.open());
        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT identifier FROM packages");
        d->executeQuery(&query);
        while (query.next()) {
            values.append(query.value(0).toString());
        }
        query.finish();
    }
    QSqlDatabase::removeDatabase("get_registered_packages");
    return values;
}


void PackageManager::update()
{
    Q_D(PackageManager);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "update");
        db.setDatabaseName(d->databasePath());
        W_ASSERT(db.open());
        QSqlQuery query = QSqlQuery(db);
        query.prepare("DELETE FROM packages");
        d->executeQuery(&query);
        query.finish();

        query.prepare("DELETE FROM packageInformations");
        d->executeQuery(&query);
        query.finish();

        query.prepare("DELETE FROM localizedPackageInformations");
        d->executeQuery(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("update");

    // First search in system widgets directories
    QDir systemWidgetsFolder = QDir(SYSTEM_WIDGETS);
    QFileInfoList folders = systemWidgetsFolder.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);

    foreach (QFileInfo folder, folders) {
        d->addPackage(folder.absoluteFilePath());
    }

}

}
