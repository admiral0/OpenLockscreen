/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

/**
 * @internal
 * @file databaseinterface_p.cpp
 * @short Implementation of Widgets::Provider::PackageManager::DatabaseInterface
 */

#include "databaseinterface_p.h"
#include "databaseinterface_p_p.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtGui/QDesktopServices>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include "widgets_global.h"
#include "filterconditionlist.h"
#include "package.h"
#include "tools.h"
#include "version.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

// DB strings
/**
 * @internal
 * @brief COMPONENT_TYPE_PACKAGE
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *COMPONENT_TYPE_PACKAGE = "package";
/**
 * @internal
 * @brief COMPONENT_TYPE_DOCK
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *COMPONENT_TYPE_DOCK = "dock";
/**
 * @internal
 * @brief COMPONENT_TYPE_WIDGET
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *COMPONENT_TYPE_WIDGET = "widget";

/**
 * @internal
 * @brief COMPONENT_INFORMATION_ICON
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *COMPONENT_INFORMATION_ICON = "icon";
/**
 * @internal
 * @brief COMPONENT_INFORMATION_SETTINGS_FILE
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *COMPONENT_INFORMATION_SETTINGS_FILE = "settings_file";
/**
 * @internal
 * @brief COMPONENT_INFORMATION_DEFAULT_LANGUAGE
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *COMPONENT_INFORMATION_DEFAULT_LANGUAGE = "default";

/**
 * @internal
 * @brief PACKAGE_INFORMATION_AUTHOR
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *PACKAGE_INFORMATION_AUTHOR = "package_author";
/**
 * @internal
 * @brief PACKAGE_INFORMATION_EMAIL
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *PACKAGE_INFORMATION_EMAIL = "package_email";
/**
 * @internal
 * @brief PACKAGE_INFORMATION_WEBSITE
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *PACKAGE_INFORMATION_WEBSITE = "package_website";
/**
 * @internal
 * @brief PACKAGE_INFORMATION_VERSION
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *PACKAGE_INFORMATION_VERSION = "package_version";
/**
 * @internal
 * @brief PACKAGE_INFORMATION_VISIBLE
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *PACKAGE_INFORMATION_VISIBLE = "package_visible";

/**
 * @internal
 * @brief DOCK_INFORMATION_WIDTH
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *DOCK_INFORMATION_WIDTH = "width";
/**
 * @internal
 * @brief DOCK_INFORMATION_HEIGHT
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *DOCK_INFORMATION_HEIGHT = "height";
/**
 * @internal
 * @brief DOCK_INFORMATION_ANCHORS_TOP
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *DOCK_INFORMATION_ANCHORS_TOP = "dock_anchors_top";
/**
 * @internal
 * @brief DOCK_INFORMATION_ANCHORS_BOTTOM
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *DOCK_INFORMATION_ANCHORS_BOTTOM = "dock_anchors_bottom";
/**
 * @internal
 * @brief DOCK_INFORMATION_ANCHORS_LEFT
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *DOCK_INFORMATION_ANCHORS_LEFT = "dock_anchors_left";
/**
 * @internal
 * @brief DOCK_INFORMATION_ANCHORS_RIGHT
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *DOCK_INFORMATION_ANCHORS_RIGHT = "dock_anchors_right";

/**
 * @internal
 * @brief WIDGET_INFORMATION_MINIMUM_WIDTH
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *WIDGET_INFORMATION_MINIMUM_WIDTH = "minimum_width";
/**
 * @internal
 * @brief WIDGET_INFORMATION_MINIMUM_HEIGHT
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *WIDGET_INFORMATION_MINIMUM_HEIGHT = "minimum_height";
/**
 * @internal
 * @brief WIDGET_INFORMATION_MAXIMUM_WIDTH
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *WIDGET_INFORMATION_MAXIMUM_WIDTH = "maximum_width";
/**
 * @internal
 * @brief WIDGET_INFORMATION_MAXIMUM_HEIGHT
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *WIDGET_INFORMATION_MAXIMUM_HEIGHT = "maximum_height";

// Folder strings
/**
 * @internal
 * @brief WIDGETS_FOLDER
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *WIDGETS_FOLDER = "widgets";
/**
 * @internal
 * @brief DOCKS_FOLDER
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *DOCKS_FOLDER = "docks";

// File strings
/**
 * @internal
 * @brief PACKAGE_FILE
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *PACKAGE_FILE = "package.desktop";
/**
 * @internal
 * @brief METADATA_FILE
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *METADATA_FILE = "metadata.desktop";


// Disambiguation strings
/**
 * @internal
 * @brief PACKAGE_IDENTIFIER_KEY
 *
 * Used in Widgets::Provider::PackageManager::DatabaseInterface.
 */
static const char *PACKAGE_IDENTIFIER_KEY = "identifier";


QString DatabaseInterfacePrivate::databasePath()
{
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
    QDir::root().mkpath(dir.absolutePath());
    return dir.absoluteFilePath("packagemanager.db");
}

bool DatabaseInterfacePrivate::executeQuery(QSqlQuery *query)
{
    if (!query->exec()) {
        qDebug() << query->lastQuery();
        qDebug() << query->lastError();
        return false;
    }

    return true;
}

bool DatabaseInterfacePrivate::executeQuery(const QString &query, const QSqlDatabase &db)
{
    QSqlQuery sqlQuery (db);
    sqlQuery.prepare(query);
    bool ok = executeQuery(&sqlQuery);
    sqlQuery.finish();
    return ok;
}

bool DatabaseInterfacePrivate::executeQueryBatch(QSqlQuery *query)
{
    if (!query->execBatch()) {
        qDebug() << query->lastQuery();
        qDebug() << query->lastError();
        return false;
    }

    return true;
}

int DatabaseInterfacePrivate::executeQueryCount(QSqlQuery *query)
{
    W_ASSERT(executeQuery(query));
    W_ASSERT(query->next());
    int count = query->value(0).toInt();
    query->finish();

    return count;
}

