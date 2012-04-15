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

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QElapsedTimer>
#include <QtCore/QSettings>
#include <QtGui/QDesktopServices>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include "desktopparserpackage.h"
#include "version.h"

static const char *CACHE_FOLDER = "Widgets";
static const char *PACKAGE_INFORMATION_AUTHOR = "author";
static const char *PACKAGE_INFORMATION_EMAIL = "email";
static const char *PACKAGE_INFORMATION_ICON = "icon";
static const char *PACKAGE_INFORMATION_WEBSITE = "website";
static const char *PACKAGE_INFORMATION_VERSION = "version";

namespace Widgets
{

class PackageManagerPrivate
{
public:
    PackageManagerPrivate(PackageManager *q);
    static QString databasePath();
    bool executeQuery(QSqlQuery *query);
    bool executeQueryBatch(QSqlQuery *query);
    void addUniquePackageInformationsProperties(const QStringList &names);
    void prepareDatabase();
    void addPackage(const QString &path);
    void addPackageInformations(int packageId, const QVariantMap &informations);
private:
    Q_DECLARE_PUBLIC(PackageManager)
    PackageManager * const q_ptr;
};

PackageManagerPrivate::PackageManagerPrivate(PackageManager *q):
    q_ptr(q)
{
}

QString PackageManagerPrivate::databasePath()
{
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
    if(!dir.cd(CACHE_FOLDER)) {
        dir.mkdir(CACHE_FOLDER);
        dir.cd(CACHE_FOLDER);
    }

    return dir.absoluteFilePath("packagemanager.db");
}

bool PackageManagerPrivate::executeQuery(QSqlQuery *query)
{
    if (!query->exec()) {
        qDebug() << query->lastQuery();
        qDebug() << query->lastError();
        return false;
    }

    return true;
}

bool PackageManagerPrivate::executeQueryBatch(QSqlQuery *query)
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
    Q_Q(PackageManager);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_package_info_properties");
        db.setDatabaseName(databasePath());
        if(!db.open()) {
            emit q->databaseError();
            return;
        }

        QVariantList trueNames;
        QSqlQuery query = QSqlQuery(db);
        foreach (QString name, names) {
            query.prepare("SELECT COUNT(*) FROM packageInformationsProperties WHERE name=:name");
            query.bindValue(":name", name);
            executeQuery(&query);
            query.next();
            int count = query.value(0).toInt();
            query.finish();
            if (count == 0) {
                trueNames.append(name);
            }
        }

        query.prepare("INSERT INTO packageInformationsProperties (id, name) VALUES (NULL, :name)");
        query.addBindValue(trueNames);
        executeQueryBatch(&query);
        query.finish();
        db.close();
    }
    QSqlDatabase::removeDatabase("add_package_info_properties");
}

void PackageManagerPrivate::prepareDatabase()
{
    Q_Q(PackageManager);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "init");
        db.setDatabaseName(databasePath());
        if(!db.open()) {
            emit q->databaseError();
            return;
        }

        // Create tables if they do not exist
        QSqlQuery query = QSqlQuery(db);
        query.prepare("CREATE TABLE IF NOT EXISTS version (major INTEGER, minor INTEGER, patch INTEGER)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS packages (id INTEGER PRIMARY KEY AUTOINCREMENT, identifier STRING, folder STRING, plugin STRING)");
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
        query.next();
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
            query.next();
            int major = query.value(0).toInt();
            int minor = query.value(1).toInt();
            int patch = query.value(2).toInt();
            Version oldVersion = Version(major, minor, patch);
            Version currentVersion = Version::currentVersion();
            if (currentVersion != oldVersion) {
                needToRescan = true;
            }
        }

//        if (needToRescan) {
            query.prepare("UPDATE version SET major=:major, minor=:minor, patch=:patch");
            query.bindValue(":major", WIDGETS_VERSION_MAJOR);
            query.bindValue(":minor", WIDGETS_VERSION_MINOR);
            query.bindValue(":patch", WIDGETS_VERSION_PATCH);
            executeQuery(&query);
            query.finish();

            q->update();
//        }

        db.close();
    }
    QSqlDatabase::removeDatabase("init");
}

void PackageManagerPrivate::addPackage(const QString &path)
{
    Q_Q(PackageManager);

    QDir dir = QDir(path);
    if (!dir.exists("package.desktop")) {
        return;
    }

    DesktopParserPackage parser (dir.absoluteFilePath("package.desktop"));
    if (!parser.isValid()) {
        return;
    }

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_package");
        db.setDatabaseName(databasePath());
        if(!db.open()) {
            emit q->databaseError();
            return;
        }

        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO packages (id, identifier, folder, plugin) VALUES (NULL, :identifier, :folder, :plugin)");
        query.bindValue(":identifier", parser.identifier());
        query.bindValue(":folder", dir.absolutePath());
        query.bindValue(":plugin", parser.plugin());
        executeQuery(&query);
        int packageId = query.lastInsertId().toInt();
        query.finish();

        QVariantList packageIdList;
        QVariantList languages;
        QVariantList names;
        QVariantList descriptions;

        foreach(QString lang, parser.languages()) {
            packageIdList.append(packageId);
            languages.append(lang);
            names.append(parser.name(lang));
            descriptions.append(parser.comment(lang));
        }
        query.prepare("INSERT INTO localizedPackageInformations (packageId, language, name, description) VALUES (:packageId, ?, ?, ?)");
        query.addBindValue(packageIdList);
        query.addBindValue(languages);
        query.addBindValue(names);
        query.addBindValue(descriptions);
        executeQueryBatch(&query);
        query.finish();
        QVariantMap informations;
        informations.insert(PACKAGE_INFORMATION_AUTHOR, parser.author());
        informations.insert(PACKAGE_INFORMATION_EMAIL, parser.email());
        informations.insert(PACKAGE_INFORMATION_ICON, parser.icon());
        informations.insert(PACKAGE_INFORMATION_WEBSITE, parser.webSite());
        informations.insert(PACKAGE_INFORMATION_VERSION, parser.version().toString());
        addPackageInformations(packageId, informations);

        db.close();
    }
    QSqlDatabase::removeDatabase("add_package");
}

void PackageManagerPrivate::addPackageInformations(int packageId,
                                                   const QVariantMap &informations)
{
    Q_Q(PackageManager);

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_package_informations");
        db.setDatabaseName(databasePath());
        if(!db.open()) {
            emit q->databaseError();
            return;
        }

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

        db.close();
    }
    QSqlDatabase::removeDatabase("add_package_informations");
}

////// End of private class //////

PackageManager::PackageManager(QObject *parent) :
    QObject(parent), d_ptr(new PackageManagerPrivate(this))
{
    Q_D(PackageManager);
    QElapsedTimer timer;
    timer.start();
    d->prepareDatabase();
    qDebug() << timer.elapsed();
    timer.invalidate();
}

PackageManager::~PackageManager()
{
}

void PackageManager::update()
{
    Q_D(PackageManager);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "update");
        db.setDatabaseName(d->databasePath());
        if(!db.open()) {
            emit databaseError();
            return;
        }

        QSqlQuery query = QSqlQuery(db);
        query.prepare("DELETE FROM packages");
        d->executeQuery(&query);
        query.finish();

        query.prepare("DELETE FROM localizedPackageInformations");
        d->executeQuery(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("update");

    // First search in system widgets directories
    QDir systemDir = QDir(SYSTEM_WIDGETS);
    QFileInfoList folders = systemDir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);

    foreach (QFileInfo folder, folders) {
        d->addPackage(folder.absoluteFilePath());
    }

}

}
