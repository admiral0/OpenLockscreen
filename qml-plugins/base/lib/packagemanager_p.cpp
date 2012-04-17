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

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

#include "packagemanager_p.h"
#include "packagemanagerdefines.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtGui/QDesktopServices>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

#include "debug.h"

namespace Widgets
{

static const char *CACHE_DIRECTORY = "Widgets";

PackageManagerPrivate::PackageManagerPrivate(PackageManager *q):
    q_ptr(q)
{
}

QString PackageManagerPrivate::databasePath() const
{
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
    if(!dir.cd(CACHE_DIRECTORY)) {
        dir.mkdir(CACHE_DIRECTORY);
        dir.cd(CACHE_DIRECTORY);
    }

    return dir.absoluteFilePath("packagemanager.db");
}

bool PackageManagerPrivate::executeQuery(QSqlQuery *query) const
{
    if (!query->exec()) {
        qDebug() << query->lastQuery();
        qDebug() << query->lastError();
        return false;
    }

    return true;
}

bool PackageManagerPrivate::executeQueryBatch(QSqlQuery *query) const
{
    if (!query->execBatch()) {
        qDebug() << query->lastQuery();
        qDebug() << query->lastError();
        return false;
    }

    return true;
}

void PackageManagerPrivate::addUniquePackageInformationsProperties(const QStringList &names)
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_package_info_properties");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QVariantList trueNames;
        QSqlQuery query = QSqlQuery(db);
        foreach (QString name, names) {
            query.prepare("SELECT COUNT(*) FROM packageInformationsProperties WHERE name=:name");
            query.bindValue(":name", name);
            executeQuery(&query);
            W_ASSERT(query.next());
            int count = query.value(0).toInt();
            query.finish();
            W_ASSERT(count == 0 || count == 1);
            if (count == 0) {
                trueNames.append(name);
            }
        }

        query.prepare("INSERT INTO packageInformationsProperties (id, name) VALUES (NULL, :name)");
        query.addBindValue(trueNames);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_package_info_properties");
}

void PackageManagerPrivate::prepareDatabase()
{
    Q_Q(PackageManager);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "init");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        // Create tables if they do not exist
        QSqlQuery query = QSqlQuery(db);
        query.prepare("CREATE TABLE IF NOT EXISTS version (major INTEGER, minor INTEGER, patch INTEGER)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS packages (id INTEGER PRIMARY KEY AUTOINCREMENT, identifier STRING, directory STRING, plugin STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS packageInformationsProperties (id INTEGER PRIMARY KEY, name STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS packageInformations (packageId INTEGER, informationId INTEGER, value STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS localizedPackageInformations (packageId INTEGER, language STRING, name STRING, description STRING)");
        executeQuery(&query);
        query.finish();

        QStringList names;
        names.append(PACKAGE_INFORMATION_AUTHOR);
        names.append(PACKAGE_INFORMATION_EMAIL);
        names.append(PACKAGE_INFORMATION_ICON);
        names.append(PACKAGE_INFORMATION_WEBSITE);
        names.append(PACKAGE_INFORMATION_VERSION);
        addUniquePackageInformationsProperties(names);

        // Check version
        query.prepare("SELECT COUNT(*) FROM version");
        executeQuery(&query);
        W_ASSERT(query.next());
        int count = query.value(0).toInt();
        query.finish();
        bool needToRescan = false;

        // Version count is wrong
        if (count != 1) {
            query.prepare("DELETE FROM version");
            executeQuery(&query);
            query.finish();
            query.prepare("INSERT INTO version VALUES(:major, :minor, :patch)");
            query.bindValue(":major", WIDGETS_VERSION_MAJOR);
            query.bindValue(":minor", WIDGETS_VERSION_MINOR);
            query.bindValue(":patch", WIDGETS_VERSION_PATCH);
            executeQuery(&query);
            query.finish();
            needToRescan = true;
        } else {
            query.prepare("SELECT major, minor, patch FROM version");
            executeQuery(&query);
            W_ASSERT(query.next());
            int major = query.value(0).toInt();
            int minor = query.value(1).toInt();
            int patch = query.value(2).toInt();
            Version oldVersion = Version(major, minor, patch);
            Version currentVersion = Version::currentVersion();
            if (currentVersion != oldVersion) {
                needToRescan = true;
            }
        }

        if (needToRescan) {
            query.prepare("UPDATE version SET major=:major, minor=:minor, patch=:patch");
            query.bindValue(":major", WIDGETS_VERSION_MAJOR);
            query.bindValue(":minor", WIDGETS_VERSION_MINOR);
            query.bindValue(":patch", WIDGETS_VERSION_PATCH);
            executeQuery(&query);
            query.finish();

            q->update();
        }
    }
    QSqlDatabase::removeDatabase("init");
}