void DatabaseInterfacePrivate::prepareDatabase()
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "init");

        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        // Create tables if they do not exist
        executeQuery("CREATE TABLE IF NOT EXISTS version \
                      (major INTEGER, \
                       minor INTEGER, \
                       patch INTEGER)", db);
        executeQuery("CREATE TABLE IF NOT EXISTS packages \
                      (id INTEGER PRIMARY KEY, \
                       identifier STRING, directory \
                       STRING, plugin STRING)", db);
        executeQuery("CREATE TABLE IF NOT EXISTS componentType \
                      (id INTEGER PRIMARY KEY, \
                       name STRING)", db);
        executeQuery("CREATE TABLE IF NOT EXISTS componentInformationProperties \
                      (id INTEGER PRIMARY KEY, \
                       name STRING)", db);
        executeQuery("CREATE TABLE IF NOT EXISTS componentInformation \
                      (componentTypeId INTEGER, componentId INTEGER, \
                       informationId INTEGER, value STRING)", db);
        executeQuery("CREATE TABLE IF NOT EXISTS componentLocalizedInformation \
                      (componentTypeId INTEGER, \
                       componentId INTEGER, \
                       language STRING, \
                       name STRING, \
                       description STRING)", db);

        executeQuery("CREATE TABLE IF NOT EXISTS docks \
                      (id INTEGER PRIMARY KEY, \
                       packageId INTEGER, \
                       directory STRING, \
                       file STRING)", db);
        executeQuery("CREATE TABLE IF NOT EXISTS widgets \
                      (id INTEGER PRIMARY KEY, \
                       packageId INTEGER, directory \
                       STRING, file STRING)", db);

        executeQuery("CREATE TABLE IF NOT EXISTS tags \
                      (id INTEGER PRIMARY KEY, \
                       name STRING)", db);
        executeQuery("CREATE TABLE IF NOT EXISTS packageTags \
                      (packageId INTEGER, \
                       tagId INTEGER)", db);

        // Create the component types
        QStringList componentTypes;
        componentTypes.append(COMPONENT_TYPE_PACKAGE);
        componentTypes.append(COMPONENT_TYPE_DOCK);
        componentTypes.append(COMPONENT_TYPE_WIDGET);
        addComponentType(componentTypes);

        // Create the component information properties
        QStringList componentInformationProperties;
        componentInformationProperties.append(COMPONENT_INFORMATION_ICON);
        componentInformationProperties.append(COMPONENT_INFORMATION_SETTINGS_FILE);
        componentInformationProperties.append(PACKAGE_INFORMATION_AUTHOR);
        componentInformationProperties.append(PACKAGE_INFORMATION_EMAIL);
        componentInformationProperties.append(PACKAGE_INFORMATION_WEBSITE);
        componentInformationProperties.append(PACKAGE_INFORMATION_VERSION);
        componentInformationProperties.append(PACKAGE_INFORMATION_VISIBLE);
        componentInformationProperties.append(DOCK_INFORMATION_WIDTH);
        componentInformationProperties.append(DOCK_INFORMATION_HEIGHT);
        componentInformationProperties.append(DOCK_INFORMATION_ANCHORS_TOP);
        componentInformationProperties.append(DOCK_INFORMATION_ANCHORS_BOTTOM);
        componentInformationProperties.append(DOCK_INFORMATION_ANCHORS_LEFT);
        componentInformationProperties.append(DOCK_INFORMATION_ANCHORS_RIGHT);
        componentInformationProperties.append(WIDGET_INFORMATION_MINIMUM_WIDTH);
        componentInformationProperties.append(WIDGET_INFORMATION_MINIMUM_HEIGHT);
        componentInformationProperties.append(WIDGET_INFORMATION_MAXIMUM_WIDTH);
        componentInformationProperties.append(WIDGET_INFORMATION_MAXIMUM_HEIGHT);
        addComponentInformationProperties(componentInformationProperties);

        // Check version
        QSqlQuery query (db);
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
        }
    }
    QSqlDatabase::removeDatabase("init");
}

void DatabaseInterfacePrivate::addComponentType(const QStringList &names)
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
            int count = executeQueryCount(&query);
            Q_ASSERT(count == 0 || count == 1);
            if (count == 0) {
                trueNames.append(name);
            }
        }

        query.prepare("INSERT OR REPLACE INTO componentType (id, name) VALUES (NULL, :name)");
        query.addBindValue(trueNames);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_component_type");
}

void DatabaseInterfacePrivate::addComponentInformationProperties(const QStringList &names)
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

        query.prepare("INSERT OR REPLACE INTO componentInformationProperties (id, name) \
                       VALUES (NULL, :name)");
        query.addBindValue(trueNames);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_component_information_properties");
}

qlonglong DatabaseInterfacePrivate::componentTypeId(const char *type)
{
    qlonglong id = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_component_type_id");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());
        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT id FROM componentType WHERE name=:name");
        query.bindValue(":name", QString(type));
        executeQuery(&query);
        if (query.next()) {
            id = query.value(0).toLongLong();
        }

        query.finish();
    }
    QSqlDatabase::removeDatabase("get_component_type_id");
    return id;
}

void DatabaseInterfacePrivate::addLocalizedInformation(const char *type, qlonglong componentId,
                                                       const QStringList &languages,
                                                       const QStringList &names,
                                                       const QStringList &descriptions)
{
    Q_ASSERT(languages.count() == names.count());
    Q_ASSERT(languages.count() == descriptions.count());

    qlonglong typeId = componentTypeId(type);
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


        query.prepare("INSERT OR REPLACE INTO componentLocalizedInformation \
                      (componentTypeId, componentId, language, name, description) \
                      VALUES (?, ?, ?, ?, ?)");
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


void DatabaseInterfacePrivate::addInformation(const char *type, qlonglong componentId,
                                              const QVariantMap &informations)
{
    qlonglong typeId = componentTypeId(type);
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

        query.prepare("INSERT INTO componentInformation \
                      (componentTypeId, componentId, informationId, value) \
                      VALUES (?, ?, ?, ?)");
        query.addBindValue(typeIdList);
        query.addBindValue(componentIdList);
        query.addBindValue(informationIdList);
        query.addBindValue(realValues);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_information");
}

qlonglong DatabaseInterfacePrivate::tagId(const QString &tag)
{
    qlonglong id = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "tag_id");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT id FROM tags WHERE name=:name");
        query.bindValue(":name", tag);
        executeQuery(&query);

        if (query.next()) {
            id = query.value(0).toInt();
        }

        if (id == -1) {
            query.prepare("INSERT INTO tags (id, name) VALUES (NULL, :name)");
            query.bindValue(":name", tag);
            executeQuery(&query);
            id = query.lastInsertId().toInt();
        }

        query.finish();
    }
    QSqlDatabase::removeDatabase("tag_id");
    return id;
}

bool DatabaseInterfacePrivate::tagExists(qlonglong packageId, const QString &tag)
{
    qlonglong id = tagId(tag);
    bool exists = false;

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "tag_exists");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT COUNT(*) FROM packageTags \
                      WHERE packageId=:packageId AND tagId=:tagId");
        query.bindValue(":packageId", packageId);
        query.bindValue(":tagId", id);
        int count = executeQueryCount(&query);
        exists = (count > 0);

        query.finish();
    }
    QSqlDatabase::removeDatabase("tag_exists");

    return exists;
}

