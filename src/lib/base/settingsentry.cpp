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
 * @file settingsentry.cpp
 * @short Implementation of Widgets::SettingsEntry
 */

#include "settingsentry.h"

namespace Widgets
{

/**
 * @internal
 * @brief Private struct for Widgets::SettingsEntry
 */
struct SettingsEntryPrivate
{
public:
    /**
     * @internal
     * @brief Group
     */
    QString group;
    /**
     * @internal
     * @brief Key
     */
    QString key;
    /**
     * @internal
     * @brief Value
     */
    QVariant value;
};

////// End of private class //////

SettingsEntry::SettingsEntry(QObject *parent) :
    QObject(parent), d_ptr(new SettingsEntryPrivate())
{
}

SettingsEntry::SettingsEntry(SettingsEntryPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

SettingsEntry::~SettingsEntry()
{
}

QString SettingsEntry::group() const
{
    Q_D(const SettingsEntry);
    return d->group;
}

QString SettingsEntry::key() const
{
    Q_D(const SettingsEntry);
    return d->key;
}

QVariant SettingsEntry::value() const
{
    Q_D(const SettingsEntry);
    return d->value;
}

void SettingsEntry::setGroup(const QString &group)
{
    Q_D(SettingsEntry);
    if(d->group != group) {
        d->group = group;
        emit groupChanged();
    }
}

void SettingsEntry::setKey(const QString &key)
{
    Q_D(SettingsEntry);
    if(d->key != key) {
        d->key = key;
        emit keyChanged();
    }
}

void SettingsEntry::setValue(const QVariant &value)
{
    Q_D(SettingsEntry);
    if(d->value != value) {
        d->value = value;
        emit valueChanged();
    }
}

}
