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
 * @file elementsettings.cpp
 * @short Implementation of Widgets::ElementSettings
 *
 * This file contains the implemetation of the
 * Widgets::ElementSettings class and the declaration and
 * implementation of Widgets::ElementSettings::ElementSettingsPrivate.
 */

#include "elementsettings.h"

namespace Widgets
{

/**
 * @internal
 * @short Private class for ElementSettings
 */
class ElementSettings::ElementSettingsPrivate
{
public:
    /**
     * @short Settings
     * 
     * A variant map used to store the
     * settings.
     */
    QVariantMap settings;
};

////// End of private class //////

ElementSettings::ElementSettings(QObject *parent):
    QObject(parent), MappableElementInterface(), d(new ElementSettingsPrivate())
{
}

ElementSettings::ElementSettings(const QVariantMap &settings, QObject *parent):
    QObject(parent), MappableElementInterface(), d(new ElementSettingsPrivate())
{
    d->settings = settings;
}

ElementSettings::~ElementSettings()
{
    delete d;
}

QVariant ElementSettings::value(const QString &key) const
{
    return d->settings.value(key);
}

QVariantMap ElementSettings::toMap() const
{
    return d->settings;
}

void ElementSettings::setValue(const QString &key, const QVariant &value)
{
    if (d->settings.value(key) != value) {
        d->settings.insert(key, value);
        emit settingsChanged(key, value);
    }
}

}