void DatabaseInterfacePrivate::addTags(qlonglong packageId, const QStringList &tags)
{
    QVariantList packageIdList;
    QVariantList tagIdList;
    foreach(QString tag, tags) {
        if (!tagExists(packageId, tag)) {
            packageIdList.append(packageId);
            tagIdList.append(tagId(tag));
        }
    }

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_tag");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO packageTags (packageId, tagId) VALUES (?, ?)");
        query.addBindValue(packageIdList);
        query.addBindValue(tagIdList);
        executeQueryBatch(&query);
        query.finish();
    }
    QSqlDatabase::removeDatabase("add_tag");
}

void DatabaseInterfacePrivate::addPackage(Package *package, const QString &path)
{
    if (!package) {
        return;
    }

    bool inserted = false;

    qlonglong packageId = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_package");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT COUNT(*) FROM packages WHERE identifier=:identifier");
        query.bindValue(":identifier", package->identifier());
        int count = executeQueryCount(&query);
        if (count == 0) {
            query.prepare("INSERT INTO packages (id, identifier, directory, plugin) \
                          VALUES (NULL, :identifier, :directory, :plugin)");
            query.bindValue(":identifier", package->identifier());
            query.bindValue(":directory", path);
            query.bindValue(":plugin", package->plugin());
            executeQuery(&query);
            packageId = query.lastInsertId().toLongLong();
            query.finish();
        } else {
            inserted = true;
        }
    }
    QSqlDatabase::removeDatabase("add_package");

    if (inserted) {
        return;
    }

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
    informations.insert(PACKAGE_INFORMATION_VISIBLE, package->isVisible());
    addInformation(COMPONENT_TYPE_PACKAGE, packageId, informations);

    addTags(packageId, package->tags());
}

qlonglong DatabaseInterfacePrivate::packageId(const QString &packageIdentifier)
{
    qlonglong returnedValue = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_package_id");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT id FROM packages WHERE identifier=:identifier");
        query.bindValue(":identifier", packageIdentifier);
        executeQuery(&query);
        if (query.next()) {
            returnedValue = query.value(0).toInt();
        }

    }
    QSqlDatabase::removeDatabase("get_package_id");
    return returnedValue;
}

void DatabaseInterfacePrivate::addDock(qlonglong packageId, const QString &subdirectory,
                                       Docks::DockBaseProperties *dock, ComponentMetadata *metadata)
{
    if (!dock) {
        return;
    }

    bool inserted = false;

    qlonglong dockId = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_dock");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT COUNT(*) FROM docks WHERE packageId=:packageId \
                       AND directory=:packageDirectory AND file=:file");
        query.bindValue(":packageId", packageId);
        query.bindValue(":packageDirectory", subdirectory);
        query.bindValue(":file", metadata->fileName());
        int count = executeQueryCount(&query);
        if (count == 0) {
            query.prepare("INSERT INTO docks (id, packageId, directory, file) \
                          VALUES (NULL, :packageId, :packageDirectory, :file)");
            query.bindValue(":packageId", packageId);
            query.bindValue(":packageDirectory", subdirectory);
            query.bindValue(":file", metadata->fileName());
            executeQuery(&query);
            dockId = query.lastInsertId().toInt();
            query.finish();
        } else {
            inserted = true;
        }
    }
    QSqlDatabase::removeDatabase("add_dock");

    if (inserted) {
        return;
    }

    QStringList languages;
    QStringList names;
    QStringList descriptions;

    languages.append(COMPONENT_INFORMATION_DEFAULT_LANGUAGE);
    names.append(metadata->defaultName());
    descriptions.append(metadata->defaultDescription());

    foreach(QString language, metadata->languages()) {
        languages.append(language);
        names.append(metadata->name(language));
        descriptions.append(metadata->description(language));
    }
    addLocalizedInformation(COMPONENT_TYPE_DOCK, dockId, languages, names, descriptions);

    QVariantMap informations;
    informations.insert(COMPONENT_INFORMATION_ICON, metadata->icon());
    informations.insert(COMPONENT_INFORMATION_SETTINGS_FILE, metadata->settingsFileName());
    informations.insert(DOCK_INFORMATION_WIDTH, dock->width());
    informations.insert(DOCK_INFORMATION_HEIGHT, dock->height());
    informations.insert(DOCK_INFORMATION_ANCHORS_TOP, dock->anchorsTop());
    informations.insert(DOCK_INFORMATION_ANCHORS_BOTTOM, dock->anchorsBottom());
    informations.insert(DOCK_INFORMATION_ANCHORS_LEFT, dock->anchorsLeft());
    informations.insert(DOCK_INFORMATION_ANCHORS_RIGHT, dock->anchorsRight());
    addInformation(COMPONENT_TYPE_DOCK, dockId, informations);

    dock->deleteLater();
}

void DatabaseInterfacePrivate::addWidget(qlonglong packageId, const QString &subdirectory,
                                         WidgetBaseProperties *widget, ComponentMetadata *metadata)
{
    if (!widget) {
        return;
    }

    bool inserted = false;

    qlonglong widgetId = -1;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "add_widget");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT COUNT(*) FROM widgets WHERE packageId=:packageId \
                       AND directory=:packageDirectory AND file=:file");
        query.bindValue(":packageId", packageId);
        query.bindValue(":packageDirectory", subdirectory);
        query.bindValue(":file", metadata->fileName());
        int count = executeQueryCount(&query);


        if (count == 0) {
            query.prepare("INSERT INTO widgets (id, packageId, directory, file) \
                          VALUES (NULL, :packageId, :packageDirectory, :file)");
            query.bindValue(":packageId", packageId);
            query.bindValue(":packageDirectory", subdirectory);
            query.bindValue(":file", metadata->fileName());
            executeQuery(&query);
            widgetId = query.lastInsertId().toInt();
            query.finish();
        } else {
            inserted = true;
        }
    }
    QSqlDatabase::removeDatabase("add_widget");

    if (inserted) {
        return;
    }

    QStringList languages;
    QStringList names;
    QStringList descriptions;

    languages.append(COMPONENT_INFORMATION_DEFAULT_LANGUAGE);
    names.append(metadata->defaultName());
    descriptions.append(metadata->defaultDescription());

    foreach(QString language, metadata->languages()) {
        languages.append(language);
        names.append(metadata->name(language));
        descriptions.append(metadata->description(language));
    }
    addLocalizedInformation(COMPONENT_TYPE_WIDGET, widgetId, languages, names, descriptions);

    QVariantMap informations;
    informations.insert(COMPONENT_INFORMATION_ICON, metadata->icon());
    informations.insert(COMPONENT_INFORMATION_SETTINGS_FILE, metadata->settingsFileName());
    informations.insert(WIDGET_INFORMATION_MINIMUM_WIDTH, widget->minimumWidth());
    informations.insert(WIDGET_INFORMATION_MINIMUM_HEIGHT, widget->minimumHeight());
    informations.insert(WIDGET_INFORMATION_MAXIMUM_WIDTH, widget->maximumWidth());
    informations.insert(WIDGET_INFORMATION_MAXIMUM_HEIGHT, widget->maximumHeight());
    addInformation(COMPONENT_TYPE_WIDGET, widgetId, informations);

    widget->deleteLater();
}

