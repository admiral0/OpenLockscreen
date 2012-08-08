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

#ifndef WIDGETS_GRAPHICALCOMPONENTBASE_P_H
#define WIDGETS_GRAPHICALCOMPONENTBASE_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file graphicalcomponentbase_p.h
 * @short Definition of Widgets::GraphicalComponentBasePrivate
 */

#include "graphicalcomponentbase.h"

#include <QtCore/QString>
#include <QtCore/QVariantHash>

namespace Widgets
{

/**
 * @internal
 * @brief Private class for Widgets::GraphicalComponentBase
 */
class GraphicalComponentBasePrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    GraphicalComponentBasePrivate(GraphicalComponentBase *q);
    /**
     * @internal
     * @brief Filename of the component
     */
    QString fileName;
    /**
     * @internal
     * @brief Disambiguation parameter of the component
     */
    QVariantHash disambiguation;
    /**
     * @internal
     * @brief Filename of the settings component of this component
     */
    QString settingsFileName;
private:
    GraphicalComponentBase *q_ptr;
    Q_DECLARE_PUBLIC(GraphicalComponentBase)
};

}

#endif // WIDGETS_GRAPHICALCOMPONENTBASE_P_H
