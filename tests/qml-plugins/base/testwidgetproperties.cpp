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
 * @file testwidgetproperties.cpp
 * @short Implementation of TestWidgetProperties
 */

#include "testwidgetproperties.h"
#include "widgetproperties.h"
#include "widgetproperties_p.h"

void TestWidgetProperties::testWidgetProperties()
{
    QString fileName ("doiejdezdjoiezjdoiezdez");
    QVariantHash disambiguation;
    disambiguation.insert("some_integer", 12);
    disambiguation.insert("some_string", QString("dezdzedz"));
    disambiguation.insert("some_boolean", true);
    QString settingsFileName ("jdoiezjdoiezdjoiezdezdezdezdez");
    int minimumWidth = 21321;
    int minimumHeight = -1314;
    int maximumWidth = 443323313;
    int maximumHeight = -321432543;
    Widgets::WidgetBaseProperties *widgetBase
            = new Widgets::WidgetBaseProperties(fileName, disambiguation, settingsFileName,
                                                minimumWidth, minimumHeight,
                                                maximumWidth, maximumHeight);

    int x = 1234;
    int y = 4532;
    int z = 32134;
    int width = 3245353;
    int height = 2354652;
    QVariantHash settings;
    settings.insert("some_integer", 1235435);
    settings.insert("some_string", QString("dvbfggfscsdcds"));
    settings.insert("some_boolean", false);
    Widgets::WidgetProperties *component
            = new Widgets::WidgetProperties(widgetBase, x, y, z, width, height, settings);


    QDomDocument document = QDomDocument();

    Widgets::BuildManager<QDomElement> *xmlBuildManager
            = new Widgets::BuildManager<QDomElement>();
    Widgets::WidgetPropertiesXmlBuilder *xmlBuilder
            = new Widgets::WidgetPropertiesXmlBuilder();
    xmlBuilder->setProperties(component, "test", &document);
    xmlBuildManager->setBuilder(xmlBuilder);
    xmlBuildManager->build();
    QDomElement builtElement = xmlBuildManager->element();

    document.appendChild(builtElement);

    delete xmlBuildManager;
    delete xmlBuilder;

    Widgets::BuildManager<Widgets::WidgetProperties* > *componentBuildManager
            = new Widgets::BuildManager<Widgets::WidgetProperties* >();
    Widgets::WidgetPropertiesComponentBuilder *componentBuilder
            = new Widgets::WidgetPropertiesComponentBuilder();
    componentBuilder->setProperties(builtElement);
    componentBuilder->setWidgetBaseProperties(widgetBase);
    componentBuildManager->setBuilder(componentBuilder);
    componentBuildManager->build();

    Widgets::WidgetProperties *builtComponent = componentBuildManager->element();

    delete componentBuildManager;
    delete componentBuilder;

    QCOMPARE(component->fileName(), builtComponent->fileName());
    QCOMPARE(component->disambiguation(), builtComponent->disambiguation());
    QCOMPARE(component->settingsFileName(), builtComponent->settingsFileName());

    delete component;
    delete builtComponent;
}
