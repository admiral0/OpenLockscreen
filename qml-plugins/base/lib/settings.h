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

#ifndef WIDGETS_SETTINGS
#define WIDGETS_SETTINGS

/**
 * @file settings.h
 * @short Definition of Widgets::Settings
 */

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeListProperty>

#include "settingsentry.h"

namespace Widgets
{

class SettingsPrivate;
/**
 * @brief %Settings
 *
 * This class is used to manage global settings.
 * It interfaces with QSettings, and make it easier
 * to use with QML.
 *
 * This class is used to store global settings, and is
 * not designed to handle too much of them. But it is
 * very helpful to for storing key-value associations.
 *
 * Settings stored this way have two levels of hiearchy,
 * as the INI files have. The first level is the group, that
 * group similar settings, and the second level is the key.
 *
 * This class creates settings using QSettings, therefore
 * the settings are stored on locations that QSettings
 * support.
 *
 * This class also support default settings that can be
 * passed in order to set default settings. These default
 * settings should be set in a QML context using the
 * defaultSettings property.
 *
 * In order to set or get settings, these methods should
 * be used
 * - value()
 * - setValue()
 *
 * The first method is used to get a settings value, providing a group
 * and the key that is associated to the settings. The second is used
 * to set the value, providing group, key and value.
 *
 * @todo Write on the global tuto that appname and orgname should be set.
 */
class Settings : public QObject
{
    Q_OBJECT
    /**
     * @short Default settings
     */
    Q_PROPERTY(QDeclarativeListProperty<Widgets::SettingsEntry> defaultSettings
               READ defaultSettings)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit Settings(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~Settings();
    /**
     * @short Get a settings value
     * @param group group of the settings value.
     * @param key key of the settings value.
     * @return the settings value associated to the group and key.
     */
    Q_INVOKABLE QVariant value(const QString &group, const QString &key) const;
    /**
     * @brief Default settings
     * @return A declarative list property that is used to manage default settings.
     */
    QDeclarativeListProperty<SettingsEntry> defaultSettings();
public Q_SLOTS:
    /**
     * @brief Set a settings value
     * @param group group of the settings value.
     * @param key key of the settings value.
     * @param value the settings value.
     */
    void setValue(const QString &group, const QString &key, const QVariant &value);
Q_SIGNALS:
    /**
     * @brief Settings value changed
     * @param group group of the settings value.
     * @param key key of the settings value.
     * @param value the settings value.
     */
    void valueChanged(const QString &group, const QString &key, const QVariant &value);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    Settings(SettingsPrivate *dd, QObject *parent = 0);
    /**
     * @brief D-pointer
     */
    const QScopedPointer<SettingsPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(Settings)
};

}

#endif // WIDGETS_SETTINGS
