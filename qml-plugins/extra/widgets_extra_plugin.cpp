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

#include "widgets_extra_plugin.h"

#include <QtDeclarative/QtDeclarative>

#include "dockinformationmodel.h"
#include "widgetinformationmodel.h"
#include "packageinformationmodel.h"

void WidgetsExtraPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets.extra
    qmlRegisterType<Widgets::Extra::PackageInformationModel>(uri, 1, 0, "PackageInformationModel");
    qmlRegisterType<Widgets::Extra::DockInformationModel>(uri, 1, 0, "DockInformationModel");
    qmlRegisterType<Widgets::Extra::WidgetInformationModel>(uri, 1, 0, "WidgetInformationModel");
}

Q_EXPORT_PLUGIN2(Widgets, WidgetsExtraPlugin)

