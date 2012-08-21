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
 * @file elementsettings.h
 * @short Definition of Widgets::ElementSettings
 *
 * This file contains the definition of the
 * Widgets::ElementSettings class.
 */

#ifndef WIDGETS_ELEMENTSETTINGS_H
#define WIDGETS_ELEMENTSETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include "mappableelementinterface.h"

namespace Widgets
{

/**
 * @short Settings for a graphic element
 *
 * This class is a conveinent class that is
 * used to store settings of a widget or a
 * dock. It uses a key-value system to store
 * the data.
 *
 * The settings can be accessed and set using
 * - value()
 * - setValue()
 *
 * The first method is used to obtain the data
 * associated to a key, the second is used to
 * set the data.
 */
class ElementSettings : public QObject, public MappableElementInterface
{
    Q_OBJECT
public:
    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit ElementSettings(QObject *parent = 0);
    /**
     * @short Overloaded constructor
     *
     * This constructor initialize the constructed
     * object with a variant map that contains
     * the settings.
     *
     * @param settings map that contains the settings.
     * @param parent parent object.
     */
    explicit ElementSettings(const QVariantMap &settings, QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~ElementSettings();
    /**
     * @short Value of a settings
     *
     * This method is used to retrieve the settings
     * associated to a key.
     *
     * @param key key of the settings to retrieve.
     * @return the settings associated to the key.
     */
    Q_INVOKABLE QVariant value(const QString &key) const;
    /**
     * @short To map
     *
     * This method copies the content
     * of this class into a map. This
     * makes saving easier.
     *
     * @return the content of this class as a map.
     */
    virtual QVariantMap toMap() const;
Q_SIGNALS:
    /**
     * @short Settings changed
     *
     * Notify that the settings has
     * changed.
     *
     * @param key key of the settings that have changed.
     * @param value new value of the settings.
     */
    void settingsChanged(const QString &key, const QVariant &value);
public Q_SLOTS:
    /**
     * @short Set the value of a settings
     *
     * This method is used to set the value
     * of a settings, given a key and the value.
     *
     * @param key key of the settings to set.
     * @param value value of the settings to set.
     */
    void setValue(const QString &key, const QVariant &value);
private:
    class ElementSettingsPrivate;
    /**
     * @short D-pointer
     */
    ElementSettingsPrivate * const d;
};

}

Q_DECLARE_METATYPE(Widgets::ElementSettings *)

#endif // WIDGETS_ELEMENTSETTINGS_H
