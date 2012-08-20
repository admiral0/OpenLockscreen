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
 * @file widgets_info_dock_plugin.cpp
 * @short Implementation of Widgets::Info::WidgetsInfoDockPlugin
 */


#include "widgets_info_dock_plugin.h"

#include <QtDeclarative/QtDeclarative>

#include "dockinformationmodel.h"

namespace Widgets
{

namespace Info
{

void WidgetsInfoDockPlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.widgets.info.dock
    qmlRegisterType<DockInformationModel>(uri, 1, 0, "DockInformationModel");
}

}

}

Q_EXPORT_PLUGIN2(Widgets, Widgets::Info::WidgetsInfoDockPlugin)

