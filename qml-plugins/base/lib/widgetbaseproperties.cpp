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
 * @file widgetbaseproperties.cpp
 * @short Implementation of Widgets::WidgetBaseProperties
 */

#include "widgetbaseproperties.h"
#include "widgetbaseproperties_p.h"

namespace Widgets
{

WidgetBasePropertiesPrivate::WidgetBasePropertiesPrivate(WidgetBaseProperties *q):
    GraphicalComponentBasePrivate(q)
{
}

////// End of private class //////

WidgetBaseProperties::WidgetBaseProperties(QObject *parent):
    GraphicalComponentBase(new WidgetBasePropertiesPrivate(this), parent)
{
}

WidgetBaseProperties::WidgetBaseProperties(const QString &fileName,
                                           const QVariantHash &disambiguation,
                                           const QString &settingsFileName,
                                           int minimumWidth, int minimumHeight,
                                           int maximumWidth, int maximumHeight,
                                           QObject *parent):
    GraphicalComponentBase(new WidgetBasePropertiesPrivate(this), parent)
{
    W_D(WidgetBaseProperties);
    d->fileName = fileName;
    d->disambiguation = disambiguation;
    d->settingsFileName = settingsFileName;
    d->minimumSize = QSize(minimumWidth, minimumHeight);
    d->maximumSize = QSize(maximumWidth, maximumHeight);
}

WidgetBaseProperties::WidgetBaseProperties(WidgetBasePropertiesPrivate *dd, QObject *parent):
    GraphicalComponentBase(dd, parent)
{
}

int WidgetBaseProperties::minimumWidth() const
{
    W_D(const WidgetBaseProperties);
    return d->minimumSize.width();
}

int WidgetBaseProperties::minimumHeight() const
{
    W_D(const WidgetBaseProperties);
    return d->minimumSize.height();
}

int WidgetBaseProperties::maximumWidth() const
{
    W_D(const WidgetBaseProperties);
    return d->maximumSize.width();
}

int WidgetBaseProperties::maximumHeight() const
{
    W_D(const WidgetBaseProperties);
    return d->maximumSize.height();
}

}
