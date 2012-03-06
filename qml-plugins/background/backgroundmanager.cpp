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

#include "backgroundmanager.h"

#include <QtCore/QSize>
#include <QtCore/QDebug>

static const char * WALLPAPER_SOURCE = "wallpaper/source";
static const char * WALLPAPER_WIDTH = "wallpaper/width";
static const char * WALLPAPER_HEIGHT = "wallpaper/height";

namespace Widgets
{

class BackgroundManager::BackgroundManagerPrivate
{
public:
    BackgroundManagerPrivate(BackgroundManager *parent);
    void loadSettings();
    void slotValueChanged(const QString &key, const QVariant &value);
    QString wallpaperSource;
    QSize wallpaperSize;
    Settings *settings;
private:
    BackgroundManager * const q;
};

BackgroundManager::BackgroundManagerPrivate::BackgroundManagerPrivate(BackgroundManager *parent):
    q(parent)
{
    wallpaperSource = QString();
    wallpaperSize = QSize(0, 0);
    settings = 0;
}

void BackgroundManager::BackgroundManagerPrivate::loadSettings()
{
    wallpaperSource = settings->value(WALLPAPER_SOURCE).toString();
    emit q->wallpaperSourceChanged(wallpaperSource);

    int wallPaperWidth = settings->value(WALLPAPER_WIDTH).toInt();
    if(wallpaperSize.width() != wallPaperWidth) {
        wallpaperSize.setWidth(wallPaperWidth);
        emit q->wallpaperWidthChanged(wallPaperWidth);
    }

    int wallPaperHeight = settings->value(WALLPAPER_HEIGHT).toInt();
    if(wallpaperSize.height() != wallPaperHeight) {
        wallpaperSize.setHeight(wallPaperHeight);
        emit q->wallpaperHeightChanged(wallPaperHeight);
    }
}

void BackgroundManager::BackgroundManagerPrivate::slotValueChanged(const QString &key,
                                                                   const QVariant &value)
{
    if(key == WALLPAPER_SOURCE) {
        QString newWallpaperSource = value.toString();
        if(wallpaperSource != newWallpaperSource) {
            wallpaperSource = newWallpaperSource;
            emit q->wallpaperSourceChanged(newWallpaperSource);
        }
    } else if(key == WALLPAPER_WIDTH) {
        int wallPaperWidth = value.toInt();
        if(wallpaperSize.width() != wallPaperWidth) {
            wallpaperSize.setWidth(wallPaperWidth);
            emit q->wallpaperWidthChanged(wallPaperWidth);
        }
    } else if(key == WALLPAPER_HEIGHT) {
        int wallPaperHeight = value.toInt();
        if(wallpaperSize.height() != wallPaperHeight) {
            wallpaperSize.setHeight(wallPaperHeight);
            emit q->wallpaperHeightChanged(wallPaperHeight);
        }
    }
}

////// End of private class /////

BackgroundManager::BackgroundManager(QObject *parent) :
    QObject(parent), d(new BackgroundManagerPrivate(this))
{
}

BackgroundManager::~BackgroundManager()
{
    delete d;
}

QString BackgroundManager::wallpaperSource() const
{
    return d->wallpaperSource;
}

int BackgroundManager::wallpaperWidth() const
{
    return d->wallpaperSize.width();
}

int BackgroundManager::wallpaperHeight() const
{
    return d->wallpaperSize.height();
}

Settings * BackgroundManager::settings() const
{
    return d->settings;
}

void BackgroundManager::setSettings(Settings *settings)
{
    if(settings == 0) {
        return;
    }

    if(d->settings == 0) {
        d->settings = settings;
        d->loadSettings();
        connect(d->settings, SIGNAL(valueChanged(QString,QVariant)),
                this, SLOT(slotValueChanged(QString,QVariant)));

        emit settingsChanged();
    }
}

}

#include "moc_backgroundmanager.cpp"
