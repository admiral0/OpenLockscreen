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
    d->minimumSize = QSize(width, height);
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

int WidgetBaseProperties::minimumWidth() const
{
    W_D(const WidgetBaseProperties);
    return d->minimumSize.width();
}

int WidgetBaseProperties::minimumHeight() const
{
    W_D(const WidgetBaseProperties);
    return d->minimumSize.height();
}

int WidgetBaseProperties::maximumWidth() const
{
    W_D(const WidgetBaseProperties);
    return d->maximumSize.width();
}

int WidgetBaseProperties::maximumHeight() const
{
    W_D(const WidgetBaseProperties);
    return d->maximumSize.height();
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

void WidgetBaseProperties::setMinimumWidth(int width)
{
    W_D(WidgetBaseProperties);
    if (d->minimumSize.width() != width) {
        d->minimumSize.setWidth(width);
        emit minimumWidthChanged(width);
    }
}

void WidgetBaseProperties::setMinimumHeight(int height)
{
    W_D(WidgetBaseProperties);
    if (d->minimumSize.height() != height) {
        d->minimumSize.setHeight(height);
        emit minimumHeightChanged(height);
    }
}

void WidgetBaseProperties::setMaximumWidth(int width)
{
    W_D(WidgetBaseProperties);
    if (d->maximumSize.width() != width) {
        d->maximumSize.setWidth(width);
        emit maximumWidthChanged(width);
    }
}

void WidgetBaseProperties::setMaximumHeight(int height)
{
    W_D(WidgetBaseProperties);
    if (d->maximumSize.height() != height) {
        d->maximumSize.setHeight(height);
        emit maximumHeightChanged(height);
    }
}

}
