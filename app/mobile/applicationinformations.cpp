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
 * @file applicationinformations.cpp
 * @short Implementation of Widgets::ApplicationInformations
 */

#include "applicationinformations.h"


/**
 * @internal
 * @short Private class for ApplicationInformations
 */
class ApplicationInformations::ApplicationInformationsPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     *
     * @param name name of the application.
     * @param icon icon of the application.
     * @param command command line used to run the application.
     */
    ApplicationInformationsPrivate(const QString &name, const QString &icon,
                                   const QString &command);
    /**
     * @internal
     * @short Name
     */
    const QString name;
    /**
     * @internal
     * @short Icon
     */
    const QString icon;
    /**
     * @internal
     * @short Command line used to run the application
     */
    const QString command;
};

////// End of private class //////

ApplicationInformations::ApplicationInformationsPrivate::
                         ApplicationInformationsPrivate(const QString &name, const QString &icon,
                                                        const QString &command):
    name(name), icon(icon), command(command)
{
}

ApplicationInformations::ApplicationInformations(const QString &name, const QString &icon,
                                                 const QString &command, QObject *parent):
    QObject(parent), d(new ApplicationInformationsPrivate(name, icon, command))

{
}

ApplicationInformations::~ApplicationInformations()
{
    delete d;
}

QString ApplicationInformations::name() const
{
    return d->name;
}

QString ApplicationInformations::icon() const
{
    return d->icon;
}

QString ApplicationInformations::command() const
{
    return d->command;
}
