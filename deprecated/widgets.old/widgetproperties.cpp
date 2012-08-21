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
 * @file widgetproperties.cpp
 * @short Implementation of Widgets::WidgetProperties
 *
 * This file contains the implemetation of the
 * Widgets::WidgetProperties class and the declaration and
 * implementation of Widgets::WidgetProperties::WidgetPropertiesPrivate.
 */

#include "widgetproperties.h"
#include <QtCore/QRect>

namespace Widgets
{

/**
 * @internal
 * @short Private class for WidgetProperties
 */
class WidgetProperties::WidgetPropertiesPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param identifier identifier.
     */
    WidgetPropertiesPrivate(const QString &identifier);
    /**
     * @short Widget bounding rectangle
     */
    QRect rect;
    /**
     * @short Z coordinate
     */
    int z;
    /**
     * @short identifier
     */
    QString identifier;
    /**
     * @short settings
     */
    ElementSettings *settings;
};

WidgetProperties::WidgetPropertiesPrivate::WidgetPropertiesPrivate(const QString &identifier):
    identifier(identifier)
{
}

////// End of private class //////

WidgetProperties::WidgetProperties(QObject *parent):
    WidgetBaseProperties(parent), d(new WidgetPropertiesPrivate(""))
{
    d->rect = QRect(0, 0, 0, 0);
    d->z = 0;
    d->settings = new ElementSettings(this);
}

WidgetProperties::WidgetProperties(const QString &name, int defaultWidth, int defaultHeight,
                                   const QString &qmlFile, const QString &package,
                                   bool hasSettings,
                                   int x, int y, int z, int width, int height,
                                   const QVariantMap &settings, QObject *parent):
    WidgetBaseProperties(name, defaultWidth, defaultHeight, qmlFile, package, hasSettings, parent),
    IdentifiedElementInterface(),
    d(new WidgetPropertiesPrivate(IdentifiedElementInterface::generateIdentifier()))
{
    d->rect = QRect(x, y, width, height);
    d->z = z;
    d->settings = new ElementSettings(settings, this);
}

WidgetProperties::WidgetProperties(const QString &name, int defaultWidth, int defaultHeight,
                                   const QString &qmlFile, const QString &package,
                                   bool hasSettings, const QString &identifier,
                                   int x, int y, int z, int width, int height,
                                   const QVariantMap &settings, QObject *parent):
    WidgetBaseProperties(name, defaultWidth, defaultHeight, qmlFile, package, hasSettings, parent),
    IdentifiedElementInterface(),
    d(new WidgetPropertiesPrivate(identifier))
{
    d->rect = QRect(x, y, width, height);
    d->z = z;
    d->settings = new ElementSettings(settings, this);
}

WidgetProperties::~WidgetProperties()
{
    delete d;
}

int WidgetProperties::x() const
{
    return d->rect.x();
}

int WidgetProperties::y() const
{
    return d->rect.y();
}

int WidgetProperties::z() const
{
    return d->z;
}

int WidgetProperties::width() const
{
    return d->rect.width();
}

int WidgetProperties::height() const
{
    return d->rect.height();
}

QString WidgetProperties::identifier() const
{
    return d->identifier;
}

ElementSettings * WidgetProperties::settings() const
{
    return d->settings;
}

void WidgetProperties::setX(int x)
{
    if (x != d->rect.x()) {
        d->rect.setX(x);
        emit xChanged(x);
    }

}

void WidgetProperties::setY(int y)
{
    if (y != d->rect.y()) {
        d->rect.setY(y);
        emit yChanged(y);
    }
}

void WidgetProperties::setZ(int z)
{
    if (z != d->z) {
        d->z = z;
        emit zChanged(z);
    }
}

QVariantMap WidgetProperties::toMap() const
{
    QVariantMap map = WidgetBaseProperties::toMap();
    map.insert("rect", d->rect);
    map.insert("z", d->z);
    map.insert("identifier", d->identifier);
    map.insert("settings", d->settings->toMap());

    return map;
}

void WidgetProperties::setWidth(int width)
{
    if (width != d->rect.width()) {
        d->rect.setWidth(width);
        emit widthChanged(width);
    }
}

void WidgetProperties::setHeight(int height)
{
    if (height != d->rect.height()) {
        d->rect.setHeight(height);
        emit heightChanged(height);
    }
}

void WidgetProperties::setSettings(const QVariantMap &settings)
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
