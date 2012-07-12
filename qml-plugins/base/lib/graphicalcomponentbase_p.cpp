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

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

#include "graphicalcomponentbase_p.h"

#include <QtCore/QDebug>
#include <QtCore/QVariant>

#include "desktopparser.h"
#include "tools.h"

namespace Widgets
{

GraphicalComponentBasePrivate::GraphicalComponentBasePrivate(GraphicalComponentBase *q):
    ComponentBasePrivate(q)
{
    settingsEnabled = false;
}

GraphicalComponentBasePrivate::GraphicalComponentBasePrivate(const QString &fileName,
                                                             const QString &packageIdentifier,
                                                             GraphicalComponentBase *q):
    ComponentBasePrivate(q), fileName(fileName), packageIdentifier(packageIdentifier)
{
    settingsEnabled = false;
}

bool GraphicalComponentBasePrivate::checkValid(const DesktopParser &parser)
{
    return ComponentBasePrivate::checkValid(parser);
}

void GraphicalComponentBasePrivate::parseDesktopFile(const DesktopParser &parser)
{
    ComponentBasePrivate::parseDesktopFile(parser);
}

}
