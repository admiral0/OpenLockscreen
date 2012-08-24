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

/**
 * @file src/bin/packagemanagerhelper/main.cpp
 * @short Entry point of package manager helper app
 */

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtGui/QDesktopServices>

#include "version.h"
#include "databaseinterface_p.h"

#include "qplatformdefs.h"

/**
 * @brief Display help
 */
void displayHelp()
{
    QString version = Widgets::Version::currentVersion().toString();

    qDebug() << "Widgets package manager helper, version" << version.toAscii().constData();
    qDebug() << "";
    qDebug() << "Usage:";
    qDebug() << "    --clear       clear package manager cache";
    qDebug() << "    --update      update package manager cache";
    qDebug() << "    --rebuild     rebuild package manager cache (clear and update)";
}

/**
 * @brief Clear
 *
 * Remove the whole package manager database
 * from the cache.
 *
 * Note: for Harmattan, it remove the database from
 * /home/user/.cache/SfietKonstantin/Widgets and
 * /home/developer/.cache/SfietKonstantin/Widgets.
 */
void clear()
{
#ifdef MEEGO_EDITION_HARMATTAN
    QDir dir ("/home/user/.cache/SfietKonstantin/Widgets");
    if (dir.exists("packagemanager.db")) {
        dir.remove("packagemanager.db");
    }

    dir = QDir("/home/developer/.cache/SfietKonstantin/Widgets");
    if (dir.exists("packagemanager.db")) {
        dir.remove("packagemanager.db");
    }

#else
    QDir dir (QDesktopServices::storageLocation(QDesktopServices::CacheLocation));

    if (dir.exists("packagemanager.db")) {
        dir.remove("packagemanager.db");
    }
#endif
}

/**
 * @brief Update
 *
 * Update the cached widgets and docks that
 * are stored in the database.
 *
 * Note: for Harmattan, it creates the database at
 * /home/user/.cache/SfietKonstantin/Widgets and
 * create a symlink to
 * /home/developer/.cache/SfietKonstantin/Widgets.
 */
void update()
{
    // Prepare database
    Widgets::Provider::PackageManager::DatabaseInterface *interface
            = new Widgets::Provider::PackageManager::DatabaseInterface();
#ifdef MEEGO_EDITION_HARMATTAN
    interface->setDatabasePath("/home/user/.cache/SfietKonstantin/Widgets/packagemanager.db");
#endif
    interface->prepareDatabase();
    interface->scan();

    interface->deleteLater();
#ifdef MEEGO_EDITION_HARMATTAN
    QFile::link("/home/user/.cache/SfietKonstantin/Widgets/packagemanager.db",
                "/home/developer/.cache/SfietKonstantin/Widgets/packagemanager.db");
#endif
}

/**
 * @brief Main
 * @param argc argc.
 * @param argv argv.
 * @return exit code.
 */
int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);
    app.setApplicationName("Widgets");
    app.setOrganizationName("SfietKonstantin");

    QStringList arguments = app.arguments();
    if (arguments.size() != 2) {
        displayHelp();
        return 0;
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

    displayHelp();
    return 0;
}
