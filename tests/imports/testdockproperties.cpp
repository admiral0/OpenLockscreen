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
 * @file testdockproperties.cpp
 * @short Implementation of TestDockProperties
 */

#include "testdockproperties.h"
#include "dockproperties.h"
#include "dockproperties_p.h"

void TestDockProperties::testDockProperties()
{
    QString fileName ("yrd,scnjdfcdsc");
    QVariantMap disambiguation;
    disambiguation.insert("some_integer", 7654);
    disambiguation.insert("some_string", QString("jjjjlkejfreelkfds,czmak"));
    disambiguation.insert("some_boolean", false);
    QString settingsFileName ("hijoezdezjdcdijpos");
    int width = 67765543;
    int height = -76453;
    bool anchorsTop = true;
    bool anchorsBottom = true;
    bool anchorsLeft = true;
    bool anchorsRight = false;

    Widgets::Docks::DockBaseProperties *dockBase
            = new Widgets::Docks::DockBaseProperties(fileName, disambiguation, settingsFileName,
                                                     width, height,
                                                     anchorsTop, anchorsBottom,
                                                     anchorsLeft, anchorsRight);

    QVariantMap settings;
    settings.insert("some_integer", 32454432);
    settings.insert("some_string", QString("jfrkcezj,clkdsv,dsjc "));
    settings.insert("some_boolean", true);
    Widgets::Docks::DockProperties *component
            = new Widgets::Docks::DockProperties(dockBase, settings);

    QDomDocument document = QDomDocument();

    Widgets::BuildManager<QDomElement> *xmlBuildManager
            = new Widgets::BuildManager<QDomElement>();
    Widgets::Docks::DockPropertiesXmlBuilder *xmlBuilder
            = new Widgets::Docks::DockPropertiesXmlBuilder();
    xmlBuilder->setProperties(component, "test", &document);
    xmlBuildManager->setBuilder(xmlBuilder);
    xmlBuildManager->build();
    QDomElement builtElement = xmlBuildManager->element();

    delete xmlBuildManager;
    delete xmlBuilder;

    Widgets::BuildManager<Widgets::Docks::DockProperties* > *componentBuildManager
            = new Widgets::BuildManager<Widgets::Docks::DockProperties* >();
    Widgets::Docks::DockPropertiesComponentBuilder *componentBuilder
            = new Widgets::Docks::DockPropertiesComponentBuilder();
    componentBuilder->setProperties(builtElement);
    componentBuilder->setDockBaseProperties(dockBase);
    componentBuildManager->setBuilder(componentBuilder);
    componentBuildManager->build();

    Widgets::Docks::DockProperties *builtComponent = componentBuildManager->element();

    delete componentBuildManager;
    delete componentBuilder;

    QCOMPARE(component->fileName(), builtComponent->fileName());
    QCOMPARE(component->disambiguation(), builtComponent->disambiguation());
    QCOMPARE(component->settingsFileName(), builtComponent->settingsFileName());
    QCOMPARE(component->settings(), builtComponent->settings());
    QCOMPARE(component->identifier(), builtComponent->identifier());

    delete component;
    delete builtComponent;

}
