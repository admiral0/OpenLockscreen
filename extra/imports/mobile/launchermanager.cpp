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
 * @file launchermanager.cpp
 * @short Implementation of Mobile::Launcher::LauncherManager
 */

#include "launchermanager.h"

#include <QtCore/QProcess>

namespace Mobile
{

namespace Launcher
{

/**
 * @internal
 * @short Private class for LauncherManager
 */
class LauncherManagerPrivate
{
public:
    /**
     * @short Default constructor
     */
    LauncherManagerPrivate();
    /**
     * @short If the launcher is visible
     */
    bool visible;
};

LauncherManagerPrivate::LauncherManagerPrivate()
{
    visible = false;
}

////// End of private class //////

LauncherManager::LauncherManager(QObject *parent) :
    QObject(parent), d_ptr(new LauncherManagerPrivate())
{
}

LauncherManager::~LauncherManager()
{
}

bool LauncherManager::isVisible() const
{
    Q_D(const LauncherManager);
    return d->visible;
}

void LauncherManager::setVisible(bool visible)
{
    Q_D(LauncherManager);
    if(visible != d->visible) {
        d->visible = visible;
        emit visibleChanged();
    }
}

void LauncherManager::launchApplication(const QString &command)
{
    QProcess::startDetached(command);
    emit applicationLaunched(command);
}

void LauncherManager::unlock()
{
    emit unlocked();
}

}

}
