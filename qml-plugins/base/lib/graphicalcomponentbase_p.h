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

#include "componentbase_p.h"
#include "graphicalcomponentbase.h"

#include <QtCore/QString>

namespace Widgets
{

class GraphicalComponentBasePrivate: public ComponentBasePrivate
{
public:
    GraphicalComponentBasePrivate(GraphicalComponentBase *q);
    GraphicalComponentBasePrivate(const QString &fileName, const QString &packageIdentifier,
                                  GraphicalComponentBase *q);
    QString fileName;
    QString packageIdentifier;
    QString settingsFileName;
protected:
    virtual void parseDesktopFile(const DesktopParser &parser);
    virtual bool checkValid(const DesktopParser &parser);
private:
    Q_DECLARE_PUBLIC(GraphicalComponentBase)
};

}

#endif // WIDGETS_GRAPHICALCOMPONENTBASE_P_H
