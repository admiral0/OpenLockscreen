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
 * @file dockbaseproperties.cpp
 * @short Implementation of Widgets::DockBaseProperties
 *
 * This file contains the implemetation of the
 * Widgets::DockBaseProperties class and the declaration and
 * implementation of Widgets::DockBaseProperties::DockBasePropertiesPrivate.
 */

#include "dockbaseproperties.h"

#include <QtCore/QSize>

namespace Widgets
{

/**
 * @internal
 * @short Private class for DockBaseProperties
 */
class DockBaseProperties::DockBasePropertiesPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param name name of the dock.
     * @param width width of the dock.
     * @param height height of the dock.
     * @param anchorsTop if the dock is anchors using top anchor.
     * @param anchorsBottom if the dock is anchors using bottom anchor.
     * @param anchorsLeft if the dock is anchors using left anchor.
     * @param anchorsRight if the dock is anchors using right anchor.
     * @param qmlFile QML file used to create the dock.
     * @param package package which the dock belongs to.
     * @param hasSettings if the dock has settings.
     */
    DockBasePropertiesPrivate(const QString &name,
                              int width, int height,
                              bool anchorsTop, bool anchorsBottom,
                              bool anchorsLeft, bool anchorsRight,
                              const QString &qmlFile, const QString &package,
                              bool hasSettings);
    /**
     * @short Name of the dock
     */
    const QString name;
    /**
     * @short Size of the dock
     */
    const QSize size;
    /**
     * @short If the dock is anchored using top anchor
     */
    const bool anchorsTop;
    /**
     * @short If the dock is anchored using bottom anchor
     */
    const bool anchorsBottom;
    /**
     * @short If the dock is anchored using left anchor
     */
    const bool anchorsLeft;
    /**
     * @short If the dock is anchored using right anchor
     */
    const bool anchorsRight;
    /**
     * @short QML file used to create the dock
     */
    const QString qmlFile;
    /**
     * @short Package which the dock belongs to
     */
    const QString package;
    /**
     * @short If the dock has settings
     */
    const bool hasSettings;
};

DockBaseProperties::DockBasePropertiesPrivate::DockBasePropertiesPrivate(const QString &name,
                                                                         int width, int height,
                                                                         bool anchorsTop,
                                                                         bool anchorsBottom,
                                                                         bool anchorsLeft,
                                                                         bool anchorsRight,
                                                                         const QString &qmlFile,
                                                                         const QString &package,
                                                                         bool hasSettings):
    name(name), size(QSize(width, height)),
    anchorsTop(anchorsTop), anchorsBottom(anchorsBottom),
    anchorsLeft(anchorsLeft), anchorsRight(anchorsRight),
    qmlFile(qmlFile), package(package), hasSettings(hasSettings)
{
}

////// End of private class //////

DockBaseProperties::DockBaseProperties(QObject *parent) :
    QObject(parent), MappableElementInterface(),
    d(new DockBasePropertiesPrivate(QString(), 0, 0, false, false, false, false,
                                    QString(),QString(), false))
{
}

DockBaseProperties::DockBaseProperties(const QString &name,
                                       int width, int height,
                                       bool anchorsTop, bool anchorsBottom,
                                       bool anchorsLeft, bool anchorsRight,
                                       const QString &qmlFile, const QString &package,
                                       bool hasSettings,
                                       QObject *parent):
    QObject(parent), MappableElementInterface(),
    d(new DockBasePropertiesPrivate(name, width, height,
                                    anchorsTop, anchorsBottom,
                                    anchorsLeft, anchorsRight,
                                    qmlFile, package, hasSettings))
{
}

DockBaseProperties::~DockBaseProperties()
{
    delete d;
}

QString DockBaseProperties::qmlFile() const
{
    return d->qmlFile;
}

int DockBaseProperties::width() const
{
    return d->size.width();
}

int DockBaseProperties::height() const
{
    return d->size.height();
}

bool DockBaseProperties::anchorsTop() const
{
    return d->anchorsTop;
}

bool DockBaseProperties::anchorsBottom() const
{
    return d->anchorsBottom;
}

bool DockBaseProperties::anchorsLeft() const
{
    return d->anchorsLeft;
}

bool DockBaseProperties::anchorsRight() const
{
    return d->anchorsRight;
}

QString DockBaseProperties::name() const
{
    return d->name;
}

QString DockBaseProperties::package() const
{
    return d->package;
}

bool DockBaseProperties::hasSettings() const
{
    return d->hasSettings;
}

QVariantMap DockBaseProperties::toMap() const
{
    QVariantMap map;
    map.insert("name", d->name);
    map.insert("size", d->size);
    map.insert("anchorsTop", d->anchorsTop);
    map.insert("anchorsBottom", d->anchorsBottom);
    map.insert("anchorsLeft", d->anchorsLeft);
    map.insert("anchorsRight", d->anchorsRight);
    map.insert("qmlFile", d->qmlFile);
    map.insert("package", d->package);
    map.insert("hasSettings", d->hasSettings);

    return map;
}

}
