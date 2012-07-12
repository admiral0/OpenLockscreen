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
 * @file widgetbaseproperties.cpp
 * @short Implementation of Widgets::WidgetBaseProperties
 *
 * This file contains the implemetation of the
 * Widgets::WidgetBaseProperties class and the declaration and
 * implementation of Widgets::WidgetBaseProperties::WidgetBasePropertiesPrivate.
 */

#include "widgetbaseproperties.h"
#include <QtCore/QRect>

namespace Widgets
{

/**
 * @internal
 * @short Private class for WidgetBaseProperties
 */
class WidgetBaseProperties::WidgetBasePropertiesPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param name name of the widget.
     * @param defaultWidth default width of the widget.
     * @param defaultHeight default height of the widget.
     * @param qmlFile QML file used to create the widget.
     * @param package package which the widget belongs to.
     * @param hasSettings if the widget has settings.
     */
    WidgetBasePropertiesPrivate(const QString &name, int defaultWidth, int defaultHeight,
                                const QString &qmlFile,
                                const QString &package, bool hasSettings);
    /**
     * @short Name of the widget
     */
    const QString name;
    /**
     * @short Default size of the widget
     */
    const QSize defaultSize;
    /**
     * @short QML file used to create the widget
     */
    const QString qmlFile;
    /**
     * @short Package which the widget belongs to
     */
    const QString package;
    /**
     * @short If the widget has settings
     */
    const bool hasSettings;
};

WidgetBaseProperties::WidgetBasePropertiesPrivate::
                      WidgetBasePropertiesPrivate(const QString &name,
                                                  int defaultWidth,
                                                  int defaultHeight,
                                                  const QString &qmlFile,
                                                  const QString &package,
                                                  bool hasSettings):
    name(name), defaultSize(QSize(defaultWidth, defaultHeight)), qmlFile(qmlFile),
    package(package), hasSettings(hasSettings)
{
}

////// End of private class //////

WidgetBaseProperties::WidgetBaseProperties(QObject *parent):
    QObject(parent), MappableElementInterface(),
    d(new WidgetBasePropertiesPrivate(QString(), 0, 0, QString(), QString(), false))
{
}

WidgetBaseProperties::WidgetBaseProperties(const QString &name, int defaultWidth, int defaultHeight,
                                           const QString &qmlFile, const QString &package,
                                           bool hasSettings, QObject *parent):
    QObject(parent), MappableElementInterface(),
    d(new WidgetBasePropertiesPrivate(name, defaultWidth, defaultHeight,
                                      qmlFile, package, hasSettings))
{
}

WidgetBaseProperties::~WidgetBaseProperties()
{
    delete d;
}

QString WidgetBaseProperties::name() const
{
    return d->name;
}

int WidgetBaseProperties::defaultWidth() const
{
    return d->defaultSize.width();
}

int WidgetBaseProperties::defaultHeight() const
{
    return d->defaultSize.height();
}

QString WidgetBaseProperties::qmlFile() const
{
    return d->qmlFile;
}

QString WidgetBaseProperties::package() const
{
    return d->package;
}

bool WidgetBaseProperties::hasSettings() const
{
    return d->hasSettings;
}

QVariantMap WidgetBaseProperties::toMap() const
{
    QVariantMap map;
    map.insert("name", d->name);
    map.insert("defaultSize", d->defaultSize);
    map.insert("qmlFile", d->qmlFile);
    map.insert("package", d->package);
    map.insert("hasSettings", d->hasSettings);

    return map;
}



}
