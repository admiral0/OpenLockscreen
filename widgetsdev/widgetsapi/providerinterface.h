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

#ifndef WIDGETS_PROVIDERINTERFACE_H
#define WIDGETS_PROVIDERINTERFACE_H

#include "widgetsapi_global.h"
#include <QtCore/QtPlugin>

namespace Widgets
{

class WIDGETSAPI_EXPORT ProviderInterface {
public:
    virtual ~ProviderInterface() {}
    virtual QString identifier() const = 0;
    virtual QVariant data(const QString & key) const = 0;
    virtual void setData(const QString & key , const QVariant & value) = 0;
};

}

Q_DECLARE_INTERFACE(Widgets::ProviderInterface, "org.sk.widgets.ProviderInterface/1.0")

#endif // WIDGETS_PROVIDERINTERFACE_H