void PackageManagerPrivate::addPackage(const QString &path)
{
    QDir dir = QDir(path);
    if (!dir.exists("package.desktop")) {
        return;
    }

    QString filePath = dir.absoluteFilePath("package.desktop");
    Package package = Package::fromDesktopFile(filePath);
    if (!package.isValid()) {
        return;
    }

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_package");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO packages (id, identifier, directory, plugin) VALUES (NULL, :identifier, :directory, :plugin)");
        query.bindValue(":identifier", package.identifier());
        query.bindValue(":directory", dir.absolutePath());
        query.bindValue(":plugin", package.plugin());
        executeQuery(&query);
        int packageId = query.lastInsertId().toInt();
        query.finish();

        QVariantList packageIdList;
        QVariantList languages;
        QVariantList names;
        QVariantList descriptions;

        packageIdList.append(packageId);
        languages.append(PACKAGE_INFORMATION_DEFAULT_LANGUAGE);
        names.append(package.defaultName());
        descriptions.append(package.defaultDesription());

        foreach(QString language, package.languages()) {
            packageIdList.append(packageId);
            languages.append(language);
            names.append(package.name(language));
            descriptions.append(package.description(language));
        }
        query.prepare("INSERT INTO localizedPackageInformations (packageId, language, name, description) VALUES (:packageId, ?, ?, ?)");
        query.addBindValue(packageIdList);
        query.addBindValue(languages);
        query.addBindValue(names);
        query.addBindValue(descriptions);
        executeQueryBatch(&query);
        query.finish();
        QVariantMap informations;
        informations.insert(PACKAGE_INFORMATION_AUTHOR, package.author());
        informations.insert(PACKAGE_INFORMATION_EMAIL, package.email());
        informations.insert(PACKAGE_INFORMATION_ICON, package.icon());
        informations.insert(PACKAGE_INFORMATION_WEBSITE, package.website());
        informations.insert(PACKAGE_INFORMATION_VERSION, package.version().toString());
        addPackageInformations(packageId, informations);
    }
    QSqlDatabase::removeDatabase("add_package");
}

void PackageManagerPrivate::addPackageInformations(int packageId,
                                                   const QVariantMap &informations)
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_package_informations");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        QVariantList packageIdList;
        QVariantList informationIdList;
        QVariantList realValues;

        foreach(QString key, informations.keys()) {

            query.prepare("SELECT id FROM packageInformationsProperties WHERE name=:name");
            query.bindValue(":name", key);
            executeQuery(&query);
            if (query.next()) {
                int id = query.value(0).toInt();
                packageIdList.append(packageId);
                informationIdList.append(id);
                realValues.append(informations.value(key));
            }
            query.finish();
        }

        query.prepare("INSERT INTO packageInformations (packageId, informationId, value) VALUES (?, ?, ?)");
        query.addBindValue(packageIdList);
        query.addBindValue(informationIdList);
        query.addBindValue(realValues);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_package_informations");
}

}
