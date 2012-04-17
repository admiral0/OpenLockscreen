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

#include "dockbaseproperties_p.h"
#include "desktopparserdefines.h"

#include <QtCore/QVariant>

#include "desktopparser.h"

namespace Widgets
{

static const char *DESKTOP_FILE_SERVICE_VALUE = "dock";
static const char *DESKTOP_FILE_DOCK_INFO_FILE = "X-Widgets-DockInfo-File";

DockBasePropertiesPrivate::DockBasePropertiesPrivate():
    GraphicalElementBasePropertiesPrivate()
{
    anchorsTop = false;
    anchorsBottom = false;
    anchorsLeft = false;
    anchorsRight = false;
    valid = false;
}

void DockBasePropertiesPrivate::checkValid()
{
    // Width and height and no anchors are set
    if (size.width() > 0 && size.height() > 0 &&
        !anchorsTop && !anchorsBottom && !anchorsLeft && !anchorsRight) {
        valid = true;
        return;
    }

    // Width is set and either top or bottom anchored
    if (size.width() > 0 && size.height() <= 0 &&
        ((anchorsTop && !anchorsBottom) || (!anchorsTop && anchorsBottom)) &&
        !anchorsLeft && !anchorsRight) {
        valid = true;
        return;
    }

    // Height is set and either left or right anchored
    if (size.height() > 0 && size.width() <= 0 &&
        ((anchorsLeft && !anchorsRight) || (!anchorsRight && anchorsLeft)) &&
        !anchorsTop && !anchorsBottom) {
        valid = true;
        return;
    }
}

bool DockBasePropertiesPrivate::checkDesktopFileValid(const DesktopParser &parser)
{
    if (!parser.contains(DESKTOP_FILE_NAME)) {
        return false;
    }
    if (!parser.contains(DESKTOP_FILE_COMMENT)) {
        return false;
    }
    if (parser.value(DESKTOP_FILE_TYPE).toString() != DESKTOP_FILE_TYPE_VALUE) {
        return false;
    }
    if (parser.value(DESKTOP_FILE_SERVICE_TYPE).toString() != DESKTOP_FILE_SERVICE_VALUE) {
        return false;
    }
    if (parser.value(DESKTOP_FILE_DOCK_INFO_FILE).toString().isEmpty()) {
        return false;
    }

    return true;
}

}
