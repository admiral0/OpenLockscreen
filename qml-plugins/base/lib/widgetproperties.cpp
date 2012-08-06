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

#include "widgetproperties.h"

#include <QtCore/QRect>

#include "widgetbaseproperties_p.h"
#include "graphicalcomponent_p.h"

namespace Widgets
{

static const char *WIDGET_PROPERTIES_GEOMETRY_TAGNAME = "geometry";
static const char *WIDGET_PROPERTIES_GEOMETRY_X_ATTRIBUTE = "x";
static const char *WIDGET_PROPERTIES_GEOMETRY_Y_ATTRIBUTE = "y";
static const char *WIDGET_PROPERTIES_GEOMETRY_Z_ATTRIBUTE = "z";
static const char *WIDGET_PROPERTIES_GEOMETRY_WIDTH_ATTRIBUTE = "width";
static const char *WIDGET_PROPERTIES_GEOMETRY_HEIGHT_ATTRIBUTE = "height";
static const char *WIDGET_PROPERTIES_SETTINGS_TAGNAME = "settings";
static const char *WIDGET_PROPERTIES_SETTINGS_ENTRY_TAGNAME = "entry";
static const char *WIDGET_PROPERTIES_SETTINGS_KEY_ATTRIBUTE = "key";
static const char *WIDGET_PROPERTIES_SETTINGS_VALUE_ATTRIBUTE = "value";
static const char *WIDGET_PROPERTIES_IDENTIFIER_ATTRIBUTE = "identifier";

class WidgetPropertiesPrivate: public WidgetBasePropertiesPrivate, public GraphicalComponentPrivate
{
public:
    WidgetPropertiesPrivate(WidgetProperties *q);
    void copyFromBase(WidgetBaseProperties *base);
    QSize size;
    QPoint position;
    int z;
    bool visible;


private:
    Q_DECLARE_PUBLIC(WidgetBaseProperties)
};

WidgetPropertiesPrivate::WidgetPropertiesPrivate(WidgetProperties *q):
    WidgetBasePropertiesPrivate(q), GraphicalComponentPrivate()
{
    visible = true;
}

void WidgetPropertiesPrivate::copyFromBase(WidgetBaseProperties *base)
{
    icon = base->icon();
    defaultName = base->defaultName();
    defaultDescription = base->defaultDescription();
    foreach (QString language, base->languages()) {
        QPair <QString, QString> data;
        data.first = base->name(language);
        data.second = base->description(language);
        nameAndDescription.insert(language, data);
    }

    fileName = base->fileName();
    packageIdentifier = base->packageIdentifier();
    settingsEnabled = base->isSettingsEnabled();
    minimumSize = QSize(base->minimumWidth(), base->minimumHeight());
    maximumSize = QSize(base->maximumWidth(), base->maximumHeight());
}

////// End of private class //////

WidgetProperties::WidgetProperties(QObject *parent):
    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
{
}

WidgetProperties::WidgetProperties(WidgetBaseProperties *base,
                                   int x, int y, int z, int width, int height,
                                   const QVariantMap &settings, QObject *parent):
    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
{
    W_D(WidgetProperties);
    d->copyFromBase(base);
    d->identifier = generateIdentifier();
    d->settings = settings;
    d->size = QSize(width, height);
    d->position = QPoint(x, y);
    d->z = z;
}

WidgetProperties::WidgetProperties(WidgetBaseProperties *base,
                                   const QRect &geometry, int z,
                                   const QVariantMap &settings, QObject *parent):
    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
{
    W_D(WidgetProperties);
    d->copyFromBase(base);
    d->identifier = generateIdentifier();
    d->settings = settings;
    d->size = QSize(geometry.width(), geometry.height());
    d->position = QPoint(geometry.x(), geometry.y());
    d->z = z;
}

WidgetProperties::WidgetProperties(WidgetBaseProperties *base, const QString &identifier,
                                   int x, int y, int z, int width, int height,
                                   const QVariantMap &settings, QObject *parent):
    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
{
    W_D(WidgetProperties);
    d->copyFromBase(base);
    d->identifier = identifier;
    d->settings = settings;
    d->size = QSize(width, height);
    d->position = QPoint(x, y);
    d->z = z;
}

WidgetProperties::WidgetProperties(WidgetBaseProperties *base,
                                   const QRect &geometry, int z,
                                   const QString &identifier,
                                   const QVariantMap &settings, QObject *parent):
    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
{
    W_D(WidgetProperties);
    d->copyFromBase(base);
    d->identifier = identifier;
    d->settings = settings;
    d->size = QSize(geometry.width(), geometry.height());
    d->position = QPoint(geometry.x(), geometry.y());
    d->z = z;
}

WidgetProperties::WidgetProperties(WidgetPropertiesPrivate *dd, QObject *parent):
    WidgetBaseProperties(dd, parent)
{
}

QString WidgetProperties::identifier() const
{
    W_D(const WidgetProperties);
    return d->identifier;
}

int WidgetProperties::x() const
{
    W_D(const WidgetProperties);
    return d->position.x();
}

int WidgetProperties::y() const
{
    W_D(const WidgetProperties);
    return d->position.y();
}

int WidgetProperties::z() const
{
    W_D(const WidgetProperties);
    return d->z;
}

int WidgetProperties::width() const
{
    W_D(const WidgetProperties);
    return d->size.width();
}

int WidgetProperties::height() const
{
    W_D(const WidgetProperties);
    return d->size.height();
}

bool WidgetProperties::isVisible() const
{
    W_D(const WidgetProperties);
    return d->visible;
}

QVariantMap WidgetProperties::settings() const
{
    W_D(const WidgetProperties);
    return d->settings;
}

bool WidgetProperties::fromXmlElement(const QDomElement &element)
{
    if (!element.hasAttribute(WIDGET_PROPERTIES_IDENTIFIER_ATTRIBUTE)) {
        return false;
    }
    QDomElement geometryElement = element.firstChildElement(WIDGET_PROPERTIES_GEOMETRY_TAGNAME);
    if (geometryElement.isNull()) {
        return false;
    }

    QDomElement settingsElement = element.firstChildElement(WIDGET_PROPERTIES_SETTINGS_TAGNAME);
    if (settingsElement.isNull()) {
        return false;
    }

    if (!WidgetBaseProperties::fromXmlElement(element)) {
        return false;
    }

    setIdentifier(element.attribute(WIDGET_PROPERTIES_IDENTIFIER_ATTRIBUTE));
    int x = geometryElement.attribute(WIDGET_PROPERTIES_GEOMETRY_X_ATTRIBUTE).toInt();
    int y = geometryElement.attribute(WIDGET_PROPERTIES_GEOMETRY_Y_ATTRIBUTE).toInt();
    int z = geometryElement.attribute(WIDGET_PROPERTIES_GEOMETRY_Z_ATTRIBUTE).toInt();
    int width = geometryElement.attribute(WIDGET_PROPERTIES_GEOMETRY_WIDTH_ATTRIBUTE).toInt();
    int height = geometryElement.attribute(WIDGET_PROPERTIES_GEOMETRY_HEIGHT_ATTRIBUTE).toInt();
    setX(x);
    setY(y);
    setZ(z);
    setWidth(width);
    setHeight(height);

    QVariantMap settings;
    QDomElement property =
            settingsElement.firstChildElement(WIDGET_PROPERTIES_SETTINGS_ENTRY_TAGNAME);
    while (!property.isNull()) {
        QString key = property.attribute(WIDGET_PROPERTIES_SETTINGS_KEY_ATTRIBUTE);
        QString value = property.attribute(WIDGET_PROPERTIES_SETTINGS_VALUE_ATTRIBUTE);

        settings.insert(key, QVariant(value));
    }

    return true;
}

QDomElement WidgetProperties::toXmlElement(const QString &tagName, QDomDocument *document) const
{
    QDomElement element = WidgetBaseProperties::toXmlElement(tagName, document);
    element.setAttribute(WIDGET_PROPERTIES_IDENTIFIER_ATTRIBUTE, identifier());

    QDomElement geometryElement = document->createElement(WIDGET_PROPERTIES_GEOMETRY_TAGNAME);
    geometryElement.setAttribute(WIDGET_PROPERTIES_GEOMETRY_X_ATTRIBUTE, x());
    geometryElement.setAttribute(WIDGET_PROPERTIES_GEOMETRY_Y_ATTRIBUTE, y());
    geometryElement.setAttribute(WIDGET_PROPERTIES_GEOMETRY_Z_ATTRIBUTE, z());
    geometryElement.setAttribute(WIDGET_PROPERTIES_GEOMETRY_WIDTH_ATTRIBUTE, width());
    geometryElement.setAttribute(WIDGET_PROPERTIES_GEOMETRY_HEIGHT_ATTRIBUTE, height());
    element.appendChild(geometryElement);

    QDomElement settingsElement = document->createElement(WIDGET_PROPERTIES_SETTINGS_TAGNAME);
    QMapIterator<QString, QVariant> settingsIterator = QMapIterator<QString, QVariant>(settings());
    while (settingsIterator.hasNext()) {
        settingsIterator.next();
        QDomElement settingsEntryElement =
                document->createElement(WIDGET_PROPERTIES_SETTINGS_ENTRY_TAGNAME);
        settingsEntryElement.setAttribute(WIDGET_PROPERTIES_SETTINGS_KEY_ATTRIBUTE,
                                          settingsIterator.key());
        settingsEntryElement.setAttribute(WIDGET_PROPERTIES_SETTINGS_VALUE_ATTRIBUTE,
                                          settingsIterator.value().toString());
        settingsElement.appendChild(settingsEntryElement);
    }
    element.appendChild(settingsElement);

    return element;
}

void WidgetProperties::setIdentifier(const QString &identifier)
{
    W_D(WidgetProperties);
    if (d->identifier != identifier) {
        d->identifier = identifier;
        emit identifierChanged(identifier);
    }
}

void WidgetProperties::setX(int x)
{
    W_D(WidgetProperties);
    if (d->position.x() != x) {
        d->position.setX(x);
        emit xChanged(x);
    }
}

void WidgetProperties::setY(int y)
{
    W_D(WidgetProperties);
    if (d->position.y() != y) {
        d->position.setY(y);
        emit yChanged(y);
    }
}

void WidgetProperties::setZ(int z)
{
    W_D(WidgetProperties);
    if (d->z != z) {
        d->z = z;
        emit xChanged(z);
    }
}

void WidgetProperties::setWidth(int width)
{
    W_D(WidgetProperties);
    if (d->size.width() != width) {
        d->size.setWidth(width);
        emit widthChanged(width);
    }
}

void WidgetProperties::setHeight(int height)
{
    W_D(WidgetProperties);
    if (d->size.height() != height) {
        d->size.setHeight(height);
        emit heightChanged(height);
    }
}

void WidgetProperties::setVisible(bool visible)
{
    W_D(WidgetProperties);
    if (d->visible != visible) {
        d->visible = visible;
        emit visibleChanged(visible);
    }
}

void WidgetProperties::setSettings(const QVariantMap &settings)
{
    W_D(WidgetProperties);
    if (d->settings != settings) {
        d->settings = settings;
        emit settingsChanged(settings);
    }
}


}
