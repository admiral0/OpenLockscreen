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
 * @short Definition of Mobile::Launcher::LauncherManager
 */

#ifndef MOBILE_LAUNCHER_LAUNCHERMANAGER_H
#define MOBILE_LAUNCHER_LAUNCHERMANAGER_H

#include <QtCore/QObject>

namespace Mobile
{

namespace Launcher
{

class LauncherManagerPrivate;
/**
 * @short Launcher manager
 *
 * This class is used to manage the application
 * launcher. It is used to show or hide the
 * application launcher, as well as launching
 * applications.
 *
 * This class uses the property visible()
 * to control the visibility of the launcher. Any
 * QML component that needs to show the launcher
 * should set this property to true.
 *
 * This class also provides the method launchApplication()
 * for running commands, and unlock(), to trigger an
 * unlock screen gesture. These methods emits a signal
 * that allow the view to react. The signals are applicationLaunched()
 * and unlocked().
 */
class LauncherManager : public QObject
{
    Q_OBJECT
    /**
     * @short If the launcher is visible
     */
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible
               NOTIFY visibleChanged)
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
     * @return if the launcher is visible.
     */
    bool isVisible() const;
Q_SIGNALS:
    /**
     * @short Launcher visibility changed
     */
    void visibleChanged();
    /**
     * @brief Unlocked
     */
    void unlocked();
    /**
     * @brief Application launched
     * @param command command used to launch the application.
     */
    void applicationLaunched(const QString &command);
public Q_SLOTS:
    /**
     * @short Set if the launcher is visible
     * @param visible if the launcher is visible.
     */
    void setVisible(bool visible);
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
    /**
     * @brief Unlock
     *
     * This method is used to trigger an unlock. It
     * do not do anything but can be used in a QML context
     * to trigger a screen unlock.
     */
    void unlock();
protected:
    QScopedPointer<LauncherManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(LauncherManager)

};

}

}

#endif // MOBILE_LAUNCHER_LAUNCHERMANAGER_H
