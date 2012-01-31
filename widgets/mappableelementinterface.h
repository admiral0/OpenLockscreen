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
 * @file mappableelementinterface.h
 * @short Definition of Widgets::MappableElementInterface
 *
 * This file contains the definition of the
 * Widgets::MappableElementInterface class.
 */

#ifndef WIDGETS_MAPPABLEELEMENTINTERFACE_H
#define WIDGETS_MAPPABLEELEMENTINTERFACE_H

#include <QtCore/QVariantMap>

namespace Widgets
{

/**
 * @short Interface for elements that can be represented by maps
 * 
 * This interface is used for any class that can
 * be represented by maps.
 * 
 * It ensure that these classes implements the toMap() 
 * method.
 */
class MappableElementInterface
{
public:
    /**
     * @short To map
     *
     * This method copies the content
     * of the class that implement it
     * into a map. This makes saving easier.
     *
     * @return the content of a class as a map.
     */
    virtual QVariantMap toMap() const = 0;
};

}

#endif // WIDGETS_MAPPABLEELEMENTINTERFACE_H
