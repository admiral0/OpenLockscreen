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

#include "dockbaseproperties.h"
#include "dockbaseproperties_p.h"

#include <QtCore/QDebug>

#include "desktopparser.h"
#include "tools.h"

namespace Widgets
{

DockBaseProperties::DockBaseProperties(QObject *parent):
    GraphicalComponentBase(new DockBasePropertiesPrivate(this), parent)
{
}

DockBaseProperties::DockBaseProperties(const QString &fileName, const QString &packageIdentifier,
                                       const QString &settingsFileName,
                                       int width, int height,
                                       bool anchorsTop, bool anchorsBottom,
                                       bool anchorsLeft, bool anchorsRight,
                                       QObject *parent):
    GraphicalComponentBase(new DockBasePropertiesPrivate(this), parent)
{
    W_D(DockBaseProperties);
    d->fileName = fileName;
    d->packageIdentifier = packageIdentifier;
    d->settingsFileName = settingsFileName;
    d->size = QSize(width, height);
    d->anchorsTop = anchorsTop;
    d->anchorsBottom = anchorsBottom;
    d->anchorsLeft = anchorsLeft;
    d->anchorsRight = anchorsRight;
}

DockBaseProperties::DockBaseProperties(DockBasePropertiesPrivate *dd, QObject *parent):
    GraphicalComponentBase(dd, parent)
{
}

DockBaseProperties::DockBaseProperties(const QString &desktopFile,
                                       const QString &packageIdentifier,
                                       QObject *parent):
    GraphicalComponentBase(new DockBasePropertiesPrivate(this), parent)
{
    W_D(DockBaseProperties);
    d->packageIdentifier = packageIdentifier;
    d->fromDesktopFile(desktopFile);
}

bool DockBaseProperties::isValid() const
{
    W_D(const DockBaseProperties);
    return d->valid;
}

int DockBaseProperties::width() const
{
    W_D(const DockBaseProperties);
    return d->size.width();
}

int DockBaseProperties::height() const
{
    W_D(const DockBaseProperties);
    return d->size.height();
}

bool DockBaseProperties::anchorsTop() const
{
    W_D(const DockBaseProperties);
    return d->anchorsTop;
}

bool DockBaseProperties::anchorsBottom() const
{
    W_D(const DockBaseProperties);
    return d->anchorsBottom;
}

bool DockBaseProperties::anchorsLeft() const
{
    W_D(const DockBaseProperties);
    return d->anchorsLeft;
}

bool DockBaseProperties::anchorsRight() const
{
    W_D(const DockBaseProperties);
    return d->anchorsRight;
}

bool DockBaseProperties::fromXmlElement(const QDomElement &element)
{
    return GraphicalComponentBase::fromXmlElement(element);
}

QDomElement DockBaseProperties::toXmlElement(const QString &tagName, QDomDocument *document) const
{
    QDomElement element = GraphicalComponentBase::toXmlElement(tagName, document);
    return element;
}

DockBaseProperties * DockBaseProperties::fromDesktopFile(const QString &desktopFile,
                                                         const QString &packageIdentifier,
                                                         QObject *parent)
{
    return new DockBaseProperties(desktopFile, packageIdentifier, parent);
}

void DockBaseProperties::setWidth(int width)
{
    W_D(DockBaseProperties);
    if (d->size.width() != width) {
        d->size.setWidth(width);
        emit widthChanged(width);
    }
}

void DockBaseProperties::setHeight(int height)
{
    W_D(DockBaseProperties);
    if (d->size.height() != height) {
        d->size.setHeight(height);
        emit heightChanged(height);
    }
}

void DockBaseProperties::setAnchorsTop(bool anchorsTop)
{
    W_D(DockBaseProperties);
    if (d->anchorsTop != anchorsTop) {
        d->anchorsTop = anchorsTop;
        emit anchorsTopChanged(anchorsTop);
    }
}

void DockBaseProperties::setAnchorsBottom(bool anchorsBottom)
{
    W_D(DockBaseProperties);
    if (d->anchorsBottom != anchorsBottom) {
        d->anchorsBottom = anchorsBottom;
        emit anchorsBottomChanged(anchorsBottom);
    }
}

void DockBaseProperties::setAnchorsLeft(bool anchorsLeft)
{
    W_D(DockBaseProperties);
    if (d->anchorsLeft != anchorsLeft) {
        d->anchorsLeft = anchorsLeft;
        emit anchorsLeftChanged(anchorsLeft);
    }
}

void DockBaseProperties::setAnchorsRight(bool anchorsRight)
{
    W_D(DockBaseProperties);
    if (d->anchorsRight != anchorsRight) {
        d->anchorsRight = anchorsRight;
        emit anchorsRightChanged(anchorsRight);
    }
}

}
