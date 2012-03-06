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

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeListProperty>

#include "settingsentry.h"

namespace Widgets
{

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<Widgets::SettingsEntry> defaultSettings
               READ defaultSettings)
public:
    explicit Settings(QObject *parent = 0);
    virtual ~Settings();
    Q_INVOKABLE QVariant value(const QString &key) const;
    QDeclarativeListProperty<SettingsEntry> defaultSettings();
Q_SIGNALS:
    void valueChanged(const QString &key, const QVariant &value);
private:
    static void appendDefaultSettings(QDeclarativeListProperty<SettingsEntry> *list,
                                      SettingsEntry *entry);
    class SettingsPrivate;
    SettingsPrivate * const d;
};

}

#endif // WIDGETS_SETTINGS
