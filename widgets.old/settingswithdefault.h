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
 * @file settingswithdefault.h
 * @short Definition of Widgets::SettingsWithDefault
 *
 * This file contains the definition of the
 * Widgets::SettingsWithDefault class.
 */

#ifndef WIDGETS_SETTINGSWITHDEFAULT_H
#define WIDGETS_SETTINGSWITHDEFAULT_H

#include "settings.h"

namespace Widgets
{

/**
 * @short Settings with default settings
 *
 * This reimplementation of Settings is used
 * to provide default settings management. It
 * reimplements the setDefaultSettings() method
 * and calls it when the object is constructed.
 */
class SettingsWithDefault : public Settings
{
public:
    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit SettingsWithDefault(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~SettingsWithDefault();
    /**
     * @short Set default settings
     *
     * This reimplementation of settings
     * set all the default settings that are
     * used in the application, like
     * the number of pages, the default layout
     * and all sort of settings.
     */
    virtual void setDefaultSettings();
};

}

#endif // WIDGETS_SETTINGSWITHDEFAULT_H
