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
 * @short Implementation of Widgets::LauncherManager
 *
 * This file contains the implemetation of the
 * Widgets::LauncherManager class and the declaration and
 * implementation of Widgets::LauncherManager::LauncherManagerPrivate.
 */

#include "launchermanager.h"

#include <QtCore/QProcess>

namespace Widgets
{

/**
 * @internal
 * @short Private class for LauncherManager
 */
class LauncherManager::LauncherManagerPrivate
{
public:
    /**
     * @short Default constructor
     */
    LauncherManagerPrivate();
    /**
     * @short If the launcher is visible
     */
    bool launcherVisible;
};

LauncherManager::LauncherManagerPrivate::LauncherManagerPrivate()
{
    launcherVisible = false;
}

////// End of private class //////

LauncherManager::LauncherManager(QObject *parent) :
    QObject(parent), d(new LauncherManagerPrivate())
{
}

LauncherManager::~LauncherManager()
{
    delete d;
}

bool LauncherManager::isLauncherVisible() const
{
    return d->launcherVisible;
}

void LauncherManager::setLauncherVisible(bool launcherVisible)
{
    if(launcherVisible != d->launcherVisible) {
        d->launcherVisible = launcherVisible;
        emit launcherVisibleChanged(launcherVisible);
    }
}

void LauncherManager::launchApplication(const QString &command)
{
    QProcess::startDetached(command);
}

}