QStringList DatabaseInterfacePrivate::registeredPackages(FilterConditionList *filter)
{
    QStringList returnedValues;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_registered_packages");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        QStringList tags;
        if (filter) {
            tags = filter->tags();
        }
        if (tags.isEmpty()) {
            query.prepare("SELECT DISTINCT packages.identifier FROM packages");
        } else {
            QStringList queryConditions;
            QString queryString = "SELECT DISTINCT packages.identifier \
                                    FROM packages INNER JOIN packageTags \
                                    ON packages.id=packageTags.packageId \
                                    INNER JOIN tags ON \
                                    packageTags.tagId=tags.id \
                                    INNER JOIN componentInformation ON \
                                    componentInformation.componentId=packages.id\
                                    INNER JOIN componentInformationProperties ON \
                                    componentInformation.informationId\
                                    =componentInformationProperties.id\
                                    WHERE componentInformation.componentTypeId=?\
                                    AND componentInformationProperties.name=?\
                                    AND componentInformation.value=? AND %1";
            for (int i = 0; i < tags.count(); i++) {
                queryConditions.append("tags.name=?");
            }
            queryString = queryString.arg(queryConditions.join(" OR "));
            query.prepare(queryString);
            query.bindValue(0, componentTypeId(COMPONENT_TYPE_PACKAGE));
            query.bindValue(1, PACKAGE_INFORMATION_VISIBLE);
            query.bindValue(2, QVariant(true));
            for (int i = 0; i < tags.count(); i++) {
                query.bindValue(i + 3, tags.at(i));
            }
        }

        executeQuery(&query);
        while (query.next()) {
            returnedValues.append(query.value(0).toString());
        }
        query.finish();
    }
    QSqlDatabase::removeDatabase("get_registered_packages");
    return returnedValues;
}

Package * DatabaseInterfacePrivate::package(const QString &identifier, QObject *parent)
{
    Package *returnedValue = 0;
    qlonglong packageTypeId = componentTypeId(COMPONENT_TYPE_PACKAGE);

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_package");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT id, directory, plugin FROM packages WHERE identifier=:identifier");
        query.bindValue(":identifier", identifier);
        executeQuery(&query);
        if (!query.next()) {
            return returnedValue;
        }

        int packageId = query.value(0).toInt();
        QString folder = query.value(1).toString();
        QString plugin = query.value(2).toString();


        QString defaultName;
        QString defaultDescription;
        QMap<QString, QString> names;
        QMap<QString, QString> descriptions;

        query.prepare("SELECT language, name, description FROM componentLocalizedInformation \
                       WHERE componentTypeId=:componentTypeId AND componentId=:componentId");
        query.bindValue(":componentTypeId", packageTypeId);
        query.bindValue(":componentId", packageId);
        executeQuery(&query);
        while (query.next()) {
            QString language = query.value(0).toString();
            QString name = query.value(1).toString();
            QString description = query.value(2).toString();

            if (language == COMPONENT_INFORMATION_DEFAULT_LANGUAGE) {
                defaultName = name;
                defaultDescription = description;
            } else {
                if (!name.isEmpty()) {
                    names.insert(language, name);
                }
                if (!description.isEmpty()) {
                    descriptions.insert(language, description);
                }
            }
        }
        query.finish();
        QMap<QString, QString> informations;

        query.prepare("SELECT name, value FROM componentInformation \
                      INNER JOIN componentInformationProperties \
                      ON componentInformation.informationId = componentInformationProperties.id \
                      WHERE componentId=:componentId");
        query.bindValue(":componentId", packageId);
        executeQuery(&query);

        while (query.next()) {
            QString name = query.value(0).toString();
            QString value = query.value(1).toString();
            informations.insert(name, value);
        }
        query.finish();

        QString author = informations.value(PACKAGE_INFORMATION_AUTHOR);
        QString email = informations.value(PACKAGE_INFORMATION_EMAIL);
        QString icon = informations.value(COMPONENT_INFORMATION_ICON);
        QString website = informations.value(PACKAGE_INFORMATION_WEBSITE);
        Version version = Version::fromString(informations.value(PACKAGE_INFORMATION_VERSION));
        bool visible = Tools::stringToBool(informations.value(PACKAGE_INFORMATION_VISIBLE));


        query.prepare("SELECT tags.name FROM tags \
                      INNER JOIN packageTags ON tags.id=packageTags.tagId \
                      WHERE packageTags.packageId=:packageId");
        query.bindValue(":packageId", packageId);
        executeQuery(&query);

        QStringList tags;
        while (query.next()) {
            QString tag = query.value(0).toString();
            tags.append(tag);
        }


        returnedValue = new Package(icon, defaultName, defaultDescription, names, descriptions,
                            identifier, folder, plugin, author, email, website, version, visible,
                            tags, parent);
    }
    QSqlDatabase::removeDatabase("get_package");

    return returnedValue;
}

QStringList DatabaseInterfacePrivate::registeredWidgets(const QString &packageIdentifier)
{
    QStringList values;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_registered_widgets");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());
        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT widgets.file FROM widgets \
                      INNER JOIN packages ON widgets.packageId=packages.id \
                      WHERE packages.identifier=:packageIdentifier");
        query.bindValue(":packageIdentifier", packageIdentifier);
        executeQuery(&query);
        while (query.next()) {
            QString name = query.value(0).toString();
            values.append(name);
        }
        query.finish();
    }
    QSqlDatabase::removeDatabase("get_registered_widgets");
    return values;
}

QStringList DatabaseInterfacePrivate::registeredDocks(const QString &packageIdentifier)
{
    QStringList values;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_registered_docks");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());
        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT docks.file FROM docks \
                      INNER JOIN packages ON docks.packageId=packages.id \
                      WHERE packages.identifier=:packageIdentifier");
        query.bindValue(":packageIdentifier", packageIdentifier);
        executeQuery(&query);
        while (query.next()) {
            QString name = query.value(0).toString();
            values.append(name);
        }
        query.finish();
    }
    QSqlDatabase::removeDatabase("get_registered_docks");
    return values;
}


