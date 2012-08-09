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
 */

#include "widgetproperties.h"
#include "widgetproperties_p.h"

#include <QtCore/QRect>
#include <QtCore/QDebug>

#include "tools.h"

namespace Widgets
{

/**
 * @brief IDENTIFIER_ATTRIBUTE
 *
 * Used in Widgets::WidgetProperties.
 */
static const char *IDENTIFIER_ATTRIBUTE = "identifier";
/**
 * @brief GEOMETRY_TAGNAME
 *
 * Used in Widgets::WidgetProperties.
 */
static const char *GEOMETRY_TAGNAME = "geometry";
/**
 * @brief GEOMETRY_X_ATTRIBUTE
 *
 * Used in Widgets::WidgetProperties.
 */
static const char *GEOMETRY_X_ATTRIBUTE = "x";
/**
 * @brief GEOMETRY_Y_ATTRIBUTE
 *
 * Used in Widgets::WidgetProperties.
 */
static const char *GEOMETRY_Y_ATTRIBUTE = "y";
/**
 * @brief GEOMETRY_Z_ATTRIBUTE
 *
 * Used in Widgets::WidgetProperties.
 */
static const char *GEOMETRY_Z_ATTRIBUTE = "z";
/**
 * @brief GEOMETRY_WIDTH_ATTRIBUTE
 *
 * Used in Widgets::WidgetProperties.
 */
static const char *GEOMETRY_WIDTH_ATTRIBUTE = "width";
/**
 * @brief GEOMETRY_HEIGHT_ATTRIBUTE
 *
 * Used in Widgets::WidgetProperties.
 */
static const char *GEOMETRY_HEIGHT_ATTRIBUTE = "height";
/**
 * @brief SETTINGS_TAGNAME
 *
 * Used in Widgets::WidgetProperties.
 */
static const char *SETTINGS_TAGNAME = "settings";
//static const char *WIDGET_PROPERTIES_SETTINGS_ENTRY_TAGNAME = "entry";
//static const char *WIDGET_PROPERTIES_SETTINGS_KEY_ATTRIBUTE = "key";
//static const char *WIDGET_PROPERTIES_SETTINGS_VALUE_ATTRIBUTE = "value";



WidgetPropertiesPrivate::WidgetPropertiesPrivate(WidgetProperties *q):
    WidgetBasePropertiesPrivate(q)
{
    visible = true;
}

void WidgetPropertiesPrivate::copyFromBase(WidgetBaseProperties *base)
{
    fileName = base->fileName();
    disambiguation = base->disambiguation();
    settingsFileName = base->settingsFileName();
    minimumSize = QSize(base->minimumWidth(), base->minimumHeight());
    maximumSize = QSize(base->maximumWidth(), base->maximumHeight());
}

WidgetPropertiesComponentBuilderHelper::WidgetPropertiesComponentBuilderHelper():
    GraphicalComponentBaseComponentBuilderHelper()
{
    m_widgetBaseProperties = 0;
}

void WidgetPropertiesComponentBuilderHelper::setProperties(const QDomElement &xmlElement,
                                                                QObject *parent)
{
    GraphicalComponentBaseComponentBuilderHelper::setProperties(xmlElement, parent);
    geometryXmlElement = xmlElement.firstChildElement(GEOMETRY_TAGNAME);
    settingsXmlElement = xmlElement.firstChildElement(SETTINGS_TAGNAME);
}

void WidgetPropertiesComponentBuilderHelper
     ::setWidgetBaseProperties(WidgetBaseProperties *widgetBaseProperties)
{
    m_widgetBaseProperties = widgetBaseProperties;
}

bool WidgetPropertiesComponentBuilderHelper::isValid() const
{
    if (!widgetBaseProperties()) {
        return false;
    }

    if (!xmlElement.hasAttribute(IDENTIFIER_ATTRIBUTE)) {
        return false;
    }
    if (geometryXmlElement.isNull()) {
        return false;
    }

    if (settingsXmlElement.isNull()) {
        return false;
    }

    return GraphicalComponentBaseComponentBuilderHelper::isValid();
}

QString WidgetPropertiesComponentBuilderHelper::identifier() const
{
    return xmlElement.attribute(IDENTIFIER_ATTRIBUTE);
}

int WidgetPropertiesComponentBuilderHelper::x() const
{
    return geometryXmlElement.attribute(GEOMETRY_X_ATTRIBUTE).toInt();
}

int WidgetPropertiesComponentBuilderHelper::y() const
{
    return geometryXmlElement.attribute(GEOMETRY_Y_ATTRIBUTE).toInt();
}

int WidgetPropertiesComponentBuilderHelper::z() const
{
    return geometryXmlElement.attribute(GEOMETRY_Z_ATTRIBUTE).toInt();
}

int WidgetPropertiesComponentBuilderHelper::width() const
{
    return geometryXmlElement.attribute(GEOMETRY_WIDTH_ATTRIBUTE).toInt();
}

int WidgetPropertiesComponentBuilderHelper::height() const
{
    return geometryXmlElement.attribute(GEOMETRY_HEIGHT_ATTRIBUTE).toInt();
}

QVariantHash WidgetPropertiesComponentBuilderHelper::settings() const
{
    return Tools::fromXmlElementToVariantHash(settingsXmlElement);
}

WidgetBaseProperties * WidgetPropertiesComponentBuilderHelper::widgetBaseProperties() const
{
    return m_widgetBaseProperties;
}

WidgetPropertiesComponentBuilder::WidgetPropertiesComponentBuilder():
    AbstractBuilder<WidgetProperties *>()
{
    m_helper = new WidgetPropertiesComponentBuilderHelper();
}

WidgetPropertiesComponentBuilder::~WidgetPropertiesComponentBuilder()
{
    delete m_helper;
}

void WidgetPropertiesComponentBuilder::setProperties(const QDomElement &xmlElement, QObject *parent)
{
    m_helper->setProperties(xmlElement, parent);
}

QString WidgetPropertiesComponentBuilder::fileName() const
{
    return m_helper->fileName();
}

QVariantHash WidgetPropertiesComponentBuilder::disambiguation() const
{
    return m_helper->disambiguation();
}

void WidgetPropertiesComponentBuilder
     ::setWidgetBaseProperties(WidgetBaseProperties *widgetBaseProperties)
{
    m_helper->setWidgetBaseProperties(widgetBaseProperties);
}

void WidgetPropertiesComponentBuilder::buildElement()
{
    if (!m_helper->isValid()) {
        builtElement = 0;
        return;
    }

    builtElement = new WidgetProperties(m_helper->widgetBaseProperties(), m_helper->identifier(),
                                        m_helper->x(), m_helper->y(), m_helper->z(),
                                        m_helper->width(), m_helper->height(),
                                        m_helper->settings(), m_helper->parent());
}

/*
WidgetPropertiesComponentBuilder::WidgetPropertiesComponentBuilder():
    GraphicalComponentBaseComponentBuilder(), widgetBaseProperties(0)
{
}

void WidgetPropertiesComponentBuilder::setProperties(const QDomElement &element, QObject *parent)
{
    GraphicalComponentBaseComponentBuilder::setProperties(element, parent);
    geometryXmlElement = xmlElement.firstChildElement(GEOMETRY_TAGNAME);
    settingsXmlElement = xmlElement.firstChildElement(SETTINGS_TAGNAME);
}

void WidgetPropertiesComponentBuilder::setWidgetBaseProperties(
        WidgetBaseProperties *widgetBasePropertiesToSet)
{
    widgetBaseProperties = widgetBasePropertiesToSet;
}

void WidgetPropertiesComponentBuilder::buildElement()
{
    builtElement = new WidgetProperties(widgetBaseProperties, identifier(),
                                        x(), y(), z(), width(), height(),
                                        settings(), parent);
}

bool WidgetPropertiesComponentBuilder::isValid() const
{
    if (!xmlElement.hasAttribute(IDENTIFIER_ATTRIBUTE)) {
        return false;
    }
    if (geometryXmlElement.isNull()) {
        return false;
    }

    if (settingsXmlElement.isNull()) {
        return false;
    }

    return GraphicalComponentBaseComponentBuilder::isValid();
}

QString WidgetPropertiesComponentBuilder::identifier() const
{
    return xmlElement.attribute(IDENTIFIER_ATTRIBUTE);
}

int WidgetPropertiesComponentBuilder::x() const
{
    return geometryXmlElement.attribute(GEOMETRY_X_ATTRIBUTE).toInt();
}

int WidgetPropertiesComponentBuilder::y() const
{
    return geometryXmlElement.attribute(GEOMETRY_Y_ATTRIBUTE).toInt();
}

int WidgetPropertiesComponentBuilder::z() const
{
    return geometryXmlElement.attribute(GEOMETRY_Z_ATTRIBUTE).toInt();
}

int WidgetPropertiesComponentBuilder::width() const
{
    return geometryXmlElement.attribute(GEOMETRY_WIDTH_ATTRIBUTE).toInt();
}

int WidgetPropertiesComponentBuilder::height() const
{
    return geometryXmlElement.attribute(GEOMETRY_HEIGHT_ATTRIBUTE).toInt();
}

QVariantHash WidgetPropertiesComponentBuilder::settings() const
{
    return Tools::fromXmlElementToVariantHash(settingsXmlElement);
}
*/
WidgetPropertiesXmlBuilder::WidgetPropertiesXmlBuilder():
    GraphicalComponentBaseXmlBuilder()
{
}

void WidgetPropertiesXmlBuilder::buildElement()
{
    GraphicalComponentBaseXmlBuilder::buildElement();
    builtElement.setAttribute(IDENTIFIER_ATTRIBUTE, component()->identifier());

    QDomElement geometryElement = document->createElement(GEOMETRY_TAGNAME);
    geometryElement.setAttribute(GEOMETRY_X_ATTRIBUTE, component()->x());
    geometryElement.setAttribute(GEOMETRY_Y_ATTRIBUTE, component()->y());
    geometryElement.setAttribute(GEOMETRY_Z_ATTRIBUTE, component()->z());
    geometryElement.setAttribute(GEOMETRY_WIDTH_ATTRIBUTE, component()->width());
    geometryElement.setAttribute(GEOMETRY_HEIGHT_ATTRIBUTE, component()->height());
    builtElement.appendChild(geometryElement);

    QDomElement settingsElement = Tools::toXmlElementFromVariantHash(component()->settings(),
                                                                     SETTINGS_TAGNAME,
                                                                     document);
    builtElement.appendChild(settingsElement);
}

WidgetProperties * WidgetPropertiesXmlBuilder::component() const
{
    return static_cast<WidgetProperties *>(GraphicalComponentBaseXmlBuilder::component());
}

////// End of private class //////

WidgetProperties::WidgetProperties(QObject *parent):
    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
{
}

WidgetProperties::WidgetProperties(WidgetBaseProperties *base,
                                   int x, int y, int z, int width, int height,
                                   const QVariantHash &settings, QObject *parent):
    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
{
    W_D(WidgetProperties);
    d->copyFromBase(base);
    d->identifier = generateIdentifier();
    d->settings = settings;
    d->geometry = QRect(x, y, width, height);
    d->z = z;
}

//WidgetProperties::WidgetProperties(WidgetBaseProperties *base,
//                                   const QRect &geometry, int z,
//                                   const QVariantHash &settings, QObject *parent):
//    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
//{
//    W_D(WidgetProperties);
//    d->copyFromBase(base);
//    d->identifier = generateIdentifier();
//    d->settings = settings;
//    d->size = QSize(geometry.width(), geometry.height());
//    d->position = QPoint(geometry.x(), geometry.y());
//    d->z = z;
//}

WidgetProperties::WidgetProperties(WidgetBaseProperties *base, const QString &identifier,
                                   int x, int y, int z, int width, int height,
                                   const QVariantHash &settings, QObject *parent):
    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
{
    W_D(WidgetProperties);
    d->copyFromBase(base);
    d->identifier = identifier;
    d->settings = settings;
    d->geometry = QRect(x, y, width, height);
    d->z = z;
}

//WidgetProperties::WidgetProperties(WidgetBaseProperties *base,
//                                   const QRect &geometry, int z,
//                                   const QString &identifier,
//                                   const QVariantHash &settings, QObject *parent):
//    WidgetBaseProperties(new WidgetPropertiesPrivate(this), parent)
//{
//    W_D(WidgetProperties);
//    d->copyFromBase(base);
//    d->identifier = identifier;
//    d->settings = settings;
//    d->size = QSize(geometry.width(), geometry.height());
//    d->position = QPoint(geometry.x(), geometry.y());
//    d->z = z;
//}

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
    return d->geometry.x();
}

