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
 * @short Implementation of Widgets::Docks::DockProperties
 */


#include "dockproperties.h"
#include "dockproperties_p.h"

#include "tools.h"

namespace Widgets
{

namespace Docks
{

/**
 * @brief IDENTIFIER_ATTRIBUTE
 *
 * Used in Widgets::Docks::DockProperties.
 */
static const char *IDENTIFIER_ATTRIBUTE = "identifier";
/**
 * @brief SETTINGS_TAGNAME
 *
 * Used in Widgets::Docks::DockProperties.
 */
static const char *SETTINGS_TAGNAME = "settings";



DockPropertiesPrivate::DockPropertiesPrivate(DockProperties *q):
    DockBasePropertiesPrivate(q)
{
}

void DockPropertiesPrivate::copyFromBase(DockBaseProperties *base)
{
    fileName = base->fileName();
    disambiguation = base->disambiguation();
    settingsFileName = base->settingsFileName();
    size = QSize(base->width(), base->height());
    anchorsTop = base->anchorsTop();
    anchorsBottom = base->anchorsBottom();
    anchorsLeft = base->anchorsLeft();
    anchorsRight = base->anchorsRight();
}

DockPropertiesComponentBuilderHelper::DockPropertiesComponentBuilderHelper():
    GraphicalComponentBaseComponentBuilderHelper()
{
    m_dockBaseProperties = 0;
}

void DockPropertiesComponentBuilderHelper::setProperties(const QDomElement &xmlElement,
                                                                QObject *parent)
{
    GraphicalComponentBaseComponentBuilderHelper::setProperties(xmlElement, parent);
    settingsXmlElement = xmlElement.firstChildElement(SETTINGS_TAGNAME);
}


void DockPropertiesComponentBuilderHelper
     ::setDockBaseProperties(DockBaseProperties *dockBaseProperties)
{
    m_dockBaseProperties = dockBaseProperties;
}

bool DockPropertiesComponentBuilderHelper::isValid() const
{
    if (!dockBaseProperties()) {
        return false;
    }

    if (!xmlElement.hasAttribute(IDENTIFIER_ATTRIBUTE)) {
        return false;
    }

    if (settingsXmlElement.isNull()) {
        return false;
    }

    return GraphicalComponentBaseComponentBuilderHelper::isValid();
}

QString DockPropertiesComponentBuilderHelper::identifier() const
{
    return xmlElement.attribute(IDENTIFIER_ATTRIBUTE);
}

QVariantHash DockPropertiesComponentBuilderHelper::settings() const
{
    return Tools::fromXmlElementToVariantHash(settingsXmlElement);
}

DockBaseProperties * DockPropertiesComponentBuilderHelper::dockBaseProperties() const
{
    return m_dockBaseProperties;
}

DockPropertiesComponentBuilder::DockPropertiesComponentBuilder():
    AbstractBuilder<DockProperties *>()
{
    m_helper = new DockPropertiesComponentBuilderHelper();
}

DockPropertiesComponentBuilder::~DockPropertiesComponentBuilder()
{
    delete m_helper;
}

void DockPropertiesComponentBuilder::setProperties(const QDomElement &xmlElement, QObject *parent)
{
    m_helper->setProperties(xmlElement, parent);
}

QString DockPropertiesComponentBuilder::fileName() const
{
    return m_helper->fileName();
}

QVariantHash DockPropertiesComponentBuilder::disambiguation() const
{
    return m_helper->disambiguation();
}

void DockPropertiesComponentBuilder
     ::setDockBaseProperties(DockBaseProperties *dockBaseProperties)
{
    m_helper->setDockBaseProperties(dockBaseProperties);
}

void DockPropertiesComponentBuilder::buildElement()
{
    if (!m_helper->isValid()) {
        builtElement = 0;
        return;
    }

    builtElement = new DockProperties(m_helper->dockBaseProperties(), m_helper->identifier(),
                                      m_helper->settings(), m_helper->parent());
}

DockPropertiesXmlBuilder::DockPropertiesXmlBuilder():
    GraphicalComponentBaseXmlBuilder()
{
}

void DockPropertiesXmlBuilder::buildElement()
{
    GraphicalComponentBaseXmlBuilder::buildElement();
    builtElement.setAttribute(IDENTIFIER_ATTRIBUTE, component()->identifier());

    QDomElement settingsElement = Tools::toXmlElementFromVariantHash(component()->settings(),
                                                                     SETTINGS_TAGNAME,
                                                                     document);
    builtElement.appendChild(settingsElement);
}

DockProperties * DockPropertiesXmlBuilder::component() const
{
    return static_cast<DockProperties *>(GraphicalComponentBaseXmlBuilder::component());
}

////// End of private class //////


DockProperties::DockProperties(QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate(this), parent)
{
}

DockProperties::DockProperties(DockBaseProperties *base,
                               const QVariantHash &settings,
                               QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate(this), parent)
{
    W_D(DockProperties);
    d->copyFromBase(base);
    d->identifier = generateIdentifier();
    d->settings = settings;
}

DockProperties::DockProperties(DockBaseProperties *base,
                               const QString &identifier,
                               const QVariantHash &settings,
                               QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate(this), parent)
{
    W_D(DockProperties);
    d->copyFromBase(base);
    d->identifier = identifier;
    d->settings = settings;
}

DockProperties::DockProperties(DockPropertiesPrivate *dd, QObject *parent):
    DockBaseProperties(dd, parent)
{
}

QString DockProperties::identifier() const
{
    W_D(const DockProperties);
    return d->identifier;
}

QVariantHash DockProperties::settings() const
{
    W_D(const DockProperties);
    return d->settings;
}

void DockProperties::setSettings(const QVariantHash &settings)
{
    W_D(DockProperties);
    if (d->settings != settings) {
        d->settings = settings;
        emit settingsChanged();
    }
}

}

}
