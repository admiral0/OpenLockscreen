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

#include <QObject>

#include "settings.h"

namespace Widgets
{

namespace Background
{

class BackgroundManagerPrivate;
class BackgroundManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString wallpaperSource READ wallpaperSource NOTIFY wallpaperSourceChanged)
    Q_PROPERTY(int wallpaperWidth READ wallpaperWidth NOTIFY wallpaperWidthChanged)
    Q_PROPERTY(int wallpaperHeight READ wallpaperHeight NOTIFY wallpaperHeightChanged)
    Q_PROPERTY(Widgets::Settings * settings READ settings WRITE setSettings NOTIFY settingsChanged)
public:
    explicit BackgroundManager(QObject *parent = 0);
    virtual ~BackgroundManager();
    QString wallpaperSource() const;
    int wallpaperWidth() const;
    int wallpaperHeight() const;
    Settings * settings() const;
Q_SIGNALS:
    void wallpaperSourceChanged(const QString &wallpaperSource);
    void wallpaperWidthChanged(int wallpaperWidth);
    void wallpaperHeightChanged(int wallpaperHeight);
    void settingsChanged();
public Q_SLOTS:
    void setSettings(Settings *settings);
protected:
    const QScopedPointer<BackgroundManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BackgroundManager)

    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(const QString &group, const QString &key,
                                                   const QVariant &value))
};

}

}

#endif // WIDGETS_BACKGROUND_BACKGROUNDMANAGER_H
