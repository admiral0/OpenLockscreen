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

#include <QtCore/QSettings>
#include <QtCore/QDebug>

static const char *ORGANIZATION_NAME = "SfietKonstantin";
static const char *APPLICATION_NAME = "Widgets";

namespace Widgets
{

class Settings::SettingsPrivate
{
public:
    SettingsPrivate(Settings *parent = 0);
    void setDefaultValue(const QString &key, const QVariant &value);
    QSettings *settings;
    int gridCellWidth;
    int gridCellHeight;
    int gridCellHorizontalMargin;
    int gridCellVerticalMargin;
private:
    Settings * const q;
};

Settings::SettingsPrivate::SettingsPrivate(Settings *parent):
    q(parent)
{
    settings = new QSettings(ORGANIZATION_NAME, APPLICATION_NAME, parent);
}

QVariant Settings::value(const QString &key) const
{
    return d->settings->value(key);
}

void Settings::SettingsPrivate::setDefaultValue(const QString &key, const QVariant &value)
{
    if(!settings->contains(key)) {
        settings->setValue(key, value);
        emit q->valueChanged(key, value);
    }
}

////// End of private class //////

Settings::Settings(QObject *parent):
    QObject(parent), d(new SettingsPrivate(this))
{
}

Settings::~Settings()
{
    delete d;
}

QDeclarativeListProperty<SettingsEntry> Settings::defaultSettings()
{
    return QDeclarativeListProperty<SettingsEntry>(this, 0,
                                                   &Widgets::Settings::appendDefaultSettings);
}

void Settings::appendDefaultSettings(QDeclarativeListProperty<SettingsEntry> *list,
                                     SettingsEntry *entry)
{
    Settings *settings = qobject_cast<Settings *>(list->object);
    if(settings) {
        settings->d->setDefaultValue(entry->key(), entry->value());
    }
}

}

#include "moc_settings.cpp"
