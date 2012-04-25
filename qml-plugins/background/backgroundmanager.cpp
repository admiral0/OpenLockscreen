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

static const char *BACKGROUND_GROUP = "background";
static const char *BACKGROUND_WALLPAPER_SOURCE = "wallpaperSource";
static const char *BACKGROUND_WALLPAPER_WIDTH = "wallpaperWidth";
static const char *BACKGROUND_WALLPAPER_HEIGHT = "wallpaperHeight";

namespace Widgets
{

namespace Background
{

class BackgroundManagerPrivate
{
public:
    BackgroundManagerPrivate(BackgroundManager *q);
    void loadSettings();
    void slotValueChanged(const QString &group, const QString &key, const QVariant &value);
    QString wallpaperSource;
    QSize wallpaperSize;
    Settings *settings;
private:
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
    emit q->wallpaperSourceChanged(wallpaperSource);

    int wallPaperWidth = settings->value(BACKGROUND_GROUP, BACKGROUND_WALLPAPER_WIDTH).toInt();
    if(wallpaperSize.width() != wallPaperWidth) {
        wallpaperSize.setWidth(wallPaperWidth);
        emit q->wallpaperWidthChanged(wallPaperWidth);
    }

    int wallPaperHeight = settings->value(BACKGROUND_GROUP, BACKGROUND_WALLPAPER_HEIGHT).toInt();
    if(wallpaperSize.height() != wallPaperHeight) {
        wallpaperSize.setHeight(wallPaperHeight);
        emit q->wallpaperHeightChanged(wallPaperHeight);
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
            emit q->wallpaperSourceChanged(newWallpaperSource);
        }
    } else if(key == BACKGROUND_WALLPAPER_WIDTH) {
        int wallPaperWidth = value.toInt();
        if(wallpaperSize.width() != wallPaperWidth) {
            wallpaperSize.setWidth(wallPaperWidth);
            emit q->wallpaperWidthChanged(wallPaperWidth);
        }
    } else if(key == BACKGROUND_WALLPAPER_HEIGHT) {
        int wallPaperHeight = value.toInt();
        if(wallpaperSize.height() != wallPaperHeight) {
            wallpaperSize.setHeight(wallPaperHeight);
            emit q->wallpaperHeightChanged(wallPaperHeight);
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
