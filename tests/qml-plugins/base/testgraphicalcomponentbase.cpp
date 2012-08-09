/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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
 * @internal
 * @file testgraphicalcomponentbase.cpp
 * @short Implementation of TestGraphicalComponentBase
 */

#include "testgraphicalcomponentbase.h"
#include "graphicalcomponentbase.h"
#include "graphicalcomponentbase_p.h"

void TestGraphicalComponentBase::testGraphicalComponentBase()
{
    QString fileName ("doiejdezdjoiezjdoiezdez");
    QVariantHash disambiguation;
    disambiguation.insert("some_integer", 12);
    disambiguation.insert("some_string", QString("dezdzedz"));
    disambiguation.insert("some_boolean", true);
    QString settingsFileName ("jdoiezjdoiezdjoiezdezdezdezdez");
    Widgets::GraphicalComponentBase *component
            = new Widgets::GraphicalComponentBase(fileName, disambiguation, settingsFileName);


    QDomDocument document = QDomDocument();

    Widgets::BuildManager<QDomElement> *xmlBuildManager
            = new Widgets::BuildManager<QDomElement>();
    Widgets::GraphicalComponentBaseXmlBuilder *xmlBuilder
            = new Widgets::GraphicalComponentBaseXmlBuilder();
    xmlBuilder->setProperties(component, "test", &document);
    xmlBuildManager->setBuilder(xmlBuilder);
    xmlBuildManager->build();
    QDomElement builtElement = xmlBuildManager->element();

    document.appendChild(builtElement);

    delete xmlBuildManager;
    delete xmlBuilder;

    Widgets::BuildManager<Widgets::GraphicalComponentBase* > *componentBuildManager
            = new Widgets::BuildManager<Widgets::GraphicalComponentBase* >();
    Widgets::GraphicalComponentBaseComponentBuilder *componentBuilder
            = new Widgets::GraphicalComponentBaseComponentBuilder();
    componentBuilder->setProperties(builtElement);
    componentBuildManager->setBuilder(componentBuilder);
    componentBuildManager->build();

    Widgets::GraphicalComponentBase *builtComponent = componentBuildManager->element();

    delete componentBuildManager;
    delete componentBuilder;

    QCOMPARE(component->fileName(), builtComponent->fileName());
    QCOMPARE(component->disambiguation(), builtComponent->disambiguation());
    QCOMPARE(component->settingsFileName(), builtComponent->settingsFileName());

    delete component;
    delete builtComponent;
}
