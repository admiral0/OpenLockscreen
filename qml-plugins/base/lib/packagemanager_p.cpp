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

#include "widgets_global.h"
#include "dockbaseproperties.h"
#include "widgetbaseproperties.h"

namespace Widgets
{

PackageManagerPrivate::PackageManagerPrivate(PackageManager *q):
    q_ptr(q)
{
}

QString PackageManagerPrivate::databasePath() const
{
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
    QDir::root().mkpath(dir.absolutePath());
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

void PackageManagerPrivate::addComponentType(const QStringList &names)
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_component_type");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QVariantList trueNames;
        QSqlQuery query = QSqlQuery(db);
        foreach (QString name, names) {
            query.prepare("SELECT COUNT(*) FROM componentType WHERE name=:name");
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

        query.prepare("INSERT INTO componentType (id, name) VALUES (NULL, :name)");
        query.addBindValue(trueNames);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_component_type");
}

void PackageManagerPrivate::addComponentInformationProperties(const QStringList &names)
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE",
                                                    "add_component_information_properties");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QVariantList trueNames;
        QSqlQuery query = QSqlQuery(db);
        foreach (QString name, names) {
            query.prepare("SELECT COUNT(*) FROM componentInformationProperties WHERE name=:name");
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

        query.prepare("INSERT INTO componentInformationProperties (id, name) VALUES (NULL, :name)");
        query.addBindValue(trueNames);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_component_information_properties");
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

        query.prepare("CREATE TABLE IF NOT EXISTS packages (id INTEGER PRIMARY KEY, identifier STRING, directory STRING, plugin STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS componentType (id INTEGER PRIMARY KEY, name STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS componentInformationProperties (id INTEGER PRIMARY KEY, name STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS componentInformation (componentTypeId INTEGER, componentId INTEGER, informationId INTEGER, value STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS componentLocalizedInformation (componentTypeId INTEGER, componentId INTEGER, language STRING, name STRING, description STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS docks (id INTEGER PRIMARY KEY, packageId INTEGER, directory STRING, file STRING)");
        executeQuery(&query);
        query.finish();

        query.prepare("CREATE TABLE IF NOT EXISTS widgets (id INTEGER PRIMARY KEY, packageId INTEGER, directory STRING, file STRING)");
        executeQuery(&query);
        query.finish();

        QStringList componentTypes;
        componentTypes.append(COMPONENT_TYPE_PACKAGE);
        componentTypes.append(COMPONENT_TYPE_DOCK);
        componentTypes.append(COMPONENT_TYPE_WIDGET);
        addComponentType(componentTypes);

        QStringList componentInformationProperties;
        componentInformationProperties.append(COMPONENT_INFORMATION_ICON);
        componentInformationProperties.append(COMPONENT_INFORMATION_SETTINGS_ENABLED);
        componentInformationProperties.append(PACKAGE_INFORMATION_AUTHOR);
        componentInformationProperties.append(PACKAGE_INFORMATION_EMAIL);
        componentInformationProperties.append(PACKAGE_INFORMATION_WEBSITE);
        componentInformationProperties.append(PACKAGE_INFORMATION_VERSION);
        componentInformationProperties.append(COMPONENT_INFORMATION_WIDTH);
        componentInformationProperties.append(COMPONENT_INFORMATION_HEIGHT);
        componentInformationProperties.append(DOCK_INFORMATION_ANCHORS_TOP);
        componentInformationProperties.append(DOCK_INFORMATION_ANCHORS_BOTTOM);
        componentInformationProperties.append(DOCK_INFORMATION_ANCHORS_LEFT);
        componentInformationProperties.append(DOCK_INFORMATION_ANCHORS_RIGHT);
        addComponentInformationProperties(componentInformationProperties);

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

int PackageManagerPrivate::componentTypeId(const char *type) const
{
    int id = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_component_type_id");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());
        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT id FROM componentType WHERE name=:name");
        query.bindValue(":name", QString(type));
        executeQuery(&query);
        if (query.next()) {
            id = query.value(0).toInt();
        }

        query.finish();
    }
    QSqlDatabase::removeDatabase("get_component_type_id");
    return id;
}

void PackageManagerPrivate::addInformation(const char *type,
                                            int componentId,
                                            const QVariantMap &informations)
{
    int typeId = componentTypeId(type);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_information");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        QVariantList typeIdList;
        QVariantList componentIdList;
        QVariantList informationIdList;
        QVariantList realValues;

        foreach(QString key, informations.keys()) {

            query.prepare("SELECT id FROM componentInformationProperties WHERE name=:name");
            query.bindValue(":name", key);
            executeQuery(&query);
            if (query.next()) {
                int id = query.value(0).toInt();
                typeIdList.append(typeId);
                componentIdList.append(componentId);
                informationIdList.append(id);
                realValues.append(informations.value(key));
            }
            query.finish();
        }

        query.prepare("INSERT INTO componentInformation (componentTypeId, componentId, informationId, value) VALUES (?, ?, ?, ?)");
        query.addBindValue(typeIdList);
        query.addBindValue(componentIdList);
        query.addBindValue(informationIdList);
        query.addBindValue(realValues);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_information");
}

void PackageManagerPrivate::addLocalizedInformation(const char *type, int componentId,
                                                    const QStringList &languages,
                                                    const QStringList &names,
                                                    const QStringList &descriptions)
{
    Q_ASSERT(languages.count() == names.count());
    Q_ASSERT(languages.count() == descriptions.count());

    int typeId = componentTypeId(type);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_localized_information");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        QVariantList typeIdList;
        QVariantList componentIdList;
        QVariantList languageList;
        QVariantList nameList;
        QVariantList descriptionList;

        for (int i = 0; i < languages.count(); i++) {
            typeIdList.append(typeId);
            componentIdList.append(componentId);
            languageList.append(languages.at(i));
            nameList.append(names.at(i));
            descriptionList.append(descriptions.at(i));
        }


        query.prepare("INSERT INTO componentLocalizedInformation (componentTypeId, componentId, language, name, description) VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(typeIdList);
        query.addBindValue(componentIdList);
        query.addBindValue(languageList);
        query.addBindValue(nameList);
        query.addBindValue(descriptionList);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_localized_information");
}

void PackageManagerPrivate::addPackage(const QString &path)
{
    QDir dir = QDir(path);
    if (!dir.exists("package.desktop")) {
        return;
    }

    QString filePath = dir.absoluteFilePath("package.desktop");
    Package *package = Package::fromDesktopFile(filePath);
    if (!package->isValid()) {
        return;
    }

    int packageId = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_package");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO packages (id, identifier, directory, plugin) VALUES (NULL, :identifier, :directory, :plugin)");
        query.bindValue(":identifier", package->identifier());
        query.bindValue(":directory", dir.absolutePath());
        query.bindValue(":plugin", package->plugin());
        executeQuery(&query);
        packageId = query.lastInsertId().toInt();
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_package");

    QStringList languages;
    QStringList names;
    QStringList descriptions;

    languages.append(COMPONENT_INFORMATION_DEFAULT_LANGUAGE);
    names.append(package->defaultName());
    descriptions.append(package->defaultDescription());

    foreach(QString language, package->languages()) {
        languages.append(language);
        names.append(package->name(language));
        descriptions.append(package->description(language));
    }
    addLocalizedInformation(COMPONENT_TYPE_PACKAGE, packageId, languages, names, descriptions);

    QVariantMap informations;
    informations.insert(COMPONENT_INFORMATION_ICON, package->icon());
    informations.insert(PACKAGE_INFORMATION_AUTHOR, package->author());
    informations.insert(PACKAGE_INFORMATION_EMAIL, package->email());
    informations.insert(PACKAGE_INFORMATION_WEBSITE, package->website());
    informations.insert(PACKAGE_INFORMATION_VERSION, package->version().toString());
    addInformation(COMPONENT_TYPE_PACKAGE, packageId, informations);

    scanPackageFolder(packageId, path, package->identifier());

    package->deleteLater();
}

void PackageManagerPrivate::scanPackageFolder(int packageId, const QString &path,
                                              const QString &packageIdentifier)
{
    // Scan docks
    QDir packageFolder (path);
    if (packageFolder.cd(DOCKS_FOLDER)) {

        QFileInfoList folders = packageFolder.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);

        foreach (QFileInfo folderInfo, folders) {
            QDir folder (folderInfo.absoluteFilePath());

            QString metadata = folder.absoluteFilePath("metadata.desktop");
            DockBaseProperties *dock = DockBaseProperties::fromDesktopFile(metadata,
                                                                           packageIdentifier);
            if (dock->isValid()) {
                addDock(packageId, folderInfo.fileName(), dock);
            }
        }
    }
    packageFolder = QDir(path);
    if (packageFolder.cd(WIDGETS_FOLDER)) {

        QFileInfoList folders = packageFolder.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);

