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
 * @file widgets_mobileextra_plugin.cpp
 * @short Implementation of Widgets::MobileExtra::WidgetsMobileExtraPlugin
 */

#include "widgets_mobileextra_plugin.h"

#include <QtDeclarative/QtDeclarative>

#include "applicationinformations.h"
#include "applicationsmodel.h"
#include "foldermodel.h"

namespace Widgets
{

namespace MobileExtra
{

void WidgetsMobileExtraPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri)

    // @uri org.SfietKonstantin.widgets.mobileextra
    engine->rootContext()->setContextProperty("ApplicationsModel", new ApplicationsModel(this));
}

void WidgetsMobileExtraPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets.mobileextra
//    QString reason = "Only one instance of Colors is allowed.";
//    qmlRegisterUncreatableType<OxygenColors>(uri, 1, 0, "OxygenColors", reason);
    qmlRegisterType<ApplicationInformations>(uri, 1, 0, "ApplicationInformations");
    qmlRegisterType<FolderModel>(uri, 1, 0, "FolderModel");
}

}

}

Q_EXPORT_PLUGIN2(Widgets, Widgets::MobileExtra::WidgetsMobileExtraPlugin)

