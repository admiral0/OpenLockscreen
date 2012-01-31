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
 * @file launchermanager.h
 * @short Definition of Widgets::LauncherManager
 *
 * This file contains the definition of the
 * Widgets::PackageManager class.
 */

#ifndef WIDGETS_LAUNCHERMANAGER_H
#define WIDGETS_LAUNCHERMANAGER_H

#include <QObject>

namespace Widgets
{

/**
 * @short Launcher manager
 * 
 * This class is used to manage the application
 * launcher. It is used to show or hide the
 * application launcher, as well as launching 
 * applications.
 * 
 * This class uses the attribute launcherVisible()
 * to control the visibility of the launcher. Any
 * QML component that needs to show the launcher
 * should set this property to true.
 * 
 * This class also provides the method launchApplication()
 * for running commands.
 * 
 * This class is used in QML context. Accessing
 * it is done using the "launcherManager" global object.
 */
class LauncherManager : public QObject
{
    Q_OBJECT
    /**
     * @short If the launcher is visible
     */
    Q_PROPERTY(bool launcherVisible READ isLauncherVisible WRITE setLauncherVisible
               NOTIFY launcherVisibleChanged)
public:
    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit LauncherManager(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~LauncherManager();
    /**
     * @short If the launcher is visible
     *
     * This method is used to check if the
     * application launcher is visible.
     *
     * @return if the application launcher is visible.
     */
    bool isLauncherVisible() const;
Q_SIGNALS:
    /**
     * @short Launcher visibility changed
     *
     * Notify that the application launcher 
     * visibility has changed.
     *
     * @param launcherVisible if the application launcher is visible.
     */
    void launcherVisibleChanged(bool launcherVisible);
public Q_SLOTS:
    /**
     * @short Set the visibility of the launcher
     *
     * This method is used to set the
     * visibility of the application launcher.
     *
     * @param launcherVisible if the application launcher is visible.
     */
    void setLauncherVisible(bool launcherVisible);
    /**
     * @short Launch an application
     * 
     * This method is used to launch an application
     * by passing the command that is used to launch
     * it.
     * 
     * @param command the command used to launch the application.
     */
    void launchApplication(const QString &command);
private:
    class LauncherManagerPrivate;
    /**
     * @short D-pointer
     */
    LauncherManagerPrivate * const d;
};

}

#endif // WIDGETS_LAUNCHERMANAGER_H