        foreach (QFileInfo folderInfo, folders) {
            QDir folder (folderInfo.absoluteFilePath());

            QString metadata = folder.absoluteFilePath("metadata.desktop");
            WidgetBaseProperties *widget =
                    WidgetBaseProperties::fromDesktopFile(metadata, packageIdentifier);
            if (widget->isValid()) {
                addWidget(packageId, folderInfo.fileName(), widget);
            }
        }
    }
}

void PackageManagerPrivate::addDock(int packageId, const QString &subdirectory,
                                    DockBaseProperties *dock)
{

    int dockId = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_dock");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO docks (id, packageId, directory, file) VALUES (NULL, :packageId, :packageDirectory, :file)");
        query.bindValue(":packageId", packageId);
        query.bindValue(":packageDirectory", subdirectory);
        query.bindValue(":file", dock->fileName());
        executeQuery(&query);
        dockId = query.lastInsertId().toInt();
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_dock");

    QStringList languages;
    QStringList names;
    QStringList descriptions;

    languages.append(COMPONENT_INFORMATION_DEFAULT_LANGUAGE);
    names.append(dock->defaultName());
    descriptions.append(dock->defaultDescription());

    foreach(QString language, dock->languages()) {
        languages.append(language);
        names.append(dock->name(language));
        descriptions.append(dock->description(language));
    }
    addLocalizedInformation(COMPONENT_TYPE_DOCK, dockId, languages, names, descriptions);

    QVariantMap informations;
    informations.insert(COMPONENT_INFORMATION_ICON, dock->icon());
    informations.insert(COMPONENT_INFORMATION_SETTINGS_ENABLED, dock->isSettingsEnabled());
    informations.insert(COMPONENT_INFORMATION_WIDTH, dock->width());
    informations.insert(COMPONENT_INFORMATION_HEIGHT, dock->height());
    informations.insert(DOCK_INFORMATION_ANCHORS_TOP, dock->anchorsTop());
    informations.insert(DOCK_INFORMATION_ANCHORS_BOTTOM, dock->anchorsBottom());
    informations.insert(DOCK_INFORMATION_ANCHORS_LEFT, dock->anchorsLeft());
    informations.insert(DOCK_INFORMATION_ANCHORS_RIGHT, dock->anchorsRight());
    addInformation(COMPONENT_TYPE_DOCK, dockId, informations);

    dock->deleteLater();
}

