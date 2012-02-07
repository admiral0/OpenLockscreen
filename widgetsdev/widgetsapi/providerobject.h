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

#ifndef WIDGETS_PROVIDEROBJECT_H
#define WIDGETS_PROVIDEROBJECT_H

#include <QtCore/QObject>
#include "widgetsapi_global.h"
#include "providerinterface.h"

namespace Widgets
{

class WIDGETSAPI_EXPORT ProviderObject :
        public QObject , public ProviderInterface
{
    Q_OBJECT
public:
    ProviderObject(QObject * parent = 0):
        QObject(parent)
    {
    }
Q_SIGNALS:
    void dataChanged(const QString & key , const QVariant & value);
};

}

#endif // WIDGETS_PROVIDEROBJECT_H
