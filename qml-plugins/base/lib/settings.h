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
 * @short Definition of Settings
 *
 * This file contains the definition of the
 * Settings class.
 */

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeListProperty>

#include "settingsentry.h"

namespace Widgets
{

class SettingsPrivate;
class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString componentName READ componentName WRITE setComponentName
               NOTIFY componentNameChanged)
    Q_PROPERTY(QDeclarativeListProperty<Widgets::SettingsEntry> defaultSettings
               READ defaultSettings)
public:
    explicit Settings(QObject *parent = 0);
    virtual ~Settings();
    QString componentName() const;
    void setGroup(const QString &group);
    void clearGroup();
    Q_INVOKABLE QVariant value(const QString &key) const;
    Q_INVOKABLE QVariant value(const QString &group, const QString &key) const;
    QDeclarativeListProperty<SettingsEntry> defaultSettings();
    QMap<QString, QVariantMap> settings() const;
    virtual bool event(QEvent *event);
public Q_SLOTS:
    void reload();
    void setComponentName(const QString &componentName);
    void setValue(const QString &key, const QVariant &value);
    void setValue(const QString &group, const QString &key, const QVariant &value);
Q_SIGNALS:
    void componentNameChanged(const QString &componentName);
    void valueChanged(const QString &group, const QString &key, const QVariant &value);
protected:
    Settings(SettingsPrivate *dd, QObject *parent = 0);
    const QScopedPointer<SettingsPrivate> d_ptr;
private:
    static void appendDefaultSettings(QDeclarativeListProperty<SettingsEntry> *list,
                                      SettingsEntry *entry);
    Q_DECLARE_PRIVATE(Settings)
};

}

#endif // WIDGETS_SETTINGS
