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

#ifndef WIDGETS_IDENTIFIEDELEMENTINTERFACE_H
#define WIDGETS_IDENTIFIEDELEMENTINTERFACE_H

/**
 * @file identifiedelementinterface.h
 * @short Definition of Widgets::IdentifiedElementInterface
 *
 * This file contains the definition of the
 * Widgets::IdentifiedElementInterface class.
 */


#include <QtCore/QString>

namespace Widgets
{

/**
 * @short Interface for elements with identifiers
 *
 * This interface (even if it do not provide any
 * interface but only protected method) is used for
 * any class that needs to have unique identifier.
 *
 * The protected method generateIdentifier() is
 * used to generate the needed unique identifier.
 */
class IdentifiedElementInterface
{
protected:
    /**
     * @short Create an identifier
     *
     * This method is used to create an identifier
     * string, that should be unique. It basically
     * uses QUuid to create the identifier and
     * remove the brackets.
     *
     * @return a generated unique identifier.
     */
    static QString generateIdentifier();
};

}

#endif // WIDGETS_IDENTIFIEDELEMENTINTERFACE_H
