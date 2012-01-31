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
 * @file app.h
 * @short Definition of Widgets::App
 *
 * This file contains the definition of the
 * Widgets::App class.
 */

#ifndef WIDGETS_APP_H
#define WIDGETS_APP_H

#include <QtGui/QApplication>

namespace Widgets
{

/**
 * @short Application
 *
 * This class contains all components of the application.
 * It is used to initialize other components, manage
 * communications between the different components,
 * declare QML context components, as well as
 * destroying unused components.
 */
class App : public QApplication
{
public:
    /**
     * @short Default constructor
     *
     * @param argc argc
     * @param argv argv
     */
    explicit App(int &argc, char **argv);
    /**
     * @short Destructor
     */
    virtual ~App();
private:
    class AppPrivate;
    /**
     * @short D-pointer
     */
    AppPrivate * const d;
};

}

#endif // APP_H
