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
#include <QtCore/QSettings>

namespace Widgets
{

static const char *ORGANIZATION_NAME = "SfietKonstantin";
static const char *APPLICATION_NAME = "Widgets";

class SettingsPrivate
{
public:
    SettingsPrivate(Settings *q = 0);
    void setDefaultValue(const QString &key, const QVariant &value);
    QSettings *settings;
    int gridCellWidth;
    int gridCellHeight;
    int gridCellHorizontalMargin;
    int gridCellVerticalMargin;
private:
    Q_DECLARE_PUBLIC(Settings)
    Settings * const q_ptr;
};

SettingsPrivate::SettingsPrivate(Settings *q):
    q_ptr(q)
{
    settings = new QSettings(ORGANIZATION_NAME, APPLICATION_NAME, q);
}

void SettingsPrivate::setDefaultValue(const QString &key, const QVariant &value)
{
    Q_Q(Settings);
    if(!settings->contains(key)) {
        settings->setValue(key, value);
        emit q->valueChanged(key, value);
    }
}

////// End of private class //////

Settings::Settings(QObject *parent):
    QObject(parent), d_ptr(new SettingsPrivate(this))
{
}

Settings::~Settings()
{
}

QVariant Settings::value(const QString &key) const
{
    Q_D(const Settings);
    return d->settings->value(key);
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
        settings->d_func()->setDefaultValue(entry->key(), entry->value());
    }
}

}

#include "moc_settings.cpp"
