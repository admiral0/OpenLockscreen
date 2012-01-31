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
 * @file settings.cpp
 * @short Implementation of Widgets::Settings
 *
 * This file contains the implemetation of the
 * Widgets::Settings class and the declaration and
 * implementation of Widgets::Settings::SettingsPrivate.
 */

#include "settings.h"
#include "global.h"

#include <QtCore/QSettings>
#include <QtCore/QStringList>

namespace Widgets
{

/**
 * @internal
 * @short Private class for Settings
 */
class Settings::SettingsPrivate {
public:
    /**
     * @short Default constructor
     *
     * @param parent parent Q-pointer
     */
    SettingsPrivate(Settings *parent);
    /**
     * @short Check version
     * 
     * This method is used to check the version
     * of the application and wipe settings if
     * needed.
     */
    void checkVersion();
    /**
     * @short %Settings store
     *
     * The settings store is managed
     * by QSettings.
     */
    QSettings *settings;
    /**
     * @short Default keys
     *
     * This list stores all the keys
     * that were set by Settings::setDefaultValue().
     * These keys should not be removed.
     */
    QStringList defaultKeys;
    /**
     * @short Settings status
     */
    Settings::SettingsStatus settingsStatus;
private:
    /**
     * @short Q-pointer
     */
    Settings * const q;
};

Settings::SettingsPrivate::SettingsPrivate(Settings *parent):
    q(parent)
{
    settings = new QSettings(q);
    settingsStatus = Settings::SettingsKept;
}

void Settings::SettingsPrivate::checkVersion()
{
    // Get versions
    int versionMajor = settings->value("version/major", -1).toInt();
    int versionMinor = settings->value("version/minor", -1).toInt();
    int versionPatch = settings->value("version/patch", -1).toInt();

    bool versionMajorLess = (versionMajor < VERSION_MAJOR);
    bool versionMajorEqual = (versionMajor == VERSION_MAJOR);

    bool versionMinorLess = (versionMinor < VERSION_MINOR);
    bool versionMinorEqual = (versionMinor == VERSION_MINOR);

    bool beta = (VERSION_PATCH >= 50);
    bool versionPatchLess = (versionPatch < VERSION_PATCH);

    // We need to check if either
    // * major version < current major version
    // * major version == current major version and minor version < current minor version
    // * We are in beta and the beta patch version < current beta patch version
    if (versionMajorLess || (versionMajorEqual && versionMinorLess) ||
        (beta && versionMinorEqual && versionPatchLess)) {
        // Check if there are actually settings
        if(versionMajor == -1 && versionMinor == -1 && versionPatch == -1) {
            settingsStatus = Settings::SettingsFresh;
        } else {
            // Need to wipe out all the settings
            settings->clear();
            settingsStatus = Settings::SettingsWiped;
        }
    }

    settings->setValue("version/major", VERSION_MAJOR);
    settings->setValue("version/minor", VERSION_MINOR);
    settings->setValue("version/patch", VERSION_PATCH);
}

////// End of private class //////

Settings::Settings(QObject *parent) :
    QObject(parent), d(new SettingsPrivate(this))
{
    d->checkVersion();
}

Settings::~Settings()
{
    delete d;
}

QVariant Settings::value(const QString &key) const
{
    return d->settings->value(key);
}

Settings::SettingsStatus Settings::settingsStatus() const
{
    return d->settingsStatus;
}

QString Settings::version() const
{
    return QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);
}

void Settings::setValue(const QString &key, const QVariant &value)
{
    d->settings->setValue(key, value);
    emit valueChanged(key, value);
}

void Settings::setDefaultValue(const QString &key, const QVariant &value)
{
    d->defaultKeys.append(key);
    if (!d->settings->contains(key)) {
        setValue(key, value);
    }
}

void Settings::remove(const QString &key)
{
    if (!d->defaultKeys.contains(key)) {
        d->settings->remove(key);
    }
}

}
