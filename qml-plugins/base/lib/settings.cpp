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
 */

#include "settings.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtCore/QVariantMap>
#include <QtGui/QDesktopServices>

#include "widgets_global.h"


namespace Widgets
{

/**
 * @internal
 * @brief Private class for Widgets::Settings
 */
class SettingsPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    SettingsPrivate(Settings *q = 0);
    /**
     * @internal
     * @brief Set default value
     *
     * This method is used to set default values for
     * some settings.
     *
     * @param group group of the settings value.
     * @param key key of the settings value.
     * @param value the settings value.
     */
    void setDefaultValue(const QString &group, const QString &key, const QVariant &value);
    /**
     * @internal
     * @brief Append default value
     *
     * This method is here for interfacing with QML.
     *
     * @param list declarative list property.
     * @param entry settings entry.
     */
    static void appendDefaultSettings(QDeclarativeListProperty<SettingsEntry> *list,
                                      SettingsEntry *entry);
    /**
     * @internal
     * @brief %Settings
     */
    QSettings settings;

private:
    /**
     * @internal
     * @brief Q-pointer
     */
    Settings * const q_ptr;
    Q_DECLARE_PUBLIC(Settings)
};

SettingsPrivate::SettingsPrivate(Settings *q):
    q_ptr(q)
{
}

void SettingsPrivate::setDefaultValue(const QString &group, const QString &key,
                                      const QVariant &value)
{
    Q_Q(Settings);

    settings.beginGroup(group);

    if(!settings.contains(key)) {
        settings.setValue(key, value);
        emit q->valueChanged(group, key, value);
    }

    settings.endGroup();
}

void SettingsPrivate::appendDefaultSettings(QDeclarativeListProperty<SettingsEntry> *list,
                                            SettingsEntry *entry)
{
    Settings *settings = qobject_cast<Settings *>(list->object);
    if(settings) {
        settings->d_func()->setDefaultValue(entry->group(), entry->key(), entry->value());
    }
}

////// End of private class //////

Settings::Settings(QObject *parent):
    QObject(parent), d_ptr(new SettingsPrivate(this))
{
}

Settings::Settings(SettingsPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

Settings::~Settings()
{
}

QVariant Settings::value(const QString &group, const QString &key) const
{

    Q_D(const Settings);
    return d->settings.value(QString("%1/%2").arg(group).arg(key));
}

QDeclarativeListProperty<SettingsEntry> Settings::defaultSettings()
{
    return QDeclarativeListProperty<SettingsEntry>(this, 0,
                                                   Widgets::SettingsPrivate::appendDefaultSettings);
}

void Settings::setValue(const QString &group, const QString &key, const QVariant &value)
{
    Q_D(Settings);
    d->settings.setValue(QString("%1/%2").arg(group).arg(key), value);
}

}

#include "moc_settings.cpp"
