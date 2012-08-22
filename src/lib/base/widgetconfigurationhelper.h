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

#ifndef WIDGETS_WIDGETCONFIGURATIONHELPER_H
#define WIDGETS_WIDGETCONFIGURATIONHELPER_H

/**
 * @file widgetconfigurationhelper.h
 * @short Definition of Widgets::WidgetConfigurationHelper
 */

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

#include "widgetproperties.h"

namespace Widgets
{

/**
 * @brief Configuration helper
 *
 * This class is a helper class that is used to
 * help settings parameters to widgets. This class
 * have two roles.
 *
 * It is first used to set settings, using
 * saveSettings(). This method will set the
 * settings variant map to the passed widget
 * properties, and in QML context, the variant map
 * should be a JS object.
 *
 * It is also used to request a save, using
 * requestSaveSettings(). This method, often
 * used by a view manager, will cause the
 * emission of saveSettingsRequested(). Any
 * component that is listening to this signal
 * should save the settings.
 */
class WidgetConfigurationHelper : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit WidgetConfigurationHelper(QObject *parent = 0);
Q_SIGNALS:
    /**
     * @brief Save settings requested
     * @param widget the widget to setup.
     */
    void saveSettingsRequested(Widgets::WidgetProperties *widget);
public Q_SLOTS:
    /**
     * @brief Request save settings
     * @param widget the widget to setup.
     */
    void requestSaveSettings(Widgets::WidgetProperties *widget);
    /**
     * @brief Save settings
     * @param widget the widget to setup.
     * @param settings settings to set.
     */
    static void saveSettings(Widgets::WidgetProperties *widget, const QVariantMap &settings);
};

}

#endif // WIDGETS_WIDGETCONFIGURATIONHELPER_H