int WidgetProperties::y() const
{
    W_D(const WidgetProperties);
    return d->geometry.y();
}

int WidgetProperties::z() const
{
    W_D(const WidgetProperties);
    return d->z;
}

int WidgetProperties::width() const
{
    W_D(const WidgetProperties);
    return d->geometry.width();
}

int WidgetProperties::height() const
{
    W_D(const WidgetProperties);
    return d->geometry.height();
}

bool WidgetProperties::isVisible() const
{
    W_D(const WidgetProperties);
    return d->visible;
}

QVariantHash WidgetProperties::settings() const
{
    W_D(const WidgetProperties);
    return d->settings;
}

/*bool WidgetProperties::fromXmlElement(const QDomElement &element)
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
}*/

void WidgetProperties::setX(int x)
{
    W_D(WidgetProperties);
    if (d->geometry.x() != x) {
        d->geometry.setX(x);
        emit xChanged();
    }
}

void WidgetProperties::setY(int y)
{
    W_D(WidgetProperties);
    if (d->geometry.y() != y) {
        d->geometry.setY(y);
        emit yChanged();
    }
}

void WidgetProperties::setZ(int z)
{
    W_D(WidgetProperties);
    if (d->z != z) {
        d->z = z;
        emit xChanged();
    }
}

void WidgetProperties::setWidth(int width)
{
    W_D(WidgetProperties);
    if (d->geometry.width() != width) {
        d->geometry.setWidth(width);
        emit widthChanged();
    }
}

void WidgetProperties::setHeight(int height)
{
    W_D(WidgetProperties);
    if (d->geometry.height() != height) {
        d->geometry.setHeight(height);
        emit heightChanged();
    }
}

void WidgetProperties::setVisible(bool visible)
{
    W_D(WidgetProperties);
    if (d->visible != visible) {
        d->visible = visible;
        emit visibleChanged();
    }
}

void WidgetProperties::setSettings(const QVariantHash &settings)
{

    W_D(WidgetProperties);
    if (d->settings != settings) {
        d->settings = settings;
        emit settingsChanged();
    }
}

}
