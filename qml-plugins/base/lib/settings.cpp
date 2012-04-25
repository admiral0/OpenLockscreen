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

#include "settings.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtCore/QVariantMap>
#include <QtGui/QDesktopServices>

#include "widgets_global.h"
#include "xmlserializableinterface.h"


namespace Widgets
{
class SettingsPrivate
{
public:
    SettingsPrivate(Settings *q = 0);
    void setDefaultValue(const QString &group, const QString &key, const QVariant &value);
    void copyDefaultValues();

    QMap<QString, QVariantMap> defaultSettings;
    QSettings settings;

private:
    Q_DECLARE_PUBLIC(Settings)
    Settings * const q_ptr;
};

SettingsPrivate::SettingsPrivate(Settings *q):
    q_ptr(q)
{
}

void SettingsPrivate::setDefaultValue(const QString &group, const QString &key,
                                      const QVariant &value)
{
    Q_Q(Settings);

    if (!defaultSettings.contains(group)) {
        defaultSettings.insert(group, QVariantMap());
    }

    if(!defaultSettings[group].contains(key)) {
        defaultSettings[group].insert(key, value);
        emit q->valueChanged(group, key, value);
    }

    settings.beginGroup(group);

    if(!settings.contains(key)) {
        settings.setValue(key, value);
        emit q->valueChanged(group, key, value);
    }

    settings.endGroup();
}

void SettingsPrivate::copyDefaultValues()
{
    QMapIterator<QString, QVariantMap> groupIterator =
            QMapIterator<QString, QVariantMap>(defaultSettings);
    while (groupIterator.hasNext()) {
        groupIterator.next();
        QString group = groupIterator.key();
        QVariantMap pair = groupIterator.value();

        settings.beginGroup(group);

        QMapIterator<QString, QVariant> pairIterator =
                QMapIterator<QString, QVariant>(pair);
        while (pairIterator.hasNext()) {
            pairIterator.next();
            QString key = pairIterator.key();
            QVariant value = pairIterator.value();

            settings.setValue(key, value);
        }

        settings.endGroup();
    }

    defaultSettings.clear();
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
                                                   &Widgets::Settings::appendDefaultSettings);
}

void Settings::setValue(const QString &group, const QString &key, const QVariant &value)
{
    Q_D(Settings);
    d->settings.setValue(QString("%1/%2").arg(group).arg(key), value);
}

void Settings::appendDefaultSettings(QDeclarativeListProperty<SettingsEntry> *list,
                                     SettingsEntry *entry)
{
    Settings *settings = qobject_cast<Settings *>(list->object);
    if(settings) {
        settings->d_func()->setDefaultValue(entry->group(), entry->key(), entry->value());
    }
}

}

#include "moc_settings.cpp"
