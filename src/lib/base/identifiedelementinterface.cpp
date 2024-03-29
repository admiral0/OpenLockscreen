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
 * @file identifiedelementinterface.cpp
 * @short Implementation of Widgets::IdentifiedElementInterface
 *
 * This file contains the implemetation of the
 * Widgets::IdentifiedElementInterface class.
 */

#include "identifiedelementinterface.h"

#include <QtCore/QUuid>

namespace Widgets
{

QString IdentifiedElementInterface::generateIdentifier()
{
    QString uuid = QUuid::createUuid().toString();
    uuid = uuid.remove(0, 1);
    uuid.chop(1);

    return uuid;
}

}
