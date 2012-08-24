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
 * @file backgroundmanager.cpp
 * @short Implementation of Widgets::Background::BackgroundManager
 */

#include "backgroundmanager.h"

#include <QtCore/QSize>
#include <QtCore/QDebug>

/**
 * @internal
 * @brief BACKGROUND_GROUP
 *
 * Used in Widgets::Background::BackgroundManager.
 */
static const char *BACKGROUND_GROUP = "background";
/**
 * @internal
 * @brief BACKGROUND_WALLPAPER_SOURCE
 *
 * Used in Widgets::Background::BackgroundManager.
 */
static const char *BACKGROUND_WALLPAPER_SOURCE = "wallpaperSource";
/**
 * @internal
 * @brief BACKGROUND_WALLPAPER_WIDTH
 *
 * Used in Widgets::Background::BackgroundManager.
 */
static const char *BACKGROUND_WALLPAPER_WIDTH = "wallpaperWidth";
/**
 * @internal
 * @brief BACKGROUND_WALLPAPER_HEIGHT
 *
 * Used in Widgets::Background::BackgroundManager.
 */
static const char *BACKGROUND_WALLPAPER_HEIGHT = "wallpaperHeight";

namespace Widgets
{

namespace Background
{

/**
 * @internal
 * @brief Private class for Widgets::Background::BackgroundManagerPrivate
 */
class BackgroundManagerPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    BackgroundManagerPrivate(BackgroundManager *q);
    /**
     * @internal
     * @brief Load settings
     */
    void loadSettings();
    /**
     * @internal
     * @brief React to value changed
     * @param group settings group.
     * @param key settings key.
     * @param value settings value.
     */
    void slotValueChanged(const QString &group, const QString &key, const QVariant &value);
    /**
     * @internal
     * @brief Wallpaper source
     */
    QString wallpaperSource;
    /**
     * @internal
     * @brief Wallpaper size
     */
    QSize wallpaperSize;
    /**
     * @internal
     * @brief %Settings
     */
    Settings *settings;
private:
    /**
     * @internal
     * @brief Q-pointer
     */
    BackgroundManager * const q_ptr;
    Q_DECLARE_PUBLIC(BackgroundManager)
};

BackgroundManagerPrivate::BackgroundManagerPrivate(BackgroundManager *q):
    q_ptr(q)
{
    wallpaperSource = QString();
    wallpaperSize = QSize(0, 0);
    settings = 0;
}

void BackgroundManagerPrivate::loadSettings()
{
    Q_Q(BackgroundManager);

    wallpaperSource = settings->value(BACKGROUND_GROUP, BACKGROUND_WALLPAPER_SOURCE).toString();
    emit q->wallpaperSourceChanged();

    int wallPaperWidth = settings->value(BACKGROUND_GROUP, BACKGROUND_WALLPAPER_WIDTH).toInt();
    if(wallpaperSize.width() != wallPaperWidth) {
        wallpaperSize.setWidth(wallPaperWidth);
        emit q->wallpaperWidthChanged();
    }

    int wallPaperHeight = settings->value(BACKGROUND_GROUP, BACKGROUND_WALLPAPER_HEIGHT).toInt();
    if(wallpaperSize.height() != wallPaperHeight) {
        wallpaperSize.setHeight(wallPaperHeight);
        emit q->wallpaperHeightChanged();
    }
}

void BackgroundManagerPrivate::slotValueChanged(const QString &group, const QString &key,
                                                const QVariant &value)
{
    Q_Q(BackgroundManager);
    if (group != BACKGROUND_GROUP) {
        return;
    }


    if(key == BACKGROUND_WALLPAPER_SOURCE) {
        QString newWallpaperSource = value.toString();
        if(wallpaperSource != newWallpaperSource) {
            wallpaperSource = newWallpaperSource;
            emit q->wallpaperSourceChanged();
        }
    } else if(key == BACKGROUND_WALLPAPER_WIDTH) {
        int wallPaperWidth = value.toInt();
        if(wallpaperSize.width() != wallPaperWidth) {
            wallpaperSize.setWidth(wallPaperWidth);
            emit q->wallpaperWidthChanged();
        }
    } else if(key == BACKGROUND_WALLPAPER_HEIGHT) {
        int wallPaperHeight = value.toInt();
        if(wallpaperSize.height() != wallPaperHeight) {
            wallpaperSize.setHeight(wallPaperHeight);
            emit q->wallpaperHeightChanged();
        }
    }
}

////// End of private class /////

BackgroundManager::BackgroundManager(QObject *parent) :
    QObject(parent), d_ptr(new BackgroundManagerPrivate(this))
{
}

BackgroundManager::~BackgroundManager()
{
}

QString BackgroundManager::wallpaperSource() const
{
    Q_D(const BackgroundManager);
    return d->wallpaperSource;
}

int BackgroundManager::wallpaperWidth() const
{
    Q_D(const BackgroundManager);
    return d->wallpaperSize.width();
}

int BackgroundManager::wallpaperHeight() const
{
    Q_D(const BackgroundManager);
    return d->wallpaperSize.height();
}

Settings * BackgroundManager::settings() const
{
    Q_D(const BackgroundManager);
    return d->settings;
}

void BackgroundManager::setSettings(Settings *settings)
{
    Q_D(BackgroundManager);
    if(settings == 0) {
        return;
    }

    d->settings = settings;
    d->loadSettings();
    connect(d->settings, SIGNAL(valueChanged(QString,QString,QVariant)),
            this, SLOT(slotValueChanged(QString,QString,QVariant)));

    emit settingsChanged();
}

}

}

#include "moc_backgroundmanager.cpp"
