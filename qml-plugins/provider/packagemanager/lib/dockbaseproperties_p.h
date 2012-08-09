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

#ifndef WIDGETS_DOCKBASEPROPERTIES_P_H
#define WIDGETS_DOCKBASEPROPERTIES_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

#include <QtCore/QSize>

#include "graphicalcomponentbase_p.h"
#include "dockbaseproperties.h"

namespace Widgets
{

class DockBasePropertiesPrivate: public GraphicalComponentBasePrivate
{
public:
    DockBasePropertiesPrivate(DockBaseProperties *q);
    DockBasePropertiesPrivate(const QString &fileName,
                              const QString &packageIdentifier,
                              DockBaseProperties *q);
    virtual bool checkValid(const DesktopParser &parser);
    virtual void parseDesktopFile(const DesktopParser &parser);
    void checkAnchorsValid();
    QSize size;
    bool anchorsTop;
    bool anchorsBottom;
    bool anchorsLeft;
    bool anchorsRight;
private:
    Q_DECLARE_PUBLIC(DockBaseProperties)
};

}

#endif // WIDGETS_DOCKBASEPROPERTIES_P_H