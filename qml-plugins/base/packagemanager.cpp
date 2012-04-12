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
#include <QtGui/QDesktopServices>
#include <QtSql/QSqlDatabase>

static const char * CACHE_FOLDER = "Widgets";

namespace Widgets
{

class PackageManagerPrivate
{
public:
    PackageManagerPrivate(PackageManager *q);
    static QString databasePath();
    void prepareDatabase();
private:
    Q_DECLARE_PUBLIC(PackageManager)
    PackageManager * const q_ptr;
};

PackageManagerPrivate::PackageManagerPrivate(PackageManager *q):
    q_ptr(q)
{
    prepareDatabase();
}

QString PackageManagerPrivate::databasePath()
{
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
    if(!dir.cd(CACHE_FOLDER)) {
        dir.mkdir(CACHE_FOLDER);
        dir.cd(CACHE_FOLDER);
    }

    return dir.absolutePath();
}

void PackageManagerPrivate::prepareDatabase()
{
    Q_Q(PackageManager);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "init");
    db.setHostName(databasePath());
    if(!db.open()) {
        emit q->databaseError();
        return;
    }

}

////// End of private class //////

PackageManager::PackageManager(QObject *parent) :
    QObject(parent), d_ptr(new PackageManagerPrivate(this))
{
}

PackageManager::~PackageManager()
{
}

}
