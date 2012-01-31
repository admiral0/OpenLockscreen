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
 * @file settingswrapper.h
 * @short Definition of Widgets::SettingsWrapper
 *
 * This file contains the definition of the
 * Widgets::SettingsWrapper class.
 */

#ifndef WIDGETS_SETTINGSWRAPPER_H
#define WIDGETS_SETTINGSWRAPPER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace Widgets
{

class Settings;
/**
 * @short Wrapper around Settings
 *
 * This class is a wrapper around settings that is
 * used to provide easy access of a set of parameters.
 *
 * Since the parameters that are provided here
 * are very important for widgets display, they should
 * not be changed when the application is running, but
 * only when the application has restarted. That's why
 * all these properties are made constants.
 *
 * This class is used in QML context. Accessing
 * it is done using the "settingsWrapper" global object.
 */
class SettingsWrapper : public QObject
{
    Q_OBJECT
    /**
     * @short Orientation
     */
    Q_PROPERTY(QString orientation READ orientation CONSTANT)
    /**
     * @short Grid cell width
     */
    Q_PROPERTY(int gridCellWidth READ gridCellWidth CONSTANT)
    /**
     * @short Grid cell height
     */
    Q_PROPERTY(int gridCellHeight READ gridCellHeight CONSTANT)
    /**
     * @short Grid cell horizontal margin
     */
    Q_PROPERTY(int gridCellHorizontalMargin READ gridCellHorizontalMargin CONSTANT)
    /**
     * @short Grid cell vertical margin
     */
    Q_PROPERTY(int gridCellVerticalMargin READ gridCellVerticalMargin CONSTANT)
    /**
     * @short Initial page index
     */
    Q_PROPERTY(int pageInitialIndex READ pageInitialIndex CONSTANT)
    /**
     * @short Wallpaper source
     */
    Q_PROPERTY(QString wallpaperSource READ wallpaperSource CONSTANT)
    /**
     * @short Wallpaper width
     */
    Q_PROPERTY(int wallpaperWidth READ wallpaperWidth CONSTANT)
    /**
     * @short Wallpaper height
     */
    Q_PROPERTY(int wallpaperHeight READ wallpaperHeight CONSTANT)
public:
    /**
     * @short Default constructor
     *
     * @param settings the Settings object to wrap.
     * @param parent parent object.
     */
    explicit SettingsWrapper(Settings *settings = 0, QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~SettingsWrapper();
    /**
     * @short Orientation
     *
     * This method is used to retrieve
     * the value of "view/orientation" settings.
     *
     * @return the orientation settings.
     */
    QString orientation() const;
    /**
     * @short Grid cell width
     *
     * This method is used to retrieve
     * the value of "view/gridCellWidth" settings.
     *
     * @return the grid cell width settings.
     */
    int gridCellWidth() const;
    /**
     * @short Grid cell height
     *
     * This method is used to retrieve
     * the value of "view/gridCellHeight" settings.
     *
     * @return the grid cell height settings.
     */
    int gridCellHeight() const;
    /**
     * @short Grid cell horizontal margin
     *
     * This method is used to retrieve
     * the value of "view/gridCellHorizontalMargin" settings.
     *
     * @return the grid cell horizontal margin.
     */
    int gridCellHorizontalMargin() const;
     /**
     * @short Grid cell vertical margin
     *
     * This method is used to retrieve
     * the value of "view/gridCellVerticalMargin" settings.
     *
     * @return the grid cell vertical margin.
     */
    int gridCellVerticalMargin() const;
    /**
     * @short Initial page index
     *
     * This method is used to retrieve
     * the value of "view/pageInitialIndex" settings.
     *
     * @return the initial page index.
     */
    int pageInitialIndex() const;
    /**
     * @short Wallpaper source
     * 
     * This method is used to retrieve
     * the value of "wallpaper/source" settings.
     * 
     * @return the wallpaper source
     */
    QString wallpaperSource() const;
    /**
     * @short Wallpaper width
     * 
     * This method is used to retrieve
     * the value of "wallpaper/width" settings.
     * 
     * @return the wallpaper width
     */
    int wallpaperWidth() const;
    /**
     * @short Wallpaper height
     * 
     * This method is used to retrieve
     * the value of "wallpaper/height" settings.
     * 
     * @return the wallpaper height
     */
    int wallpaperHeight() const;
private:
    class SettingsWrapperPrivate;
    /**
     * @short D-pointer
     */
    SettingsWrapperPrivate * const d;

};

}

#endif // WIDGETS_SETTINGSWRAPPER_H

