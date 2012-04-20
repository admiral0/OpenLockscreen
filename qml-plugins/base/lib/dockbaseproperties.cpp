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
#include "dockbasepropertiesdefines.h"

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
                                       bool settingsEnabled,
                                       int width, int height,
                                       bool anchorsTop, bool anchorsBottom,
                                       bool anchorsLeft, bool anchorsRight,
                                       QObject *parent):
    GraphicalComponentBase(new DockBasePropertiesPrivate(this), parent)
{
    Q_D(DockBaseProperties);
    d->fileName = fileName;
    d->packageIdentifier = packageIdentifier;
    d->settingsEnabled = settingsEnabled;
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
    Q_D(DockBaseProperties);
    d->packageIdentifier = packageIdentifier;
    d->fromDesktopFile(desktopFile);
}

bool DockBaseProperties::isValid() const
{
    Q_D(const DockBaseProperties);
    return d->valid;
}

int DockBaseProperties::width() const
{
    Q_D(const DockBaseProperties);
    return d->size.width();
}

int DockBaseProperties::height() const
{
    Q_D(const DockBaseProperties);
    return d->size.height();
}

bool DockBaseProperties::anchorsTop() const
{
    Q_D(const DockBaseProperties);
    return d->anchorsTop;
}

bool DockBaseProperties::anchorsBottom() const
{
    Q_D(const DockBaseProperties);
    return d->anchorsBottom;
}

bool DockBaseProperties::anchorsLeft() const
{
    Q_D(const DockBaseProperties);
    return d->anchorsLeft;
}

bool DockBaseProperties::anchorsRight() const
{
    Q_D(const DockBaseProperties);
    return d->anchorsRight;
}

bool DockBaseProperties::fromXmlElement(const QDomElement &element)
{
    QDomElement geometryElement = element.firstChildElement(DOCK_BASE_PROPERTIES_GEOMETRY_TAGNAME);
    if (geometryElement.isNull()) {
        return false;
    }
    if (!geometryElement.hasAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_WIDTH_ATTRIBUTE)) {
        return false;
    }
    if (!geometryElement.hasAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_HEIGHT_ATTRIBUTE)) {
        return false;
    }
    if (!geometryElement.hasAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_TOP_ATTRIBUTE)) {
        return false;
    }
    if (!geometryElement.hasAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_BOTTOM_ATTRIBUTE)) {
        return false;
    }
    if (!geometryElement.hasAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_LEFT_ATTRIBUTE)) {
        return false;
    }
    if (!geometryElement.hasAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_RIGHT_ATTRIBUTE)) {
        return false;
    }

    if (!GraphicalComponentBase::fromXmlElement(element)) {
        return false;
    }

    setWidth(geometryElement.attribute(DOCK_BASE_PROPERTIES_GEOMETRY_WIDTH_ATTRIBUTE).toInt());
    setHeight(geometryElement.attribute(DOCK_BASE_PROPERTIES_GEOMETRY_HEIGHT_ATTRIBUTE).toInt());
    QString anchorsTopString =
            geometryElement.attribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_TOP_ATTRIBUTE);
    QString anchorsBottomString =
            geometryElement.attribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_BOTTOM_ATTRIBUTE);
    QString anchorsLeftString =
            geometryElement.attribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_LEFT_ATTRIBUTE);
    QString anchorsRightString =
            geometryElement.attribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_RIGHT_ATTRIBUTE);
    setAnchorsTop(Tools::stringToBool(anchorsTopString));
    setAnchorsBottom(Tools::stringToBool(anchorsBottomString));
    setAnchorsLeft(Tools::stringToBool(anchorsLeftString));
    setAnchorsRight(Tools::stringToBool(anchorsRightString));

    return true;
}

QDomElement DockBaseProperties::toXmlElement(const QString &tagName, QDomDocument *document) const
{
    QDomElement element = GraphicalComponentBase::toXmlElement(tagName, document);
    QDomElement geometryElement = document->createElement(DOCK_BASE_PROPERTIES_GEOMETRY_TAGNAME);
    geometryElement.setAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_WIDTH_ATTRIBUTE, width());
    geometryElement.setAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_HEIGHT_ATTRIBUTE, height());
    geometryElement.setAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_TOP_ATTRIBUTE,
                                 Tools::boolToString(anchorsTop()));
    geometryElement.setAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_BOTTOM_ATTRIBUTE,
                                 Tools::boolToString(anchorsBottom()));
    geometryElement.setAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_LEFT_ATTRIBUTE,
                                 Tools::boolToString(anchorsLeft()));
    geometryElement.setAttribute(DOCK_BASE_PROPERTIES_GEOMETRY_ANCHORS_RIGHT_ATTRIBUTE,
                                 Tools::boolToString(anchorsRight()));
    element.appendChild(geometryElement);
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
    Q_D(DockBaseProperties);
    if (d->size.width() != width) {
        d->size.setWidth(width);
        emit widthChanged(width);
    }
}

void DockBaseProperties::setHeight(int height)
{
    Q_D(DockBaseProperties);
    if (d->size.height() != height) {
        d->size.setHeight(height);
        emit heightChanged(height);
    }
}

void DockBaseProperties::setAnchorsTop(bool anchorsTop)
{
    Q_D(DockBaseProperties);
    if (d->anchorsTop != anchorsTop) {
        d->anchorsTop = anchorsTop;
        emit anchorsTopChanged(anchorsTop);
    }
}

void DockBaseProperties::setAnchorsBottom(bool anchorsBottom)
{
    Q_D(DockBaseProperties);
    if (d->anchorsBottom != anchorsBottom) {
        d->anchorsBottom = anchorsBottom;
        emit anchorsBottomChanged(anchorsBottom);
    }
}

void DockBaseProperties::setAnchorsLeft(bool anchorsLeft)
{
    Q_D(DockBaseProperties);
    if (d->anchorsLeft != anchorsLeft) {
        d->anchorsLeft = anchorsLeft;
        emit anchorsLeftChanged(anchorsLeft);
    }
}

void DockBaseProperties::setAnchorsRight(bool anchorsRight)
{
    Q_D(DockBaseProperties);
    if (d->anchorsRight != anchorsRight) {
        d->anchorsRight = anchorsRight;
        emit anchorsRightChanged(anchorsRight);
    }
}

}
