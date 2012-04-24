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

#ifndef WIDGETS_WIDGETBASEPROPERTIES_P_H
#define WIDGETS_WIDGETBASEPROPERTIES_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

#include "graphicalcomponentbase_p.h"
#include "widgetbaseproperties.h"

#include <QtCore/QSize>

namespace Widgets
{

class WidgetBasePropertiesPrivate: public GraphicalComponentBasePrivate
{
public:
    WidgetBasePropertiesPrivate(WidgetBaseProperties *q);
    WidgetBasePropertiesPrivate(const QString &fileName,
                                const QString &packageIdentifier,
                                WidgetBaseProperties *q);
    virtual bool checkValid(const DesktopParser &parser);
    virtual void parseDesktopFile(const DesktopParser &parser);
    QSize size;
private:
    Q_DECLARE_PUBLIC(WidgetBaseProperties)
};

}

#endif // WIDGETS_WIDGETBASEPROPERTIES_P_H
