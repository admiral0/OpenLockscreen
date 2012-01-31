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
 * @file settingsmanager.h
 * @short Definition of Widgets::SettingsManager
 *
 * This file contains the definition of the
 * Widgets::SettingsManager class.
 */

#ifndef WIDGETS_SETTINGSMANAGER_H
#define WIDGETS_SETTINGSMANAGER_H

#include "../widgets/settingswithdefault.h"

namespace Widgets
{

/**
 * @short Settings with management capabilities
 * 
 * This class is used to control specific
 * settings. It can control specific settings
 * associated to some keys.
 * 
 * It is possible to control these parameters
 * - wallpaperSource()
 * 
 * This class is used in QML context. Accessing
 * it is done using the "settingsManager" global object.
 * 
 */
class SettingsManager : public SettingsWithDefault
{
    Q_OBJECT
    /**
     * @short The wallpaper source
     * 
     * The wallpaper source is associated to the
     * key wallpaper/source.
     */
    Q_PROPERTY(QString wallpaperSource READ wallpaperSource WRITE setWallpaperSource
               NOTIFY wallpaperSourceChanged)
public:
    /**
     * @short Default constructor
     * 
     * @param parent parent object.
     */
    explicit SettingsManager(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~SettingsManager();
    /**
     * @short Wallpaper source
     * 
     * This method is used to retrive the current wallpaper
     * source that is stored in the settings.
     * 
     * @return path to the current wallpaper source.
     */
    QString wallpaperSource() const;
Q_SIGNALS:
    /**
     * @short Wallpaper changed
     *
     * This signal is emitted when the wallpaper 
     * changed.
     *
     * @param wallpaperSource path to the new wallpaper source.
     */
    void wallpaperSourceChanged(const QString &wallpaperSource);
public Q_SLOTS:
    /**
     * @short Set wallpaper source
     * 
     * This method is used to set the wallpaper source.
     * 
     * @param wallpaperSource path to the wallpaper to set.
     */
    void setWallpaperSource(const QString &wallpaperSource);
private:
    class SettingsManagerPrivate;
    /**
     * @short D-pointer
     */
    SettingsManagerPrivate * const d;
};

}

#endif // WIDGETS_SETTINGSMANAGER_H
