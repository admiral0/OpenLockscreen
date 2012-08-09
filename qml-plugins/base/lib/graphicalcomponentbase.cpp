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
 * @file graphicalcomponentbase.cpp
 * @short Implementation of Widgets::GraphicalComponentBase
 */


#include "graphicalcomponentbase.h"
#include "graphicalcomponentbase_p.h"

#include <QtCore/QDebug>

#include "tools.h"

namespace Widgets
{

/**
 * @brief FILENAME_ATTRIBUTE
 *
 * Used in Widgets::GraphicalComponentBase.
 */
static const char *FILENAME_ATTRIBUTE = "filename";
/**
 * @brief SETTINGS_FILENAME_ATTRIBUTE
 *
 * Used in Widgets::GraphicalComponentBase.
 */
static const char *SETTINGS_FILENAME_ATTRIBUTE = "settings_filename";
/**
 * @brief DISAMBIGUATION_TAG
 *
 * Used in Widgets::GraphicalComponentBase.
 */
static const char *DISAMBIGUATION_TAG = "disambiguation";

GraphicalComponentBasePrivate::GraphicalComponentBasePrivate(GraphicalComponentBase *q):
    q_ptr(q)
{
}

GraphicalComponentBaseComponentBuilderHelper::GraphicalComponentBaseComponentBuilderHelper():
    m_parent(0)
{
}

GraphicalComponentBaseComponentBuilderHelper::~GraphicalComponentBaseComponentBuilderHelper()
{
}

void GraphicalComponentBaseComponentBuilderHelper::
               setProperties(const QDomElement &xmlElementToSet, QObject *parent)
{
    xmlElement = xmlElementToSet;
    m_parent = parent;
}

QObject * GraphicalComponentBaseComponentBuilderHelper::parent() const
{
    return m_parent;
}

bool GraphicalComponentBaseComponentBuilderHelper::isValid() const
{
    if (!xmlElement.hasAttribute(FILENAME_ATTRIBUTE)
        || !xmlElement.hasAttribute(SETTINGS_FILENAME_ATTRIBUTE)) {
        return false;
    }

    QDomElement disambiguationElement = xmlElement.firstChildElement(DISAMBIGUATION_TAG);
    if (disambiguationElement.isNull()) {
        return false;
    }

    return true;
}

QString GraphicalComponentBaseComponentBuilderHelper::fileName() const
{
    return xmlElement.attribute(FILENAME_ATTRIBUTE);
}

QString GraphicalComponentBaseComponentBuilderHelper::settingsFileName() const
{
    return xmlElement.attribute(SETTINGS_FILENAME_ATTRIBUTE);
}

QVariantHash GraphicalComponentBaseComponentBuilderHelper::disambiguation() const
{
    QDomElement disambiguationElement = xmlElement.firstChildElement(DISAMBIGUATION_TAG);
    return Tools::fromXmlElementToVariantHash(disambiguationElement);
}

GraphicalComponentBaseComponentBuilder::GraphicalComponentBaseComponentBuilder():
    AbstractBuilder<GraphicalComponentBase *>()
{
    m_helper = new GraphicalComponentBaseComponentBuilderHelper();
}

GraphicalComponentBaseComponentBuilder::~GraphicalComponentBaseComponentBuilder()
{
    delete m_helper;
}

void GraphicalComponentBaseComponentBuilder::setProperties(const QDomElement &xmlElement,
                                                           QObject *parent)
{
    m_helper->setProperties(xmlElement, parent);
}

void GraphicalComponentBaseComponentBuilder::buildElement()
{
    if (!m_helper->isValid()) {
        builtElement = 0;
        return;
    }
    builtElement = new GraphicalComponentBase(m_helper->fileName(), m_helper->disambiguation(),
                                              m_helper->settingsFileName(), m_helper->parent());
}

GraphicalComponentBaseXmlBuilder::GraphicalComponentBaseXmlBuilder():
    m_component(0)
{
}

void GraphicalComponentBaseXmlBuilder::setProperties(GraphicalComponentBase *componentToSet,
                                                         const QString &tagNameToSet,
                                                         QDomDocument *documentToSet)
{
    m_component = componentToSet;
    tagName = tagNameToSet;
    document = documentToSet;
}

void GraphicalComponentBaseXmlBuilder::buildElement()
{
    builtElement = document->createElement(tagName);
    builtElement.setAttribute(FILENAME_ATTRIBUTE, component()->fileName());
    builtElement.setAttribute(SETTINGS_FILENAME_ATTRIBUTE, component()->settingsFileName());

    QDomElement disambiguationElement
            = Tools::toXmlElementFromVariantHash(component()->disambiguation(), DISAMBIGUATION_TAG,
                                                 document);
    builtElement.appendChild(disambiguationElement);
}

GraphicalComponentBase * GraphicalComponentBaseXmlBuilder::component() const
{
    return m_component;
}

////// End of private class //////

GraphicalComponentBase::GraphicalComponentBase(const QString &fileName,
                                               const QVariantHash &disambiguation,
                                               const QString &settingsFileName,
                                               QObject *parent):
    QObject(parent), d_pointer(new GraphicalComponentBasePrivate(this))
{
    W_D(GraphicalComponentBase);
    d->fileName = fileName;
    d->disambiguation = disambiguation;
    d->settingsFileName = settingsFileName;
}

GraphicalComponentBase::GraphicalComponentBase(GraphicalComponentBasePrivate *dd, QObject *parent):
    QObject(parent), d_pointer(dd)
{
}

GraphicalComponentBase::~GraphicalComponentBase()
{
}

QString GraphicalComponentBase::fileName() const
{
    W_D(const GraphicalComponentBase);
    return d->fileName;
}

QVariantHash GraphicalComponentBase::disambiguation() const
{
    W_D(const GraphicalComponentBase);
    return d->disambiguation;
}

bool GraphicalComponentBase::isSettingsEnabled() const
{
    W_D(const GraphicalComponentBase);
    return !d->settingsFileName.isEmpty();
}

QString GraphicalComponentBase::settingsFileName() const
{
    W_D(const GraphicalComponentBase);
    return d->settingsFileName;
}

}
