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

#include "widgetbaseproperties.h"
#include "widgetbaseproperties_p.h"

namespace Widgets
{

WidgetBaseProperties::WidgetBaseProperties(QObject *parent):
    GraphicalComponentBase(new WidgetBasePropertiesPrivate(this), parent)
{
}

WidgetBaseProperties::WidgetBaseProperties(const QString &fileName,
                                           const QString &packageIdentifier,
                                           bool settingsEnabled,
                                           int width, int height,
                                           QObject *parent):
    GraphicalComponentBase(new WidgetBasePropertiesPrivate(this), parent)
{
    W_D(WidgetBaseProperties);
    d->fileName = fileName;
    d->packageIdentifier = packageIdentifier;
    d->settingsEnabled = settingsEnabled;
    d->size = QSize(width, height);
}

WidgetBaseProperties::WidgetBaseProperties(WidgetBasePropertiesPrivate *dd, QObject *parent):
    GraphicalComponentBase(dd, parent)
{
}

WidgetBaseProperties::WidgetBaseProperties(const QString &desktopFile,
                                           const QString &packageIdentifier,
                                           QObject *parent):
    GraphicalComponentBase(new WidgetBasePropertiesPrivate(this), parent)
{
    W_D(WidgetBaseProperties);
    d->packageIdentifier = packageIdentifier;
    d->fromDesktopFile(desktopFile);
}

bool WidgetBaseProperties::isValid() const
{
    W_D(const WidgetBaseProperties);
    return d->valid;
}

int WidgetBaseProperties::width() const
{
    W_D(const WidgetBaseProperties);
    return d->size.width();
}

int WidgetBaseProperties::height() const
{
    W_D(const WidgetBaseProperties);
    return d->size.height();
}

bool WidgetBaseProperties::fromXmlElement(const QDomElement &element)
{
    return GraphicalComponentBase::fromXmlElement(element);
}

QDomElement WidgetBaseProperties::toXmlElement(const QString &tagName, QDomDocument *document) const
{
    QDomElement element = GraphicalComponentBase::toXmlElement(tagName, document);
    return element;
}

WidgetBaseProperties * WidgetBaseProperties::fromDesktopFile(const QString &desktopFile,
                                                             const QString &packageIdentifier,
                                                             QObject *parent)
{
    return new WidgetBaseProperties(desktopFile, packageIdentifier, parent);
}

void WidgetBaseProperties::setWidth(int width)
{
    W_D(WidgetBaseProperties);
    if (d->size.width() != width) {
        d->size.setWidth(width);
        emit widthChanged(width);
    }
}

void WidgetBaseProperties::setHeight(int height)
{
    W_D(WidgetBaseProperties);
    if (d->size.height() != height) {
        d->size.setHeight(height);
        emit heightChanged(height);
    }
}

}