ComponentMetadata * DatabaseInterfacePrivate::widgetMetadata(const QString &packageIdentifier,
                                                             const QString &fileName,
                                                             QObject *parent)
{
    ComponentMetadata *returnedValue = 0;

    qlonglong widgetTypeId = componentTypeId(COMPONENT_TYPE_WIDGET);

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_widget_metadata");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT widgets.id FROM widgets INNER JOIN packages \
                      ON widgets.packageId=packages.id \
                      WHERE packages.identifier=:packageIdentifier AND widgets.file=:widgetFile");
        query.bindValue(":packageIdentifier", packageIdentifier);
        query.bindValue(":widgetFile", fileName);
        executeQuery(&query);
        if (!query.next()) {
            return returnedValue;
        }

        int widgetId = query.value(0).toInt();

        QString defaultName;
        QMap<QString, QString> names;
        QString defaultDescription;
        QMap<QString, QString> descriptions;
        query.prepare("SELECT language, name, description \
                      FROM componentLocalizedInformation \
                      WHERE componentTypeId=:componentTypeId AND componentId=:componentId");
        query.bindValue(":componentTypeId", widgetTypeId);
        query.bindValue(":componentId", widgetId);
        executeQuery(&query);
        while (query.next()) {
            QString language = query.value(0).toString();
            QString name = query.value(1).toString();
            QString description = query.value(2).toString();

            if (language == COMPONENT_INFORMATION_DEFAULT_LANGUAGE) {
                defaultName = name;
                defaultDescription = description;
            } else {
                if (!name.isEmpty()) {
                    names.insert(language, name);
                }
                if (!description.isEmpty()) {
                    descriptions.insert(language, description);
                }
            }
        }
        query.finish();

        QMap<QString, QString> informations;

        query.prepare("SELECT name, value FROM componentInformation \
                       INNER JOIN componentInformationProperties \
                       ON componentInformation.informationId = componentInformationProperties.id \
                       WHERE componentInformation.componentId=:componentId \
                       AND componentInformation.componentTypeId=:componentTypeId");
        query.bindValue(":componentId", widgetId);
        query.bindValue(":componentTypeId", widgetTypeId);
        executeQuery(&query);

        while (query.next()) {
            QString name = query.value(0).toString();
            QString value = query.value(1).toString();
            informations.insert(name, value);
        }
        query.finish();

        QString icon = informations.value(COMPONENT_INFORMATION_ICON);
        QString settingsFileName = informations.value(COMPONENT_INFORMATION_SETTINGS_FILE);

        QVariantMap disambiguation;
        disambiguation.insert(PACKAGE_IDENTIFIER_KEY, packageIdentifier);
        returnedValue = new ComponentMetadata(icon, defaultName, defaultDescription,
                                              names, descriptions,
                                              ComponentMetadata::WidgetComponentType,
                                              fileName, settingsFileName, parent);

    }
    QSqlDatabase::removeDatabase("get_widget_metadata");

    return returnedValue;
}

ComponentMetadata * DatabaseInterfacePrivate::dockMetadata(const QString &packageIdentifier,
                                                           const QString &fileName,
                                                           QObject *parent)
{
    ComponentMetadata *returnedValue = 0;

    qlonglong widgetTypeId = componentTypeId(COMPONENT_TYPE_DOCK);

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_dock_metadata");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT docks.id FROM docks INNER JOIN packages \
                      ON docks.packageId=packages.id \
                      WHERE packages.identifier=:packageIdentifier AND docks.file=:dockFile");
        query.bindValue(":packageIdentifier", packageIdentifier);
        query.bindValue(":dockFile", fileName);
        executeQuery(&query);
        if (!query.next()) {
            return returnedValue;
        }

        int widgetId = query.value(0).toInt();

        QString defaultName;
        QMap<QString, QString> names;
        QString defaultDescription;
        QMap<QString, QString> descriptions;
        query.prepare("SELECT language, name, description \
                      FROM componentLocalizedInformation \
                      WHERE componentTypeId=:componentTypeId AND componentId=:componentId");
        query.bindValue(":componentTypeId", widgetTypeId);
        query.bindValue(":componentId", widgetId);
        executeQuery(&query);
        while (query.next()) {
            QString language = query.value(0).toString();
            QString name = query.value(1).toString();
            QString description = query.value(2).toString();

            if (language == COMPONENT_INFORMATION_DEFAULT_LANGUAGE) {
                defaultName = name;
                defaultDescription = description;
            } else {
                if (!name.isEmpty()) {
                    names.insert(language, name);
                }
                if (!description.isEmpty()) {
                    descriptions.insert(language, description);
                }
            }
        }
        query.finish();

        QMap<QString, QString> informations;

        query.prepare("SELECT name, value FROM componentInformation \
                       INNER JOIN componentInformationProperties \
                       ON componentInformation.informationId = componentInformationProperties.id \
                       WHERE componentInformation.componentId=:componentId \
                       AND componentInformation.componentTypeId=:componentTypeId");
        query.bindValue(":componentId", widgetId);
        query.bindValue(":componentTypeId", widgetTypeId);
        executeQuery(&query);

        while (query.next()) {
            QString name = query.value(0).toString();
            QString value = query.value(1).toString();
            informations.insert(name, value);
        }
        query.finish();

        QString icon = informations.value(COMPONENT_INFORMATION_ICON);
        QString settingsFileName = informations.value(COMPONENT_INFORMATION_SETTINGS_FILE);

        QVariantMap disambiguation;
        disambiguation.insert(PACKAGE_IDENTIFIER_KEY, packageIdentifier);
        returnedValue = new ComponentMetadata(icon, defaultName, defaultDescription,
                                              names, descriptions,
                                              ComponentMetadata::DockComponentType,
                                              fileName, settingsFileName, parent);

    }
    QSqlDatabase::removeDatabase("get_dock_metadata");

    return returnedValue;
}

