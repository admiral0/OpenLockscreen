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

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtGui/QDesktopServices>

#include "version.h"
#include "databaseinterface_p.h"

int displayHelp()
{
    QString version = Widgets::Version::currentVersion().toString();

    qDebug() << "Widgets package manager helper, version" << version.toAscii().constData();
    qDebug() << "";
    qDebug() << "Usage:";
    qDebug() << "    --clear       clear package manager cache";
    qDebug() << "    --update      update package manager cache";
    qDebug() << "    --rebuild     rebuild package manager cache (clear and update)";

    return 0;
}

void clear()
{
    // Clear
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
    if (dir.exists("packagemanager.db")) {
        dir.remove("packagemanager.db");
    }
}

void update()
{
    // Prepare database
    Widgets::Provider::PackageManager::DatabaseInterface *interface
            = new Widgets::Provider::PackageManager::DatabaseInterface();
    interface->prepareDatabase();
    interface->scan();

    interface->deleteLater();
}


int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);
    app.setApplicationName("Widgets");
    app.setOrganizationName("SfietKonstantin");

    QStringList arguments = app.arguments();
    if (arguments.size() != 2) {
        return displayHelp();
    }

    if (arguments.at(1) == "--clear") {
        clear();
        return 0;
    }

    if (arguments.at(1) == "--update") {
        update();
        return 0;
    }

    if (arguments.at(1) == "--rebuild") {
        clear();
        update();
        return 0;
    }

    return displayHelp();
}
