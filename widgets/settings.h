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
 * @file settings.h
 * @short Definition of Widgets::Settings
 *
 * This file contains the definition of the
 * Widgets::Settings class.
 */

#ifndef WIDGETS_SETTINGS_H
#define WIDGETS_SETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace Widgets
{

/**
 * @short %Settings
 *
 * This class is used to deal with settings.
 * It provides a wrapper around QSettings and
 * allows to store and retrieve settings from
 * a QSettings object.
 *
 * Storing and retrieving settings is done using
 * - value(const QString &key) const
 * - setValue(const QString &key, const QVariant &value)
 *
 * In these two methods, the key parameter should
 * be a path to a settings, separated by "/", as
 * in QSettings.
 *
 * When a value is saved using setValue, a signal,
 * valueChanged, is automatically emitted with
 * the key and value that have changed.
 *
 * Default values can be managed using
 * - setDefaultValue(const QString &key, const QVariant &value)
 * - setDefaultSettings()
 * The first method behaves like setValue() but will
 * not override a value that already exists. The
 * second method is never called, but can be used
 * in reimplemented classes in order to set default
 * settings values.
 *
 * This class is used in QML context. Accessing
 * it is done using the "settings" global object.
 *
 * @section defaultSettings Some default settings
 *
 * Some default settings that is interesting to set
 * using setDefaultSettings() are
 * - view/orientation
 * - view/pageCount
 * - view/pageInitialIndex
 * - view/gridCellWidth
 * - view/gridCellHeight
 * - view/gridCellHorizontalMargin
 * - view/gridCellVerticalMargin
 * 
 * @section settingsStatus Settings status and versions
 * 
 * During each startup, %Widgets checks the current
 * version, and the version saved in the settings file.
 * If the current version is higher, it will wipe out all
 * old settings, since settings are, most of the time, 
 * incompatible from one version to another.
 * 
 * In order to check if settings has been wiped out, 
 * and check current version, two properties can 
 * be checked in QML context :
 * - settingsStatus()
 * - version()
 * 
 * The first return if settings has been wiped out, and 
 * the second returns the version, formatted as a string.
 */
class Settings : public QObject
{
    Q_OBJECT
    Q_ENUMS(SettingsStatus)
    /**
     * @short Settings status
     */
    Q_PROPERTY(SettingsStatus settingsStatus READ settingsStatus CONSTANT)
    /**
     * @short Version
     */
    Q_PROPERTY(QString version READ version CONSTANT)
public:
    /**
     * @short Settings status
     */
    enum SettingsStatus {
        /**
         * @short The settings were kept
         */
        SettingsKept,
        /**
         * @short The settings results from a fresh installation
         */
        SettingsFresh,
        /**
         * @short The settings were wiped out
         */
        SettingsWiped
    };

    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit Settings(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~Settings();
    /**
     * @short Set default settings
     *
     * This method should be reimplemented and called
     * in subclasses in order to provide to the settings
     * object default parameters.
     *
     * When reimplemeting this method, it is recommanded
     * to use setDefaultValue() method.
     */
    virtual void setDefaultSettings() {}
    /**
     * @short Get value
     *
     * This method is used to retrieve a value from
     * the settings store. The key parameter should
     * be a path to a settings, separated by "/", as
     * in QSettings.
     *
     * If the key do not point on any parameter in
     * the settings store, this method will return
     * an invalid QVariant.
     *
     * @param key key of the value to retrieve.
     * @return value of the parameter as a variant.
     */
    Q_INVOKABLE QVariant value(const QString &key) const;
    /**
     * @short Settings status
     * 
     * This method is used to retrieve 
     * the settings status.
     * 
     * @return the settings status.
     */
    SettingsStatus settingsStatus() const;
    /**
     * @short Version
     * 
     * This method is used to retrieve the current
     * application version, formatted as a string.
     * 
     * @return current version.
     */
    QString version() const;
Q_SIGNALS:
    /**
     * @short Value changed
     *
     * This signal is emitted when a value in the
     * store has changed, that means that setValue
     * has been called.
     *
     * This signal carries the key for which the
     * value has changed and the new value.
     *
     * @param key key of the value that changed.
     * @param value new value.
     */
    void valueChanged(const QString &key, const QVariant &value);
public Q_SLOTS:
    /**
     * @short Set value
     *
     * This method is used to set a value in the
     * settings store. The key parameter should
     * be a path to a settings, separated by "/", as
     * in QSettings.
     *
     * This method triggers an emission of the
     * signal valueChanged().
     *
     * @param key key of the value to set.
     * @param value the value to set.
     */
    void setValue(const QString &key, const QVariant &value);
    /**
     * @short Set default value
     *
     * This method is used to set a default value
     * in the settings store. If a value already
     * exists in the settings store associated to
     * the key, this method will do nothing.
     *
     * The key parameter should be a path to a
     * settings, separated by "/", as in QSettings.
     *
     * It is recommanded to use this method for
     * reimplementing setDefaultSettings().
     *
     * @param key key of the value to set.
     * @param value the value to set.
     */
    void setDefaultValue(const QString &key, const QVariant &value);
    /**
     * @short Remove a key
     *
     * This method is used to remove a key from
     * the settings store. The key parameter should
     * be a path to a settings, separated by "/", as
     * in QSettings.
     *
     * This method do not remove any key that was
     * set by setDefaultValue().
     *
     * @param key the key to remove.
     */
    void remove(const QString &key);
private:
    class SettingsPrivate;
    /**
     * @short D-pointer
     */
    SettingsPrivate *const d;
};

}

#endif // WIDGETS_SETTINGS_H