WidgetBaseProperties * DatabaseInterfacePrivate::widget(const QString &packageIdentifier,
                                                        const QString &fileName, QObject *parent)
{
    WidgetBaseProperties *returnedValue = 0;

    qlonglong widgetTypeId = componentTypeId(COMPONENT_TYPE_WIDGET);

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_widget");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT widgets.id FROM widgets INNER JOIN packages \
                      ON widgets.packageId=packages.id \
                      WHERE packages.identifier=:packageIdentifier AND widgets.file=:widgetFile");
        query.bindValue(":packageIdentifier", packageIdentifier);
        query.bindValue(":widgetFile", fileName);
        executeQuery(&query);
        if (!query.next()) {
            return returnedValue;
        }

        int widgetId = query.value(0).toInt();
        QMap<QString, QString> informations;

        query.prepare("SELECT name, value FROM componentInformation \
                       INNER JOIN componentInformationProperties \
                       ON componentInformation.informationId = componentInformationProperties.id \
                       WHERE componentInformation.componentId=:componentId \
                       AND componentInformation.componentTypeId=:componentTypeId");
        query.bindValue(":componentId", widgetId);
        query.bindValue(":componentTypeId", widgetTypeId);
        executeQuery(&query);

        while (query.next()) {
            QString name = query.value(0).toString();
            QString value = query.value(1).toString();
            informations.insert(name, value);
        }
        query.finish();


        QString settingsFileName = informations.value(COMPONENT_INFORMATION_SETTINGS_FILE);
        int minimumWidth = informations.value(WIDGET_INFORMATION_MINIMUM_WIDTH).toInt();
        int minimumHeight = informations.value(WIDGET_INFORMATION_MINIMUM_HEIGHT).toInt();
        int maximumWidth = informations.value(WIDGET_INFORMATION_MAXIMUM_WIDTH).toInt();
        int maximumHeight = informations.value(WIDGET_INFORMATION_MAXIMUM_HEIGHT).toInt();

        QVariantMap disambiguation;
        disambiguation.insert(PACKAGE_IDENTIFIER_KEY, packageIdentifier);
        returnedValue = new WidgetBaseProperties(fileName, disambiguation, settingsFileName,
                                         minimumWidth, minimumHeight,
                                         maximumWidth, maximumHeight, parent);

    }
    QSqlDatabase::removeDatabase("get_widget");

    return returnedValue;
}

Docks::DockBaseProperties * DatabaseInterfacePrivate::dock(const QString &packageIdentifier,
                                                           const QString &fileName,
                                                           QObject *parent)
{
    Docks::DockBaseProperties *returnedValue = 0;

    qlonglong dockTypeId = componentTypeId(COMPONENT_TYPE_DOCK);

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_dock");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT docks.id FROM docks \
                      INNER JOIN packages ON docks.packageId=packages.id \
                      WHERE packages.identifier=:packageIdentifier AND docks.file=:dockFile");
        query.bindValue(":packageIdentifier", packageIdentifier);
        query.bindValue(":dockFile", fileName);
        executeQuery(&query);
        if (!query.next()) {
            return returnedValue;
        }

        int dockId = query.value(0).toInt();
        QMap<QString, QString> informations;

        query.prepare("SELECT name, value FROM componentInformation \
                      INNER JOIN componentInformationProperties \
                      ON componentInformation.informationId = componentInformationProperties.id \
                      WHERE componentInformation.componentId=:componentId \
                      AND componentInformation.componentTypeId=:componentTypeId");
        query.bindValue(":componentId", dockId);
        query.bindValue(":componentTypeId", dockTypeId);
        executeQuery(&query);

        while (query.next()) {
            QString name = query.value(0).toString();
            QString value = query.value(1).toString();
            informations.insert(name, value);
        }
        query.finish();


        QString anchorsTopString = informations.value(DOCK_INFORMATION_ANCHORS_TOP);
        QString anchorsBottomString = informations.value(DOCK_INFORMATION_ANCHORS_BOTTOM);
        QString anchorsLeftString = informations.value(DOCK_INFORMATION_ANCHORS_LEFT);
        QString anchorsRightString = informations.value(DOCK_INFORMATION_ANCHORS_RIGHT);
        QString settingsFileName = informations.value(COMPONENT_INFORMATION_SETTINGS_FILE);
        int width = informations.value(DOCK_INFORMATION_WIDTH).toInt();
        int height = informations.value(DOCK_INFORMATION_HEIGHT).toInt();
        bool anchorsTop = Tools::stringToBool(anchorsTopString);
        bool anchorsBottom = Tools::stringToBool(anchorsBottomString);
        bool anchorsLeft = Tools::stringToBool(anchorsLeftString);
        bool anchorsRight = Tools::stringToBool(anchorsRightString);

        QVariantMap disambiguation;
        disambiguation.insert(PACKAGE_IDENTIFIER_KEY, packageIdentifier);
        returnedValue = new Docks::DockBaseProperties(fileName, disambiguation, settingsFileName,
                                              width, height,
                                              anchorsTop, anchorsBottom, anchorsLeft, anchorsRight,
                                              parent);
    }
    QSqlDatabase::removeDatabase("get_dock");

    return returnedValue;
}

QString DatabaseInterfacePrivate::widgetAbsoluteFolder(const QString &packageIdentifier,
                                                       const QString &fileName)
{
    QString returnedValue;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_widget_absolute_folder");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT packages.directory, widgets.directory \
                       FROM packages \
                       INNER JOIN widgets ON packages.id=widgets.packageId \
                       WHERE packages.identifier=:packageIdentifier AND widgets.file=:widgetFile");
        query.bindValue(":packageIdentifier", packageIdentifier);
        query.bindValue(":widgetFile", fileName);
        executeQuery(&query);
        if (query.next()) {
            QString subdir = query.value(1).toString();
            QDir dir = QDir(query.value(0).toString());

            if (dir.cd(WIDGETS_FOLDER)) {
                if (dir.cd(subdir)) {
                    returnedValue = dir.absolutePath();
                }
            }
        }
    }
    QSqlDatabase::removeDatabase("get_widget_absolute_folder");
    return returnedValue;
}

QString DatabaseInterfacePrivate::widgetFile(const QString &packageIdentifier,
                                             const QString &fileName)
{
    QString absoluteFolder = widgetAbsoluteFolder(packageIdentifier, fileName);
    if (absoluteFolder.isEmpty()) {
        return QString();
    }

    QDir folder (absoluteFolder);
    if (!folder.exists(fileName)) {
        return QString();
    }

    return folder.absoluteFilePath(fileName);
}