void PackageManagerPrivate::addWidget(int packageId, const QString &subdirectory,
                                      WidgetBaseProperties *widget)
{

    int widgetId = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_widget");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO widgets (id, packageId, directory, file) VALUES (NULL, :packageId, :packageDirectory, :file)");
        query.bindValue(":packageId", packageId);
        query.bindValue(":packageDirectory", subdirectory);
        query.bindValue(":file", widget->fileName());
        executeQuery(&query);
        widgetId = query.lastInsertId().toInt();
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_widget");

    QStringList languages;
    QStringList names;
    QStringList descriptions;

    languages.append(COMPONENT_INFORMATION_DEFAULT_LANGUAGE);
    names.append(widget->defaultName());
    descriptions.append(widget->defaultDescription());

    foreach(QString language, widget->languages()) {
        languages.append(language);
        names.append(widget->name(language));
        descriptions.append(widget->description(language));
    }
    addLocalizedInformation(COMPONENT_TYPE_WIDGET, widgetId, languages, names, descriptions);

    QVariantMap informations;
    informations.insert(COMPONENT_INFORMATION_ICON, widget->icon());
    informations.insert(COMPONENT_INFORMATION_SETTINGS_ENABLED, widget->isSettingsEnabled());
    informations.insert(COMPONENT_INFORMATION_WIDTH, widget->width());
    informations.insert(COMPONENT_INFORMATION_HEIGHT, widget->height());
    addInformation(COMPONENT_TYPE_WIDGET, widgetId, informations);

    widget->deleteLater();
}

}
