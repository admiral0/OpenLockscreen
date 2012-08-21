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

#ifndef WIDGETS_BACKGROUND_BACKGROUNDMANAGER_H
#define WIDGETS_BACKGROUND_BACKGROUNDMANAGER_H

/**
 * @file backgroundmanager.h
 * @short Definition of Widgets::Background::BackgroundManager
 */

#include <QtCore/QObject>

#include "settings.h"

namespace Widgets
{

namespace Background
{

class BackgroundManagerPrivate;

/**
 * @brief Background manager
 *
 * This class is used to manage background related
 * settings, inclding background sources, background
 * size, as well as interfacing with settings file.
 * It is used to interface those properties with
 * QML.
 *
 * Background settings are available through these properties
 * - wallpaperSource()
 * - wallpaperWidth()
 * - wallpaperHeight()
 *
 * This class also uses a Widgets::Settings class that is
 * used to store background related settings. This object
 * should be set using the settings() properties.
 */
class BackgroundManager : public QObject
{
    Q_OBJECT
    /**
     * @short Wallpaper source
     */
    Q_PROPERTY(QString wallpaperSource READ wallpaperSource NOTIFY wallpaperSourceChanged)
    /**
     * @short Wallpaper width
     */
    Q_PROPERTY(int wallpaperWidth READ wallpaperWidth NOTIFY wallpaperWidthChanged)
    /**
     * @short Wallpaper height
     */
    Q_PROPERTY(int wallpaperHeight READ wallpaperHeight NOTIFY wallpaperHeightChanged)
    /**
     * @short %Settings
     */
    Q_PROPERTY(Widgets::Settings * settings READ settings WRITE setSettings NOTIFY settingsChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit BackgroundManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~BackgroundManager();
    /**
     * @brief Wallpaper source
     * @return wallpaper source.
     */
    QString wallpaperSource() const;
    /**
     * @brief Wallpaper width
     * @return wallpaper width.
     */
    int wallpaperWidth() const;
    /**
     * @brief Wallpaper height
     * @return wallpaper height.
     */
    int wallpaperHeight() const;
    /**
     * @brief %Settings
     * @return settings.
     */
    Settings * settings() const;
Q_SIGNALS:
    /**
     * @brief Wallpaper source changed
     */
    void wallpaperSourceChanged();
    /**
     * @brief Wallpaper width changed
     */
    void wallpaperWidthChanged();
    /**
     * @brief Wallpaper height changed
     */
    void wallpaperHeightChanged();
    /**
     * @brief %Settings changed
     */
    void settingsChanged();
public Q_SLOTS:
    /**
     * @brief Set settings
     * @param settings settings.
     */
    void setSettings(Settings *settings);
protected:
    /**
     * @brief D-pointer
     */
    const QScopedPointer<BackgroundManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BackgroundManager)

    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(const QString &group, const QString &key,
                                                   const QVariant &value))
};

}

}

#endif // WIDGETS_BACKGROUND_BACKGROUNDMANAGER_H
