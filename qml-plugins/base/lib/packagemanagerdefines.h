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

#ifndef PACKAGEMANAGERDEFINES_H
#define PACKAGEMANAGERDEFINES_H

namespace Widgets
{

static const char *DOCKS_FOLDER = "docks";
static const char *WIDGETS_FOLDER = "widgets";

static const char *COMPONENT_TYPE_PACKAGE = "package";
static const char *COMPONENT_TYPE_DOCK = "dock";
static const char *COMPONENT_TYPE_WIDGET = "widget";

static const char *COMPONENT_INFORMATION_ICON = "icon";
static const char *COMPONENT_INFORMATION_SETTINGS_ENABLED = "settings_enabled";
static const char *COMPONENT_INFORMATION_DEFAULT_LANGUAGE = "default";

static const char *PACKAGE_INFORMATION_AUTHOR = "package_author";
static const char *PACKAGE_INFORMATION_EMAIL = "package_email";
static const char *PACKAGE_INFORMATION_WEBSITE = "package_website";
static const char *PACKAGE_INFORMATION_VERSION = "package_version";

static const char *COMPONENT_INFORMATION_WIDTH = "dock_width";
static const char *COMPONENT_INFORMATION_HEIGHT = "dock_height";
static const char *DOCK_INFORMATION_ANCHORS_TOP = "dock_anchors_top";
static const char *DOCK_INFORMATION_ANCHORS_BOTTOM = "dock_anchors_bottom";
static const char *DOCK_INFORMATION_ANCHORS_LEFT = "dock_anchors_left";
static const char *DOCK_INFORMATION_ANCHORS_RIGHT = "dock_anchors_right";

}

#endif // PACKAGEMANAGERDEFINES_H
