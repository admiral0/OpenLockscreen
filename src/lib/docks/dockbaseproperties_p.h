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

#ifndef WIDGETS_DOCKS_DOCKBASEPROPERTIES_P_H
#define WIDGETS_DOCKS_DOCKBASEPROPERTIES_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file dockbaseproperties_p.h
 * @short Definition of Widgets::Docks::DockBasePropertiesPrivate
 */

#include <QtCore/QSize>

#include "graphicalcomponentbase_p.h"
#include "dockbaseproperties.h"

namespace Widgets
{

namespace Docks
{

/**
 * @internal
 * @brief Private class for Widgets::Docks::DockBaseProperties
 */
class DockBasePropertiesPrivate: public GraphicalComponentBasePrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    DockBasePropertiesPrivate(DockBaseProperties *q);
    /**
     * @internal
     * @brief Check if a set of anchors and size is valid
     *
     * This method is used to check if a set of anchors and
     * size is valid. If one of the component of size is not set,
     * it should be passed as -1.
     *
     * The correct anchorings are
     * - With width and height defined
     *   - Anchored at top and left
     *   - Anchored at top and right
     *   - Anchored at bottom and left
     *   - Anchored at bottom and right
     *
     * (This anchoring corresponds to a corner anchoring)
     *
     * - With width defined
     *   - Anchored at top, bottom and left
     *   - Anchored at top, bottom and right
     *
     * (This anchoring corresponds to a vertical panel)
     *
     * - With height defined
     *   - Anchored at left, right and top
     *   - Anchored at left, right and bottom
     *
     * (This anchoring corresponds to a horizontal panel)
     *
     * @param anchorsTop if the dock is anchored using top anchor.
     * @param anchorsBottom if the dock is anchored using bottom anchor.
     * @param anchorsLeft if the dock is anchored using left anchor.
     * @param anchorsRight if the dock is anchored using right anchor.
     * @param size size of the dock.
     * @return
     */
    static bool checkAnchorsValid(bool anchorsTop, bool anchorsBottom,
                                  bool anchorsLeft, bool anchorsRight,
                                  const QSize &size);
    /**
     * @internal
     * @brief Size
     */
    QSize size;
    /**
     * @internal
     * @brief If the dock is anchored using top anchor
     */
    bool anchorsTop;
    /**
     * @internal
     * @brief If the dock is anchored using bottom anchor
     */
    bool anchorsBottom;
    /**
     * @internal
     * @brief If the dock is anchored using left anchor
     */
    bool anchorsLeft;
    /**
     * @internal
     * @brief If the dock is anchored using right anchor
     */
    bool anchorsRight;
private:
    Q_DECLARE_PUBLIC(DockBaseProperties)
};

}

}

#endif // WIDGETS_DOCKS_DOCKBASEPROPERTIES_P_H
