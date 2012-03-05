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
 * @file settingswrapper.cpp
 * @short Implementation of Widgets::SettingsWrapper
 *
 * This file contains the implemetation of the
 * Widgets::SettingsWrapper class and the declaration and
 * implementation of Widgets::SettingsWrapper::SettingsWrapperPrivate.
 */

#include "settingswrapper.h"
#include "settings.h"

#include <QtCore/QSize>

namespace Widgets
{

/**
 * @internal
 * @short Private class for SettingsWrapper
 */
class SettingsWrapper::SettingsWrapperPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param settings the Settings object to wrap.
     * @param parent parent Q-pointer.
     */
    SettingsWrapperPrivate(Settings *settings, SettingsWrapper *parent);
    /**
     * @short Wrapped settings object
     */
    Settings * const settings;
    /**
     * @short Orientation
     */
    QString orientation;
    /**
     * @short Grid cell size
     */
    QSize gridCellSize;
    /**
     * @short Grid cell margins
     */
    QSize gridCellMargins;
    /**
     * @short Page initial index
     */
    int pageInitialIndex;
    /**
     * @short Wallpaper source
     */
    QString wallpaperSource;
    /**
     * @short Wallpaper size
     */
    QSize wallpaperSize;
private:
    /**
     * @short Q-pointer
     */
    SettingsWrapper * const q;
};

SettingsWrapper::SettingsWrapperPrivate::SettingsWrapperPrivate(Settings *settings,
                                                                SettingsWrapper *parent):
    settings(settings), q(parent)
{
    // Set the wrapped settings
    // Orientation
    orientation = settings->value("view/orientation").toString();
    
    // Grid properties
    int gridCellWidth = settings->value("view/gridCellWidth").toInt();
    int gridCellHeight = settings->value("view/gridCellHeight").toInt();
    gridCellSize = QSize(gridCellWidth, gridCellHeight);
    int gridCellHorizontalMargin = settings->value("view/gridCellHorizontalMargin").toInt();
    int gridCellVerticalMargin = settings->value("view/gridCellVerticalMargin").toInt();
    gridCellMargins = QSize(gridCellHorizontalMargin, gridCellVerticalMargin);
    pageInitialIndex = settings->value("view/pageInitialIndex").toInt();
    
    // wallpaper properties
    wallpaperSource = settings->value("wallpaper/source").toString();
    int wallpaperWidth = settings->value("wallpaper/width").toInt();
    int wallpaperHeight = settings->value("wallpaper/height").toInt();
    wallpaperSize = QSize(wallpaperWidth, wallpaperHeight);
}
////// End of private class //////

SettingsWrapper::SettingsWrapper(Settings *settings, QObject *parent):
    QObject(parent), d(new SettingsWrapperPrivate(settings, this))
{
}

SettingsWrapper::~SettingsWrapper()
{
    delete d;
}

QString SettingsWrapper::orientation() const
{
    return d->orientation;
}

int SettingsWrapper::gridCellWidth() const
{
    return d->gridCellSize.width();
}

int SettingsWrapper::gridCellHeight() const
{
    return d->gridCellSize.height();
}

int SettingsWrapper::gridCellHorizontalMargin() const
{
    return d->gridCellMargins.width();
}

int SettingsWrapper::gridCellVerticalMargin() const
{
    return d->gridCellMargins.height();
}

int SettingsWrapper::pageInitialIndex() const
{
    return d->pageInitialIndex;
}

QString SettingsWrapper::wallpaperSource() const
{
    return d->wallpaperSource;
}

int SettingsWrapper::wallpaperWidth() const
{
    return d->wallpaperSize.width();
}

int SettingsWrapper::wallpaperHeight() const
{
    return d->wallpaperSize.height();
}

}
