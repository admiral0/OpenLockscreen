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
 *
 * This file contains the implemetation of the
 * Widgets::PackageManager class and the declaration and
 * implementation of Widgets::PackageManager::PackageManagerPrivate.
 */

#include "packagemanager.h"
#include "package.h"
#include "widgetbaseproperties.h"
#include "availablewidgetsmodel.h"
#include "availabledocksmodel.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QDir>
#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @internal
 * @short Private structure for PackageManager
 */
class PackageManager::PackageManagerPrivate
{
public:
    /**
     * @short Default constructor
     */
    PackageManagerPrivate(PackageManager *parent);
    /**
     * @short Search package information files
     *
     * This method search in the two default
     * package folders for package information
     * files.
     */
    void searchPackageInformationFiles();
    /**
     * @short Add available widgets
     *
     * Add available widgets, that are contained
     * in a package, to the widgets cache.
     *
     * @param package package to add.
     */
    void addAvailableWidgets(const Package &package);
    /**
     * @short Add available docks
     *
     * Add available docks, that are contained
     * in a package, to the docks cache.
     *
     * @param package package to add.
     */
    void addAvailableDocks(const Package &package);
    /**
     * @short List of available packages
     *
     * This list actually contains the absolute
     * path to the information files that describes the
     * packages.
     */
    QList<Package> availablePackages;
    /**
     * @short Available widgets cache
     *
     * This map associates the absolute path
     * to a widget to the widget base properties.
     */
    QMap<QString, WidgetBaseProperties *> availableWidgets;
    /**
     * @short Available docks cache
     *
     * This map associates the absolute path
     * to a dock to the dock base properties.
     */
    QMap<QString, DockBaseProperties * > availableDocks;
    /**
     * @short Available widgets model
     */
    AvailableWidgetsModel *availableWidgetsModel;
    /**
     * @short Available docks model
     */
    AvailableDocksModel *availableDocksModel;
private:
    PackageManager * const q;
};

PackageManager::PackageManagerPrivate::PackageManagerPrivate(PackageManager *parent):
    q(parent)
{
    availableWidgetsModel = new AvailableWidgetsModel(q);
    availableDocksModel = new AvailableDocksModel(q);
}

void PackageManager::PackageManagerPrivate::searchPackageInformationFiles()
{
    QDir dir = QDir(QCoreApplication::instance()->applicationDirPath());

    // 1. Scan qml dir
    dir.cdUp();
    dir.cd("qml");

    QStringList fileList = dir.entryList(QStringList() << "*.xml" ,QDir::Files);
    foreach (QString fileName, fileList) {
        Package package = Package::fromInformationFile(dir.absoluteFilePath(fileName), q);
        availablePackages.append(package);
        addAvailableWidgets(package);
        addAvailableDocks(package);
    }

    // 2. Scan widgets dir
    dir = QDir(QCoreApplication::instance()->applicationDirPath());
    dir.cdUp();
    dir.cd("widgets");
    QStringList dirsName = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    foreach (QString dirName, dirsName) {
        dir.cd(dirName);
        fileList = dir.entryList(QStringList() << "*.xml" ,QDir::Files);
        if (fileList.count() == 1) {
            QString fileName = fileList.first();
            Package package = Package::fromInformationFile(dir.absoluteFilePath(fileName), q);
            availablePackages.append(package);
            addAvailableWidgets(package);
            addAvailableDocks(package);
        }
        dir.cdUp();
    }
}

void PackageManager::PackageManagerPrivate::addAvailableWidgets(const Package &package) {

    foreach (WidgetBaseProperties *widget, package.widgets()) {
        QString qmlFile = widget->qmlFile();
        if (package.isVisible()) {
            availableWidgetsModel->addWidget(package.name(), widget);
        }
        availableWidgets.insert(qmlFile, widget);
    }
}

void PackageManager::PackageManagerPrivate::addAvailableDocks(const Package &package) {
    foreach (DockBaseProperties *dock, package.docks()) {
        QString qmlFile = dock->qmlFile();
        if (package.isVisible()) {
            availableDocksModel->addDock(package.name(), dock);
        }
        availableDocks.insert(qmlFile, dock);
    }
}

////// End of private class //////

PackageManager::PackageManager(QObject *parent):
    QObject(parent), d(new PackageManagerPrivate(this))
{
    d->searchPackageInformationFiles();
}

PackageManager::~PackageManager()
{
    delete d;
}

WidgetBaseProperties * PackageManager::widget(const QString &qmlFile) const
{
    return d->availableWidgets.value(qmlFile, 0);
}

DockBaseProperties * PackageManager::dock(const QString &qmlFile) const
{
    return d->availableDocks.value(qmlFile, 0);
}

AvailableWidgetsModel * PackageManager::availableWidgetsModel() const
{
    return d->availableWidgetsModel;
}

AvailableDocksModel * PackageManager::availableDocksModel() const
{
    return d->availableDocksModel;
}


}
