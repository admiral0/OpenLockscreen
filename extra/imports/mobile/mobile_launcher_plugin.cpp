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
 * @file mobile_launcher_plugin.cpp
 * @short Implementation of Mobile::Launcher::MobileLauncherPlugin
 */

#include "mobile_launcher_plugin.h"

#include <QtDeclarative/QtDeclarative>

#include "applicationinformations.h"
#include "applicationsmodel.h"
#include "launchermanager.h"
#include "foldermodel.h"

namespace Mobile
{

namespace Launcher
{

void MobileLauncherPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri)

    // @uri org.SfietKonstantin.mobile.launcher
    engine->rootContext()->setContextProperty("ApplicationsModelInstance",
                                              new ApplicationsModel(this));
    engine->rootContext()->setContextProperty("LauncherManagerInstance", new LauncherManager(this));
}

void MobileLauncherPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.mobile.launcher
    qmlRegisterType<ApplicationInformations>(uri, 1, 0, "ApplicationInformations");
    qmlRegisterType<FolderModel>(uri, 1, 0, "FolderModel");
    QString reason = "Only one instance of ApplicationsModel is allowed";
    qmlRegisterUncreatableType<ApplicationsModel>(uri, 1, 0, "ApplicationsModel", reason);
    reason = "Only one instance of LauncherManager is allowed";
    qmlRegisterUncreatableType<LauncherManager>(uri, 1, 0, "LauncherManager", reason);
}

}

}

Q_EXPORT_PLUGIN2(Mobile, Mobile::Launcher::MobileLauncherPlugin)

