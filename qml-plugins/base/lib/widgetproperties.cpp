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

#include "widgetproperties.h"

#include "dockpropertiesdefines.h"
#include "dockbaseproperties_p.h"
#include "graphicalcomponent_p.h"

namespace Widgets
{

class WidgetPropertiesPrivate: public WidgetBasePropertiesPrivate, public GraphicalComponentPrivate
{
public:
    WidgetPropertiesPrivate(WidgetProperties *q);

    void copyFromBase(WidgetBaseProperties *base);

private:
    Q_DECLARE_PUBLIC(WidgetBaseProperties)
};

WidgetPropertiesPrivate::WidgetPropertiesPrivate(WidgetProperties *q):
    WidgetBasePropertiesPrivate(q), GraphicalComponentPrivate()
{
}

void WidgetPropertiesPrivate::copyFromBase(WidgetBaseProperties *base)
{
    icon = base->icon();
    defaultName = base->defaultName();
    defaultDescription = base->defaultDescription();
    foreach (QString language, base->languages()) {
        QPair <QString, QString> data;
        data.first = base->name(language);
        data.second = base->description(language);
        nameAndDescription.insert(language, data);
    }


    fileName = base->fileName();
    packageIdentifier = base->packageIdentifier();
    settingsEnabled = base->isSettingsEnabled();
    size = QSize(base->width(), base->height());
    anchorsTop = base->anchorsTop();
    anchorsBottom = base->anchorsBottom();
    anchorsLeft = base->anchorsLeft();
    anchorsRight = base->anchorsRight();
}

////// End of private class //////
