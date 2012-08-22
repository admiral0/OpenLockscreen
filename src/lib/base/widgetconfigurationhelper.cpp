/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#include "widgetconfigurationhelper.h"
#include <QtCore/QDebug>

/**
 * @file widgetconfigurationhelper.cpp
 * @short Implementation of Widgets::WidgetConfigurationHelper
 */

namespace Widgets
{

WidgetConfigurationHelper::WidgetConfigurationHelper(QObject *parent) :
    QObject(parent)
{
}

void WidgetConfigurationHelper::requestSaveSettings(WidgetProperties *widget)
{
    emit saveSettingsRequested(widget);
}

void WidgetConfigurationHelper::saveSettings(WidgetProperties *widget, const QVariantMap &settings)
{
    if (!widget) {
        return;
    }
    widget->setSettings(settings);
}

}