QString DatabaseInterfacePrivate::widgetSettingsFile(const QString &packageIdentifier,
                                                     const QString &fileName)
{
    QString returnedValue;
    QString absoluteFolder = widgetAbsoluteFolder(packageIdentifier, fileName);

    qlonglong widgetTypeId = componentTypeId(COMPONENT_TYPE_WIDGET);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_widget_settings_file");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT widgets.id FROM widgets INNER JOIN packages \
                      ON widgets.packageId=packages.id \
                      WHERE packages.identifier=:packageIdentifier AND widgets.file=:widgetFile");
        query.bindValue(":packageIdentifier", packageIdentifier);
        query.bindValue(":widgetFile", fileName);
        executeQuery(&query);
        if (!query.next()) {
            return returnedValue;
        }

        int widgetId = query.value(0).toInt();

        query.prepare("SELECT name, value FROM componentInformation \
                       INNER JOIN componentInformationProperties \
                       ON componentInformation.informationId = componentInformationProperties.id \
                       WHERE componentInformation.componentId=:componentId \
                       AND componentInformation.componentTypeId=:componentTypeId");
        query.bindValue(":componentId", widgetId);
        query.bindValue(":componentTypeId", widgetTypeId);
        executeQuery(&query);

        while (query.next() || returnedValue.isEmpty()) {
            QString name = query.value(0).toString();
            QString value = query.value(1).toString();
            if (name == COMPONENT_INFORMATION_SETTINGS_FILE) {
                QDir folder (absoluteFolder);
                if (folder.exists(value)) {
                    returnedValue = folder.absoluteFilePath(value);
                }
            }
        }
        query.finish();
    }
    QSqlDatabase::removeDatabase("get_widget_settings_file");

    return returnedValue;
}

QString DatabaseInterfacePrivate::dockAbsoluteFolder(const QString &packageIdentifier,
                                                     const QString &fileName)
{
    QString returnedValue;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_dock_absolute_folder");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT packages.directory, docks.directory \
                       FROM packages \
                       INNER JOIN docks ON packages.id=docks.packageId \
                       WHERE packages.identifier=:packageIdentifier AND docks.file=:dockFile");
        query.bindValue(":packageIdentifier", packageIdentifier);
        query.bindValue(":dockFile", fileName);
        executeQuery(&query);
        if (query.next()) {
            QString subdir = query.value(1).toString();
            QDir dir = QDir(query.value(0).toString());

            if (dir.cd(DOCKS_FOLDER)) {
                if (dir.cd(subdir)) {
                    returnedValue = dir.absolutePath();
                }
            }
        }
    }
    QSqlDatabase::removeDatabase("get_dock_absolute_folder");
    return returnedValue;
}


QString DatabaseInterfacePrivate::dockFile(const QString &packageIdentifier,
                                           const QString &fileName)
{
    QString absoluteFolder = dockAbsoluteFolder(packageIdentifier, fileName);
    if (absoluteFolder.isEmpty()) {
        return QString();
    }

    QDir folder (absoluteFolder);
    if (!folder.exists(fileName)) {
        return QString();
    }

    return folder.absoluteFilePath(fileName);
}

QString DatabaseInterfacePrivate::dockSettingsFile(const QString &packageIdentifier,
                                                   const QString &fileName)
{
    QString returnedValue;
    QString absoluteFolder = dockAbsoluteFolder(packageIdentifier, fileName);

    qlonglong dockTypeId = componentTypeId(COMPONENT_TYPE_DOCK);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "get_dock_settings_file");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());

        QSqlQuery query = QSqlQuery(db);
        query.prepare("SELECT docks.id FROM docks INNER JOIN packages \
                      ON widgets.packageId=packages.id \
                      WHERE packages.identifier=:packageIdentifier AND widgets.file=:dockFile");
        query.bindValue(":packageIdentifier", packageIdentifier);
        query.bindValue(":dockFile", fileName);
        executeQuery(&query);
        if (!query.next()) {
            return returnedValue;
        }

        int dockId = query.value(0).toInt();

        query.prepare("SELECT name, value FROM componentInformation \
                       INNER JOIN componentInformationProperties \
                       ON componentInformation.informationId = componentInformationProperties.id \
                       WHERE componentInformation.componentId=:componentId \
                       AND componentInformation.componentTypeId=:componentTypeId");
        query.bindValue(":componentId", dockId);
        query.bindValue(":componentTypeId", dockTypeId);
        executeQuery(&query);

        while (query.next() || returnedValue.isEmpty()) {
            QString name = query.value(0).toString();
            QString value = query.value(1).toString();
            if (name == COMPONENT_INFORMATION_SETTINGS_FILE) {
                QDir folder (absoluteFolder);
                if (folder.exists(value)) {
                    returnedValue = folder.absoluteFilePath(value);
                }
            }
        }
        query.finish();
    }
    QSqlDatabase::removeDatabase("get_dock_settings_file");
    return returnedValue;
}

void DatabaseInterfacePrivate::clean()
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "clean");
        db.setDatabaseName(databasePath());
        W_ASSERT(db.open());
        executeQuery("DELETE FROM packages", db);
        executeQuery("DELETE FROM docks", db);
        executeQuery("DELETE FROM widgets", db);
        executeQuery("DELETE FROM componentInformation", db);
        executeQuery("DELETE FROM componentLocalizedInformation", db);
        executeQuery("DELETE FROM tags", db);
    }
    QSqlDatabase::removeDatabase("clean");
}

QString DatabaseInterfacePrivate::scanFolderForPackage(const QString &path)
{
    QDir dir = QDir(path);
    if (!dir.exists(PACKAGE_FILE)) {
        return QString();
    }

    QString filePath = dir.absoluteFilePath(PACKAGE_FILE);
    Package *package = Package::fromDesktopFile(filePath);

    if (!package) {
        return QString();
    }

    addPackage(package, path);

    return package->identifier();

}


void DatabaseInterfacePrivate::scanFolderForWidgets(const QString &path,
                                                    const QString &packageIdentifier,
                                                    qlonglong packageId)
{
    QDir widgetFolder (path);
    QFileInfoList folders = widgetFolder.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);

    foreach (QFileInfo folderInfo, folders) {
        QDir folder (folderInfo.absoluteFilePath());

        QString metadataFile = folder.absoluteFilePath(METADATA_FILE);
        ComponentMetadata *metadata = ComponentMetadata::fromDesktopFile(metadataFile);

        if (!metadata) {
            break;
        }

        if (metadata->type() == ComponentMetadata::WidgetComponentType) {
            QString file = folder.absoluteFilePath(metadata->fileName());
            QString settingsFile = metadata->settingsFileName();
            QVariantMap disambiguation;
            disambiguation.insert(PACKAGE_IDENTIFIER_KEY, packageIdentifier);
            WidgetBaseProperties *widget = WidgetBaseProperties::fromQmlFile(file,
                                                                             disambiguation,
                                                                             settingsFile);
            if (widget) {
                addWidget(packageId, folderInfo.fileName(), widget, metadata);
            }
        }
        metadata->deleteLater();
    }
}

