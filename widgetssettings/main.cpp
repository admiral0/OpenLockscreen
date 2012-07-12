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
 * @file widgetssettings/main.cpp
 * @short Entry point of the application
 */

#include "qplatformdefs.h"
#include <QtCore/QDir>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>

#include "settingsmanager.h"

/**
 * @short Main
 *
 * Entry point of the application.
 *
 * @param argc argc
 * @param argv argv
 * @return exit code.
 */
int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    app.setOrganizationName("sk");
    app.setApplicationName("Widgets");

    QDeclarativeView *view = new QDeclarativeView();

    // Settings manager used to manage the settings
    Widgets::SettingsManager *settingsManager = new Widgets::SettingsManager(view);
    view->rootContext()->setContextProperty("settingsManager", settingsManager);


    // QML file
    QDir qmlPath = QDir(app.applicationDirPath());
    qmlPath.cdUp();
    qmlPath.cd("qml");
    view->setSource(QUrl(qmlPath.absoluteFilePath("main.qml")));

#ifdef MEEGO_EDITION_HARMATTAN
    view->showFullScreen();
#else
    view->show();
#endif

    return app.exec();
}
