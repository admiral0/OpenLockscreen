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
 * @file settingsmanager.cpp
 * @short Implementation of Widgets::SettingsManager
 *
 * This file contains the implemetation of the
 * Widgets::SettingsManager class and the declaration and
 * implementation of Widgets::SettingsManager::SettingsManagerPrivate.
 */

#include "settingsmanager.h"
#include <QtGui/QImageReader>
#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @internal
 * @short Private class for SettingsManager
 */
class SettingsManager::SettingsManagerPrivate
{
public:
    /**
     * @short Default constructor
     * 
     * @param parent parent Q-pointer.
     */
    SettingsManagerPrivate(SettingsManager * parent);
    /**
     * @short Load settings
     */
    void loadSettings();
    /**
     * @short Save settings
     */
    void saveSettings();
    /**
     * @short Wallpaper source
     */
    QString wallpaperSource;
private:
    /**
     * @short Q-pointer
     */
    SettingsManager * const q;
};

SettingsManager::SettingsManagerPrivate::SettingsManagerPrivate(SettingsManager *parent):
    q(parent)
{
}

void SettingsManager::SettingsManagerPrivate::loadSettings()
{
    wallpaperSource = q->value("wallpaper/source").toString();
}

void SettingsManager::SettingsManagerPrivate::saveSettings()
{
    q->setValue("wallpaper/source", wallpaperSource);
}

////// End of private class //////

SettingsManager::SettingsManager(QObject *parent):
    SettingsWithDefault(parent), d(new SettingsManagerPrivate(this))
{
    d->loadSettings();
}

SettingsManager::~SettingsManager()
{
    delete d;
}

QString SettingsManager::wallpaperSource() const
{
    return d->wallpaperSource;
}

void SettingsManager::setWallpaperSource(const QString &wallpaperSource)
{
    if(wallpaperSource != d->wallpaperSource) {
        d->wallpaperSource = wallpaperSource;
        emit wallpaperSourceChanged(wallpaperSource);

        setValue("wallpaper/source", wallpaperSource);
    }
}

}