void DatabaseInterfacePrivate::scanFolderForDocks(const QString &path,
                                                  const QString &packageIdentifier,
                                                  qlonglong packageId)
{
    QDir dockFolder (path);
    QFileInfoList folders = dockFolder.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);

    foreach (QFileInfo folderInfo, folders) {
        QDir folder (folderInfo.absoluteFilePath());

        QString metadataFile = folder.absoluteFilePath(METADATA_FILE);
        ComponentMetadata *metadata = ComponentMetadata::fromDesktopFile(metadataFile);

        if (!metadata) {
            break;
        }

        if (metadata->type() == ComponentMetadata::DockComponentType) {
            QString file = folder.absoluteFilePath(metadata->fileName());
            QString settingsFile = metadata->settingsFileName();
            QVariantMap disambiguation;
            disambiguation.insert(PACKAGE_IDENTIFIER_KEY, packageIdentifier);
            Docks::DockBaseProperties *dock
                    = Docks::DockBaseProperties::fromQmlFile(file, disambiguation,
                                                             settingsFile);
            if (dock) {
                addDock(packageId, folderInfo.fileName(), dock, metadata);
            }
        }
        metadata->deleteLater();
    }
}



////// End of private class //////

DatabaseInterface::DatabaseInterface(QObject *parent):
    QObject(parent), d_ptr(new DatabaseInterfacePrivate())
{
}

DatabaseInterface::~DatabaseInterface()
{
}

QVariantMap DatabaseInterface::disambiguation(const QString &packageIdentifier)
{
    QVariantMap data;
    data.insert(PACKAGE_IDENTIFIER_KEY, packageIdentifier);
    return data;
}

QString DatabaseInterface::packageIdentifier(const QVariantMap &disambiguation)
{
    return disambiguation.value(PACKAGE_IDENTIFIER_KEY).toString();
}


void DatabaseInterface::prepareDatabase() const
{
    Q_D(const DatabaseInterface);
    d->prepareDatabase();
}

void DatabaseInterface::cleanDatabase() const
{
    Q_D(const DatabaseInterface);
    d->clean();
}

void DatabaseInterface::scan() const
{
    Q_D(const DatabaseInterface);
    // First search in system widgets directories
    QDir systemWidgetsFolder = QDir(SYSTEM_WIDGETS);


    QFileInfoList folders = systemWidgetsFolder.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);

    foreach (QFileInfo folder, folders) {
        QString packageIdentifier = d->scanFolderForPackage(folder.absoluteFilePath());
        if (!packageIdentifier.isEmpty()) {
            qlonglong packageId = d->packageId(packageIdentifier);

            // Search for widgets
            QDir widgetsFolder (folder.absoluteFilePath());
            if (widgetsFolder.cd(WIDGETS_FOLDER)) {
                d->scanFolderForWidgets(widgetsFolder.absolutePath(), packageIdentifier, packageId);
            }

            // Search for docks
            QDir docksFolder (folder.absoluteFilePath());
            if (docksFolder.cd(DOCKS_FOLDER)) {
                d->scanFolderForDocks(docksFolder.absolutePath(), packageIdentifier, packageId);
            }
        }

    }
}

QStringList DatabaseInterface::registeredPackages(FilterConditionList *filter) const
{
    Q_D(const DatabaseInterface);
    return d->registeredPackages(filter);
}

QStringList DatabaseInterface::registeredWidgets(const QString &packageIdentifier) const
{
    Q_D(const DatabaseInterface);
    return d->registeredWidgets(packageIdentifier);
}

QStringList DatabaseInterface::registeredDocks(const QString &packageIdentifier) const
{
    Q_D(const DatabaseInterface);
    return d->registeredDocks(packageIdentifier);
}

Package * DatabaseInterface::package(const QString &packageIdentifier, QObject *parent) const
{
    Q_D(const DatabaseInterface);
    return d->package(packageIdentifier, parent);
}

QString DatabaseInterface::widgetFile(const QString &packageIdentifier,
                                      const QString &fileName) const
{
    Q_D(const DatabaseInterface);
    return d->widgetFile(packageIdentifier, fileName);
}

QString DatabaseInterface::widgetSettingsFile(const QString &packageIdentifier,
                                              const QString &fileName) const
{
    Q_D(const DatabaseInterface);
    return d->widgetSettingsFile(packageIdentifier, fileName);
}

WidgetBaseProperties * DatabaseInterface::widget(const QString &packageIdentifier,
                                                 const QString &fileName, QObject *parent) const
{
    Q_D(const DatabaseInterface);
    return d->widget(packageIdentifier, fileName, parent);
}

QString DatabaseInterface::widgetName(const QString &packageIdentifier,
                                      const QString &fileName) const
{
    Q_D(const DatabaseInterface);
    QString name;
    ComponentMetadata *metadata = d->widgetMetadata(packageIdentifier, fileName);
    if (metadata) {
        name = metadata->name();
        metadata->deleteLater();
    }
    return name;
}

QString DatabaseInterface::widgetDescription(const QString &packageIdentifier,
                                             const QString &fileName) const
{
    Q_D(const DatabaseInterface);
    QString description;
    ComponentMetadata *metadata = d->widgetMetadata(packageIdentifier, fileName);
    if (metadata) {
        description = metadata->description();
        metadata->deleteLater();
    }
    return description;
}

QString DatabaseInterface::dockFile(const QString &packageIdentifier,
                                    const QString &fileName) const
{
    Q_D(const DatabaseInterface);
    return d->dockFile(packageIdentifier, fileName);
}

QString DatabaseInterface::dockSettingsFile(const QString &packageIdentifier,
                                            const QString &fileName) const
{
    Q_D(const DatabaseInterface);
    return d->dockSettingsFile(packageIdentifier, fileName);
}

Docks::DockBaseProperties * DatabaseInterface::dock(const QString &packageIdentifier,
                                                    const QString &fileName, QObject *parent) const
{
    Q_D(const DatabaseInterface);
    return d->dock(packageIdentifier, fileName, parent);
}

QString DatabaseInterface::dockName(const QString &packageIdentifier,
                                    const QString &fileName) const
{
    Q_D(const DatabaseInterface);
    QString name;
    ComponentMetadata *metadata = d->dockMetadata(packageIdentifier, fileName);
    if (metadata) {
        name = metadata->name();
        metadata->deleteLater();
    }
    return name;
}

QString DatabaseInterface::dockDescription(const QString &packageIdentifier,
                                           const QString &fileName) const
{
    Q_D(const DatabaseInterface);
    QString description;
    ComponentMetadata *metadata = d->dockMetadata(packageIdentifier, fileName);
    if (metadata) {
        description = metadata->description();
        metadata->deleteLater();
    }
    return description;
}

}

}

}
