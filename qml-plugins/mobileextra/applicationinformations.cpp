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
 * @short Implementation of Widgets::MobileExtra::ApplicationInformations
 */

#include "applicationinformations.h"

namespace Widgets
{

namespace MobileExtra
{

/**
 * @internal
 * @short Private class for Widgets::MobileExtra::ApplicationInformations
 */
class ApplicationInformationsPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    ApplicationInformationsPrivate();
    /**
     * @internal
     * @short Name
     */
    QString name;
    /**
     * @internal
     * @short Icon
     */
    QString icon;
    /**
     * @internal
     * @short Command line used to run the application
     */
    QString command;
};

////// End of private class //////

ApplicationInformationsPrivate::ApplicationInformationsPrivate()
{
}

ApplicationInformations::ApplicationInformations(const QString &name, const QString &icon,
                                                 const QString &command, QObject *parent):
    QObject(parent), d_ptr(new ApplicationInformationsPrivate())

{
    Q_D(ApplicationInformations);
    d->name = name;
    d->icon = icon;
    d->command = command;
}

ApplicationInformations::~ApplicationInformations()
{
}

QString ApplicationInformations::name() const
{
    Q_D(const ApplicationInformations);
    return d->name;
}

QString ApplicationInformations::icon() const
{
    Q_D(const ApplicationInformations);
    return d->icon;
}

QString ApplicationInformations::command() const
{
    Q_D(const ApplicationInformations);
    return d->command;
}

}

}
