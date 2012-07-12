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

#include "temporarypackagemanager.h"
#include "../../../qml-plugins/base/packagemanager_p.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtGui/QDesktopServices>

static const char *CACHE_DIRECTORY = "Widgets";

class TemporaryPackageManagerPrivate: public Widgets::PackageManagerPrivate
{
public:
    TemporaryPackageManagerPrivate(Widgets::PackageManager *q);
    virtual QString databasePath() const;
};

TemporaryPackageManagerPrivate::TemporaryPackageManagerPrivate(Widgets::PackageManager *q):
    Widgets::PackageManagerPrivate(q)
{
}

QString TemporaryPackageManagerPrivate::databasePath() const
{
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::TempLocation));
    if(!dir.cd(CACHE_DIRECTORY)) {
        dir.mkdir(CACHE_DIRECTORY);
        dir.cd(CACHE_DIRECTORY);
    }
    return dir.absoluteFilePath("packagemanager.db");
}

////// End of private class //////


TemporaryPackageManager::TemporaryPackageManager():
    Widgets::PackageManager(new TemporaryPackageManagerPrivate(this))
{
}

void TemporaryPackageManager::deleteDb()
{
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::TempLocation));
    dir.cd(CACHE_DIRECTORY);
    dir.remove("packagemanager.db");
}
