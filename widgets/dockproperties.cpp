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
 * @file dockproperties.cpp
 * @short Implementation of Widgets::DockProperties
 *
 * This file contains the implemetation of the
 * Widgets::DockProperties class and the declaration and
 * implementation of Widgets::DockProperties::DockPropertiesPrivate.
 */

#include "dockproperties.h"

namespace Widgets
{

/**
 * @internal
 * @short Private class for DockProperties
 */
class DockProperties::DockPropertiesPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param identifier identifier.
     */
    DockPropertiesPrivate(const QString &identifier);
    /**
     * @short identifier
     */
    QString identifier;
    /**
     * @short settings
     */
    ElementSettings *settings;
};

DockProperties::DockPropertiesPrivate::DockPropertiesPrivate(const QString &identifier):
    identifier(identifier)
{
}


////// End of private class //////

DockProperties::DockProperties(QObject *parent):
    DockBaseProperties(parent), IdentifiedElementInterface(), d(new DockPropertiesPrivate(""))
{
    d->settings = new ElementSettings(this);
}

DockProperties::DockProperties(const QString &name, int width, int height,
                               bool anchorsTop, bool anchorsBottom,
                               bool anchorsLeft, bool anchorsRight,
                               const QString &qmlFile, const QString &package,
                               bool hasSettings,
                               const QVariantMap &settings, QObject *parent):
    DockBaseProperties(name, width, height,
                       anchorsTop, anchorsBottom, anchorsLeft, anchorsRight,
                       qmlFile, package, hasSettings, parent),
    IdentifiedElementInterface(),
    d(new DockPropertiesPrivate(generateIdentifier()))
{
    d->settings = new ElementSettings(settings, this);
}

DockProperties::DockProperties(const QString &name, int width, int height,
                               bool anchorsTop, bool anchorsBottom,
                               bool anchorsLeft, bool anchorsRight,
                               const QString &qmlFile, const QString &package,
                               bool hasSettings,
                               const QString &identifier,
                               const QVariantMap &settings,
                               QObject *parent):
    DockBaseProperties(name, width, height,
                       anchorsTop, anchorsBottom, anchorsLeft, anchorsRight,
                       qmlFile, package, hasSettings, parent),
    IdentifiedElementInterface(),
    d(new DockPropertiesPrivate(identifier))
{
    d->settings = new ElementSettings(settings, this);
}

DockProperties::~DockProperties()
{
    delete d;
}

QString DockProperties::identifier() const
{
    return d->identifier;
}

ElementSettings * DockProperties::settings() const
{
    return d->settings;
}

QVariantMap DockProperties::toMap() const
{
    QVariantMap map = DockBaseProperties::toMap();
    map.insert("identifier", d->identifier);
    map.insert("settings", d->settings->toMap());

    return map;
}

void DockProperties::setSettings(const QVariantMap &settings)
{
    bool hasChanges = false;
    QMapIterator<QString, QVariant> iterator = QMapIterator<QString, QVariant>(settings);
    while (iterator.hasNext()) {
        QString key = iterator.key();
        QVariant value = iterator.value();

        if (d->settings->value(key) != value) {
            hasChanges = true;
            d->settings->setValue(key, value);
        }
    }

    if (hasChanges) {
        emit settingsChanged(d->settings);
    }
}

}
